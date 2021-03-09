#include "lru.h"

void lru_execucao(int total_paginas, Tabela tabela_nao_fifo, int numero_pagina_acessada,  unsigned int endereco, char operacao, int contador_clock, Quadro *quadros_memoria, int *paginas_lidas, int *paginas_escritas) {
      int i_pagina;
      int i;

      int pagina_esta_na_tabela = 0;
      for(i_pagina = 0; i_pagina < total_paginas; i_pagina++){
        if(tabela_nao_fifo.paginas[i_pagina].numero == numero_pagina_acessada){    
          *paginas_escritas += 1;      

          tabela_nao_fifo.paginas[i_pagina].endereco_acessado = endereco;
          tabela_nao_fifo.paginas[i_pagina].bit_controle = (operacao == 'W');
          tabela_nao_fifo.paginas[i_pagina].ultimo_acesso = contador_clock;

          pagina_esta_na_tabela = 1;
          break;
        }
      }

      if(!pagina_esta_na_tabela){
        *paginas_lidas += 1;      
        int indice_quadro_a_inserir = -1;
        for(i = 0; i < total_paginas; i++){
          if(!quadros_memoria[i].esta_na_memoria){
            indice_quadro_a_inserir = i;
            break;
          }
        }
        if(indice_quadro_a_inserir == -1){
          int menor_ultimo_acesso = -1;
          for(i_pagina = 0; i_pagina < total_paginas; i_pagina++){
            if(tabela_nao_fifo.paginas[i_pagina].ultimo_acesso < menor_ultimo_acesso){
              menor_ultimo_acesso = tabela_nao_fifo.paginas[i_pagina].ultimo_acesso;
              indice_quadro_a_inserir = i_pagina;
            }
          }          
        }

        tabela_nao_fifo.paginas[indice_quadro_a_inserir].numero = numero_pagina_acessada;
        tabela_nao_fifo.paginas[indice_quadro_a_inserir].identificador = indice_quadro_a_inserir;
        tabela_nao_fifo.paginas[indice_quadro_a_inserir].bit_controle = (operacao == 'W');
        tabela_nao_fifo.paginas[indice_quadro_a_inserir].endereco_acessado = endereco;
        tabela_nao_fifo.paginas[indice_quadro_a_inserir].ultimo_acesso = contador_clock;

        quadros_memoria[indice_quadro_a_inserir].esta_na_memoria = 1;
      }
}

void lru_listagem(int tamanho_tabela, Tabela tabela_nao_fifo){
  int i_pagina;
  for(i_pagina = 0; i_pagina < tamanho_tabela; i_pagina++){            
      if(tabela_nao_fifo.paginas[i_pagina].identificador != -1){
          printf("Numero da pagina: %u | Ultimo endereco acessado: %u | bit de controle(pagina suja): %d\n",
              tabela_nao_fifo.paginas[i_pagina].numero, 
              tabela_nao_fifo.paginas[i_pagina].endereco_acessado, 
              tabela_nao_fifo.paginas[i_pagina].bit_controle ? 1 : 0);
      }
  }
}