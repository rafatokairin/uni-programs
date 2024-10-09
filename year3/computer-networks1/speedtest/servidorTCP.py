import socket
import time

HOST = '0.0.0.0'
PORT = 65432
TIMEOUT = 10  # Timeout de 25 segundos

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

def handle_client(conn):
    global pacotes_recebidos
    try:
        with conn:
            print(f"Connected to {conn.getpeername()}\n")

            start_time = time.time()
            data_received = 0  # Total de bytes recebidos
            conn.settimeout(TIMEOUT)  # Define o timeout para 25 segundos

            while True:
                try:
                    data = conn.recv(500)
                    
                    if b'UPLOAD_COMPLETE' in data:
                        # Extrai o número de pacotes enviados do cliente
                        info = data.decode('utf-8').split(',')
                        pacotes_enviados = int(info[1])
                        data = data.replace(f"UPLOAD_COMPLETE,{pacotes_enviados}".encode('utf-8'), b'')  # Remove o pacote de término
                        if len(data) == 0:
                            break
                    
                    if len(data) == 0:
                        break

                    # Contar o total de bytes recebidos
                    data_received += len(data)

                except socket.timeout:
                    print(f"Timeout de {TIMEOUT} segundos atingido sem receber dados. Encerrando conexão.")
                    return False  # Timeout aconteceu

            end_time = time.time()

            upload_time = end_time - start_time
            upload_bps = (data_received * 8) / upload_time if upload_time > 0 else 0

            # Calcular o número de pacotes baseando-se nos bytes recebidos
            packet_count = data_received // 500  # 1 pacote == 500 bytes
            if data_received % 500 != 0:
                packet_count += 1  # Contabilizar um pacote adicional se houver bytes restantes

            upload_pps = packet_count / upload_time if upload_time > 0 else 0

            print(f"Tempo de download: {upload_time} segundos")
            print(f"Taxa de Download: {format_all_speeds(upload_bps)}")
            print(f"Pacotes por segundo: {upload_pps:,.2f}")
            print(f"Pacotes recebidos: {packet_count:,}")
            print(f"Bytes recebidos: {data_received:,} bytes\n")

            pacotes_recebidos = packet_count
            print(f"Pacotes perdidos = {pacotes_enviados - pacotes_recebidos}")
            return True  # Operação bem-sucedida

    except Exception as e:
        print(f"Erro na conexão com o cliente: {e}")
        return False  # Qualquer outro erro

def start_tcp_server():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen()
        print(f"Started a TCP server -> port:{PORT}...")

        while True:
            try:
                conn, addr = s.accept()
                print(f"New connection from {addr}")

                # Se a comunicação for bem-sucedida
                handle_client(conn)
                
                break  # Encerra o loop após lidar com um cliente

            except socket.timeout:
                print(f"Timeout de {TIMEOUT} segundos atingido sem receber conexão.")
                continue  # Continua esperando novas conexões
