#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Prototypes */

typedef struct artista Artista;
typedef struct album Album;
typedef struct arvartista ArvArtista;
typedef struct arvalbum ArvAlbum;
/* Structs infos */

typedef struct artista
{
    char nome_artista[50];
    char estilo[50];
    int num_albuns;
    
} Artista;

typedef struct album
{
    char titulo[50];
    int ano;
    int quantidade_musica;
}Album;

typedef struct musica
{
    char nome_musica[50];
    int minutos;
    struct musica *prox;
}Musica;


/* Structs arvores */

typedef struct arvartista
{
    Artista info_1, info_2;
    int Nkeys;
    ArvAlbum *arvAlbum;
    struct arvartista *esq, *cen, *dir;
} ArvArtista;

typedef struct arvalbum
{
    Album info_1, info_2;
    Musica *musica;
    int Nkeys;
    struct arvalbum *esq, *cen,*dir;
}ArvAlbum;

/* Function Declarations */

Artista ler_artista();
ArvArtista *criaArvArtista();
int ehFolhaArtista(ArvArtista *raiz);
void criaNoArtista(ArvArtista **no, Artista a, ArvArtista *esq, ArvArtista *cen);
void adicionaNoArtista(ArvArtista **no, Artista info, ArvArtista *filho);
void quebraNoArtista(ArvArtista **no, Artista info, Artista *sobe, ArvArtista **no_maior, ArvArtista *filho);
ArvArtista *insereArvArtista(ArvArtista **pai, ArvArtista **raiz, Artista info, Artista *sobe);
void imprimirArvArtista(ArvArtista *raiz);
void liberaNoArtista(ArvArtista **no);
int removeEsqFolhaArtista(ArvArtista **raiz, ArvArtista **pai);
int removeCenFolhaArtista(ArvArtista **raiz, ArvArtista **pai);
void removeDirFolhaArtista(ArvArtista **raiz, ArvArtista **pai);
int removeFolhaArtista(ArvArtista **pai, ArvArtista **raiz, char *nome);
int removeNoFilhoFolhaArtista(ArvArtista **raiz, char *nome);
int balanceiaArvArtista(ArvArtista **raiz, int desbalanceamento);
int removeMenorNoArtista(ArvArtista **pai_aux, ArvArtista **no, Artista *info_sobe);
int removerArtista(ArvArtista **pai, ArvArtista **raiz, char *nome);
ArvArtista *buscaArvArtista(ArvArtista **raiz, char *nome);

Album ler_album();
ArvAlbum *criaArvAlbum();
int ehFolhaAlbum(ArvAlbum *raiz);
void criaNoAlbum(ArvAlbum **no, Album a, ArvAlbum *esq, ArvAlbum *cen);
void adicionaNoAlbum(ArvAlbum **no, Album info, ArvAlbum *filho);
void quebraNoAlbum(ArvAlbum **no, Album info, Album *sobe, ArvAlbum **no_maior, ArvAlbum *filho);
ArvAlbum *insereArvAlbum(ArvAlbum **pai, ArvAlbum **raiz, Album info, Album *sobe);
void imprimirArvAlbum(ArvAlbum *raiz);
void liberaNoAlbum(ArvAlbum **no);
int removeEsqFolhaAlbum(ArvAlbum **raiz, ArvAlbum **pai);
int removeCenFolhaAlbum(ArvAlbum **raiz, ArvAlbum **pai);
void removeDirFolhaAlbum(ArvAlbum **raiz, ArvAlbum **pai);
int removeFolhaAlbum(ArvAlbum **pai, ArvAlbum **raiz, char *nome);
int removeNoFilhoFolhaAlbum(ArvAlbum **raiz, char *nome);
int balanceiaArvAlbum(ArvAlbum **raiz, int desbalanceamento);
int removeMenorNoAlbum(ArvAlbum **pai_aux, ArvAlbum **no, Album *info_sobe);
int removerAlbum(ArvAlbum **pai, ArvAlbum **raiz, char *nome);
ArvAlbum *buscaArvAlbum(ArvAlbum **raiz, char *nome);
Musica ler_musica();
Musica *criarLista();
void inserirMusica(ArvAlbum *lista);
Musica *busca_musica(ArvAlbum *lista, char *nome);
void excluir_musica(ArvAlbum *lista, char *nome);
void imprimir_todas_musicas(ArvAlbum *lista);
void imprimir_uma_musica(Musica* m);

/* Function Definitions */

Artista ler_artista()
{
    Artista art;

    fflush(stdin);
    printf("Informe o nome do artista: ");
    scanf(" %[^\n]s", art.nome_artista);
    fflush(stdin);
    printf("Informe o estilo musical: ");
    scanf(" %[^\n]s", art.estilo);
    fflush(stdin);
    art.num_albuns = 0;
    fflush(stdin);
    return art;
}

ArvArtista *criaArvArtista()
{
    return NULL;
}

int ehFolhaArtista(ArvArtista *raiz)
{
    int folha = 0;
    if (raiz != NULL)
        if (raiz->esq == NULL)
            folha = 1;
    return folha;
}

void criaNoArtista(ArvArtista **no, Artista a, ArvArtista *esq, ArvArtista *cen)
{
    *no = (ArvArtista*)malloc(sizeof(ArvArtista));

    (*no)->info_1 = a;
    (*no)->arvAlbum = criaArvAlbum();
    (*no)->Nkeys = 1;
    (*no)->esq = esq;
    (*no)->cen = cen;
    (*no)->dir = NULL;
}

void adicionaNoArtista(ArvArtista **no, Artista info, ArvArtista *filho)
{
    if (strcmp(info.nome_artista, (*no)->info_1.nome_artista) > 0)
    {
        (*no)->info_2 = info;
        (*no)->dir = filho;
    }else{
        (*no)->info_2 = (*no)->info_1;
        (*no)->info_1 = info;
        (*no)->dir = (*no)->cen;
        (*no)->cen = filho;
    }
    (*no)->Nkeys = 2;
}

void quebraNoArtista(ArvArtista **no, Artista info, Artista *sobe, ArvArtista **no_maior, ArvArtista *filho)
{
    if (strcmp(info.nome_artista, (*no)->info_1.nome_artista) < 0)
    {
        *sobe = (*no)->info_1;
        (*no)->info_1 = info;
        criaNoArtista(no_maior, (*no)->info_2, (*no)->cen, (*no)->dir);
        (*no)->cen = filho;
    }else if (strcmp(info.nome_artista, (*no)->info_2.nome_artista) < 0)
    {
       *sobe = info;
       criaNoArtista(no_maior, (*no)->info_2, filho, (*no)->dir);
    }else{
        *sobe = (*no)->info_2;
        criaNoArtista(no_maior, info, (*no)->dir, filho);
    }
    (*no)->dir = NULL;
    (*no)->Nkeys = 1;
    
}

