#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct arvtemporada ArvTemporada; 
typedef struct arvserie ArvSerie; 
typedef struct serie Serie;
typedef struct temporada Temporada;




ArvSerie* criaArvSerie();
ArvTemporada* criaArvTemp();

void inserirArvSerie(ArvSerie **raiz, Serie s);
ArvTemporada* buscaArvTemp(ArvTemporada *raiz, int temporada);


Serie ler_serie();
Temporada ler_temporada(int temp);


typedef struct serie
{
    int codigo;
    int num_temporadas;
    char titulo[50];
}Serie;

typedef struct temporada
{
    int num_temporada;
    int ano;
    int quantidade_ep;
    char titulo_temp[50];
}Temporada;




typedef struct arvserie
{
    Serie serie;
    ArvTemporada *arvTemp;
    struct arvserie *esq, *dir;
}ArvSerie;

typedef struct arvtemporada
{
    Temporada temp; 
    struct arvtemporada *esq, *dir;
}ArvTemporada;


Serie ler_serie()
{
    Serie s;
    
    s.codigo = rand()%100 + 1;
    
    s.num_temporadas = rand()%4+1;
    
    strcpy(s.titulo, "oi");

    return s;
}


ArvSerie* criaArvSerie()
{
    return NULL;
}

void inserirArvSerie(ArvSerie **raiz, Serie s)
{
    if (*raiz == NULL)
    {
        *raiz = (ArvSerie*)malloc(sizeof(ArvSerie));
        (*raiz)->esq = NULL;
        (*raiz)->dir = NULL;
        (*raiz)->arvTemp = criaArvTemp();
        (*raiz)->serie = s;
    }else{
        if ((*raiz)->serie.codigo > s.codigo)
            inserirArvSerie(&(*raiz)->esq, s);
        else if ((*raiz)->serie.codigo < s.codigo)
            inserirArvSerie(&(*raiz)->dir, s);
    }
}



ArvTemporada* criaArvTemp()
{
    return NULL;
}



ArvTemporada* buscaArvTemp(ArvTemporada *raiz, int temporada)
{
    while(raiz)
    {
        if (raiz->temp.num_temporada > temporada)
            raiz = raiz->esq;
        else if (raiz->temp.num_temporada < temporada)
            raiz = raiz->dir;
        else
            return raiz;
    }

    return NULL;
}


void liberarArvTemp(ArvTemporada *raiz) {
    if (raiz == NULL) {
        return;
    }
    liberarArvTemp(raiz->esq);
    liberarArvTemp(raiz->dir);
    free(raiz);
}


void liberarArvSerie(ArvSerie *raiz) {
    if (raiz == NULL) {
        return;
    }
    liberarArvSerie(raiz->esq);
    liberarArvSerie(raiz->dir);
    liberarArvTemp(raiz->arvTemp); 
    free(raiz);
}

int main() 
{   
    ArvSerie *raiz_s;
    for (int i = 0; i < 30; i++)
    {
        raiz_s = criaArvSerie();
        clock_t inicio, fim;
        double tempo;
        double media_busca = 0, media_insercao = 0;
        for (int j = 1; j <= 30000; j++)
        {
            inicio = clock();
            Serie nova_serie = ler_serie();
            inserirArvSerie(&raiz_s, nova_serie);
            fim = clock();
            tempo = (((double)(fim - inicio)) / CLOCKS_PER_SEC) * 1e9;
            media_insercao += tempo;
        }
        for (int j = 1; j <= 30000; j++)
        {
            inicio = clock();
            buscaArvTemp(raiz_s->arvTemp, 5);
            fim = clock();
            tempo = (((double)(fim - inicio)) / CLOCKS_PER_SEC) * 1e9;
            media_busca += tempo;
        }
        printf("Insercao: %.2lf nanossegundos\n", media_insercao/30000);
        printf("Busca: %.2lf nanossegundos\n",  media_busca/30000);
        printf("--------------------------------\n");
        liberarArvSerie(raiz_s);
    }
    
    return 0;
}
