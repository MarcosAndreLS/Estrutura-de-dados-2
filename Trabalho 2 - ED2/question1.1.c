#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>


#define RED 1
#define BLACK 0

typedef struct artista
{
    char nome[50];
}Artista;

typedef struct arvartista
{
    Artista artista;
    struct arvartista *esq, *dir;
    int cor;
}ArvArtista;

int cor_artista(ArvArtista *raiz)
{
    if (raiz == NULL)
        return BLACK;
    else
        return raiz->cor;
}

void trocaCor_artista(ArvArtista *raiz)
{
    raiz->cor = !raiz->cor;
    if (raiz->esq != NULL)
        raiz->esq->cor = !raiz->esq->cor;
    if(raiz->dir != NULL)
        raiz->dir->cor = !raiz->dir->cor;
}

void rotacionaEsquerdaArtista(ArvArtista **A)
{
    ArvArtista *B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = *A;
    B->cor = (*A)->cor;
    (*A)->cor = RED;
    *A = B;
}

void rotacionaDireitaArtista(ArvArtista **A)
{
    ArvArtista *B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    B->cor = (*A)->cor;
    (*A)->cor = RED;
    *A = B;
}

void move2EsqREDArtista(ArvArtista **raiz)
{
    trocaCor_artista(*raiz);
    if (cor_artista((*raiz)->dir->esq) == RED)
    {
        rotacionaDireitaArtista(&(*raiz)->dir);
        rotacionaEsquerdaArtista(&(*raiz));
        trocaCor_artista(*raiz);
    }
}

void move2DirREDArtista(ArvArtista **raiz)
{
    trocaCor_artista(*raiz);
    if (cor_artista((*raiz)->esq->esq) == RED)
    {
        rotacionaDireitaArtista(&(*raiz));
        trocaCor_artista(*raiz);
    }
}

void balancear_artista(ArvArtista **raiz)
{
    if (cor_artista((*raiz)->dir) == RED)
        rotacionaEsquerdaArtista(raiz);
    if((*raiz)->esq != NULL && cor_artista((*raiz)->esq) == RED && cor_artista((*raiz)->esq->esq) == RED)
        rotacionaDireitaArtista(raiz);
    if (cor_artista((*raiz)->esq) == RED && cor_artista((*raiz)->dir) == RED)
        trocaCor_artista(*raiz);
    
}

ArvArtista *removerMenor(ArvArtista *raiz)
{
    if ((raiz->esq) == NULL)
    {
        free(raiz);
        return raiz;
    }
    if (cor_artista(raiz->esq) == BLACK && cor_artista(raiz->esq->esq) == BLACK)
        move2EsqREDArtista(&raiz);

    removerMenor(raiz->esq);

    balancear_artista(&raiz);

    return raiz;
}

ArvArtista *procuraMenor(ArvArtista *atual)
{
    ArvArtista *no1 = atual;
    ArvArtista *no2 = atual->esq;
    while (no2 != NULL)
    {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

ArvArtista *inserir_artista(ArvArtista *raiz, Artista a, int *resp)
{
    if (raiz == NULL)
    {
        ArvArtista *novo;
        novo = (ArvArtista*)malloc(sizeof(ArvArtista));
        if(novo == NULL)
        {
            *resp = 0;
            return NULL;
        }
        novo->artista = a;
        novo->cor = RED;
        novo->dir = NULL;
        novo->esq = NULL;
        *resp = 1;
        return novo;
    }
    if(strcmp(a.nome, raiz->artista.nome) == 0)
        *resp = 0;
    else
    {
        if (strcmp(a.nome, raiz->artista.nome) < 0)
            raiz->esq = inserir_artista(raiz->esq, a, resp);
        else
            raiz->dir = inserir_artista(raiz->dir, a, resp);  
    }
    if (cor_artista(raiz->dir) == RED && cor_artista(raiz->esq) == BLACK)
        rotacionaEsquerdaArtista(&raiz);
    if (cor_artista(raiz->esq) == RED && cor_artista(raiz->esq->esq) == RED)
        rotacionaDireitaArtista(&raiz);
    if(cor_artista(raiz->dir) == RED && cor_artista(raiz->esq) == RED)
        trocaCor_artista(raiz);

    return raiz;
        
} 

ArvArtista **buscaTestes(ArvArtista **tree, char *codigo)
{
    ArvArtista **NO;
    NO = NULL;
    if (*tree != NULL)
    {
        if (strcmp(codigo, (*tree)->artista.nome) == 0)
        {
            NO = tree;
        }
        else
        {
            if (strcmp(codigo, (*tree)->artista.nome) < 0)
            {
                NO = buscaTestes(&(*tree)->esq, codigo);
            }
            else
            {
                NO = buscaTestes(&(*tree)->dir, codigo);
            }
        }
    }
    return NO;
}

int main()
{

    ArvArtista *tree = NULL;
    double elapsed_nanos;
    double soma = 0;

    

   
    char *artistas[30] = {
        "Ana", "Beatriz", "Carlos", "Daniel", "Eduardo", "Fernanda", "Gabriel", "Helena", "Igor",
        "Julia", "Kleber", "Laura", "Marcos", "Natalia", "Otavio", "Patricia", "Quirino", "Rafael",
        "Sabrina", "Tiago", "Ursula", "Vitor", "Wagner", "Ximena", "Yasmin", "Zacarias",
        "Alice", "Bruno", "Cecilia", "Diego"};

    
    for (int i = 0; i < 30; i++)
    {
        Artista artista1;
        strncpy(artista1.nome, artistas[i], sizeof(artista1.nome) - 1);
        artista1.nome[sizeof(artista1.nome) - 1] = '\0';
        

        int resp = 0;
        tree = inserir_artista(tree, artista1, &resp);
       
        LARGE_INTEGER start, end, frequency;

        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);

        
        buscaTestes(&tree, artistas[i]);

        QueryPerformanceCounter(&end);

        
        elapsed_nanos = ((end.QuadPart - start.QuadPart) * 1.0 / frequency.QuadPart) * 1000000000;
        //printf("Tempo de execucao: %.2f nanossegundos\n", elapsed_nanos);
        soma += elapsed_nanos;

       
    }

    printf("Tempo total de execucao: %.2f nanossegundos\n", soma);
    printf("Media da soma total de execucao: %.2f nanossegundos\n", soma/30);

    return 0;
}