import yfinance as yf
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os
import random
from datetime import datetime
# Estrutura do perfil do empreendedor
class PerfilEmpreendedor:
    def __init__(self):
        self.segmento_nivel_2 = 0
        self.liquidez_diaria = 0
        self.lucro_10_anos = 0
        self.DY = 0
        self.crescimento_lucro = 0
        self.divida_liquida_patrimonio = 0
        self.ROE = 0
        self.CAGR_receitas = 0
        self.CAGR_lucros = 0
        self.margem_liquida = 0
    
    def mostrar_perfil(self):
        print(f"Segmento Nível 2: {self.segmento_nivel_2}")
        print(f"Liquidez Diária: {self.liquidez_diaria}")
        print(f"Lucro 10 Anos: {self.lucro_10_anos}")
        print(f"Dividend Yield (DY): {self.DY}")
        print(f"Crescimento do Lucro: {self.crescimento_lucro}")
        print(f"Dívida/Patrimônio: {self.divida_liquida_patrimonio}")
        print(f"ROE: {self.ROE}")
        print(f"CAGR Receitas: {self.CAGR_receitas}")
        print(f"CAGR Lucros: {self.CAGR_lucros}")
        print(f"Margem Líquida: {self.margem_liquida}")


# Função para criar o nome do arquivo com a data atual
def gerar_nome_arquivo(base_name):
    hoje = datetime.now()
    data_formatada = hoje.strftime("%d-%m")  # Formatar como "dia-mês"
    return f"dados-analisados/{base_name}_{data_formatada}.png"

# Criar pasta "dados-analisados" se não existir
os.makedirs("dados-analisados", exist_ok=True)

def obter_dados(acao):
    stock = yf.Ticker(acao)
    
    # Obter informações históricas
    info = stock.info
    historico = stock.history(period="1y")  # Dados do último ano

    # Verificar se o DataFrame de histórico não está vazio
    if historico.empty:
        raise ValueError(f"O histórico para a ação {acao} está vazio.")
    
    # Exemplo de informações que podemos obter
    segmento_nivel_2 = info.get('marketCap', 0) > 0  # Placeholder para o nível de segmentação
    liquidez_diaria = historico['Volume'].mean() * historico['Close'].mean()  # Simplificação
    lucro_10_anos = info.get('profitMargins', 0) > 0
    DY = info.get('dividendYield', 0) * 100  # Convertendo para porcentagem
    crescimento_lucro = info.get('earningsQuarterlyGrowth', 0) > 0  # Placeholder
    divida_liquida_patrimonio = info.get('debtToEquity', 0)
    ROE = info.get('returnOnEquity', 0) * 100  # Convertendo para porcentagem
    CAGR_receitas = info.get('revenueGrowth', 0) * 100  # Convertendo para porcentagem
    CAGR_lucros = info.get('earningsGrowth', 0) * 100  # Convertendo para porcentagem
    margem_liquida = info.get('profitMargins', 0) * 100  # Convertendo para porcentagem

    return {
        'segmento_nivel_2': segmento_nivel_2,
        'liquidez_diaria': liquidez_diaria,
        'lucro_10_anos': lucro_10_anos,
        'DY': DY,
        'crescimento_lucro': crescimento_lucro,
        'divida_liquida_patrimonio': divida_liquida_patrimonio,
        'ROE': ROE,
        'CAGR_receitas': CAGR_receitas,
        'CAGR_lucros': CAGR_lucros,
        'margem_liquida': margem_liquida,
        'historico': historico
    }

def verificar_criterios(dados):
    criterios = {
        'Segmento nível 2': dados['segmento_nivel_2'],
        'Liquidez ≥ R$5M': dados['liquidez_diaria'] >= 5000000,
        'Lucro 10 anos': dados['lucro_10_anos'],
        'DY ≥ 5%': dados['DY'] >= 5,
        'Crescimento lucro 5 anos': dados['crescimento_lucro'],
        'Dívida/patrimônio > 1': dados['divida_liquida_patrimonio'] > 1,
        'ROE ≥ 10%': dados['ROE'] >= 10,
        'CAGR receitas 5 anos ≥ 10%': dados['CAGR_receitas'] >= 10,
        'CAGR lucros 5 anos ≥ 10%': dados['CAGR_lucros'] >= 10,
        'Margem líquida ≥ 10%': dados['margem_liquida'] >= 10
    }

    return criterios

