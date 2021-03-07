#include <stdio.h>
#include "doisa.h"
#include "estruturas.h"

int idx;

Tabela doisa_execucao(int tamanho_tabela, int numero_pagina_acessada,  unsigned int endereco, char operacao, int clock_cont)
{    
    Tabela tabela;
    tabela.paginas = (Pagina *) malloc(tamanho_tabela * sizeof(Pagina));    
    for(idx = 0; idx < tamanho_tabela; idx++)
    {
        tabela.paginas[idx].quadro = -1;        
    }    
    
    int pagina_esta_na_tabela = 0;
    for(idx = 0; idx < tamanho_tabela; idx++){
      
      if(tabela.paginas[idx].numero == numero_pagina_acessada)
      {        
        tabela.paginas[idx].ultimo_endereco_acessado = endereco;
        tabela.paginas[idx].suja = (operacao == 'W');
        tabela.paginas[idx].ultimo_acesso = clock_cont;        
        pagina_esta_na_tabela = 1;
        break;
      }
    }
    
    if(!pagina_esta_na_tabela){        
      int indice_quadro_a_inserir = -1;      
      
      if(indice_quadro_a_inserir == -1){        
        int menor_ultimo_acesso = -1;
        for(idx = 0; idx < tamanho_tabela; idx++){

          if(tabela.paginas[idx].ultimo_acesso < menor_ultimo_acesso){
            menor_ultimo_acesso = tabela.paginas[idx].ultimo_acesso;
            indice_quadro_a_inserir = idx;
          }          
        }        
      }
      
      tabela.paginas[indice_quadro_a_inserir].numero = numero_pagina_acessada;
      tabela.paginas[indice_quadro_a_inserir].quadro = indice_quadro_a_inserir;
      tabela.paginas[indice_quadro_a_inserir].suja = (operacao == 'W');
      tabela.paginas[indice_quadro_a_inserir].ultimo_endereco_acessado = endereco;
      tabela.paginas[indice_quadro_a_inserir].ultimo_acesso = clock_cont;      

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