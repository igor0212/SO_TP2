#include "estruturas.h"
#include "analises.h"

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