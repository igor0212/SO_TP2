#include "lru.h"

int idx;

Tabela lru_execucao(int tamanho_tabela, int numero_pagina_acessada,  unsigned int endereco, char operacao, int contador_clock, Quadro *quadros_memoria, int *paginas_lidas, int *paginas_escritas) 
{
      Tabela tabela;
      tabela.paginas = (Pagina *) malloc(tamanho_tabela * sizeof(Pagina));    
      for(idx = 0; idx < tamanho_tabela; idx++)
      {
          tabela.paginas[idx].id = -1;        
      }          

      int pagina_esta_na_tabela = 0;
      for(idx = 0; idx < tamanho_tabela; idx++){
        if(tabela.paginas[idx].numero == numero_pagina_acessada){    
          *paginas_escritas += 1;      

          tabela.paginas[idx].endereco_acessado = endereco;
          tabela.paginas[idx].bit_controle = (operacao == 'W');
          tabela.paginas[idx].ultimo_acesso = contador_clock;

          pagina_esta_na_tabela = 1;
          break;
        }
      }

      if(!pagina_esta_na_tabela){
        *paginas_lidas += 1;      
        int indice_quadro_a_inserir = -1;
        for(idx = 0; idx < tamanho_tabela; idx++){
          if(!quadros_memoria[idx].esta_na_memoria){
            indice_quadro_a_inserir = idx;
            break;
          }
        }
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
        tabela.paginas[indice_quadro_a_inserir].id = indice_quadro_a_inserir;
        tabela.paginas[indice_quadro_a_inserir].bit_controle = (operacao == 'W');
        tabela.paginas[indice_quadro_a_inserir].endereco_acessado = endereco;
        tabela.paginas[indice_quadro_a_inserir].ultimo_acesso = contador_clock;

        quadros_memoria[indice_quadro_a_inserir].esta_na_memoria = 1;
      }

      return tabela;
}

void lru_listagem(Tabela tabela, int tamanho_tabela)
{  
  for(idx = 0; idx < tamanho_tabela; idx++)
  {            
      if(tabela.paginas[idx].id != -1)
      {
          printf("Pagina: %u - Suja: %s - Ultimo endereco: %u\n", tabela.paginas[idx].numero, tabela.paginas[idx].bit_controle ? "Sim" : "Não", tabela.paginas[idx].endereco_acessado);
      }
  }
}