ArvArtista *insereArvArtista(ArvArtista **pai, ArvArtista **raiz, Artista info, Artista *sobe)
{
    ArvArtista *no_maior = NULL;
    if (*raiz == NULL)
        criaNoArtista(raiz, info, NULL, NULL);
    else{
        if (ehFolhaArtista(*raiz) == 1)
        {
            if ((*raiz)->Nkeys == 1)
                adicionaNoArtista(raiz, info, NULL);
            else{
                quebraNoArtista(raiz, info, sobe, &no_maior, NULL);
                if (*pai == NULL)
                {
                    ArvArtista *aux;
                    criaNoArtista(&aux, *sobe, *raiz, no_maior);
                    *raiz = aux;
                    no_maior = NULL;
                }    
            } 
        }else{
            if (strcmp(info.nome_artista, (*raiz)->info_1.nome_artista) < 0)
                no_maior = insereArvArtista(raiz, &(*raiz)->esq, info, sobe);
            else if(strcmp(info.nome_artista, (*raiz)->info_2.nome_artista) > 0 && (*raiz)->Nkeys == 2)
                no_maior = insereArvArtista(raiz, &(*raiz)->dir, info, sobe);
            else
                no_maior = insereArvArtista(raiz, &(*raiz)->cen, info, sobe);
            if (no_maior != NULL)
            {
                if ((*raiz)->Nkeys == 1)
                {
                    adicionaNoArtista(raiz, *sobe, no_maior);
                    no_maior = NULL;
                }else{
                    Artista sobe2;
                    ArvArtista *no_maior_2;

                    quebraNoArtista(raiz, *sobe, &sobe2, &no_maior_2, no_maior);
                    if (*pai == NULL)
                    {
                        ArvArtista *aux;
                        criaNoArtista(&aux, sobe2, *raiz, no_maior_2);
                        *raiz = aux;
                        no_maior = NULL;
                    }else{
                        *sobe = sobe2;
                        no_maior = no_maior_2;
                    }
                    
                }
                
            }
            
        }
    }    
    return no_maior;
}

void imprimirArvArtista(ArvArtista *raiz)
{
    if (raiz != NULL)
    {
        imprimirArvArtista(raiz->esq);
        if (raiz->Nkeys == 1)
            printf("Nome do artista: %s\nEstilo musical: %s\nQuantidade de albuns: %d\n", raiz->info_1.nome_artista, raiz->info_1.estilo, raiz->info_1.num_albuns);
        else if (raiz->Nkeys == 2)
        {
            printf("Nome do artista: %s\nEstilo musical: %s\nQuantidade de albuns: %d\n", raiz->info_1.nome_artista, raiz->info_1.estilo, raiz->info_1.num_albuns);
            printf("Nome do artista: %s\nEstilo musical: %s\nQuantidade de albuns: %d\n", raiz->info_2.nome_artista, raiz->info_2.estilo, raiz->info_2.num_albuns);
        }  
        imprimirArvArtista(raiz->cen);
        imprimirArvArtista(raiz->dir);
    }
}
/*----------------------------------------------------------------*/

void liberaNoArtista(ArvArtista **no)
{
    ArvArtista *aux;

    aux = *no;
    *no = NULL;
    free(aux);
}

int removeEsqFolhaArtista(ArvArtista **raiz, ArvArtista **pai)
{
    int flag = 0;
    (**raiz).info_1 = (**pai).info_1;

    if ((**pai).cen->Nkeys == 2)
    {
        (**pai).info_1 = (**pai).cen->info_1;
        (**pai).cen->info_1 = (**pai).cen->info_2;
        (**pai).cen->Nkeys = 1;
    }else if((**pai).Nkeys == 2){
        (**pai).info_1 = (**pai).cen->info_1;
        (**pai).cen->info_1 = (**pai).info_2;
        if ((**pai).dir->Nkeys == 2)
        {
            (**pai).info_2 = (**pai).dir->info_1;
            (**pai).dir->info_1 = (**pai).dir->info_2;
            (**pai).dir->Nkeys = 1;
        }
        else{
            adicionaNoArtista(&(**pai).cen, (**pai).dir->info_1, NULL);
            liberaNoArtista(&(**pai).dir);
            (**pai).Nkeys = 1;
        }
        
    }else{
        adicionaNoArtista(pai, (**pai).cen->info_1, NULL);
        (**pai).Nkeys = 2;
        liberaNoArtista(&(**pai).esq);
        liberaNoArtista(&(**pai).cen);
        flag = 1;
    }

    return flag;
}

int removeCenFolhaArtista(ArvArtista **raiz, ArvArtista **pai)
{
    int flag = 0;

    if ((**pai).esq->Nkeys == 2)
    {
        (**raiz).info_1 = (**pai).info_1;
        (**pai).info_1 = (**pai).esq->info_2;
        (**pai).esq->Nkeys = 1;
    }else if ((**pai).Nkeys == 2)
    {
        (**raiz).info_1 = (**pai).info_2;
        if ((**pai).dir->Nkeys == 2)
        {
            (**pai).info_2 = (**pai).dir->info_1;
            (**pai).dir->info_1 = (**pai).dir->info_2;
            (**pai).dir->Nkeys = 1;
        }else{
            adicionaNoArtista(&(**pai).cen, (**pai).dir->info_1, NULL);
            liberaNoArtista(&(**pai).dir);
            (**pai).Nkeys = 1;
        }
    }else{
        adicionaNoArtista(pai, (**pai).esq->info_1, NULL);
        (**pai).Nkeys = 2;
        liberaNoArtista(&(**pai).esq);
        liberaNoArtista(&(**pai).dir);
        flag = 1;
    }

    return flag;    
}

void removeDirFolhaArtista(ArvArtista **raiz, ArvArtista **pai)
{
    (**raiz).info_1 = (**pai).info_2;
    if ((**pai).cen->Nkeys == 2)
    {
        (**pai).info_2 = (**pai).cen->info_2;
        (**pai).cen->Nkeys = 1;
    }else if ((**pai).esq->Nkeys == 2)
    {
        Artista aux = (**pai).cen->info_1;
        (**pai).cen->info_1 = (**pai).info_1;
        (**pai).info_1 = (**pai).esq->info_2;
        (**pai).info_2 = aux;
        (**pai).esq->Nkeys = 1;
    }else{
        adicionaNoArtista(&(**pai).cen, (**pai).info_2, NULL);
        (**pai).Nkeys = 1;
        liberaNoArtista(&(**pai).dir);
    } 
}

int removeFolhaArtista(ArvArtista **pai, ArvArtista **raiz, char *nome)
{
    int balanceamento = 0;
    if ((*raiz)->Nkeys == 2)
    {
        if (strcmp(nome, (*raiz)->info_1.nome_artista) == 0)
            (*raiz)->info_1 = (*raiz)->info_2;
        (*raiz)->Nkeys = 1;
    }else if (*pai == NULL)
    {
        liberaNoArtista(raiz);
    }else{
        if (*raiz == (**pai).esq)
            balanceamento = removeEsqFolhaArtista(raiz, pai);
        else if (*raiz == (**pai).cen)
            balanceamento = removeCenFolhaArtista(raiz, pai);
        else if (*raiz == (**pai).dir)
            removeDirFolhaArtista(raiz, pai);
    }
    
    return balanceamento;
}

