#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "fifo.h"

char *nome_algoritmo;
char *nome_arquivo;
int tamanho_paginas;
int tamanho_memoria;
int tamanho_tabela;

void leitura(FILE *arquivo_log)
{
    if(strcmp(nome_algoritmo, "fifo") == 0)
    {
        leitura_fifo(arquivo_log);
    }
}

void main( int argc, char *argv[] )  {        

    clock_t inicio;
    inicio = clock();

    if( argc != 5 ) {
      printf("Error: Informar parâmetros corretamente.\n");
      return;
    }

    nome_algoritmo = argv[1];
    nome_arquivo = argv[2];
    tamanho_paginas = atoi(argv[3]);
    tamanho_memoria = atoi(argv[4]);    
    tamanho_tabela = tamanho_memoria/tamanho_paginas;

    if(strcmp(nome_algoritmo, "lru") != 0 && strcmp(nome_algoritmo, "2a") != 0 && strcmp(nome_algoritmo, "fifo") != 0)
    {
        printf("Error: Algoritmo %s desconhecido.\n", nome_algoritmo);
        return;
    }

    printf("Executando o simulador...\n");    
    printf("Arquivo de entrada: %s\n", nome_arquivo);
    printf("Tamanho da memoria: %d KB\n", tamanho_memoria);
    printf("Tamanho das páginas: %d KB\n", tamanho_paginas);
    printf("Tamanho da tabela: %d KB\n", tamanho_tabela);
    printf("Técnica de reposição: %s\n", nome_algoritmo);    
    
    FILE *arquivo_log = fopen(nome_arquivo, "r");

    if (arquivo_log == NULL){        
        printf("Error: Arquivo %s não encontrado.\n", nome_arquivo);
        return;
    }

    leitura(arquivo_log);

    fclose(arquivo_log);    

    printf("Tempode execução: %g ms \n",((clock() - inicio) * 1000.0) / (double) CLOCKS_PER_SEC);    
};
