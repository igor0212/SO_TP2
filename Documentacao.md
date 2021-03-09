---
title: "Documentação SO"
output: "pdf_document"
---

## <center> Universidade Federal de Minas Gerais </center>

###### <center> Vitor Ribeiro dos Santos - 2017023676
###### <center> Igor Oliveira Valente da Silveira 

<br><br><br><br><br><br><br>

#### 1. Introdução 

O objetivo desse trabalho é a implementação dos algoritmos de subtituição simulando uma memória virtual. A idéia desse simulador é a comparação entre os diferentes tipos de algoritmos a fim de identificar os resultados e obter respostas significativas entre esses algoritmos e seu funcionamento em uma mémoria virtual.

#### 2. Estruturas e Organização


Para implementação do projeto utilizamos um conjunto de estruturas para armazenar e facilitar os dados coletados dos arquivos de log recebidos pelo programa. 

Os dados contidos e cada estrutura, são, respectivamente:

* Pagina: O indice de quadros ligados à página, numero da página, ultimo endereço que foi acessado, se a mesma está suja ou não.

* Tabela: Na tabela temos o número de entradas e a estrutura de páginas.

* Quadro: Armazenamos o último acesso, o momento de carregamento para a memória e informação se o quadro está sendo utilizado ou não.

###### O próximos elementos são utilizados exclusivamente para a implementação do FIFO

* StructItem: Armazena a página e um ponteiro para o próximo item

* Lista: Guarda o tamanho e ponteiros para inicio e o fim da lista.


Também vinculado a essas estruturas temos a função inserir e remover para manipulação da lista.

###### Divisão dos arquivos

Optamos por dividir os algoritimos de substituição em diferentes arquivos a fim de obter um código
mais claro e de fácil entendimento. No código será encontrado os arquivos:

* fifo.c/fifo.h: Contem a função de execução do algoritmo e a função de exibir os dados da tabela.
* doisa.c/doisa.h Contem a função de execução do algoritmo e a função de exibir os dados da tabela.
* lru.c/lru.h Contem a função de execução do algoritmo e a função de exibir os dados da tabela.
* estruturas.c/estruturas.h: Contém as estruturas citadas anteriormente.
* main.c: Funcionamento de todo o sistema

#### 3. Implementação

O arquivo principal main.c será responsável por:

* Recuperar as informações de entrada especificada no trabalho: Algoritimo de substituição, arquivo, tamanho de cada página, e tamanho total da memoria.
* Fazer a validação dos dados recuperados.
* Inicializar as estruturas para executar os algoritmos de substituicao de acordo com o que foi solicitado
* Resgatar endereço e operação lida em cada arquivo
* Cria um contador que salva numero maximo de bits que podem ser usados para identificar as paginas(algoritmo foi retirado da espeficação do trabalho).
* Faz o processo de leitura do arquivo fornecido e chama a função de algoritmo de substituição de acordo com o que foi repassado
* Printa a saida dos dados gerais de acordo com a especifição fornecida no trabalho.