int removeNoFilhoFolhaArtista(ArvArtista **raiz, char *nome)
{
    int balanceamento = 0;
    if (strcmp(nome, (**raiz).info_1.nome_artista) == 0)
    {
        if ((**raiz).cen->Nkeys == 2)
        {
            (**raiz).info_1 = (**raiz).cen->info_1;
            (**raiz).cen->info_1 = (**raiz).cen->info_2;
            (**raiz).Nkeys = 1;
        }else if ((**raiz).esq->Nkeys == 2)
        {
            (**raiz).info_1 = (**raiz).esq->info_2;
            (**raiz).esq->Nkeys = 1;
        }else if ((**raiz).Nkeys == 2)
        {
            (**raiz).info_1 = (**raiz).cen->info_1;
            (**raiz).cen->info_1 = (**raiz).info_2;
            if ((**raiz).dir->Nkeys == 2)
            {
                (**raiz).info_2 = (**raiz).dir->info_1;
                (**raiz).dir->info_1 = (**raiz).dir->info_2;
                (**raiz).dir->Nkeys = 1;
            }else{
                adicionaNoArtista(&(**raiz).cen, (**raiz).dir->info_1, NULL);
                (**raiz).Nkeys = 1;
                liberaNoArtista(&(**raiz).dir);
            }
            
        }else{
            ArvArtista *aux;
            adicionaNoArtista(&(**raiz).esq, (**raiz).cen->info_1, NULL);
            aux = (**raiz).esq;
            liberaNoArtista(&(**raiz).cen);
            liberaNoArtista(raiz);
            *raiz = aux;
            balanceamento = 1;
        }
    }else{
        if ((**raiz).dir->Nkeys == 2)
        {
            (**raiz).info_2 = (**raiz).dir->info_1;
            (**raiz).dir->info_1 = (**raiz).dir->info_2;
            (**raiz).dir->Nkeys = 1;
        }else if ((**raiz).cen->Nkeys == 2)
        {
            (**raiz).info_2 = (**raiz).cen->info_2;
            (**raiz).cen->Nkeys = 1;
        }else if ((**raiz).esq->Nkeys == 2)
        {
            (**raiz).info_2 = (**raiz).cen->info_1;
            (**raiz).cen->info_1 = (**raiz).info_1;
            (**raiz).info_1 = (**raiz).esq->info_2;
            (**raiz).esq->Nkeys = 1;
        }else{
            adicionaNoArtista(&(**raiz).cen, (**raiz).dir->info_1, NULL);
            (**raiz).Nkeys = 1;
            liberaNoArtista(&(**raiz).dir);
        }
    }
    
    return balanceamento;
}

int balanceiaArvArtista(ArvArtista **raiz, int desbalanceamento)
{
    Artista sobe;
    ArvArtista *no_maior;
    ArvArtista *aux;

    if (desbalanceamento == -1)
    {
        aux = (*raiz)->cen->esq;
        (*raiz)->cen->esq = (*raiz)->esq;
        if ((*raiz)->cen->Nkeys == 1)
        {
            adicionaNoArtista(&(*raiz)->cen, (*raiz)->info_1, aux);
            (*raiz)->esq = NULL;
            if ((*raiz)->Nkeys == 1)
            {
                aux = *raiz;
                *raiz = (*raiz)->cen;
                liberaNoArtista(&aux);
            }else{
                (*raiz)->info_1 = (*raiz)->info_2;
                (*raiz)->esq = (*raiz)->cen;
                (*raiz)->cen = (*raiz)->dir;
                (*raiz)->dir = NULL;
                (*raiz)->Nkeys = 1;
            }
            
        }else{
            quebraNoArtista(&(*raiz)->cen, (*raiz)->info_1, &sobe, &no_maior, aux);
            (*raiz)->info_1 = sobe;
            (*raiz)->esq = (*raiz)->cen;
            (*raiz)->cen = no_maior;
        }   
    }else if (desbalanceamento == 0)
    {
        if ((*raiz)->esq->Nkeys == 1)
        {
            adicionaNoArtista(&(*raiz)->esq, (*raiz)->info_1, (*raiz)->cen);
            (*raiz)->cen = NULL;
            if ((*raiz)->Nkeys == 1)
            {
                aux = *raiz;
                *raiz = (*raiz)->esq;
                liberaNoArtista(&aux);
            }else{
                (*raiz)->info_1 = (*raiz)->info_2;
                (*raiz)->cen = (*raiz)->dir;
                (*raiz)->dir = NULL;
                (*raiz)->Nkeys = 1;
            }
            
        }else{
            quebraNoArtista(&(*raiz)->esq, (*raiz)->info_1, &sobe, &no_maior, (*raiz)->cen);
            (*raiz)->info_1 = sobe;
            (*raiz)->cen = no_maior;
        }
    }else{
        if ((*raiz)->cen->Nkeys == 1)
        {
            adicionaNoArtista(&(*raiz)->cen, (*raiz)->info_2, (*raiz)->dir);
            (*raiz)->Nkeys = 1;
            (*raiz)->dir = NULL;
        }else{
            quebraNoArtista(&(*raiz)->cen, (*raiz)->info_2, &sobe, &no_maior, (*raiz)->dir);
            (*raiz)->info_2 = sobe;
            (*raiz)->dir = no_maior;
        }
    }
    
    return 0;
}

int removeMenorNoArtista(ArvArtista **pai_aux, ArvArtista **no, Artista *info_sobe)
{
    int balanceamento = 0;
    if ((*no)->esq != NULL)
        balanceamento = removeMenorNoArtista(no, &(*no)->esq, info_sobe);
    else{
        *info_sobe = (*no)->info_1;
        balanceamento = removeFolhaArtista(pai_aux, no, (*no)->info_1.nome_artista);
    }
    return balanceamento;
}

