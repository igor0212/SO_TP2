#include "lru.h"

int idx;

Tabela lru_execucao(int tamanho_tabela, int pagina_acesso, unsigned int endereco, char operacao, int contador_clock, int *paginas_lidas, int *paginas_escritas) 
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
          *paginas_escritas += 1;
          tabela.paginas[idx].endereco_acessado = endereco;
          tabela.paginas[idx].bit_controle = (operacao == 'W');
          tabela.paginas[idx].ultimo_acesso = contador_clock;
          pagina_tabela = 1;
          break;
        }
      }

      if(pagina_tabela == 0)
      {
        *paginas_lidas += 1;      
        int idx_inserir = -1;

        for(idx = 0; idx < tamanho_tabela; idx++)
        {
          if(!itens_memoria[idx].existe)
          {
            idx_inserir = idx;
            break;
          }
        }

        if(idx_inserir == -1)
        {
          int auxiliar_minimo = -1;
          for(idx = 0; idx < tamanho_tabela; idx++)
          {
            if(tabela.paginas[idx].ultimo_acesso < auxiliar_minimo){
              auxiliar_minimo = tabela.paginas[idx].ultimo_acesso;
              idx_inserir = idx;
            }
          }          
        }
        
        tabela.paginas[idx_inserir].ultimo_acesso = contador_clock;  
        tabela.paginas[idx_inserir].numero = pagina_acesso;
        tabela.paginas[idx_inserir].id = idx_inserir;        
        tabela.paginas[idx_inserir].endereco_acessado = endereco;
        tabela.paginas[idx_inserir].bit_controle = operacao == 'W';             
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