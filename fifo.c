#include <stdio.h>
#include "fifo.h"
#include "estruturas.h"

int i;

void fifo(int total_paginas, Fila* tabela_fifo, int numero_pagina_acessada, int hit,  unsigned int endereco, char operacao, int contador_clock, int miss, Quadro *quadros_memoria, int escritas)
{
    //verifica se pagina esta na fila
    Item* i_elemento;
    i_elemento = tabela_fifo->inicio;
    int pagina_esta_na_fila = 0;
    while(i_elemento != NULL){
      //se a pagina acessada esta na tabela de paginas
      if(i_elemento->pagina.numero == numero_pagina_acessada){
        hit++;

        //atualiza dados da tabela, referentes a pagina acessada
        i_elemento->pagina.ultimo_endereco_acessado = endereco;
        i_elemento->pagina.suja = (operacao == 'W');

        pagina_esta_na_fila = 1;
        break;
      }

      i_elemento = i_elemento->proximo;
    }

    //se a pagina nao esta na fila
    if(!pagina_esta_na_fila){
      miss++;

      //pega o indice, no array de quadros na memoria, que recebera o novo quadro ou detecta que todos os quadros na memoria estao ocupados
      int indice_quadro_a_inserir = -1;
      for(i = 0; i < total_paginas; i++){
        if(!quadros_memoria[i].esta_na_memoria){
          indice_quadro_a_inserir = i;
          break;
        }
      }

      //se a memoria ja estiver lotada de quadros
      if(indice_quadro_a_inserir == -1){
        indice_quadro_a_inserir = tabela_fifo->inicio->pagina.quadro;
        remover(tabela_fifo);
        escritas += tabela_fifo->inicio->pagina.suja ? 1 : 0;
      }

      //insere uma nova pagina na fila
      Pagina* pagina = (Pagina*) malloc(sizeof(Pagina));
      pagina->numero = numero_pagina_acessada;
      pagina->quadro = indice_quadro_a_inserir;
      pagina->suja = (operacao == 'W');
      pagina->ultimo_endereco_acessado = endereco;
      inserir(tabela_fifo, tabela_fifo->fim, *pagina);

      //atualiza um atributo do quadro que estara na memoria
      quadros_memoria[indice_quadro_a_inserir].esta_na_memoria = 1;
    }  
}