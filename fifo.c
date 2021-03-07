#include <stdio.h>
#include "fifo.h"
#include "estruturas.h"

int i;

Fila* fifo_execucao(int tamanho_tabela, int numero_pagina_acessada, unsigned int endereco, char operacao)
{
    Fila *fila;

    if ((fila = (Fila *) malloc(sizeof(Fila))) == NULL)           
    {
        printf("Erro: Fila fifo não criada\n");
        exit(1);
    }
    
    Item* item;
    item = fila->inicio;
    int pagina_esta_na_fila = 0;

    while(item != NULL){      
      if(item->pagina.numero == numero_pagina_acessada){        
        item->pagina.ultimo_endereco_acessado = endereco;
        item->pagina.suja = (operacao == 'W');

        pagina_esta_na_fila = 1;
        break;
      }

      item = item->proximo;
    }

    
    if(!pagina_esta_na_fila){

      Pagina* pagina = (Pagina*) malloc(sizeof(Pagina));
      pagina->numero = numero_pagina_acessada;    
      pagina->suja = (operacao == 'W');
      pagina->ultimo_endereco_acessado = endereco;
      inserir(fila, fila->fim, *pagina);
    }  

    return fila;
}

void fifo_listagem(Fila* fila)
{
  Item* item;
  item = fila->inicio;

  while(item != NULL){
      printf("Numero da pagina: %u | Ultimo endereco acessado: %u | bit de controle(pagina suja): %d\n", item->pagina.numero, item->pagina.ultimo_endereco_acessado, item->pagina.suja);
      item = item->proximo;
  }
}