def calcular_pontuacao(dados):
    pontos = 0

    # Verificação das condições
    criterios = verificar_criterios(dados)
    for criterio, atende in criterios.items():
        if atende:
            pontos += 1

    return pontos

def criar_imagem_criterios_x_acoes(acoes):
    resultados = {}

    for acao in acoes:
        dados = obter_dados(acao)
        criterios = verificar_criterios(dados)
        resultados[acao] = {criterio: 'X' if atende else '' for criterio, atende in criterios.items()}

    criterios = list(next(iter(resultados.values())).keys())
    acoes_list = list(resultados.keys())

    # Preparar os dados para a tabela transposta
    tabela_transposta = []
    tabela_transposta.append(['Critério'] + acoes_list)
    for criterio in criterios:
        linha = [criterio] + [resultados[acao].get(criterio, '') for acao in acoes_list]
        tabela_transposta.append(linha)

    tabela_transposta = np.array(tabela_transposta)
    
    fig, ax = plt.subplots(figsize=(len(acoes) * 2, len(criterios) * 0.8))  # Ajustar tamanho para maior largura
    ax.axis('tight')
    ax.axis('off')

    tabela_table = ax.table(cellText=tabela_transposta, colLabels=None, cellLoc='center', loc='center', colColours=['#f5f5f5'] * len(tabela_transposta[0]))
    tabela_table.auto_set_font_size(False)
    tabela_table.set_fontsize(8)  # Ajustar o tamanho da fonte
    tabela_table.scale(1.2, 1.2)  # Ajustar a escala da tabela para melhorar a visualização

    plt.title('Critérios vs Ações')
    plt.savefig(gerar_nome_arquivo('criterios_vs_acoes_transposta'), bbox_inches='tight')  # Adicionar bbox_inches='tight' para ajustar o layout
    plt.close()

# Função para simular o investimento
def simular_investimento(perfil, dados_acao):
    print("\nInvestindo na ação...")
    
    # Atualizar o perfil do empreendedor somando os critérios da ação selecionada
    perfil.segmento_nivel_2 += 1 if dados_acao['segmento_nivel_2'] else 0
    perfil.liquidez_diaria += 1 if dados_acao['liquidez_diaria'] >= 5000000 else 0
    perfil.lucro_10_anos += 1 if dados_acao['lucro_10_anos'] else 0
    perfil.DY += 1 if dados_acao['DY'] >= 5 else 0
    perfil.crescimento_lucro += 1 if dados_acao['crescimento_lucro'] else 0
    perfil.divida_liquida_patrimonio += 1 if dados_acao['divida_liquida_patrimonio'] > 1 else 0
    perfil.ROE += 1 if dados_acao['ROE'] >= 10 else 0
    perfil.CAGR_receitas += 1 if dados_acao['CAGR_receitas'] >= 10 else 0
    perfil.CAGR_lucros += 1 if dados_acao['CAGR_lucros'] >= 10 else 0
    perfil.margem_liquida += 1 if dados_acao['margem_liquida'] >= 10 else 0

