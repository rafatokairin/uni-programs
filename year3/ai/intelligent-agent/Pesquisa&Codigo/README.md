Análise de Ações com Python
Descrição do Projeto
Este projeto tem como objetivo realizar uma análise de ações da bolsa de valores brasileira utilizando a biblioteca yfinance para obter dados de mercado, pandas para manipulação de dados e matplotlib para gerar visualizações gráficas. O código avalia critérios financeiros como liquidez, dividendos, crescimento de lucros, dívida/patrimônio e outros indicadores financeiros importantes, com o intuito de comparar e gerar gráficos sobre as ações analisadas. O software foi pensado para uso cotiano, ao gerar analises rápidas e visuais das ações do mercado, o usuário será capaz de acompanhar com mais facilidade as quedas e altas das bolsas escolhidas por ele.

Agentes baseados em objetivos
1. Objetivo: O código é programado para atingir o objetivo de selecionar e avaliar ações com base em critérios financeiros predefinidos (liquidez, dividendos, crescimento de lucros, etc.).

2. Busca por Ações: O agente utiliza a biblioteca yfinance para coletar dados financeiros e aplica os critérios de avaliação, que podem ser vistos como uma técnica de busca para encontrar as melhores ações que satisfazem as condições estabelecidas.

3. Não considera eficiência, apenas o objetivo: O foco do código não é a eficiência da busca, mas sim atingir o objetivo de análise, gerando gráficos que mostram a comparação entre as ações.

4. Flexibilidade: O código é flexível, permitindo ajustes nos critérios de avaliação (por exemplo, alterar o peso dado ao Dividend Yield ou ROE) e, assim, adaptar-se a diferentes objetivos do investidor. As decisões sobre quais ações são as melhores são representadas de maneira explícita e podem ser modificadas conforme necessário.

5. Exemplo Prático de Objetivo: Selecionar as melhores ações para compor uma carteira de investimentos diversificada com base em indicadores financeiros, auxiliando investidores ou analistas a encontrar as melhores oportunidades de investimento.

Conteúdo Pesquisado
1. Biblioteca yfinance para Coleta de Dados Financeiros
    yfinance é uma API amplamente usada para acessar dados financeiros de ações e outros ativos. Ela facilita a obtenção de informações históricas e financeiras detalhadas diretamente da Yahoo Finance.
    Funcionalidades incluídas:
    - Obtenção de dados históricos de preços (ex: fechamento diário, volume).
    - Acesso a dados financeiros como dividend yield (DY), crescimento de lucros, dívida/patrimônio, entre outros.
    - Pesquisa de propriedades das ações como capitalização de mercado e retorno sobre patrimônio (ROE).

2. Indicadores Financeiros Utilizados no Código
    O código avalia vários indicadores financeiros, os quais são amplamente utilizados por analistas de investimentos e investidores para determinar a atratividade de uma ação. A seguir estão algumas definições básicas:
    - Dividend Yield (DY): Representa a taxa de retorno de dividendos de uma empresa com relação ao preço da ação.
    - ROE (Return on Equity): Mede a rentabilidade de uma empresa em relação ao patrimônio líquido dos acionistas.
    - Crescimento de Lucros e Receitas (CAGR): Taxa de crescimento anual composta usada para medir a evolução dos lucros e receitas ao longo de um período de 5 anos.
    - Dívida Líquida/Patrimônio: Relaciona o total da dívida da empresa ao patrimônio líquido, indicando o grau de alavancagem.
    - Margem Líquida: Proporção do lucro líquido em relação à receita total, expressa como uma porcentagem.
    - Liquidez Diária: Volume de negociação médio multiplicado pelo preço de fechamento médio, indicando o quanto a ação é negociada no mercado.

3. Avaliação de Critérios para Seleção de Ações
    A lógica de verificar os critérios para cada ação está baseada em práticas comuns de análise fundamentalista, que busca identificar empresas sólidas e com boa saúde financeira para investimentos de longo prazo. Critérios como:
    - Lucro positivo por 10 anos: Indica a consistência da lucratividade.
    - Dívida/Patrimônio menor que 1: Mostra que a empresa tem uma alavancagem controlada.
    - DY maior que 5%: Mostra empresas que pagam dividendos elevados.

4. Visualização Gráfica com matplotlib
    O projeto utiliza a biblioteca matplotlib para gerar gráficos que ilustram a performance histórica das ações e a distribuição da carteira.
    - Gráfico de linhas: Utilizado para mostrar o preço de fechamento diário das ações ao longo do tempo.
    - Gráfico de barras: Usado para ilustrar a valorização ou desvalorização percentual das ações.
    - Gráfico de pizza: Mostra a distribuição percentual das ações em uma carteira com base em seus pontuações.
