#include "estruturas.h"

void inicializacao (Fila * sequencia){         
  sequencia->inicio = NULL;         
  sequencia->fim = NULL;         
  sequencia->tamanho = 0;       
}

/* inserir (adicionar) um elemento na fila */       
int inserir (Fila * sequencia, Item * atual, Pagina pagina){         
  Item *novo_elemento;         
  if ((novo_elemento = (Item *) malloc (sizeof (Item))) == NULL)
    return -1;         

  novo_elemento->pagina.numero = pagina.numero;
  novo_elemento->pagina.quadro = pagina.quadro;
  novo_elemento->pagina.ultimo_endereco_acessado = pagina.ultimo_endereco_acessado;
  novo_elemento->pagina.suja = pagina.suja;
          
  if(atual == NULL){           
    if(sequencia->tamanho == 0)             
      sequencia->fim = novo_elemento;           
    novo_elemento->proximo = sequencia->inicio;           
    sequencia-> inicio = novo_elemento;         
  }
  else 
  {           
    if(atual->proximo == NULL)             
      sequencia->fim = novo_elemento;           
    novo_elemento->proximo = atual->proximo;           
    atual-> proximo = novo_elemento;         
  }         
  sequencia->tamanho++;         
  return 0;       
}

/* remover (eliminar) elemento da fila */       
int remover (Fila * sequencia){         
  Item *remov_elemento;         
  if (sequencia->tamanho == 0)           
    return -1;         
  remov_elemento = sequencia->inicio;         
  sequencia-> inicio = sequencia->inicio->proximo;
  if(remov_elemento == sequencia->fim)
    sequencia->fim = NULL;                   
  free (remov_elemento);         
  sequencia->tamanho--;         
  return 0;       
}

/* exibição da fila */       
void exibir (Fila *sequencia){         
  Item *atual;         
  int i;         
  atual = sequencia->inicio;         
  for(i=0;i<sequencia->tamanho;++i){           
    printf("numero da página: %u \n", atual->pagina.numero);           
    atual = atual->proximo;         
  }       
}
