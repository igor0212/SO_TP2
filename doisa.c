#include <stdio.h>
#include "doisa.h"
#include "estruturas.h"

int idx;

Tabela doisa_execucao(int tamanho_tabela, int pagina_acesso,  unsigned int endereco, char operacao, int clock_cont, int *paginas_lidas, int *paginas_escritas)
{    
    Tabela tabela;
    tabela.paginas = (Pagina *) malloc(tamanho_tabela * sizeof(Pagina));    
    for(idx = 0; idx < tamanho_tabela; idx++)
    {
        tabela.paginas[idx].identificador = -1;        
    }    
    
    int pagina_tabela = 0;
    for(idx = 0; idx < tamanho_tabela; idx++)
    {      
      if(tabela.paginas[idx].numero == pagina_acesso)
      {     
        *paginas_escritas+=1;
        tabela.paginas[idx].endereco_acessado = endereco;        
        tabela.paginas[idx].ultimo_acesso = clock_cont;        
        tabela.paginas[idx].bit_controle = operacao == 'W';
        pagina_tabela = 1;
        break;
      }
    }
    
    if(pagina_tabela == 0)
    {    
      *paginas_lidas+=1;
      int idx_inserir = -1;
      int auxiliar_minimo = -1;

      for(idx = 0; idx < tamanho_tabela; idx++)
      {
        if(tabela.paginas[idx].ultimo_acesso < auxiliar_minimo)
        {
          auxiliar_minimo = tabela.paginas[idx].ultimo_acesso;
          idx_inserir = idx;
        }          
      }      

      tabela.paginas[idx_inserir].bit_controle = operacao == 'W';      
      tabela.paginas[idx_inserir].numero = pagina_acesso;
      tabela.paginas[idx_inserir].identificador = idx_inserir;      
      tabela.paginas[idx_inserir].endereco_acessado = endereco;
      tabela.paginas[idx_inserir].ultimo_acesso = clock_cont;      

      return tabela;
    }
}

void doisa_listagem(Tabela tabela, int tamanho_tabela)
{  
  for(idx = 0; idx < tamanho_tabela; idx++)
  {            
      if(tabela.paginas[idx].identificador != -1)
      {
          printf("Pagina: %u - Suja: %s - Ultimo endereco: %u\n", tabela.paginas[idx].numero, tabela.paginas[idx].bit_controle ? "Sim" : "Não", tabela.paginas[idx].endereco_acessado);
      }
  }
}