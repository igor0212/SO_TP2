#include "lru.h"

int idx;

Tabela lru_execucao(int tamanho_tabela, int pagina_acesso, unsigned int endereco, char operacao, int contador, int *paginas_lidas, int *paginas_escritas) 
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
          itens_memoria[idx].existe = 0;
      }     

      int pagina_tabela = 0;
      for(idx = 0; idx < tamanho_tabela; idx++)
      {
        if(tabela.paginas[idx].numero == pagina_acesso)
        {    
          *paginas_escritas += 1;
          tabela.paginas[idx].endereco_acessado = endereco;
          tabela.paginas[idx].bit_controle = (operacao == 'W');
          tabela.paginas[idx].ultimo_acesso = contador;
          pagina_tabela = 1;
          break;
        }
      }

      if(pagina_tabela == 0)
      {
        *paginas_lidas += 1;      
        int idx_item_inserir = -1;
        for(idx = 0; idx < tamanho_tabela; idx++)
        {
          if(!itens_memoria[idx].existe)
          {
            idx_item_inserir = idx;
            break;
          }
        }
        if(idx_item_inserir == -1)
        {
          int menor_ultimo_acesso = -1;
          for(idx = 0; idx < tamanho_tabela; idx++)
          {
            if(tabela.paginas[idx].ultimo_acesso < menor_ultimo_acesso)
            {
              menor_ultimo_acesso = tabela.paginas[idx].ultimo_acesso;
              idx_item_inserir = idx;
            }
          }          
        }

        tabela.paginas[idx_item_inserir].numero = pagina_acesso;
        tabela.paginas[idx_item_inserir].id = idx_item_inserir;
        tabela.paginas[idx_item_inserir].bit_controle = (operacao == 'W');
        tabela.paginas[idx_item_inserir].endereco_acessado = endereco;
        tabela.paginas[idx_item_inserir].ultimo_acesso = contador;

        itens_memoria[idx_item_inserir].existe = 1;
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