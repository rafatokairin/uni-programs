import socket
import time

# Configurações do servidor
HOST = '0.0.0.0'  # Endereço IP do servidor
PORT = 12345      # Porta do servidor
TIMEOUT = 10      # Timeout de 25 segundos

pacotes_recebidos = 0

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

def handle_client(server_socket, client_addr):
    global pacotes_recebidos
    print(f"Connected to {client_addr}\n")

    # Configura o timeout para 25 segundos
    server_socket.settimeout(TIMEOUT)

    # FASE 1: Receber dados do cliente (Upload)
    start_time = time.time()
    data_received = 0
    packet_count = 0

    try:
        while True:
            try:
                data, addr = server_socket.recvfrom(500)  # Recebe 500 bytes por vez
                if b'UPLOAD_COMPLETE' in data:
                    print("Fim da Fase 1")
                    break
                if not data:
                    print("Nenhum dado recebido, encerrando")
                    break
                data_received += len(data)
                packet_count += 1
            except socket.timeout:
                print(f"Timeout de {TIMEOUT} segundos atingido sem receber dados. Encerrando conexão.")
                break # Retorna False em caso de erro de timeout
    except Exception as e:
        print(f"Erro durante a comunicação: {e}")
        return False  # Retorna False em caso de qualquer outro erro

    end_time = time.time()

    upload_time = end_time - start_time
    upload_bps = (data_received * 8) / upload_time if upload_time > 0 else 0
    upload_pps = packet_count / upload_time if upload_time > 0 else 0
    print(f"Tempo de download: {upload_time} segundos")
    print(f"Taxa de download: {format_all_speeds(upload_bps)}")
    print(f"Pacotes por segundo: {upload_pps:,.2f}")
    print(f"Pacotes recebidos: {packet_count:,}")
    print(f"Bytes recebidos: {data_received:,} bytes\n")
    pacotes_recebidos = packet_count
    return True  # Retorna True se tudo ocorreu bem

def start_udp_server():
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as server_socket:
        server_socket.bind((HOST, PORT))
        print(f"Started an UDP server -> port: {PORT}...")

        while True:
            try:
                # Espera qualquer dado para iniciar a conexão com o cliente
                data, client_addr = server_socket.recvfrom(500)
                print(f"New connection from {client_addr}")
                if handle_client(server_socket, client_addr):
                    # Somente solicita pacotes enviados se a função handle_client for bem-sucedida
                    pacotes_enviados = int(input("Pacotes enviados: "))
                    print("Pacotes perdidos = " + str(pacotes_enviados - pacotes_recebidos))
                else:
                    print("Erro na comunicação com o cliente, pacotes enviados não solicitados.")
                break
            except socket.timeout:
                print(f"Timeout de {TIMEOUT} segundos atingido sem receber conexão.")
                continue  # Continua esperando por novas conexões