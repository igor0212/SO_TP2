#include "media.h"

int idx;

Tabela media_execucao(int tamanho_tabela, int pagina_acesso, unsigned int endereco, char operacao, int contador_clock, int *paginas_lidas, int *paginas_escritas) 
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
            idx_inserir =   tamanho_tabela/2;
        }
        
        tabela.paginas[idx_inserir].ultimo_acesso = contador_clock;  
        tabela.paginas[idx_inserir].numero = pagina_acesso;
        tabela.paginas[idx_inserir].id = idx_inserir;        
        tabela.paginas[idx_inserir].endereco_acessado = endereco;
        tabela.paginas[idx_inserir].bit_controle = operacao == 'W';             
      }

      return tabela;
}