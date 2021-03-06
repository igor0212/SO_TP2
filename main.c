#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct {
    const char *name;
    pthread_t thread;
} friend;

pthread_mutex_t oven;
pthread_cond_t queue;
pthread_cond_t rules;
int it;

void main( int argc, char *argv[] )  {        

    clock_t inicio, fim;
    inicio = clock();

    if( argc != 5 ) {
      printf("Error: Informar parâmetros corretamente.\n");
      return;
    }

    char *algoritmo = argv[1];
    char *arquivo = argv[2];
    int tamanho_paginas = atoi(argv[3]);
    int tamanho_memoria = atoi(argv[4]);    

    if(strcmp(algoritmo, "lru") != 0 && strcmp(algoritmo, "2a") != 0 && strcmp(algoritmo, "fifo") != 0)
    {
        printf("Error: Algoritmo %s desconhecido.\n", algoritmo);
        return;
    }

    printf("Executando o simulador...\n");    
    printf("Arquivo de entrada: %s\n", arquivo);
    printf("Tamanho da memoria: %d KB\n", tamanho_memoria);
    printf("Tamanho das páginas: %d KB\n", tamanho_paginas);
    printf("Técnica de reposição: %s\n", algoritmo);
    
    fim = clock();    
};
