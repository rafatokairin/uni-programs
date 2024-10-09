from servidorUDP import start_udp_server
from clienteUDP import start_udp_client
from servidorTCP import start_tcp_server
from clienteTCP import start_tcp_client
import socket

def get_local_ip():
    # Conecta a um endereço externo para determinar o IP local, sem enviar dados reais
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        # O endereço de destino e a porta não importam
        s.connect(("8.8.8.8", 80))
        ip = s.getsockname()[0]
    except Exception as e:
        ip = "127.0.0.1"
    finally:
        s.close()
    return ip

if __name__ == "__main__":
    while 1:
        tipo = int(input("UDP[0]\nTCP[1]\n->"))
        if tipo == 0: break
        elif tipo == 1: break
        print("Invalid input!")

    while 1:
        formato = int(input("server[0]\nclient[1]\n->"))
        if formato == 0: break
        elif formato == 1: break
        print("Invalid input!")

    if formato == 0: print("local ip : "+ get_local_ip())
    if formato == 1 : 
        ipServer = input("ip server: ")
    
    #=========== UDP ==============
    if tipo == 0 :
        # ============= CLIENT =============
        if formato == 1: start_udp_client(ipServer)
        # ============== SERVER ===========
        else: start_udp_server()

    # =============== TCP =============
    if tipo == 1 :
        # ============== CLIENT =============
        if formato == 1: start_tcp_client(ipServer)
        # =============== SERVER ===========
        else: start_tcp_server()