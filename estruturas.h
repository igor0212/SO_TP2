#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#pragma once
///////////////////////////////////////////////////////////////
//                         tabela                           //
/////////////////////////////////////////////////////////////

typedef struct Pagina{
    int quadro;//indice do array de quadros que corresponde a esta pagina.
    unsigned int numero;//numero da pagina, de acordo com os bits extraidos de um endereco do .log
    unsigned int ultimo_endereco_acessado;//contem o ultimo endereco acessado desta pagina
    int ultimo_acesso;//indica o instante do ultimo acesso a essa pagina
    int suja;//indica se a pagina esta suja ou nao
    int segunda_chance;//indica se a pagina tem mais uma chance de ficar na tabela(apenas para o algoritmo "second chance")
} Pagina;

//esta tabela nao sera usada para o fifo ou para o lru
typedef struct tabela{
    unsigned int num_entradas;
    Pagina *paginas;
} tabela;

typedef struct quadro{
    unsigned int ultimo_acesso; //Os clocks podem ser considerados como a colocação da intrução lida
    unsigned int _carregamento; //O instante de carregamento para a memória
    int esta_na_memoria;//indica se o quadro esta na memoria ou nao
} quadro;

typedef struct StructItem{         
    Pagina pagina;         
    struct StructItem *seguinte;       
} Item;

typedef struct Fila{         
     int tamanho;       
    Item *inicio; 
    Item *fim;     
} Fila;


void inicializacao (Fila * sequencia);

int inserir (Fila * sequencia, Item * atual, Pagina page);

void exibir (Fila *sequencia);