int removerArtista(ArvArtista **pai, ArvArtista **raiz, char *nome)
{
    int balanceamento = 0;
    if (*raiz != NULL)
    {
        if ((strcmp(nome, (*raiz)->info_1.nome_artista) == 0) || ((*raiz)->Nkeys == 2 && strcmp(nome, (*raiz)->info_2.nome_artista) == 0))
        {
            
            if (ehFolhaArtista(*raiz) == 1)
                balanceamento = removeFolhaArtista(pai, raiz, nome);
            else if (((ehFolhaArtista((*raiz)->esq) == 1) && ehFolhaArtista((*raiz)->cen) == 1 && ehFolhaArtista((*raiz)->dir) == 1) || ((ehFolhaArtista((*raiz)->esq) == 1) && ehFolhaArtista((*raiz)->cen) == 1 && (*raiz)->Nkeys == 1 ))
                balanceamento = removeNoFilhoFolhaArtista(raiz, nome); 
            else{
                ArvArtista *pai_aux = NULL;
                Artista info_sobe;
                if (strcmp(nome, (*raiz)->info_1.nome_artista) == 0)
                {
                    balanceamento = removeMenorNoArtista(&pai_aux, &(*raiz)->cen, &info_sobe);
                    (*raiz)->info_1 = info_sobe;
                    if (balanceamento == 1)
                    {
                        balanceamento = balanceiaArvArtista(raiz, 0);
                    }   
                }else{
                    balanceamento = removeMenorNoArtista(&pai_aux, &(*raiz)->dir, &info_sobe);
                    (*raiz)->info_2 = info_sobe;
                    if (balanceamento == 1)
                    {
                        balanceamento = balanceiaArvArtista(raiz, 1);
                    }
                }
            }
        }
        else if (strcmp(nome,(*raiz)->info_1.nome_artista) < 0)
            balanceamento = removerArtista(raiz, &(*raiz)->esq, nome);
        else if (strcmp(nome,(*raiz)->info_2.nome_artista) > 0 && (*raiz)->Nkeys == 2)
            balanceamento = removerArtista(raiz, &(*raiz)->dir, nome);
        else
            balanceamento = removerArtista(raiz, &(*raiz)->cen, nome);
        if (balanceamento == 1 && *raiz != NULL && *pai != NULL)
        {
            if (*raiz == (**pai).esq)
                balanceamento = balanceiaArvArtista(pai, -1);
            else if(*raiz == (*pai)->cen)
                balanceamento = balanceiaArvArtista(pai, 0);
            else if(*raiz == (*pai)->dir)
                balanceamento = balanceiaArvArtista(pai, 1);
            
        }
        
    }
    return balanceamento;
}

ArvArtista *buscaArvArtista(ArvArtista **raiz, char *nome)
{
    ArvArtista *no = NULL;
    if (*raiz != NULL)
    {
        if (strcmp(nome, (*raiz)->info_1.nome_artista) == 0)
            no = *raiz;
        else if(strcmp(nome, (*raiz)->info_2.nome_artista) == 0)
            no = *raiz;
        else
        {
            if (strcmp(nome, (*raiz)->info_1.nome_artista) < 0)
                no = buscaArvArtista(&(*raiz)->esq, nome);
            else if (strcmp(nome, (*raiz)->info_2.nome_artista) < 0 || (*raiz)->Nkeys == 1)
                no = buscaArvArtista(&(*raiz)->cen, nome);
            else
                no = buscaArvArtista(&(*raiz)->dir, nome);
        }   
    }
    
    return no;
}



/*-------------------------------------------------------------------------------*/

Album ler_album() 
{
    Album album;
    fflush(stdin);
    printf("Informe o nome do album: ");
    scanf("%[^\n]s", album.titulo);
    fflush(stdin);
    printf("Informe o ano do album: ");
    scanf("%d", &album.ano);
    fflush(stdin);
    album.quantidade_musica = 0;

    return album;
}

ArvAlbum *criaArvAlbum()
{
    return NULL;
}

int ehFolhaAlbum(ArvAlbum *raiz)
{
    int folha = 0;
    if (raiz != NULL)
        if (raiz->esq == NULL)
            folha = 1;
    return folha;
}

void criaNoAlbum(ArvAlbum **no, Album a, ArvAlbum *esq, ArvAlbum *cen)
{
    *no = (ArvAlbum*)malloc(sizeof(ArvAlbum));

    (*no)->info_1 = a;
    (*no)->Nkeys = 1;
    (*no)->esq = esq;
    (*no)->cen = cen;
    (*no)->dir = NULL;
}

void adicionaNoAlbum(ArvAlbum **no, Album info, ArvAlbum *filho)
{
    if (strcmp(info.titulo, (*no)->info_1.titulo) > 0)
    {
        (*no)->info_2 = info;
        (*no)->dir = filho;
    }else{
        (*no)->info_2 = (*no)->info_1;
        (*no)->info_1 = info;
        (*no)->dir = (*no)->cen;
        (*no)->cen = filho;
    }
    (*no)->Nkeys = 2;
}

void quebraNoAlbum(ArvAlbum **no, Album info, Album *sobe, ArvAlbum **no_maior, ArvAlbum *filho)
{
    if (strcmp(info.titulo, (*no)->info_1.titulo) < 0)
    {
        *sobe = (*no)->info_1;
        (*no)->info_1 = info;
        criaNoAlbum(no_maior, (*no)->info_2, (*no)->cen, (*no)->dir);
        (*no)->cen = filho;
    }else if (strcmp(info.titulo, (*no)->info_2.titulo) < 0)
    {
       *sobe = info;
       criaNoAlbum(no_maior, (*no)->info_2, filho, (*no)->dir);
    }else{
        *sobe = (*no)->info_2;
        criaNoAlbum(no_maior, info, (*no)->dir, filho);
    }
    (*no)->dir = NULL;
    (*no)->Nkeys = 1;
    
}

ArvAlbum *insereArvAlbum(ArvAlbum **pai, ArvAlbum **raiz, Album info, Album *sobe)
{
    ArvAlbum *no_maior = NULL;
    if (*raiz == NULL)
        criaNoAlbum(raiz, info, NULL, NULL);
    else{
        if (ehFolhaAlbum(*raiz) == 1)
        {
            if ((*raiz)->Nkeys == 1)
                adicionaNoAlbum(raiz, info, NULL);
            else{
                quebraNoAlbum(raiz, info, sobe, &no_maior, NULL);
                if (*pai == NULL)
                {
                    ArvAlbum *aux;
                    criaNoAlbum(&aux, *sobe, *raiz, no_maior);
                    *raiz = aux;
                    no_maior = NULL;
                }    
            } 
        }else{
            if (strcmp(info.titulo, (*raiz)->info_1.titulo) < 0)
                no_maior = insereArvAlbum(raiz, &(*raiz)->esq, info, sobe);
            else if(strcmp(info.titulo, (*raiz)->info_2.titulo) > 0 && (*raiz)->Nkeys == 2)
                no_maior = insereArvAlbum(raiz, &(*raiz)->dir, info, sobe);
            else
                no_maior = insereArvAlbum(raiz, &(*raiz)->cen, info, sobe);
            if (no_maior != NULL)
            {
                if ((*raiz)->Nkeys == 1)
                {
                    adicionaNoAlbum(raiz, *sobe, no_maior);
                    no_maior = NULL;
                }else{
                    Album sobe2;
                    ArvAlbum *no_maior_2;

                    quebraNoAlbum(raiz, *sobe, &sobe2, &no_maior_2, no_maior);
                    if (*pai == NULL)
                    {
                        ArvAlbum *aux;
                        criaNoAlbum(&aux, sobe2, *raiz, no_maior_2);
                        *raiz = aux;
                        no_maior = NULL;
                    }else{
                        *sobe = sobe2;
                        no_maior = no_maior_2;
                    }
                    
                }
                
            }
            
        }
    }    
    return no_maior;
}

