import sys
sys.path.append('.')  
from mapagreedy import mapa

def greedy_search(start, goal, graph):
    from heapq import heappop, heappush
    frontier = []
    heappush(frontier, (0, start))
    came_from = {start: None}
    cost_so_far = {start: 0}
    
    while frontier:
        _, current = heappop(frontier)
        
        if current == goal:
            path = []
            while current is not None:
                path.append(current)
                current = came_from[current]
            path.reverse()
            return path
        
        for neighbor, distance in graph[current].items():
            new_cost = cost_so_far[current] + distance
            if neighbor not in cost_so_far or new_cost < cost_so_far[neighbor]:
                cost_so_far[neighbor] = new_cost
                priority = new_cost
                heappush(frontier, (priority, neighbor))
                came_from[neighbor] = current
    return None

print(greedy_search("Marialva", "Assaí", mapa))
print(greedy_search("Bela Vista do Paraíso", "Maringá", mapa))