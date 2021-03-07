#include <stdio.h>
#include "doisa.h"
#include "estruturas.h"

int i;

void doisa(int total_paginas, tabela tabela_nao_fifo, int numero_pagina_acessada, int hit,  unsigned int endereco, char operacao, int contador_clock, int miss, quadro *quadros_memoria, int escritas)
{
    //verifica se pagina esta na tabela
    int i_pagina;
    int pagina_esta_na_tabela = 0;
    for(i_pagina = 0; i_pagina < total_paginas; i_pagina++){
      //se a pagina acessada esta na tabela de paginas
      if(tabela_nao_fifo.paginas[i_pagina].numero == numero_pagina_acessada){
        hit++;

        //atualiza dados da tabela, referentes a pagina acessada
        tabela_nao_fifo.paginas[i_pagina].ultimo_endereco_acessado = endereco;
        tabela_nao_fifo.paginas[i_pagina].suja = (operacao == 'W');
        tabela_nao_fifo.paginas[i_pagina].ultimo_acesso = contador_clock;
        tabela_nao_fifo.paginas[i_pagina].segunda_chance = 1;

        pagina_esta_na_tabela = 1;
        break;
      }
    }

    //se a pagina nao esta na tabela
    if(!pagina_esta_na_tabela){
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
        //pego o indice da pagina least recently used
        int menor_ultimo_acesso = -1;
        for(i_pagina = 0; i_pagina < total_paginas; i_pagina++){

          if(tabela_nao_fifo.paginas[i_pagina].ultimo_acesso < menor_ultimo_acesso){
            menor_ultimo_acesso = tabela_nao_fifo.paginas[i_pagina].ultimo_acesso;
            indice_quadro_a_inserir = i_pagina;
          }
          
          //se a pagina LRU tem uma segunda chance, remove esta segunda chance e reavalia a tabela de paginas
          if((i_pagina == total_paginas - 1) && (tabela_nao_fifo.paginas[indice_quadro_a_inserir].segunda_chance)){
            tabela_nao_fifo.paginas[indice_quadro_a_inserir].segunda_chance = 0;
            i_pagina = 0; 
          }
        }

        escritas += tabela_nao_fifo.paginas[indice_quadro_a_inserir].suja ? 1 : 0;
      }

      //escreve(ou sobrescreve) uma nova pagina na tabela
      tabela_nao_fifo.paginas[indice_quadro_a_inserir].numero = numero_pagina_acessada;
      tabela_nao_fifo.paginas[indice_quadro_a_inserir].quadro = indice_quadro_a_inserir;
      tabela_nao_fifo.paginas[indice_quadro_a_inserir].suja = (operacao == 'W');
      tabela_nao_fifo.paginas[indice_quadro_a_inserir].ultimo_endereco_acessado = endereco;
      tabela_nao_fifo.paginas[indice_quadro_a_inserir].ultimo_acesso = contador_clock;
      tabela_nao_fifo.paginas[indice_quadro_a_inserir].segunda_chance = 0; 

      //atualiza um atributo do quadro que estara na memoria
      quadros_memoria[indice_quadro_a_inserir].esta_na_memoria = 1;
    }
}