void imprimirArvAlbum(ArvAlbum *raiz)
{
    if (raiz != NULL)
    {
        imprimirArvAlbum(raiz->esq);
        
        printf("Titulo: %s\nAno: %d\nQuantidade de musicas: %d\n", raiz->info_1.titulo, raiz->info_1.ano, raiz->info_1.quantidade_musica);

        if (raiz->Nkeys == 2)
        {
            printf("Titulo: %s\nAno: %d\nQuantidade de musica: %d\n", raiz->info_2.titulo, raiz->info_2.ano, raiz->info_2.quantidade_musica);
        }  
        
        imprimirArvAlbum(raiz->cen);
        imprimirArvAlbum(raiz->dir);
    }
}


/*-------------------------------------------------------------------------------*/

void liberaNoAlbum(ArvAlbum **no)
{
    ArvAlbum *aux;

    aux = *no;
    *no = NULL;
    free(aux);
}

int removeEsqFolhaAlbum(ArvAlbum **raiz, ArvAlbum **pai)
{
    int flag = 0;
    (**raiz).info_1 = (**pai).info_1;

    if ((**pai).cen->Nkeys == 2)
    {
        (**pai).info_1 = (**pai).cen->info_1;
        (**pai).cen->info_1 = (**pai).cen->info_2;
        (**pai).cen->Nkeys = 1;
    }else if((**pai).Nkeys == 2){
        (**pai).info_1 = (**pai).cen->info_1;
        (**pai).cen->info_1 = (**pai).info_2;
        if ((**pai).dir->Nkeys == 2)
        {
            (**pai).info_2 = (**pai).dir->info_1;
            (**pai).dir->info_1 = (**pai).dir->info_2;
            (**pai).dir->Nkeys = 1;
        }
        else{
            adicionaNoAlbum(&(**pai).cen, (**pai).dir->info_1, NULL);
            liberaNoAlbum(&(**pai).dir);
            (**pai).Nkeys = 1;
        }
        
    }else{
        adicionaNoAlbum(pai, (**pai).cen->info_1, NULL);
        (**pai).Nkeys = 2;
        liberaNoAlbum(&(**pai).esq);
        liberaNoAlbum(&(**pai).cen);
        flag = 1;
    }

    return flag;
}

int removeCenFolhaAlbum(ArvAlbum **raiz, ArvAlbum **pai)
{
    int flag = 0;

    if ((**pai).esq->Nkeys == 2)
    {
        (**raiz).info_1 = (**pai).info_1;
        (**pai).info_1 = (**pai).esq->info_2;
        (**pai).esq->Nkeys = 1;
    }else if ((**pai).Nkeys == 2)
    {
        (**raiz).info_1 = (**pai).info_2;
        if ((**pai).dir->Nkeys == 2)
        {
            (**pai).info_2 = (**pai).dir->info_1;
            (**pai).dir->info_1 = (**pai).dir->info_2;
            (**pai).dir->Nkeys = 1;
        }else{
            adicionaNoAlbum(&(**pai).cen, (**pai).dir->info_1, NULL);
            liberaNoAlbum(&(**pai).dir);
            (**pai).Nkeys = 1;
        }
    }else{
        adicionaNoAlbum(pai, (**pai).esq->info_1, NULL);
        (**pai).Nkeys = 2;
        liberaNoAlbum(&(**pai).esq);
        liberaNoAlbum(&(**pai).dir);
        flag = 1;
    }

    return flag;    
}

void removeDirFolhaAlbum(ArvAlbum **raiz, ArvAlbum **pai)
{
    (**raiz).info_1 = (**pai).info_2;
    if ((**pai).cen->Nkeys == 2)
    {
        (**pai).info_2 = (**pai).cen->info_2;
        (**pai).cen->Nkeys = 1;
    }else if ((**pai).esq->Nkeys == 2)
    {
        Album aux = (**pai).cen->info_1;
        (**pai).cen->info_1 = (**pai).info_1;
        (**pai).info_1 = (**pai).esq->info_2;
        (**pai).info_2 = aux;
        (**pai).esq->Nkeys = 1;
    }else{
        adicionaNoAlbum(&(**pai).cen, (**pai).info_2, NULL);
        (**pai).Nkeys = 1;
        liberaNoAlbum(&(**pai).dir);
    } 
}

int removeFolhaAlbum(ArvAlbum **pai, ArvAlbum **raiz, char *nome)
{
    int balanceamento = 0;
    if ((*raiz)->Nkeys == 2)
    {
        if (strcmp(nome, (*raiz)->info_1.titulo) == 0)
            (*raiz)->info_1 = (*raiz)->info_2;
        (*raiz)->Nkeys = 1;
    }else if (*pai == NULL)
    {
        liberaNoAlbum(raiz);
    }else{
        if (*raiz == (**pai).esq)
            balanceamento = removeEsqFolhaAlbum(raiz, pai);
        else if (*raiz == (**pai).cen)
            balanceamento = removeCenFolhaAlbum(raiz, pai);
        else if (*raiz == (**pai).dir)
            removeDirFolhaAlbum(raiz, pai);
    }
    
    return balanceamento;
}

int removeNoFilhoFolhaAlbum(ArvAlbum **raiz, char *nome)
{
    int balanceamento = 0;
    if (strcmp(nome, (**raiz).info_1.titulo) == 0)
    {
        if ((**raiz).cen->Nkeys == 2)
        {
            (**raiz).info_1 = (**raiz).cen->info_1;
            (**raiz).cen->info_1 = (**raiz).cen->info_2;
            (**raiz).Nkeys = 1;
        }else if ((**raiz).esq->Nkeys == 2)
        {
            (**raiz).info_1 = (**raiz).esq->info_2;
            (**raiz).esq->Nkeys = 1;
        }else if ((**raiz).Nkeys == 2)
        {
            (**raiz).info_1 = (**raiz).cen->info_1;
            (**raiz).cen->info_1 = (**raiz).info_2;
            if ((**raiz).dir->Nkeys == 2)
            {
                (**raiz).info_2 = (**raiz).dir->info_1;
                (**raiz).dir->info_1 = (**raiz).dir->info_2;
                (**raiz).dir->Nkeys = 1;
            }else{
                adicionaNoAlbum(&(**raiz).cen, (**raiz).dir->info_1, NULL);
                (**raiz).Nkeys = 1;
                liberaNoAlbum(&(**raiz).dir);
            }
            
        }else{
            ArvAlbum *aux;
            adicionaNoAlbum(&(**raiz).esq, (**raiz).cen->info_1, NULL);
            aux = (**raiz).esq;
            liberaNoAlbum(&(**raiz).cen);
            liberaNoAlbum(raiz);
            *raiz = aux;
            balanceamento = 1;
        }
    }else{
        if ((**raiz).dir->Nkeys == 2)
        {
            (**raiz).info_2 = (**raiz).dir->info_1;
            (**raiz).dir->info_1 = (**raiz).dir->info_2;
            (**raiz).dir->Nkeys = 1;
        }else if ((**raiz).cen->Nkeys == 2)
        {
            (**raiz).info_2 = (**raiz).cen->info_2;
            (**raiz).cen->Nkeys = 1;
        }else if ((**raiz).esq->Nkeys == 2)
        {
            (**raiz).info_2 = (**raiz).cen->info_1;
            (**raiz).cen->info_1 = (**raiz).info_1;
            (**raiz).info_1 = (**raiz).esq->info_2;
            (**raiz).esq->Nkeys = 1;
        }else{
            adicionaNoAlbum(&(**raiz).cen, (**raiz).dir->info_1, NULL);
            (**raiz).Nkeys = 1;
            liberaNoAlbum(&(**raiz).dir);
        }
    }
    
    return balanceamento;
}

