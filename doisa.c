#include <stdio.h>
#include "doisa.h"
#include "estruturas.h"

int idx;

Tabela doisa_execucao(int total_paginas, int numero_pagina_acessada, int hit,  unsigned int endereco, char operacao, int contador_clock, int miss, Quadro *quadros_memoria, int escritas)
{

    //Inicializar
    Tabela tabela;
    tabela.paginas = (Pagina *) malloc(total_paginas * sizeof(Pagina));
    for(idx = 0; idx < total_paginas; idx++)
    {
        tabela.paginas[idx].quadro = -1;
        tabela.paginas[idx].segunda_chance = 0;
    }    
    
    int pagina_esta_na_tabela = 0;
    for(idx = 0; idx < total_paginas; idx++){
      
      if(tabela.paginas[idx].numero == numero_pagina_acessada)
      {        
        tabela.paginas[idx].ultimo_endereco_acessado = endereco;
        tabela.paginas[idx].suja = (operacao == 'W');
        tabela.paginas[idx].ultimo_acesso = contador_clock;
        tabela.paginas[idx].segunda_chance = 1;
        pagina_esta_na_tabela = 1;
        hit++;
        break;
      }
    }
    
    if(!pagina_esta_na_tabela){
      miss++;     
      int indice_quadro_a_inserir = -1;

      for(idx = 0; idx < total_paginas; idx++){
        if(!quadros_memoria[idx].esta_na_memoria){
          indice_quadro_a_inserir = idx;
          break;
        }
      }
      
      if(indice_quadro_a_inserir == -1){        
        int menor_ultimo_acesso = -1;
        for(idx = 0; idx < total_paginas; idx++){

          if(tabela.paginas[idx].ultimo_acesso < menor_ultimo_acesso){
            menor_ultimo_acesso = tabela.paginas[idx].ultimo_acesso;
            indice_quadro_a_inserir = idx;
          }          
          
          if((idx == total_paginas - 1) && (tabela.paginas[indice_quadro_a_inserir].segunda_chance)){
            tabela.paginas[indice_quadro_a_inserir].segunda_chance = 0;
            idx = 0; 
          }
        }

        escritas += tabela.paginas[indice_quadro_a_inserir].suja ? 1 : 0;
      }
      
      tabela.paginas[indice_quadro_a_inserir].numero = numero_pagina_acessada;
      tabela.paginas[indice_quadro_a_inserir].quadro = indice_quadro_a_inserir;
      tabela.paginas[indice_quadro_a_inserir].suja = (operacao == 'W');
      tabela.paginas[indice_quadro_a_inserir].ultimo_endereco_acessado = endereco;
      tabela.paginas[indice_quadro_a_inserir].ultimo_acesso = contador_clock;
      tabela.paginas[indice_quadro_a_inserir].segunda_chance = 0; 
      
      quadros_memoria[indice_quadro_a_inserir].esta_na_memoria = 1;

      return tabela;
    }
}

void doisa_listagem(Tabela tabela, int tamanho_tabela)
{
  int idx;
  for(idx = 0; idx < tamanho_tabela; idx++){            
      if(tabela.paginas[idx].quadro != -1){
          printf("Numero da pagina: %u | Ultimo endereco acessado: %u | bit de controle(pagina suja): %d\n",
              tabela.paginas[idx].numero, 
              tabela.paginas[idx].ultimo_endereco_acessado, 
              tabela.paginas[idx].suja);
      }
  }
}