5. Manipulação de Dados com pandas
    A biblioteca pandas é amplamente utilizada no código para manipulação de grandes volumes de dados financeiros:
    - Leitura e manipulação de DataFrames com dados históricos das ações.
    - Cálculos de métricas financeiras (ex: média de volumes, preços de fechamento, variação percentual).
    - Normalização e comparação de valores para criar uma tabela de critérios por ação.

6. Estratégias de Avaliação de Ações
    O código aplica uma pontuação baseada em critérios financeiros para comparar as ações e atribuir uma importância relativa a cada uma na carteira. Este método de pontuação é uma estratégia de análise de ações chamada stock scoring e é comum em ferramentas de análise de investimento.

7. Gerenciamento de Arquivos com os
    O código utiliza a biblioteca os para criar pastas e salvar os gráficos gerados em arquivos PNG. Essa abordagem é útil para automatizar o armazenamento e organização dos resultados, especialmente em projetos que geram muitas saídas gráficas.

Funcionalidadess
    - Coleta automática de dados históricos de ações via yfinance.
    - Avaliação de ações com base em critérios financeiros como:
        - Dividend Yield (DY)
        - Crescimento de lucro nos últimos 5 anos
        - Dívida líquida/patrimônio
        - Margem líquida, entre outros
    - Geração de gráficos de preço de fechamento das ações.
    - Geração de gráficos de valorização/desvalorização anual das ações.
    - Cálculo de pontuações e distribuição percentual das ações na carteira.
    - Criação de uma tabela visual comparando ações e critérios financeiros.

Pré-requisitos
Para rodar este projeto, é necessário ter Python instalado junto com as seguintes bibliotecas:
    - yfinance
    - pandas
    - matplotlib
    - numpy
Você pode instalar as dependências utilizando o seguinte comando:
    pip install yfinance pandas matplotlib numpy

Estrutura do Projeto
    - obter_dados(acao): Função que busca os dados históricos e informações financeiras da ação especificada.
    - verificar_criterios(dados): Função que verifica se os dados obtidos atendem aos critérios estabelecidos.
    - calcular_pontuacao(dados): Função que atribui uma pontuação para cada ação com base nos critérios financeiros.
    - Geração de gráficos: O código gera três gráficos principais:
    - Preços de fechamento das ações.
    - Gráfico de valorização/desvalorização anual.
    - Gráfico de pizza com a distribuição percentual das ações na carteira.
    - Tabela comparativa de critérios: Uma tabela é gerada comparando o atendimento de critérios para cada ação.

Resultados
    Ao rodar o script, você terá:
    - Um gráfico com o histórico de preços das ações.
    - Um gráfico mostrando a valorização ou desvalorização das ações ao longo do último ano.
    - Um gráfico de pizza mostrando a distribuição percentual das ações com base nos critérios estabelecidos.
    - Uma tabela visual comparando quais critérios são atendidos por cada ação.

Uso
    Uma situação real em que esse código pode ser aplicado no cotidiano é na análise de ações para investidores individuais ou analistas de mercado, que buscam construir uma carteira de investimentos sólida com base em critérios financeiros específicos.
    Por exemplo, um investidor que deseja selecionar ações para sua carteira com base em indicadores financeiros como liquidez, dividend yield (DY), crescimento de lucros e retorno sobre o patrimônio (ROE), pode usar esse código para:
    - Avaliar múltiplas ações automaticamente: O investidor insere os tickers das ações que está interessado em analisar. O código coleta informações relevantes para cada ação, verifica se elas atendem a certos critérios financeiros, e calcula uma pontuação com base nessas informações.
    - Visualizar o desempenho das ações: O código gera gráficos que mostram o preço das ações ao longo de um ano e a valorização ou desvalorização no período. Isso ajuda o investidor a identificar quais ações estão em tendência de alta ou baixa.
    - Tomar decisões de alocação de ativos: Com base na pontuação calculada, o código gera um gráfico de pizza que sugere uma distribuição percentual de cada ação em uma carteira diversificada, facilitando a visualização de como cada ativo poderia ser representado.
    - Identificar oportunidades de investimento: O investidor pode usar os critérios, como crescimento dos lucros e margem líquida, para identificar ações que estão com bons fundamentos e podem ter um bom desempenho no futuro.
    Essa automação permite que o investidor economize tempo na análise de dados e tome decisões mais informadas sobre a composição de sua carteira de ações, facilitando o processo de planejamento financeiro de longo prazo e gestão de risco.