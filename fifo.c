#include <stdio.h>
#include "fifo.h"
#include "estruturas.h"

int i;
Fila *fila;

void fifo_execucao(int total_paginas, int numero_pagina_acessada, int hit,  unsigned int endereco, char operacao, int contador_clock, int miss, Quadro *quadros_memoria, int escritas)
{
    if ((fila = (Fila *) malloc(sizeof(Fila))) == NULL)           
    {
        printf("Erro: Fila fifo não criada\n");
        return;
    }
    
    Item* item;
    item = fila->inicio;
    int pagina_esta_na_fila = 0;

    while(item != NULL){      
      if(item->pagina.numero == numero_pagina_acessada){
        hit++;
        
        item->pagina.ultimo_endereco_acessado = endereco;
        item->pagina.suja = (operacao == 'W');

        pagina_esta_na_fila = 1;
        break;
      }

      item = item->proximo;
    }

    
    if(!pagina_esta_na_fila){
      miss++;    
      int indice_quadro_a_inserir = -1;
      for(i = 0; i < total_paginas; i++){
        if(!quadros_memoria[i].esta_na_memoria){
          indice_quadro_a_inserir = i;
          break;
        }
      }
      
      if(indice_quadro_a_inserir == -1){
        indice_quadro_a_inserir = fila->inicio->pagina.quadro;
        remover(fila);
        escritas += fila->inicio->pagina.suja ? 1 : 0;
      }
      
      Pagina* pagina = (Pagina*) malloc(sizeof(Pagina));
      pagina->numero = numero_pagina_acessada;
      pagina->quadro = indice_quadro_a_inserir;
      pagina->suja = (operacao == 'W');
      pagina->ultimo_endereco_acessado = endereco;
      inserir(fila, fila->fim, *pagina);      
      quadros_memoria[indice_quadro_a_inserir].esta_na_memoria = 1;
    }  
}

void fifo_listagem()
{
  Item* item;
  item = fila->inicio;

  while(item != NULL){
      printf("Numero da pagina: %u | Ultimo endereco acessado: %u | bit de controle(pagina suja): %d\n", item->pagina.numero, item->pagina.ultimo_endereco_acessado, item->pagina.suja);
      item = item->proximo;
  }
}