#include "segundachance.h"
#include "analises.h"

int idx;

Tabela segundachance_execucao(int tamanho_tabela, int pagina_acesso, unsigned int endereco, char operacao, int clock_cont, int *paginas_lidas, int *paginas_escritas)
{    
    Tabela tabela;
    tabela.paginas = (Pagina *) malloc(tamanho_tabela * sizeof(Pagina));    
    for(idx = 0; idx < tamanho_tabela; idx++)
    {
        tabela.paginas[idx].id = -1;                
    }

    ItemMemoria itens_memoria[tamanho_tabela];
    for(idx = 0; idx < tamanho_tabela; idx++)
    {
        itens_memoria[idx].existe = false;
    }    
  
    int pagina_tabela = 0;
    for(idx = 0; idx < tamanho_tabela; idx++)
    {      
      if(tabela.paginas[idx].numero == pagina_acesso)
      {     
        *paginas_escritas+=1;
        tabela.paginas[idx].endereco_acessado = endereco;                    
        tabela.paginas[idx].bit_controle = operacao == 'W';        
        pagina_tabela = 1;

        break;
      }
    }    
    
    if(pagina_tabela == 0)
    {    
      return analisarPaginaForaTabela(tabela, itens_memoria, paginas_lidas, tamanho_tabela, pagina_acesso, endereco, operacao);
    }

    return tabela;
}

void segundachance_listagem(Tabela tabela, int tamanho_tabela)
{  
  for(idx = 0; idx < tamanho_tabela; idx++)
  {            
      if(tabela.paginas[idx].id != -1 && tabela.paginas[idx].numero != 0 && tabela.paginas[idx].endereco_acessado != 0)
      {
          printf("     Pagina: %u - Endereço: %u - Bit de controle (Sim ou não): %s\n", tabela.paginas[idx].numero, tabela.paginas[idx].endereco_acessado, tabela.paginas[idx].bit_controle ? "Sim" : "Não");
      }
  }
}