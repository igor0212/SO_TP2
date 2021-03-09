#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#pragma once

typedef struct Pagina
{
    int id;
    unsigned int numero;
    unsigned int endereco_acessado;
    int ultimo_acesso;
    bool bit_controle;    
} Pagina;

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

typedef struct Tabela
{    
    Pagina *paginas;
} Tabela;

typedef struct Quadro
{
    unsigned int ultimo_acesso;    
    bool esta_na_memoria;
} Quadro;

void adicionarItemFila(Fila *fila, Item *item, Pagina pagina);