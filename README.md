# AlgoritmosOrdenacao
O executavel "projeto.bat" é o responsavel por integrar a tabela de dados gerada pelo algoritmo em C, a criação do gráfico com gnuplot e inserção do grafico no documento Latex com saída em pdf.

projeto.cpp imprime uma tabela com as colunas
n || tempo_qsort || desvio_qsort || tempo_counting || desvio_counting || tempo_selection || desvio_selection

grafico.gp desenha o gráfico com os valores de n=min no eixo x e os demais valores são determinados pelos parâmetros de entrada ARG1 e ARG2, que são: testar selection sort e usar vetores ordenados, respectivamente.

projeto.bat executa projeto.exe, e cria um arquivo texto output.txt para gravação da tabela gerada por projeto.cpp. Os parâmetros projeto.exe são requeridos do usuário drante execução. Depois esse algoritmo gera um gráfico chamando grafico.gp com os parâmetros ARG1 e ARG2. Após a geração do gráfico, o programa insere em projeto.tex e cria um pdf projeto.pdf.