int balanceiaArvAlbum(ArvAlbum **raiz, int desbalanceamento)
{
    Album sobe;
    ArvAlbum *no_maior;
    ArvAlbum *aux;

    if (desbalanceamento == -1)
    {
        aux = (*raiz)->cen->esq;
        (*raiz)->cen->esq = (*raiz)->esq;
        if ((*raiz)->cen->Nkeys == 1)
        {
            adicionaNoAlbum(&(*raiz)->cen, (*raiz)->info_1, aux);
            (*raiz)->esq = NULL;
            if ((*raiz)->Nkeys == 1)
            {
                aux = *raiz;
                *raiz = (*raiz)->cen;
                liberaNoAlbum(&aux);
            }else{
                (*raiz)->info_1 = (*raiz)->info_2;
                (*raiz)->esq = (*raiz)->cen;
                (*raiz)->cen = (*raiz)->dir;
                (*raiz)->dir = NULL;
                (*raiz)->Nkeys = 1;
            }
            
        }else{
            quebraNoAlbum(&(*raiz)->cen, (*raiz)->info_1, &sobe, &no_maior, aux);
            (*raiz)->info_1 = sobe;
            (*raiz)->esq = (*raiz)->cen;
            (*raiz)->cen = no_maior;
        }   
    }else if (desbalanceamento == 0)
    {
        if ((*raiz)->esq->Nkeys == 1)
        {
            adicionaNoAlbum(&(*raiz)->esq, (*raiz)->info_1, (*raiz)->cen);
            (*raiz)->cen = NULL;
            if ((*raiz)->Nkeys == 1)
            {
                aux = *raiz;
                *raiz = (*raiz)->esq;
                liberaNoAlbum(&aux);
            }else{
                (*raiz)->info_1 = (*raiz)->info_2;
                (*raiz)->cen = (*raiz)->dir;
                (*raiz)->dir = NULL;
                (*raiz)->Nkeys = 1;
            }
            
        }else{
            quebraNoAlbum(&(*raiz)->esq, (*raiz)->info_1, &sobe, &no_maior, (*raiz)->cen);
            (*raiz)->info_1 = sobe;
            (*raiz)->cen = no_maior;
        }
    }else{
        if ((*raiz)->cen->Nkeys == 1)
        {
            adicionaNoAlbum(&(*raiz)->cen, (*raiz)->info_2, (*raiz)->dir);
            (*raiz)->Nkeys = 1;
            (*raiz)->dir = NULL;
        }else{
            quebraNoAlbum(&(*raiz)->cen, (*raiz)->info_2, &sobe, &no_maior, (*raiz)->dir);
            (*raiz)->info_2 = sobe;
            (*raiz)->dir = no_maior;
        }
    }
    
    return 0;
}

int removeMenorNoAlbum(ArvAlbum **pai_aux, ArvAlbum **no, Album *info_sobe)
{
    int balanceamento = 0;
    if ((*no)->esq != NULL)
        balanceamento = removeMenorNoAlbum(no, &(*no)->esq, info_sobe);
    else{
        *info_sobe = (*no)->info_1;
        balanceamento = removeFolhaAlbum(pai_aux, no, (*no)->info_1.titulo);
    }
    return balanceamento;
}

int removerAlbum(ArvAlbum **pai, ArvAlbum **raiz, char *nome)
{
    int balanceamento = 0;
    if (*raiz != NULL)
    {
        if ((strcmp(nome, (*raiz)->info_1.titulo) == 0) || ((*raiz)->Nkeys == 2 && strcmp(nome, (*raiz)->info_2.titulo) == 0))
        {
            
            if (ehFolhaAlbum(*raiz) == 1)
                balanceamento = removeFolhaAlbum(pai, raiz, nome);
            else if (((ehFolhaAlbum((*raiz)->esq) == 1) && ehFolhaAlbum((*raiz)->cen) == 1 && ehFolhaAlbum((*raiz)->dir) == 1) || ((ehFolhaAlbum((*raiz)->esq) == 1) && ehFolhaAlbum((*raiz)->cen) == 1 && (*raiz)->Nkeys == 1 ))
                balanceamento = removeNoFilhoFolhaAlbum(raiz, nome); 
            else{
                ArvAlbum *pai_aux = NULL;
                Album info_sobe;
                if (strcmp(nome, (*raiz)->info_1.titulo) == 0)
                {
                    balanceamento = removeMenorNoAlbum(&pai_aux, &(*raiz)->cen, &info_sobe);
                    (*raiz)->info_1 = info_sobe;
                    if (balanceamento == 1)
                    {
                        balanceamento = balanceiaArvAlbum(raiz, 0);
                    }   
                }else{
                    balanceamento = removeMenorNoAlbum(&pai_aux, &(*raiz)->dir, &info_sobe);
                    (*raiz)->info_2 = info_sobe;
                    if (balanceamento == 1)
                    {
                        balanceamento = balanceiaArvAlbum(raiz, 1);
                    }
                }
            }
        }
        else if (strcmp(nome,(*raiz)->info_1.titulo) < 0)
            balanceamento = removerAlbum(raiz, &(*raiz)->esq, nome);
        else if (strcmp(nome,(*raiz)->info_2.titulo) > 0 && (*raiz)->Nkeys == 2)
            balanceamento = removerAlbum(raiz, &(*raiz)->dir, nome);
        else
            balanceamento = removerAlbum(raiz, &(*raiz)->cen, nome);
        if (balanceamento == 1 && *raiz != NULL && *pai != NULL)
        {
            if (*raiz == (**pai).esq)
                balanceamento = balanceiaArvAlbum(pai, -1);
            else if(*raiz == (*pai)->cen)
                balanceamento = balanceiaArvAlbum(pai, 0);
            else if(*raiz == (*pai)->dir)
                balanceamento = balanceiaArvAlbum(pai, 1);
            
        }
        
    }
    return balanceamento;
}

