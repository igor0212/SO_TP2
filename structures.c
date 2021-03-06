#include "structures.h"

void inicializacao (Fila * sequencia){         
  sequencia->inicio = NULL;         
  sequencia->fim = NULL;         
  sequencia->tamanho = 0;       
}

/* inserir (adicionar) um elemento na fila */       
int inserir (Fila * sequencia, Elemento * atual, pagina page){         
  Elemento *novo_elemento;         
  if ((novo_elemento = (Elemento *) malloc (sizeof (Elemento))) == NULL)
    return -1;         

  novo_elemento->page.numero_pagina = page.numero_pagina;
  novo_elemento->page.quadro = page.quadro;
  novo_elemento->page.ultimo_endereco_acessado = page.ultimo_endereco_acessado;
  novo_elemento->page.suja = page.suja;
          
  if(atual == NULL){           
    if(sequencia->tamanho == 0)             
      sequencia->fim = novo_elemento;           
    novo_elemento->seguinte = sequencia->inicio;           
    sequencia-> inicio = novo_elemento;         
  }
  else 
  {           
    if(atual->seguinte == NULL)             
      sequencia->fim = novo_elemento;           
    novo_elemento->seguinte = atual->seguinte;           
    atual-> seguinte = novo_elemento;         
  }         
  sequencia->tamanho++;         
  return 0;       
}

/* remover (eliminar) elemento da fila */       
int remover (Fila * sequencia){         
  Elemento *remov_elemento;         
  if (sequencia->tamanho == 0)           
    return -1;         
  remov_elemento = sequencia->inicio;         
  sequencia-> inicio = sequencia->inicio->seguinte;
  if(remov_elemento == sequencia->fim)
    sequencia->fim = NULL;                   
  free (remov_elemento);         
  sequencia->tamanho--;         
  return 0;       
}

/* exibição da fila */       
void exibir (Fila *sequencia){         
  Elemento *atual;         
  int i;         
  atual = sequencia->inicio;         
  for(i=0;i<sequencia->tamanho;++i){           
    printf("numero da página: %u \n", atual->page.numero_pagina);           
    atual = atual->seguinte;         
  }       
}

///////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

//Função para validação do algorítmo recebido por parametro em main()
int valida_entrada(char* alg){

  if ((strcmp(alg, "lru") == 0) || (strcmp(alg, "2a") == 0) || (strcmp(alg, "fifo") == 0) || (strcmp(alg, "new") == 0)){
    return 1;
  }
  else
    return 0;
}