def calcular_diferenca(perfil, dados_acao):
    # Função que calcula a diferença absoluta entre o perfil e os dados de uma ação
    diferenca = 0
    diferenca += abs(perfil.segmento_nivel_2 - (1 if dados_acao['segmento_nivel_2'] else 0))
    diferenca += abs(perfil.liquidez_diaria - (1 if dados_acao['liquidez_diaria'] >= 5000000 else 0))
    diferenca += abs(perfil.lucro_10_anos - (1 if dados_acao['lucro_10_anos'] else 0))
    diferenca += abs(perfil.DY - (1 if dados_acao['DY'] >= 5 else 0))
    diferenca += abs(perfil.crescimento_lucro - (1 if dados_acao['crescimento_lucro'] else 0))
    diferenca += abs(perfil.divida_liquida_patrimonio - (1 if dados_acao['divida_liquida_patrimonio'] > 1 else 0))
    diferenca += abs(perfil.ROE - (1 if dados_acao['ROE'] >= 10 else 0))
    diferenca += abs(perfil.CAGR_receitas - (1 if dados_acao['CAGR_receitas'] >= 10 else 0))
    diferenca += abs(perfil.CAGR_lucros - (1 if dados_acao['CAGR_lucros'] >= 10 else 0))
    diferenca += abs(perfil.margem_liquida - (1 if dados_acao['margem_liquida'] >= 10 else 0))
    return diferenca

def melhores_opcoes(perfil, acoes):
    # Lista para armazenar as diferenças entre o perfil e cada ação
    opcoes = []
    
    # Iterar sobre cada ação, calcular a diferença e armazenar na lista
    for acao in acoes:
        dados_acao = obter_dados(acao)  # Obter os dados de cada ação
        diferenca = calcular_diferenca(perfil, dados_acao)
        opcoes.append((acao, diferenca))
    
    # Ordenar a lista de ações com base na diferença (quanto menor, melhor)
    opcoes.sort(key=lambda x: x[1])
    
    # Retornar as 3 melhores opções (menores diferenças)
    return opcoes[:3]

# Função que utiliza aprendizado por reforço para decidir qual ação investir
# Função que utiliza aprendizado por reforço com decaimento de epsilon
def aprendizado_por_reforco(perfil, acoes, episodos=1000, epsilon_decay=0.995):
    q_table = {acao: 0 for acao in acoes}
    alpha = 0.1  # Taxa de aprendizado
    gamma = 0.9  # Fator de desconto
    epsilon = 1.0  # Valor inicial de epsilon (para exploração)
    vetor = [-1,0,1]
    sentimento = random.choice(vetor)
    print(f"O sentimento simulado do mercado é de {sentimento}")

    for episodio in range(episodos):
        # Escolher ação: exploração vs. exploração
        if random.uniform(0, 1) < epsilon:
            acao_escolhida = random.choice(acoes)  # Explorar: escolher ação aleatória
        else:
            acao_escolhida = max(q_table, key=q_table.get)  # Explorar: escolher melhor ação conhecida

        # Obter os dados da ação escolhida
        dados_acao = obter_dados(acao_escolhida)

        # Calcular a recompensa: baseada na compatibilidade do perfil
        recompensa = calcular_pontuacao(dados_acao) + sentimento

        # Atualizar valor na tabela Q
        q_atual = q_table[acao_escolhida]
        q_table[acao_escolhida] = (1 - alpha) * q_atual + alpha * (recompensa + gamma * max(q_table.values()))

        # Reduzir o valor de epsilon para diminuir a exploração ao longo do tempo
        epsilon = max(0.01, epsilon * epsilon_decay)

    # Ordenar ações pelo valor Q (decisão final)
    melhor_acao = max(q_table, key=q_table.get)
    print(f"A melhor ação após {episodos} episódios é: {melhor_acao}")

    return melhor_acao

acoes = ['PETR4.SA', 'ITUB4.SA', 'VALE3.SA', 'WEGE3.SA', 'ABEV3.SA', 'BBAS3.SA', 'BPAC11.SA']
pontuacoes = {}
percentuais = {}

# Criar gráficos de preços das ações
num_acoes = len(acoes)
num_linhas = int(np.ceil(num_acoes / 3))  # Define o número de linhas necessário
num_colunas = min(3, num_acoes)  # Máximo de 3 colunas

plt.figure(figsize=(16, num_linhas * 4))

