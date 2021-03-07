#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "estruturas.h"
#include "fifo.h"
#include "doisa.h"
#include "lru.h"

char *nome_algoritmo;
char *nome_arquivo;
int tamanho_paginas;
int tamanho_memoria;
int tamanho_tabela;
int i;

void main(int argc, char *argv[] ){     

    clock_t inicio = clock();   

    if( argc != 5 ) 
    {
      printf("Error: Informar parâmetros corretamente.\n");
      return;
    }

    nome_algoritmo = argv[1];
    nome_arquivo = argv[2];
    tamanho_paginas = atoi(argv[3]);
    tamanho_memoria = atoi(argv[4]);    
    tamanho_tabela = tamanho_memoria/tamanho_paginas;    
    int tamanho_paginas_bytes = tamanho_paginas * pow(2, 10);       

    if(strcmp(nome_algoritmo, "lru") != 0 && strcmp(nome_algoritmo, "2a") != 0 && strcmp(nome_algoritmo, "fifo") != 0)
    {
        printf("Error: Algoritmo %s desconhecido.\n", nome_algoritmo);
        return;
    }   

    FILE *arquivo_log = fopen(nome_arquivo, "r");

    if (arquivo_log == NULL)
    {        
        printf("Error: Arquivo %s não encontrado.\n", nome_arquivo);
        return;
    }

    printf("Arquivo de entrada: %s\n", nome_arquivo);
    printf("Tamanho da memoria: %d KB\n", tamanho_memoria);
    printf("Tamanho das páginas: %d KB\n", tamanho_paginas);
    printf("Tamanho da tabela: %d KB\n", tamanho_tabela);
    printf("Técnica de reposição: %s\n", nome_algoritmo);   
    printf("Executando o simulador...\n");      
    
    Tabela tabela_nao_fifo; 

    if(strcmp(nome_algoritmo, "lru") == 0 || strcmp(nome_algoritmo, "2a") == 0 || strcmp(nome_algoritmo, "new") == 0)
    {
        tabela_nao_fifo.paginas = (Pagina *) malloc(tamanho_tabela * sizeof(Pagina));
        for(i = 0; i < tamanho_tabela; i++){
            tabela_nao_fifo.paginas[i].quadro = -1;
            tabela_nao_fifo.paginas[i].segunda_chance = 0;
        }
    }

    char operacao;
    unsigned int endereco;    
    unsigned int contador = 0;
    unsigned tamanho_paginas_bytes_aux;

    tamanho_paginas_bytes_aux = tamanho_paginas_bytes;    
    while (tamanho_paginas_bytes_aux > 1) {
        tamanho_paginas_bytes_aux = tamanho_paginas_bytes_aux >> 1;
        contador++;
    }

    contador = 32u - contador;
           
    int clock_cont = 1;

    Quadro quadros_memoria[tamanho_tabela];

    for(i = 0; i < tamanho_tabela; i++){
        quadros_memoria[i].esta_na_memoria = 0;
    }

    while(fscanf(arquivo_log,"%x %c\n", &endereco, &operacao) != EOF){       

        unsigned int numero_pagina_acessada = endereco >> contador;

        if(strcmp(nome_algoritmo, "fifo") == 0)
        {            
            Fila* fila = fifo_execucao(tamanho_tabela, numero_pagina_acessada, endereco, operacao);            
            fifo_listagem(fila);
        }
        else if(strcmp(nome_algoritmo, "lru") == 0)
        {
            lru(tamanho_tabela, tabela_nao_fifo, numero_pagina_acessada, endereco, operacao, clock_cont, quadros_memoria);
        } 
        else if(strcmp(nome_algoritmo, "2a") == 0)
        {  
            Tabela tabela = doisa_execucao(tamanho_tabela, numero_pagina_acessada, endereco, operacao, clock_cont);
            doisa_listagem(tabela, tamanho_tabela);
        }

        clock_cont++;
    }    

    if(strcmp(nome_algoritmo, "lru") == 0){
        int i_pagina;
        for(i_pagina = 0; i_pagina < tamanho_tabela; i_pagina++){            
            if(tabela_nao_fifo.paginas[i_pagina].quadro != -1){
                printf("Numero da pagina: %u | Ultimo endereco acessado: %u | bit de controle(pagina suja): %d\n",
                    tabela_nao_fifo.paginas[i_pagina].numero, 
                    tabela_nao_fifo.paginas[i_pagina].ultimo_endereco_acessado, 
                    tabela_nao_fifo.paginas[i_pagina].suja ? 1 : 0);
            }
        }
    }        

    printf("Tempo de execucao: %g ms. \n", (double)(clock() - inicio) * 1000.0 / CLOCKS_PER_SEC);

    return;   
}