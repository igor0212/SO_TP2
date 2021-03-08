#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#pragma once

typedef struct Pagina
{
    int identificador;
    unsigned int numero;
    unsigned int endereco;
    int ultimo_acesso;
    bool bit_controle;    
} Pagina;

typedef struct Tabela{    
    Pagina *paginas;
} Tabela;

typedef struct Quadro
{
    unsigned int ultimo_acesso;
    unsigned int _carregamento;
    bool esta_na_memoria;
} Quadro;

typedef struct StructItem
{         
    Pagina pagina;         
    struct StructItem *proximo;       
} Item;

typedef struct Fila
{         
    Item *inicio;  
    Item *fim;  
    int tamanho;       
} Fila;

void adicionarItemFila(Fila *fila, Item *item, Pagina pagina);