for i, acao in enumerate(acoes):
    dados = obter_dados(acao)
    print(f"\nAnalisando a ação: {acao}")
    criterios = verificar_criterios(dados)  # Obter critérios e resultados
    pontos = calcular_pontuacao(dados)
    pontuacoes[acao] = pontos

    # Gráfico de preços das ações
    plt.subplot(num_linhas, num_colunas, i + 1)
    historico = dados['historico']
    historico['Close'].plot(title=f'Preço das Ações - {acao}', xlabel='Data', ylabel='Preço de Fechamento')

# Ajustar o layout dos gráficos de preços das ações
plt.tight_layout()
plt.savefig(gerar_nome_arquivo('precos_acoes'))
plt.close()

# Gráficos de valorização/desvalorização
plt.figure(figsize=(8, 6))
for acao in acoes:
    dados = obter_dados(acao)
    historico = dados['historico']
    if not historico.empty:
        preco_inicial = historico['Close'].iloc[0]
        preco_final = historico['Close'].iloc[-1]
        variacao_percentual = ((preco_final - preco_inicial) / preco_inicial) * 100

        # Adicionando gráfico de valorização/desvalorização
        plt.bar(acao, variacao_percentual, color='green' if variacao_percentual >= 0 else 'red')

plt.title('Valorização/Desvalorização Anual')
plt.ylabel('Valorização/Desvalorização (%)')
plt.axhline(0, color='black', linewidth=0.8)
plt.savefig(gerar_nome_arquivo('valorizacao_desvalorizacao'))
plt.close()

# Normalizar as pontuações para calcular a porcentagem
total_pontos = sum(pontuacoes.values())
if total_pontos > 0:
    percentuais = {acao: (pontuacao / total_pontos) * 100 for acao, pontuacao in pontuacoes.items()}
else:
    percentuais = {acao: 0 for acao in acoes}

# Criando gráfico de pizza para percentual da carteira
plt.figure(figsize=(8, 8))
plt.pie(percentuais.values(), labels=percentuais.keys(), autopct='%1.1f%%', startangle=140)
plt.title('Distribuição Percentual da Carteira')
plt.savefig(gerar_nome_arquivo('percentual_carteira'))
plt.close()

criar_imagem_criterios_x_acoes(acoes)

# Exemplo de como usar o perfil e a função de investimento
perfil_investidor = PerfilEmpreendedor()  # Perfil do investidor com critérios já atualizados
# acoes = ['PETR4.SA', 'ITUB4.SA', 'VALE3.SA', 'WEGE3.SA', 'ABEV3.SA', 'BBAS3.SA', 'BPAC11.SA']
# Simular investimentos para atualizar o perfil (opcional)
dados_acao_escolhida = obter_dados('PETR4.SA')  # Exemplo de investimento
simular_investimento(perfil_investidor, dados_acao_escolhida)
dados_acao_escolhida = obter_dados('ITUB4.SA')  # Exemplo de investimento
simular_investimento(perfil_investidor, dados_acao_escolhida)
dados_acao_escolhida = obter_dados('VALE3.SA')  # Exemplo de investimento
simular_investimento(perfil_investidor, dados_acao_escolhida)
dados_acao_escolhida = obter_dados('WEGE3.SA')  # Exemplo de investimento
simular_investimento(perfil_investidor, dados_acao_escolhida)
dados_acao_escolhida = obter_dados('ABEV3.SA')  # Exemplo de investimento
simular_investimento(perfil_investidor, dados_acao_escolhida)
dados_acao_escolhida = obter_dados('BBAS3.SA')  # Exemplo de investimento
simular_investimento(perfil_investidor, dados_acao_escolhida)
dados_acao_escolhida = obter_dados('BPAC11.SA')  # Exemplo de investimento
simular_investimento(perfil_investidor, dados_acao_escolhida)
# Agora, encontrar as 3 melhores opções de ação para o investidor
perfil_investidor.mostrar_perfil()

# Usar o aprendizado por reforço para escolher uma ação e investir
melhor_acao = aprendizado_por_reforco(perfil_investidor, acoes, episodos=1000)
dados_acao_escolhida = obter_dados(melhor_acao) 
simular_investimento(perfil_investidor,dados_acao_escolhida)

perfil_investidor.mostrar_perfil()