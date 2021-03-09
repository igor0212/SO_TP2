#include "lru.h"

int idx;

Tabela lru_execucao(int tamanho_tabela, int numero_pagina_acessada,  unsigned int endereco, char operacao, int contador_clock, Quadro *quadros_memoria, int *paginas_lidas, int *paginas_escritas) 
{

      Tabela tabela_nao_fifo;
      tabela_nao_fifo.paginas = (Pagina *) malloc(tamanho_tabela * sizeof(Pagina));    
      for(idx = 0; idx < tamanho_tabela; idx++)
      {
          tabela_nao_fifo.paginas[idx].id = -1;        
      }    

      int i_pagina;
      int i;

      int pagina_esta_na_tabela = 0;
      for(i_pagina = 0; i_pagina < tamanho_tabela; i_pagina++){
        if(tabela_nao_fifo.paginas[i_pagina].numero == numero_pagina_acessada){    
          *paginas_escritas += 1;      

          tabela_nao_fifo.paginas[i_pagina].endereco_acessado = endereco;
          tabela_nao_fifo.paginas[i_pagina].suja = (operacao == 'W');
          tabela_nao_fifo.paginas[i_pagina].ultimo_acesso = contador_clock;

          pagina_esta_na_tabela = 1;
          break;
        }
      }

      if(!pagina_esta_na_tabela){
        *paginas_lidas += 1;      
        int indice_quadro_a_inserir = -1;
        for(i = 0; i < tamanho_tabela; i++){
          if(!quadros_memoria[i].esta_na_memoria){
            indice_quadro_a_inserir = i;
            break;
          }
        }
        if(indice_quadro_a_inserir == -1){
          int menor_ultimo_acesso = -1;
          for(i_pagina = 0; i_pagina < tamanho_tabela; i_pagina++){
            if(tabela_nao_fifo.paginas[i_pagina].ultimo_acesso < menor_ultimo_acesso){
              menor_ultimo_acesso = tabela_nao_fifo.paginas[i_pagina].ultimo_acesso;
              indice_quadro_a_inserir = i_pagina;
            }
          }          
        }

        tabela_nao_fifo.paginas[indice_quadro_a_inserir].numero = numero_pagina_acessada;
        tabela_nao_fifo.paginas[indice_quadro_a_inserir].id = indice_quadro_a_inserir;
        tabela_nao_fifo.paginas[indice_quadro_a_inserir].suja = (operacao == 'W');
        tabela_nao_fifo.paginas[indice_quadro_a_inserir].endereco_acessado = endereco;
        tabela_nao_fifo.paginas[indice_quadro_a_inserir].ultimo_acesso = contador_clock;

        quadros_memoria[indice_quadro_a_inserir].esta_na_memoria = 1;
      }

      return tabela_nao_fifo;
}

void lru_listagem(Tabela tabela, int tamanho_tabela)
{  
  for(idx = 0; idx < tamanho_tabela; idx++)
  {            
      if(tabela.paginas[idx].id != -1)
      {
          printf("Pagina: %u - Suja: %s - Ultimo endereco: %u\n", tabela.paginas[idx].numero, tabela.paginas[idx].suja ? "Sim" : "Não", tabela.paginas[idx].endereco_acessado);
      }
  }
}