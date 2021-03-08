#include <stdio.h>
#include "doisa.h"
#include "estruturas.h"

int idx;

Tabela doisa_execucao(int tamanho_tabela, int pagina_acesso,  unsigned int endereco, char operacao, int clock_cont)
{    
    Tabela tabela;
    tabela.paginas = (Pagina *) malloc(tamanho_tabela * sizeof(Pagina));    
    for(idx = 0; idx < tamanho_tabela; idx++)
    {
        tabela.paginas[idx].quadro = -1;        
    }    
    
    int pagina_tabela = 0;
    for(idx = 0; idx < tamanho_tabela; idx++)
    {      
      if(tabela.paginas[idx].numero == pagina_acesso)
      {        
        tabela.paginas[idx].ultimo_endereco_acessado = endereco;        
        tabela.paginas[idx].ultimo_acesso = clock_cont;        
        tabela.paginas[idx].suja = operacao == 'W';
        pagina_tabela = 1;
        break;
      }
    }
    
    if(pagina_tabela == 0)
    {    
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

      tabela.paginas[idx_inserir].suja = operacao == 'W';      
      tabela.paginas[idx_inserir].numero = pagina_acesso;
      tabela.paginas[idx_inserir].quadro = idx_inserir;      
      tabela.paginas[idx_inserir].ultimo_endereco_acessado = endereco;
      tabela.paginas[idx_inserir].ultimo_acesso = clock_cont;      

      return tabela;
    }
}

void doisa_listagem(Tabela tabela, int tamanho_tabela)
{  
  for(idx = 0; idx < tamanho_tabela; idx++)
  {            
      if(tabela.paginas[idx].quadro != -1)
      {
          printf("Pagina: %u - Suja: %s - Ultimo endereco: %u\n", tabela.paginas[idx].numero, tabela.paginas[idx].suja ? "Sim" : "Não", tabela.paginas[idx].ultimo_endereco_acessado);
      }
  }
}