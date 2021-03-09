#include "segundachance.h"

int idx;

Tabela analisarPaginaForaTabela(Tabela tabela, ItemMemoria* itens_memoria, int *paginas_lidas, int tamanho_tabela, int pagina_acesso, unsigned int endereco, char operacao)
{
      *paginas_lidas += 1;
      int idx_inserir = -1;
      int auxiliar_minimo = -1;

      for(idx = 0; idx < tamanho_tabela; idx++)
      {
          if(!itens_memoria[idx].existe)
          {
            idx_inserir = idx;
            break;
          }
      }

      if(idx_inserir < 0)
      {
        for(idx = 0; idx < tamanho_tabela; idx++)
        {
          if(tabela.paginas[idx].ultimo_acesso < auxiliar_minimo)
          {
            auxiliar_minimo = tabela.paginas[idx].ultimo_acesso;
            idx_inserir = idx;
          }

          if((idx == tamanho_tabela - 1))
          {                 
              idx_inserir = 0;               
          }
        }
      }

      tabela.paginas[idx_inserir].bit_controle = operacao == 'W';      
      tabela.paginas[idx_inserir].numero = pagina_acesso;
      tabela.paginas[idx_inserir].id = idx_inserir;      
      tabela.paginas[idx_inserir].endereco_acessado = endereco;        

      return tabela;
}

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