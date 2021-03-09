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

* fifo.c/fifo.h: Contem a função de execução do algoritmo FIFO e a função de exibir os dados da tabela.
* doisa.c/doisa.h Contem a função de execução do algoritmo Segunda Chance a função de exibir os dados da tabela.
* lru.c/lru.h Contem a função de execução do algoritmo LRU e a função de exibir os dados da tabela.
* media.c/media.h Contem a função de execução do algoritmo Media e a função de exibir os dados da tabela.
* estruturas.c/estruturas.h: Contém as estruturas citadas anteriormente.
* main.c: Funcionamento geral do código

#### 3. Implementação

O arquivo principal main.c será responsável por:

* Recuperar as informações de entrada especificada no trabalho: Algoritimo de substituição, arquivo, tamanho de cada página, e tamanho total da memoria.
* Fazer a validação dos dados recuperados.
* Inicializar as estruturas para executar os algoritmos de substituicao de acordo com o que foi solicitado
* Resgatar endereço e operação lida em cada arquivo
* Cria um contador que salva numero maximo de bits que podem ser usados para identificar as paginas(algoritmo foi retirado da espeficação do trabalho).
* Faz o processo de leitura do arquivo fornecido e chama a função de algoritmo de substituição de acordo com o que foi repassado
* Printa a saida dos dados gerais de acordo com a especifição fornecida no trabalho.


Agora, revisando o funcionamento de cada uma dos algoritimos de substituição:

##### 3.1 FIFO

Basicamente equanto o algorirmo le as entradas do endereço e da operação do arquivo e caso ele tenha selecionado o algoritimo FIFO, ele verifica se a página está na fila e se a página criada está na tabela de página ele atualiza os dados da tabela da página acessada como por exemplo o último endereço acessado e se a página está suja ou não.

Caso a página não esteja na fila ele verifica se todos os quadros estão lotados, caso esteja lotado ele segue o sugerido pelo algoritimo removendo o primeiro endereço acessado da lista. e se caso a página não tenha sido criada ele insere a página na fila com seus respectivos dados coletados.

Complexidade apresentada: O(n)

##### 3.2 LRU

Com um processo semelhante as etapas do algoritimo anterior ele inicia verificando se a página está na tabela, logo depois percorre as páginas inseridas na tabela para atualizar o ultimo endereço, se a página está suja e o ultimo acesso daquela página.

Logo depois é verificado se a página está na tabela ou não e caso não esteja analisamos o quadro para verificar se está cheio ou não. Caso esteja lotado ele segue o ajuste seguido pelo algoritimo removendo o ultimo endereço acessado.

Por fim ele registra os dados coletados do arquivo enviado.

Complexidade apresentada O(n2)

##### 3.3 Segunda Chance

Segue com um processo bem semelhante ao funcionamento do algoritimo LRU porém seguindo os ajustes do próprio algoritimo criamos uma veriavel de boolean para utilizar como referência dos bits.

Complexidade apresentada O(n2)

##### 3.4 Media

Segue com um processo bem semelhante ao funcionamento do algoritimo LRU porém para escolher um novo indice a ser selecionado utilizamos a média do total de página que existem e removemos o valor medio desse resultado.

Complexidade apresentada O(n)


#### 3.5 Decisões de Projeto

Como decisões do projeto nosso interpretador não escreve em páginas sujas quando não existe a linha de operação de escrita por exemplo. E no caso da tabela optamos por colocar os seguintes campos:

* Endereço: Ultimo endereço acessado 
* Numero da página lida
* Bit de controle para vericar se a página está suja (SIM) ou (NÃO)

#### Analise dos resultados

