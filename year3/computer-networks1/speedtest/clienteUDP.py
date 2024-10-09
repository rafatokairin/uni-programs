import socket
import time

# Configurações do cliente
PORT = 12345            # Porta do servidor
TIMEOUT = 10

def format_all_speeds(bps):
    gbps = bps / 10**9
    mbps = bps / 10**6
    kbps = bps / 10**3
    return (
        f"{gbps:,.2f} Gbps\n"
        f"{mbps:,.2f} Mbps\n"
        f"{kbps:,.2f} Kbps\n"
        f"{bps:,.2f} bps"
    )

def generate_test_string():
    # Gerar string de 500 bytes contendo "teste de rede *2024*"
    base_string = "teste de rede *2024*"
    repeated_string = (base_string * (500 // len(base_string)))[:500]
    return repeated_string.encode('utf-8')  # Converter para bytes

def start_udp_client(HOST):
    packet_size = 500  # Tamanho de cada pacote enviado
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        s.settimeout(TIMEOUT)  # Definir o timeout do socket UDP
        server_addr = (HOST, PORT)
        print(f"Started a UDP client -> host/port: {HOST}:{PORT}")

        # FASE 1: Enviar múltiplos pacotes de 500 bytes por 20 segundos
        data_to_send = generate_test_string()  # Gera dados para enviar (500 bytes)
        total_bytes_sent = 0
        packet_count = 0
        start_time = time.time()

        try:
            # Limitar o upload a 20 segundos
            while time.time() - start_time < 20:
                try:
                    s.sendto(data_to_send, server_addr)
                    total_bytes_sent += packet_size
                    packet_count += 1
                    # print(f"Enviado pacote {packet_count}, total enviado: {total_bytes_sent} bytes")
                except socket.timeout:
                    print(f"Timeout atingido ao enviar pacote {packet_count}")
                    break  # Interrompe o loop se o timeout for atingido
                except socket.error as e:
                    print(f"Erro de socket ao enviar pacote {packet_count}: {e}")
                    break

            end_time = time.time()
            upload_time = end_time - start_time

            if upload_time == 0:
                upload_time = 1e-9  # Prevenir divisão por zero

            upload_bps = (total_bytes_sent * 8) / upload_time  # bits por segundo
            upload_pps = packet_count / upload_time
            print(f"Tempo de upload: {upload_time} segundos")
            print(f"Taxa de Upload:\n{format_all_speeds(upload_bps)}")
            print(f"Pacotes por segundo: {upload_pps:,.2f}")
            print(f"Pacotes enviados: {packet_count:,}")
            print(f"Bytes enviados: {total_bytes_sent:,} bytes\n")

            # FASE 2: Enviar mensagem de término para o servidor
            try:
                s.sendto(b'UPLOAD_COMPLETE', server_addr)
            except socket.error as e:
                print(f"Erro ao enviar 'UPLOAD_COMPLETE': {e}")

        except Exception as e:
            print(f"Ocorreu um erro inesperado: {e}")
        finally:
            print("Cliente UDP encerrado.")