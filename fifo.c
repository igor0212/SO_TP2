#include <stdio.h>
#include "fifo.h"

typedef struct item{                  
  struct item *proximo;       
} Item;     

typedef struct Fila{         
    Item *inicio;  
    Item *fim;  
    int tamanho;       
} Fila;

void leitura_fifo(FILE *arquivo_log)
{
    char * linha = NULL;
    size_t tamanho = 0;
    ssize_t leitura;    
}