ArvAlbum *buscaArvAlbum(ArvAlbum **raiz, char *nome)
{
    ArvAlbum *no = NULL;
    if (*raiz != NULL)
    {
        if (strcmp(nome, (*raiz)->info_1.titulo) == 0)
            no = *raiz;
        else if(strcmp(nome, (*raiz)->info_2.titulo) == 0)
            no = *raiz;
        else
        {
            if (strcmp(nome, (*raiz)->info_1.titulo) < 0)
                no = buscaArvAlbum(&(*raiz)->esq, nome);
            else if (strcmp(nome, (*raiz)->info_2.titulo) < 0 || (*raiz)->Nkeys == 1)
                no = buscaArvAlbum(&(*raiz)->cen, nome);
            else
                no = buscaArvAlbum(&(*raiz)->dir, nome);
        }   
    }
    
    return no;
}
/*-------------------------------------------------------------------------------*/
Musica ler_musica()
{
    Musica musica;
    fflush(stdin);
    printf("Informe o nome da musica: ");
    scanf("%[^\n]s", musica.nome_musica);
    getchar();
    fflush(stdin);
    printf("Informe quantidade de minutos: ");
    scanf("%d", &musica.minutos);
    return musica;
}


Musica *criarLista()
{
    return NULL;
}

void inserirMusica(ArvAlbum *lista)
{
    Musica *m = (Musica *)malloc(sizeof(Musica));

    *m = ler_musica();
    m->prox = NULL;

    Musica *atual = lista->musica;
    Musica *anterior = NULL;

    while (atual != NULL && strcmp(m->nome_musica, atual->nome_musica) > 0)
    {
        anterior = atual;
        atual = atual->prox;
    }

    if (anterior == NULL)
    {
        m->prox = lista->musica;
        lista->musica = m;
    }
    else
    {
        anterior->prox = m;
        m->prox = atual;
    }
}

Musica *busca_musica(ArvAlbum *lista, char *nome)
{
    Musica *atual = lista->musica;

    while (atual != NULL && strcmp(atual->nome_musica, nome) != 0)
        atual = atual->prox;
    
    return atual;
}

void excluir_musica(ArvAlbum *lista, char *nome)
{
    Musica *anterior = NULL;
    Musica *atual = lista->musica;

    while (atual != NULL && strcmp(atual->nome_musica, nome) != 0)
    {
        anterior = atual;
        atual = atual->prox;
    }
    if (atual != NULL)
    {
        if (anterior == NULL)
            lista->musica = atual->prox;
        else
            anterior->prox = atual->prox;
        free(atual);
    }
}

void imprimir_todas_musicas(ArvAlbum *lista)
{
    Musica *m = lista->musica;
    while (m != NULL)
    {
        imprimir_uma_musica(m);
        m = m->prox;
    }
}

void imprimir_uma_musica(Musica* m)
{
    printf("Nome da musica: %s\nDuracao em minutos: %d min\n", m->nome_musica, m->minutos);
}

void imprimir_um_artista(Artista info)
{
    printf("Nome do artista: %s\nEstilo musical: %s\nQuantidade de albuns: %d\n", info.nome_artista, info.estilo, info.num_albuns);
}

void imprimir_um_album(Album info)
{
    printf("Titulo: %s\nAno: %d\nQuantidade de musicas: %d\n", info.titulo, info.ano, info.quantidade_musica);
}
/*-------------------------------------------------------------------------------*/

void menu()
{
    printf("==============MENU==============\n");
    printf(": 1 - Cadastro de Artista      :\n");
    printf(": 2 - Excluir Artista          :\n");
    printf(": 3 - Imprimir Artistas        :\n");
    printf(": 4 - Busca                    :\n");
    printf(": 5 - Cadastro de Album        :\n");
    printf(": 6 - Excluir Album            :\n");
    printf(": 7 - Imprimir Albuns          :\n");
    printf(": 8 - Cadastro de Musica       :\n");
    printf(": 9 - Excluir Musica           :\n");
    printf(": 10 - Imprimir Musica         :\n");
    printf(": 0 - Sair                     :\n");
    printf("================================\n");
}

void menu_busca()
{
    system("cls");
    printf("==============MENU==============\n");
    printf(": 1 - Buscar Artista           :\n");
    printf(": 2 - Buscar Album             :\n");
    printf(": 3 - Buscar Musica            :\n");
    printf(": 0 - Sair                     :\n");
    printf("================================\n");
}



