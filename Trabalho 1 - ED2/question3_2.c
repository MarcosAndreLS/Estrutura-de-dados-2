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
ArvTemporada* buscaArvTemp(ArvTemporada *raiz, int temporada);


Serie ler_serie();

void inserirArvSerie(ArvSerie **raiz, Serie s);

int alturaNOArvSerie(ArvSerie* raiz);
int fbArvSerie(ArvSerie* raiz);
int maiorArvSerie(int a, int b);
void rotacaoDEDArvSerie(ArvSerie **raiz);
void rotacaoDDEArvSerie(ArvSerie **raiz);
void rotacaoSDArvSerie(ArvSerie **raiz);
void rotacaoSEArvSerie(ArvSerie **raiz);




typedef struct serie
{
    int codigo;
    int num_temporadas;
    char titulo[50];
}Serie;



typedef struct temporada
{
    int num_temporada;
    int quantidade_ep;
    int ano;
    char titulo_temp[50];
}Temporada;



typedef struct arvserie
{
    Serie serie;
    ArvTemporada *arvTemp;
    int alt;
    struct arvserie *esq, *dir;
}ArvSerie;

typedef struct arvtemporada
{
    Temporada temp;
    int alt;
    struct arvtemporada *esq, *dir;
}ArvTemporada;




Serie ler_serie()
{
    Serie s;
    
    s.codigo = rand()%100 + 1;
    
    s.num_temporadas = rand()%5 + 1;
    
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
        (*raiz)->serie = s;
        (*raiz)->alt = 0;
        (*raiz)->esq = NULL;
        (*raiz)->dir = NULL;
        (*raiz)->arvTemp = criaArvTemp(); 
    }
    else if (s.codigo < (*raiz)->serie.codigo)
    {
        inserirArvSerie(&(*raiz)->esq, s);
    }
    else if (s.codigo > (*raiz)->serie.codigo)
    {
        inserirArvSerie(&(*raiz)->dir, s);
    }

    (*raiz)->alt = maiorArvSerie(alturaNOArvSerie((*raiz)->esq), alturaNOArvSerie((*raiz)->dir)) + 1;

    int fb = fbArvSerie(*raiz);
    if (fb == 2)
    {
        if (fbArvSerie((*raiz)->esq) == 1)
            rotacaoSDArvSerie(raiz);
        else
            rotacaoDEDArvSerie(raiz);
    }
    else if (fb == -2)
    {
        if (fbArvSerie((*raiz)->dir) == -1)
            rotacaoSEArvSerie(raiz);
        else
            rotacaoDDEArvSerie(raiz);
    }
}

int alturaNOArvSerie(ArvSerie* raiz)
{
    if (raiz == NULL) 
        return -1;
    else 
        return raiz->alt;
}

int fbArvSerie(ArvSerie* raiz)
{
    return alturaNOArvSerie(raiz->esq) - alturaNOArvSerie(raiz->dir);
}

int maiorArvSerie(int a, int b) 
{
    return (a > b) ? a : b;
}

void rotacaoSDArvSerie(ArvSerie **raiz)
{
    ArvSerie *aux = (*raiz)->esq;
    (*raiz)->esq = aux->dir;
    aux->dir = *raiz;
    (*raiz)->alt = maiorArvSerie(alturaNOArvSerie((*raiz)->esq), alturaNOArvSerie((*raiz)->dir)) + 1;
    aux->alt = maiorArvSerie(alturaNOArvSerie(aux->esq), (*raiz)->alt) + 1;
    *raiz = aux;
}

void rotacaoSEArvSerie(ArvSerie **raiz)
{
    ArvSerie *aux = (*raiz)->dir;
    (*raiz)->dir = aux->esq;
    aux->esq = *raiz;
    (*raiz)->alt = maiorArvSerie(alturaNOArvSerie((*raiz)->esq), alturaNOArvSerie((*raiz)->dir)) + 1;
    aux->alt = maiorArvSerie(alturaNOArvSerie(aux->dir), (*raiz)->alt) + 1;
    *raiz = aux;
}

void rotacaoDEDArvSerie(ArvSerie **raiz)
{
    rotacaoSEArvSerie(&(*raiz)->esq);
    rotacaoSDArvSerie(raiz);
}

void rotacaoDDEArvSerie(ArvSerie **raiz)
{
    rotacaoSDArvSerie(&(*raiz)->dir);
    rotacaoSEArvSerie(raiz);
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
            int temp = rand()%5 + 1;
            buscaArvTemp(raiz_s->arvTemp, temp);
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



