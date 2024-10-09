import socket
import time

PORT = 65432            

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
    base_string = "teste de rede *2024*"
    repeated_string = (base_string * (500 // len(base_string)))[:500]
    return repeated_string.encode('utf-8')  # Converter para bytes

def start_tcp_client(HOST):
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((HOST, PORT))
            print(f"Started a TCP client -> host/port: {HOST}:{PORT}")

            # FASE 1: Enviar múltiplos pacotes de 500 bytes por 20 segundos 
            data_to_send = generate_test_string() 
            packet_size = 500
            total_bytes_sent = 0
            packet_count = 0
            start_time = time.time()

            # Limitar o upload a 20 segundos
            while time.time() - start_time < 20:
                s.sendall(data_to_send)
                total_bytes_sent += packet_size
                packet_count += 1
            end_time = time.time()

            upload_time = end_time - start_time
            print(f"Tempo de upload: {upload_time} segundos")
            if upload_time == 0:
                upload_time = 1e-9  # Prevenir divisão por zero

            upload_bps = (total_bytes_sent * 8) / upload_time
            upload_pps = packet_count / upload_time
            print(f"Taxa de Upload:\n{format_all_speeds(upload_bps)}")
            print(f"Pacotes por segundo: {upload_pps:,.2f}")
            print(f"Pacotes enviados: {packet_count:,}")
            print(f"Bytes enviados: {total_bytes_sent:,} bytes\n")

            # Enviar mensagem indicando término e número de pacotes enviados
            s.sendall(f"UPLOAD_COMPLETE,{packet_count}".encode('utf-8'))
    except socket.timeout:
        print("Rede instável.")
    except Exception as ex:
        print(f"Ocorreu um erro: {ex}")