int main() 
{
    Artista sobe;
    ArvAlbum *paiAlbum = criaArvAlbum();
    ArvArtista *pai = criaArvArtista();
    ArvArtista *raiz = criaArvArtista();


    int op = -1;
    
    while (op != 0)
    {
        menu();
        scanf("%d", &op);
        switch (op)
        {
            case 1:
            {
                insereArvArtista(&pai, &raiz, ler_artista(), &sobe);
                printf("Artista inserido.\n");
                break;
            }

            case 2:
            {   
                fflush(stdin);
                int op_excluir;
                printf("Todos os albuns e musicas do artista serao excluidos juntamente. Continuar? \n1 - Sim\n2 - Nao\n");
                scanf("%d", &op_excluir);
                
                if (op_excluir == 1)
                {
                    fflush(stdin);
                    char nome[50];
                    fflush(stdin);
                    printf("Informe o artista a ser excluido: ");
                    scanf("%[^\n]", nome);
                    ArvArtista *busca = buscaArvArtista(&raiz, nome);
                    if (busca != NULL)
                    {
                        removerArtista(&pai, &raiz, nome);
                        printf("Artista excluido com sucesso!!\n");
                    }
                    else
                        printf("Artista nao encontrado!!\n");
                }else if(op_excluir == 2)
                    printf("Operacao cancelada!!\n");
                  
                break;
            }

            case 3:
                imprimirArvArtista(raiz);
                break;
            case 4:
            {
                int op_busca;
                menu_busca();
                scanf("%d", &op_busca); 
                if (op_busca == 1)
                {
                    char nome[50];
                    fflush(stdin);
                    printf("Informe o artista a ser buscado: ");
                    scanf("%[^\n]", nome);
                    fflush(stdin);
                    ArvArtista *busca = buscaArvArtista(&raiz, nome);
                    if (busca != NULL)
                        imprimir_um_artista(busca->info_1);
                    else
                        printf("Artista nao encontrado!!\n");
                }
                else if(op_busca == 2)
                {
                    char nome_artista[50];
                    fflush(stdin);
                    printf("Informe o artista que tenha o album a ser buscado: ");
                    scanf("%[^\n]", nome_artista);
                    fflush(stdin);
                    ArvArtista *busca = buscaArvArtista(&raiz, nome_artista);
                    if (busca != NULL)
                    {
                        char nome[50];
                        fflush(stdin);
                        printf("Informe o artista que tenha o album a ser buscado: ");
                        scanf("%[^\n]", nome);
                        fflush(stdin);
                        ArvAlbum *busca_album = buscaArvAlbum(&raiz->arvAlbum, nome);
                        if (busca_album != NULL)
                            imprimir_um_album(busca_album->info_1);
                        else
                            printf("Album nao encontrado!!\n");
                    }
                    else
                        printf("Artista nao encontrado!!\n");
                    
                    
                }
                else if (op_busca == 3)
                {
                    
                    char nome_artista[50];
                    fflush(stdin);
                    printf("Informe o artista que tenha o album a ser buscado: ");
                    scanf("%[^\n]", nome_artista);
                    fflush(stdin);
                    ArvArtista *busca = buscaArvArtista(&raiz, nome_artista);
                    if (busca != NULL)
                    {
                        char nome[50];
                        fflush(stdin);
                        printf("Informe o artista que tenha o album a ser buscado: ");
                        scanf("%[^\n]", nome);
                        fflush(stdin);
                        ArvAlbum *busca_album = buscaArvAlbum(&raiz->arvAlbum, nome);
                        if (busca_album != NULL)
                        {
                            char nome_musica[50];
                            printf("Informe o nome da musica: ");
                            scanf("%[^\n]", nome_musica);
                            Musica *mus = busca_musica(busca_album, nome_musica);
                            if (mus != NULL)
                                imprimir_uma_musica(mus);
                            else
                                printf("Musica nao encontrada!!\n");
                            
                        }       
                        else
                            printf("Album nao encontrado!!\n");
                        
                    }
                    else
                        printf("Artista nao encontrado!!\n");
                }
                break;
            }

            case 5:
            {
                
                char nome[50];
                fflush(stdin);
                printf("Informe o artista que deseja cadastrar um album: ");
                scanf("%[^\n]", nome);
                fflush(stdin);
                ArvArtista *busca = buscaArvArtista(&raiz, nome);
                if (busca != NULL)
                {
                    
                    
                    ArvAlbum *raizAlbum = busca->arvAlbum;
                    Album sobeAlbum;
                    insereArvAlbum(&paiAlbum, &raizAlbum, ler_album(), &sobeAlbum);
                    busca->info_1.num_albuns++;
                    printf("Album inserido.\n");
                }
                else
                    printf("Artista nao encontrado!!\n");
                
                break;
            }

            case 6:
            {
                fflush(stdin);
                int op_excluir;
                printf("Todos as musicas do album serao excluidos juntamente. Continuar? \n1 - Sim\n2 - Nao\n");
                scanf("%d", &op_excluir);
                if (op_excluir == 1)
                {
                    
                    char nome[50];
                    fflush(stdin);
                    printf("Informe o artista que deseja excluir o album: ");
                    scanf("%[^\n]", nome);
                    fflush(stdin);
                    ArvArtista *busca = buscaArvArtista(&raiz, nome);
                    if (busca != NULL)
                    {
                        char titulo[50];
                        fflush(stdin);
                        printf("Informe o album a ser excluido: ");
                        scanf("%[^\n]", titulo);
                        fflush(stdin);
                        ArvAlbum *busca_album = buscaArvAlbum(&raiz->arvAlbum, titulo);
                        if (busca_album != NULL)
                        {
                            removerAlbum(&paiAlbum, &busca->arvAlbum, titulo);
                            busca->info_1.num_albuns--;
                            printf("Album excluido com sucesso!!\n");
                        }
                        else
                            printf("Album nao encontrado!!\n");
                    }
                    else
                        printf("Artista nao encontrado!!\n");
                    
                }else
                    printf("Operacao cancelada!!\n");

                break;
            }

            case 7:
            {
                
                char nome[50];
                fflush(stdin);
                printf("Informe o artista que deseja mostrar os albuns: ");
                scanf("%[^\n]", nome);
                fflush(stdin);
                ArvArtista *busca = buscaArvArtista(&raiz, nome);
                if (busca != NULL)
                    imprimirArvAlbum(busca->arvAlbum);
                else
                    printf("Artista nao encontrado!!\n");
                
                break;
            }
            case 8:
            {
                fflush(stdin);
                
                char nome[50];
                fflush(stdin);
                printf("Informe o artista que deseja cadastrar a musica: ");
                scanf("%[^\n]", nome);
                fflush(stdin);
                ArvArtista *busca = buscaArvArtista(&raiz, nome);
                if (busca != NULL)
                {
                    char nome_album[50];
                    fflush(stdin);
                    printf("Informe o album que deseja cadastrar musica: ");
                    scanf("%[^\n]", nome_album);
                    ArvAlbum *busca_album  = buscaArvAlbum(&busca->arvAlbum, nome_album);
                    if (busca_album != NULL)
                    {
                        inserirMusica(busca_album);
                        printf("Musica inserida com sucesso!!\n");
                    }               
                    else
                        printf("Album nao encontrado!!\n");
                    
                }
                else
                    printf("Artista nao encontrado!!\n");
                break;
            }
            case 9:
            {
                
                char nome[50];
                fflush(stdin);
                printf("Informe o artista que deseja excluir a musica: ");
                scanf("%[^\n]", nome);
                fflush(stdin);
                ArvArtista *busca = buscaArvArtista(&raiz, nome);
                if (busca != NULL)
                {
                    char nome_album[50];
                    fflush(stdin);
                    printf("Informe o album que deseja excluir a musica: ");
                    scanf("%[^\n]", nome_album);
                    ArvAlbum *busca_album  = buscaArvAlbum(&busca->arvAlbum, nome_album);
                    if (busca_album != NULL)
                    {
                        char nome_musica[50];
                        
                        fflush(stdin);
                        printf("Informe a musica que deseja excluir: ");
                        scanf("%[^\n]", nome_musica);
                        Musica *buscaMusica = busca_musica(busca_album, nome_musica);
                        if (buscaMusica != NULL)
                        {
                            excluir_musica(busca_album, nome_musica);
                            busca_album->info_1.quantidade_musica--;
                            printf("Musica deletada com sucesso!!\n");
                        }
                        else
                            printf("Musica nao encontrada!!\n");  
                    }
                    else
                        printf("Album nao encontrado!!\n");
                    
                }
                else
                    printf("Artista nao encontrado!!\n");
                break;
            }
            case 10:
            {
                
                char nome[50];
                fflush(stdin);
                printf("Informe o artista que deseja mostrar a musica: ");
                scanf("%[^\n]", nome);
                fflush(stdin);
                ArvArtista *busca = buscaArvArtista(&raiz, nome);
                if (busca != NULL)
                {
                    char nome_album[50];
                    fflush(stdin);
                    printf("Informe o album que deseja mostrar as musicas: ");
                    scanf("%[^\n]", nome_album);
                    ArvAlbum *busca_album  = buscaArvAlbum(&busca->arvAlbum, nome_album);
                    if (busca_album != NULL)
                        imprimir_todas_musicas(busca_album);  
                    else
                        printf("Album nao encontrado!!\n");   
                }
                else
                    printf("Artista nao encontrado!!\n");
                break;
            }
            default:
                break;
        }
    }
    

    return 0;
}

