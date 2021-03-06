#include <stdio.h>
#include "fifo.h"
#include "estruturas.h"

typedef struct item{     
  Pagina pagina;                      
  struct item *proximo;       
} Item;     

typedef struct Fila{         
    Item *inicio;  
    Item *fim;  
    int tamanho;       
} Fila;

void leitura_fifo(FILE *arquivo_log, int tamanho_pagina)
{

    int tamanho_pagina_bytes = tamanho_pagina * pow(2, 10);

    unsigned numero_maximo_bits, temporario;
    temporario = tamanho_pagina_bytes;
    numero_maximo_bits = 0;

    while (temporario > 1) {
      temporario = temporario >> 1;
      numero_maximo_bits++;
    }

    numero_maximo_bits = 32u - numero_maximo_bits;

    char * linha = NULL;
    size_t tamanho = 0;
    ssize_t leitura;   
    unsigned int endereco;
    char operacao;

    Fila *fila; 

    if ((fila = (Fila *) malloc(sizeof(Fila))) == NULL)      
    {
      printf("Error: Fila do algoritmo Fifo não criada.\n");
      exit();
    }

    fila->inicio = NULL;         
    fila->fim = NULL;         
    fila->tamanho = 0; 

    while(fscanf(arquivo_log,"%x %c\n", &endereco, &operacao) != EOF){

      unsigned int numero_pagina_atual = endereco >> numero_maximo_bits;

      Item* item;
      item = fila->inicio;
      int pagina_fila = 0;

       while(item != NULL){

          if(item->pagina.numero == numero_pagina_atual){

          }

       }

    }


  
}