from collections import deque
import importlib.util

def bfs(cidade_origem, cidade_destino, nome_arquivo):
    # Carrega mapa
    spec = importlib.util.spec_from_file_location("mapa", nome_arquivo)
    mapa_module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mapa_module)
    mapa = mapa_module.mapa
    
    if cidade_origem == cidade_destino:
        return [cidade_origem]
    # Fila para BFS
    fila = deque([[cidade_origem]])
    visitados = set([cidade_origem])
    while fila:
        caminho = fila.popleft()
        cidade_atual = caminho[-1]
        
        for vizinho in mapa.get(cidade_atual, []):
            if vizinho not in visitados:
                novo_caminho = caminho + [vizinho]
                if vizinho == cidade_destino:
                    return novo_caminho
                else:
                    fila.append(novo_caminho)
                    visitados.add(vizinho)
    return None

print(bfs("Maringá", "Uraí", "mapabfs.py"))  # Caminho Maringá para Uraí
print(bfs("Guaravera", "Santa Fé", "mapabfs.py"))  # Caminho Guaravera para Santa Fé
print(bfs("Astorga", "Jandaia do Sul", "mapabfs.py"))  # Caminho Astorga para Jandaia do Sul