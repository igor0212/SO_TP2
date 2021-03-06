#include "structures.h"
#include "fifo.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>


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

    if( argc != 5 ) {
      printf("Error: Informar parâmetros corretamente.\n");
      return;
    }

    nome_algoritmo = argv[1];
    nome_arquivo = argv[2];
    tamanho_paginas = atoi(argv[3]);
    tamanho_memoria = atoi(argv[4]);    
    tamanho_tabela = tamanho_memoria/tamanho_paginas;

    FILE *arquivo = fopen(nome_arquivo,"r");

    if(arquivo == NULL){
        printf("Erro ao ler arquivo.\n");
        return 1;
    }

    //Verificando se a política de substituição é válida
    if(!valida_entrada(nome_algoritmo)){
        printf("Erro ao identificar política de substituição.\n");
        return 0;
    }

    int i;

    if(strcmp(nome_algoritmo, "lru") != 0 && strcmp(nome_algoritmo, "2a") != 0 && strcmp(nome_algoritmo, "fifo") != 0)
    {
        printf("Error: Algoritmo %s desconhecido.\n", nome_algoritmo);
        return;
    }

    int total_paginas = tamanho_memoria / tamanho_paginas; //numero total de paginas/quadros na tabela e na memoria
    printf("Numero total de paginas na memoria e na tabela: %d\n", total_paginas);

    //inicializando estruturas para executar os algoritmos de substituicao
    Fila *tabela_fifo;
    tabela tabela_nao_fifo; 

    if(strcmp(nome_algoritmo, "fifo") == 0){
        if ((tabela_fifo = (Fila *) malloc(sizeof(Fila))) == NULL)           
        return -1;         
        inicializacao(tabela_fifo); 
    }
    else
    if(strcmp(nome_algoritmo, "lru") == 0 || strcmp(nome_algoritmo, "2a") == 0 || strcmp(nome_algoritmo, "new") == 0){

        tabela_nao_fifo.paginas = (pagina *) malloc(total_paginas * sizeof(pagina));
        for(i = 0; i < total_paginas; i++){
        tabela_nao_fifo.paginas[i].quadro = -1;
        tabela_nao_fifo.paginas[i].segunda_chance = false;
        }
    }
    
    quadro quadros_memoria[total_paginas];//esta sera a estrutura responsavel por simular os quadros que estarao na memoria
    //inicializo atributos dos quadros

    for(i = 0; i < total_paginas; i++){
        quadros_memoria[i].esta_na_memoria = false;
    }
    for(i = 0; i < total_paginas; i++){
        quadros_memoria[i].esta_na_memoria = false;
    }

    unsigned int endereco;//endereco lido em uma linha do arquivo
    char operacao;//operacao descrita em uma linha do arquivo
    int tamPaginaBytes = tamanho_paginas * pow(2, 10); //tamanho da pagina em bytes

    //Pego o numero maximo de bits que podem ser usados para identificar as paginas(algoritmo retirado da especificacao deste trabalho) 
    unsigned s, tmp;
    tmp = tamPaginaBytes;
    s = 0;
    while (tmp>1) {
        tmp = tmp>>1;
        s++;
    }
    s = 32u - s;

    printf("valor de s: %u\n", s);

    unsigned int indice;
    unsigned int miss = 0;
    unsigned int hit = 0;
    unsigned int escritas = 0;

    printf("Executando o simulador...\n");  

    clock_t inicio;
    inicio = clock();
    int contador_clock = 0;

    while(fscanf(arquivo,"%x %c\n", &endereco, &operacao) != EOF){
        contador_clock++;

        unsigned int numero_pagina_acessada = endereco >> s;

        if(strcmp(nome_algoritmo, "fifo") == 0){

        }else
        if(strcmp(nome_algoritmo, "lru") == 0){

        } else
        if(strcmp(nome_algoritmo, "2a") == 0){  

        } else
        if(strcmp(nome_algoritmo, "new") == 0){
    }



    printf("Arquivo de entrada: %s\n", nome_arquivo);
    printf("Tamanho da memoria: %d KB\n", tamanho_memoria);
    printf("Tamanho das páginas: %d KB\n", tamanho_paginas);
    printf("Tamanho da tabela: %d KB\n", tamanho_tabela);
    printf("Técnica de reposição: %s\n", nome_algoritmo);    


    clock_t fim = clock();

    double tempoExecucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
    
    FILE *arquivo_log = fopen(nome_arquivo, "r");

    if (arquivo_log == NULL){        
        printf("Error: Arquivo %s não encontrado.\n", nome_arquivo);
        return;
    }

    if(strcmp(nome_algoritmo, "fifo") == 0){
        Elemento* i_elemento;
        i_elemento = tabela_fifo->inicio;

        while(i_elemento != NULL){
        printf("Numero da pagina: %u | Ultimo endereco acessado: %u | bit de controle(pagina suja): %d\n",
                i_elemento->page.numero_pagina, 
                i_elemento->page.ultimo_endereco_acessado, 
                i_elemento->page.suja ? 1 : 0);

        i_elemento = i_elemento->seguinte;
        }
    }
    else
    if(strcmp(nome_algoritmo, "lru") == 0 || strcmp(nome_algoritmo, "2a") == 0 || strcmp(nome_algoritmo, "new") == 0){
        int i_pagina;
        for(i_pagina = 0; i_pagina < total_paginas; i_pagina++){
        //se a pagina acessada tem um quadro na memoria
        if(tabela_nao_fifo.paginas[i_pagina].quadro != -1){
            printf("Numero da pagina: %u | Ultimo endereco acessado: %u | bit de controle(pagina suja): %d\n",
                tabela_nao_fifo.paginas[i_pagina].numero_pagina, 
                tabela_nao_fifo.paginas[i_pagina].ultimo_endereco_acessado, 
                tabela_nao_fifo.paginas[i_pagina].suja ? 1 : 0);
        }
        }
    }

    return 0;   
};
