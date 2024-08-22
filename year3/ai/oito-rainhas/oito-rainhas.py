import numpy as np
import random

class NQueensGA:
    def __init__(self, n, population_size=100, generations=1000, mutation_rate=0.01):
        self.n = n  # Número de rainhas e dimensões do tabuleiro
        self.population_size = population_size  # Tamanho da população
        self.generations = generations  # Número de gerações
        self.mutation_rate = mutation_rate  # Taxa de mutação
        self.population = self.initialize_population()  # Inicialização da população

    # Representação da População Inicial: gera uma população inicial de soluções aleatórias
    def initialize_population(self):
        return [self.random_solution() for _ in range(self.population_size)]

    # Gera uma solução aleatória: uma permutação dos números de 0 a n-1 representando as posições das rainhas
    def random_solution(self):
        return list(np.random.permutation(self.n))

    # Função Fitness: avalia a qualidade da solução com base no número de conflitos entre rainhas
    def fitness(self, solution):
        conflicts = 0
        for i in range(self.n):
            for j in range(i + 1, self.n):
                if (solution[i] == solution[j] or
                    abs(solution[i] - solution[j]) == abs(i - j)):
                    conflicts += 1
        # A função de fitness é inversamente proporcional ao número de conflitos
        return 1 / (conflicts + 1)

    # Seleção: seleciona os dois melhores pais da população com base na função de fitness
    def select(self):
        sorted_population = sorted(self.population, key=lambda x: self.fitness(x), reverse=True)
        return sorted_population[:2]

    # Cruzamento (crossover): cria dois novos cromossomos (filhos) a partir de dois pais
    def crossover(self, parent1, parent2):
        point = random.randint(1, self.n - 1)  # Define um ponto de cruzamento aleatório
        # Gera dois filhos combinando partes dos pais
        child1 = parent1[:point] + [x for x in parent2 if x not in parent1[:point]]
        child2 = parent2[:point] + [x for x in parent1 if x not in parent2[:point]]
        return child1, child2

    # Mutação: altera aleatoriamente a posição de duas rainhas na solução com uma probabilidade definida
    def mutate(self, solution):
        if random.random() < self.mutation_rate:
            i, j = random.sample(range(self.n), 2)  # Escolhe dois índices aleatórios
            solution[i], solution[j] = solution[j], solution[i]  # Troca as posições das rainhas

    # Executa o algoritmo genético
    def run(self):
        for generation in range(self.generations):
            new_population = []
            # Cria uma nova população a partir dos pais selecionados
            for _ in range(self.population_size // 2):
                parent1, parent2 = self.select()  # Seleciona os pais
                child1, child2 = self.crossover(parent1, parent2)  # Aplica o crossover
                self.mutate(child1)  # Aplica a mutação nos filhos
                self.mutate(child2)
                new_population.extend([child1, child2])  # Adiciona os filhos à nova população
            self.population = new_population  # Atualiza a população
            best_solution = max(self.population, key=lambda x: self.fitness(x))  # Encontra a melhor solução da população atual
            print(f"Generation {generation}: Best Fitness = {self.fitness(best_solution)}")

        best_solution = max(self.population, key=lambda x: self.fitness(x))  # Encontra a melhor solução final
        print(f"Best solution: {best_solution}")
        print(f"Fitness: {self.fitness(best_solution)}")

if __name__ == "__main__":
    n = 8  # Número de rainhas (pode ser ajustado)
    ga = NQueensGA(n)
    ga.run()