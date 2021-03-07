#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Pagina
{
    int quadro;
    unsigned int numero;
    unsigned int ultimo_endereco_acessado;
    int ultimo_acesso;
    int suja;
} Pagina;

typedef struct Tabela
{
    unsigned int num_entradas;
    Pagina *paginas;
} Tabela;

typedef struct Quadro
{
    unsigned int ultimo_acesso; 
    unsigned int _carregamento; 
    int esta_na_memoria;
} Quadro;

typedef struct StructItem
{         
    Pagina pagina;         
    struct StructItem *proximo;       
} Item;

typedef struct Fila
{         
    int tamanho;       
    Item *inicio; 
    Item *fim;     
} Fila;

int inserir(Fila * sequencia, Item * atual, Pagina pagina);