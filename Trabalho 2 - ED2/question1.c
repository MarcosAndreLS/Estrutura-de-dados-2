/*  Faça um programa em C de uma Biblioteca de Música. As informações são organizadas por
Artista (cantor(a), Dupla, Banda, Grupo, …). E para cada artista deve ser ter o nome do artista, o estilo
musical, o número de álbuns, e os Álbuns (endereço da árvore vermelho e preta). Cada álbum deve ter, o
título, o ano de lançamento, a quantidade de músicas e as Músicas (endereço lista ordenada). Para cada
música deve se ter o título, e a quantidade de minutos. Quando o usuário abre o programa o mesmo deve
automaticamente criar uma árvore vermelha-preta, contendo informações sobre os Artistas (organizado pelo
nome), e inclui como chave o nome do artista.

    O programa deve permitir a inserção de Artistas, Álbuns e Músicas. Lembrando que uma música, deve estar
em um álbum e um álbum deve estar em um Artista, ou seja, uma música só pode ser inserida em um álbum
já cadastrado e um álbum só pode ser inserido para um Artista já cadastrado. O programa deve permitir
todos os tipos de busca: por artista, por álbum por música. E também permitir a remoção de uma
determinada música, e de um álbum (neste caso lembrar ao usuário que todas as músicas daquele álbum
serão removidas e o mesmo referente aos artistas, para a remoção de um artista, lembrar ao usuário que
todos os álbuns e consequentemente todas as músicas daquele artista serão removidas. Faça um
experimento que busque por 30 itens(artistas), mostre o caminho percorrido na árvore para encontrar o item
e o tempo gasto. Depois faça uma análise dos resultados obtidos. 
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED 1
#define BLACK 0

/*Prototipos*/
typedef struct arvartista ArvArtista;
typedef struct arvllrb ArvLLRB;
typedef struct artista Artista;
typedef struct arvalbum ArvAlbum; 
typedef struct album Album;
typedef struct musica Musica;
/*----------------------------------------------------------------------------------------------*/
ArvArtista* criaArvArtista();
int cor_artista(ArvArtista *raiz);
void trocaCor_artista(ArvArtista *raiz);
void rotacionaEsquerdaArtista(ArvArtista **A);
void rotacionaDireitaArtista(ArvArtista **A);
void move2EsqREDArtista(ArvArtista **raiz);
void move2DirREDArtista(ArvArtista **raiz);
void balancear_artista(ArvArtista **raiz);
ArvArtista *removerMenor(ArvArtista *raiz);
ArvArtista *procuraMenor(ArvArtista *atual);
ArvArtista *inserir_artista(ArvArtista *raiz, Artista a, int *resp);
int insereArvLLRB_artista(ArvArtista **raiz, Artista a);
ArvArtista *excluir_artista(ArvArtista *raiz, char *nome);
ArvArtista* buscaArvSArtista(ArvArtista *raiz, char *nome, int *achou);

/*----------------------------------------------------------------------------------------------*/
ArvAlbum* criaArvAlbum();
int cor_album(ArvAlbum *raiz);
void trocaCor_album(ArvAlbum *raiz);
void rotacionaEsquerdaAlbum(ArvAlbum **A);
void rotacionaDireitaAlbum(ArvAlbum **A);
void move2EsqREDAlbum(ArvAlbum **raiz);
void move2DirREDAlbum(ArvAlbum **raiz);
void balancear_album(ArvAlbum **raiz);
ArvAlbum *removerMenorAlbum(ArvAlbum *raiz);
ArvAlbum *procuraMenorAlbum(ArvAlbum *atual);
ArvAlbum *inserir_album(ArvAlbum *raiz, Album a, int *resp);
int insereArvLLRB_album(ArvAlbum **raiz, Album a);
ArvAlbum *excluir_album(ArvAlbum *raiz, char *titulo);
void imprimir_um_album(Album a);
void imprimir_todos_album(ArvAlbum *raiz);
ArvAlbum* buscaArvSAlbum(ArvAlbum *raiz, char *titulo, int *achou);
/*----------------------------------------------------------------------------------------------*/
Musica *criarLista();
void inserirMusica(ArvAlbum *lista);
Musica *busca_musica(ArvAlbum *lista, char *nome);
void excluir_musica(ArvAlbum *lista, char *nome, int *excluiu);
void imprimir_todas_musicas(ArvAlbum *lista);
void imprimir_uma_musica(Musica* m);
/*----------------------------------------------------------------------------------------------*/
void liberarTodaMemoria(ArvArtista *raiz);
void liberarArtistas(ArvArtista *raiz);
void liberarAlbums(ArvAlbum *raiz);
void liberarMusicas(Musica *lista);
/*Structs*/
typedef struct artista
{
    char nome[50];
    char estilo[50];
    int num_albuns;
}Artista;

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


/*Arvores*/

typedef struct arvartista
{
    Artista artista;
    ArvAlbum *arvAlbum;
    struct arvartista *esq, *dir;
    int cor;
}ArvArtista;

typedef struct arvllrb
{
    Artista artista;
    ArvAlbum *arvAlbum;
    struct arvartista *esq, *dir;
    int cor;
}ArvLLRB;

typedef struct arvalbum
{
    Album album;
    Musica *musica; //lista
    struct arvalbum *esq, *dir;
    int cor;
}ArvAlbum;

typedef struct arvllrbalbum
{
    Album album;
    Musica *musica; //lista
    struct arvalbum *esq, *dir;
    int cor;
}ArvLLRBalbum;

/*Leituras*/

Artista ler_artista()
{
    Artista art;

    fflush(stdin); 
    printf("Informe o nome do artista: ");
    scanf("%[^\n]s", art.nome);
    fflush(stdin); 
    printf("Informe o estilo musical: ");
    scanf("%[^\n]s", art.estilo);
    fflush(stdin); 
    art.num_albuns = 0;
    fflush(stdin); 
    return art;
}

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

Musica ler_musica()
{
    Musica musica;
    fflush(stdin);
    printf("Informe o nome da musica: ");
    scanf("%[^\n]s", musica.nome_musica);
    fflush(stdin);
    printf("Informe quantidade de minutos: ");
    scanf("%d", &musica.minutos);
    return musica;
}

/*Implementação das Arvores*/

/*Artistas*/

ArvArtista* criaArvArtista()
{
    return NULL;
}

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
        return NULL;
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
        novo->arvAlbum = criaArvAlbum();
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

int insereArvLLRB_artista(ArvArtista **raiz, Artista a)
{
    int resp;
    *raiz = inserir_artista(*raiz, a, &resp);
    if (*raiz != NULL)
        (*raiz)->cor = BLACK;
    
    return resp;
}

ArvArtista *excluir_artista(ArvArtista *raiz, char *nome) 
{
    if (raiz == NULL) {
        return NULL;
    }

    if (strcmp(nome, raiz->artista.nome) < 0) 
        raiz->esq = excluir_artista(raiz->esq, nome);
    else if (strcmp(nome, raiz->artista.nome) > 0) 
        raiz->dir = excluir_artista(raiz->dir, nome);
    else 
    {

        if (raiz->esq == NULL && raiz->dir == NULL) 
        { //sem filho
            
            free(raiz);
            return NULL;
        } 
        else if (raiz->esq == NULL || raiz->dir == NULL) 
        { //um filho
            
            ArvArtista *temp = (raiz->esq != NULL) ? raiz->esq : raiz->dir;
            free(raiz);
            return temp;
        } 
        else 
        { //dois filhos
            ArvArtista *temp = procuraMenor(raiz->dir);
            raiz->artista = temp->artista;
            raiz->dir = excluir_artista(raiz->dir, temp->artista.nome);
        }
        
    }

    balancear_artista(&raiz);

    return raiz;
}

ArvArtista* buscaArvSArtista(ArvArtista *raiz, char *nome, int *achou)
{
    if (raiz != NULL)
    {
        if (strcmp(nome, raiz->artista.nome) < 0)
            return buscaArvSArtista(raiz->esq, nome, achou);
        else if (strcmp(nome, raiz->artista.nome) > 0)
            return buscaArvSArtista(raiz->dir, nome, achou);
        else
        {
            *achou = 1;
            return raiz;
        }
    }

    *achou = 0;
    return NULL;
}

void imprimir_um(Artista a)
{
    printf("Nome: %s\nEstilo: %s\nNumero de albuns: %d\n\n", a.nome, a.estilo, a.num_albuns);
}

void imprimir_todos_artistas(ArvArtista *raiz)
{
    if (raiz != NULL)
    {
        imprimir_todos_artistas(raiz->esq);
        imprimir_um(raiz->artista);
        imprimir_todos_artistas(raiz->dir);
    }
    
}

/*Albuns*/

ArvAlbum* criaArvAlbum()
{
    return NULL;
}

int cor_album(ArvAlbum *raiz)
{
    if (raiz == NULL)
        return BLACK;
    else
        return raiz->cor;
}

void trocaCor_album(ArvAlbum *raiz)
{
    raiz->cor = !raiz->cor;
    if (raiz->esq != NULL)
        raiz->esq->cor = !raiz->esq->cor;
    if(raiz->dir != NULL)
        raiz->dir->cor = !raiz->dir->cor;
}

void rotacionaEsquerdaAlbum(ArvAlbum **A)
{
    ArvAlbum *B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = *A;
    B->cor = (*A)->cor;
    (*A)->cor = RED;
    *A = B;
}

void rotacionaDireitaAlbum(ArvAlbum **A)
{
    ArvAlbum *B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    B->cor = (*A)->cor;
    (*A)->cor = RED;
    *A = B;
}

void move2EsqREDAlbum(ArvAlbum **raiz)
{
    trocaCor_album(*raiz);
    if (cor_album((*raiz)->dir->esq) == RED)
    {
        rotacionaDireitaAlbum(&(*raiz)->dir);
        rotacionaEsquerdaAlbum(&(*raiz));
        trocaCor_album(*raiz);
    }
}

void move2DirREDAlbum(ArvAlbum **raiz)
{
    trocaCor_album(*raiz);
    if (cor_album((*raiz)->esq->esq) == RED)
    {
        rotacionaDireitaAlbum(&(*raiz));
        trocaCor_album(*raiz);
    }
}

void balancear_album(ArvAlbum **raiz)
{
    if (cor_album((*raiz)->dir) == RED)
        rotacionaEsquerdaAlbum(raiz);
    if((*raiz)->esq != NULL && cor_album((*raiz)->esq) == RED && cor_album((*raiz)->esq->esq) == RED)
        rotacionaDireitaAlbum(raiz);
    if (cor_album((*raiz)->esq) == RED && cor_album((*raiz)->dir) == RED)
        trocaCor_album(*raiz);
    
}

ArvAlbum *removerMenorAlbum(ArvAlbum *raiz)
{
    if ((raiz->esq) == NULL)
    {
        free(raiz);
        return NULL;
    }
    if (cor_album(raiz->esq) == BLACK && cor_album(raiz->esq->esq) == BLACK)
        move2EsqREDAlbum(&raiz);

    removerMenorAlbum(raiz->esq);

    balancear_album(&raiz);

    return raiz;
}

ArvAlbum *procuraMenorAlbum(ArvAlbum *atual)
{
    ArvAlbum *no1 = atual;
    ArvAlbum *no2 = atual->esq;
    while (no2 != NULL)
    {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

ArvAlbum *inserir_album(ArvAlbum *raiz, Album a, int *resp)
{
    if (raiz == NULL)
    {
        ArvAlbum *novo;
        novo = (ArvAlbum*)malloc(sizeof(ArvAlbum));
        if(novo == NULL)
        {
            *resp = 0;
            return NULL;
        }
        novo->album = a;
        novo->cor = RED;
        novo->dir = NULL;
        novo->esq = NULL;
        novo->musica = criarLista();
        *resp = 1;
        return novo;
    }
    if(strcmp(a.titulo, raiz->album.titulo) == 0)
        *resp = 0;
    else
    {
        if (a.ano < raiz->album.ano)
            raiz->esq = inserir_album(raiz->esq, a, resp);
        else
            raiz->dir = inserir_album(raiz->dir, a, resp);  
    }
    if (cor_album(raiz->dir) == RED && cor_album(raiz->esq) == BLACK)
        rotacionaEsquerdaAlbum(&raiz);
    if (cor_album(raiz->esq) == RED && cor_album(raiz->esq->esq) == RED)
        rotacionaDireitaAlbum(&raiz);
    if(cor_album(raiz->dir) == RED && cor_album(raiz->esq) == RED)
        trocaCor_album(raiz);

    return raiz;
        
} 

int insereArvLLRB_album(ArvAlbum **raiz, Album a)
{
    int resp;
    *raiz = inserir_album(*raiz, a, &resp);
    if (*raiz != NULL)
        (*raiz)->cor = BLACK;
    
    return resp;
}

ArvAlbum *excluir_album(ArvAlbum *raiz, char *titulo) 
{
    if (raiz == NULL)
        return NULL; 

    if (strcmp(titulo, raiz->album.titulo) < 0) 
        raiz->esq = excluir_album(raiz->esq, titulo);
    else if (strcmp(titulo, raiz->album.titulo) > 0) 
        raiz->dir = excluir_album(raiz->dir, titulo);
    else 
    {

        if (raiz->esq == NULL && raiz->dir == NULL) 
        { //sem filho
            
            free(raiz);
            return NULL;
        } 
        else if (raiz->esq == NULL || raiz->dir == NULL) 
        { //um filho
            
            ArvAlbum *temp = (raiz->esq != NULL) ? raiz->esq : raiz->dir;
            free(raiz);
            return temp;
        } 
        else 
        { //dois filhos
            ArvAlbum *temp = procuraMenorAlbum(raiz->dir);
            raiz->album = temp->album;
            raiz->dir = excluir_album(raiz->dir, temp->album.titulo);
        }
        
    }

    balancear_album(&raiz);

    return raiz;
}

ArvAlbum* buscaArvSAlbum(ArvAlbum *raiz, char *titulo, int *achou)
{
    if (raiz != NULL)
    {
        if (strcmp(titulo, raiz->album.titulo) < 0)
            return buscaArvSAlbum(raiz->esq, titulo, achou);
        else if (strcmp(titulo, raiz->album.titulo) > 0)
            return buscaArvSAlbum(raiz->dir, titulo, achou);
        else
        {
            *achou = 1;
            return raiz;
        }
    }

    *achou = 0;
    return NULL;
}

void imprimir_um_album(Album a)
{
    printf("Ano: %d\nTitulo: %s\nQuantidade de musicas: %d\n\n", a.ano, a.titulo, a.quantidade_musica);
}

void imprimir_todos_album(ArvAlbum *raiz)
{
    if (raiz != NULL)
    {
        imprimir_todos_album(raiz->esq);
        imprimir_um_album(raiz->album);
        imprimir_todos_album(raiz->dir);
    }
    
}

/*Musica*/

Musica *criarLista()
{
    return NULL;
}

void inserirMusica(ArvAlbum *lista)
{
    Musica *m = (Musica *)malloc(sizeof(Musica));
    *m = ler_musica();
    
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
    lista->album.quantidade_musica++;
}


Musica *busca_musica(ArvAlbum *lista, char *nome)
{
    Musica *atual = lista->musica;

    while (atual != NULL && strcmp(atual->nome_musica, nome) != 0)
        atual = atual->prox;
    
    return atual;
}

void excluir_musica(ArvAlbum *lista, char *nome, int *excluiu)
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
        *excluiu = 1;
    }else   
        *excluiu = 0; 
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

void liberarMusicas(Musica *lista) {
    while (lista != NULL) {
        Musica *temp = lista;
        lista = lista->prox;
        free(temp);
    }
}

void liberarAlbums(ArvAlbum *raiz) {
    if (raiz != NULL) {
        liberarAlbums(raiz->esq);
        liberarAlbums(raiz->dir);
        liberarMusicas(raiz->musica);
        free(raiz);
    }
}

void liberarArtistas(ArvArtista *raiz) {
    if (raiz != NULL) {
        liberarArtistas(raiz->esq);
        liberarArtistas(raiz->dir);
        liberarAlbums(raiz->arvAlbum);
        free(raiz);
    }
}

void liberarTodaMemoria(ArvArtista *raiz) {
    liberarArtistas(raiz);
}

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
    ArvArtista *raiz = NULL;

    int op = -1;
    
    while (op != 0)
    {
        menu();
        scanf("%d", &op);
        switch (op)
        {
            case 1:
            {
                int result = insereArvLLRB_artista(&raiz, ler_artista());
                if (result == 1)
                    printf("Artista inserido.\n");
                else
                    printf("O artista ja esta cadastrado.\n");
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
                    raiz = excluir_artista(raiz, nome);
                    if (raiz != NULL)
                        printf("Artista excluido com sucesso!!\n");
                    else
                        printf("Artista nao encontrado!!\n");
                }else if(op_excluir == 2)
                    printf("Operacao cancelada!!\n");
                  
                break;
            }

            case 3:
                imprimir_todos_artistas(raiz);
                break;
            case 4:
            {
                int op_busca;
                menu_busca();
                scanf("%d", &op_busca); 
                if (op_busca == 1)
                {
                    int achou = 0;
                    char nome[50];
                    fflush(stdin);
                    printf("Informe o artista a ser buscado: ");
                    scanf("%[^\n]", nome);
                    fflush(stdin);
                    ArvArtista *busca = buscaArvSArtista(raiz, nome, &achou);
                    if (achou == 1)
                        imprimir_um(busca->artista);
                    else
                        printf("Artista nao encontrado!!\n");
                }
                else if(op_busca == 2)
                {
                    int achou = 0;
                    char nome[50];
                    fflush(stdin);
                    printf("Informe o album a ser buscado: ");
                    scanf("%[^\n]", nome);
                    fflush(stdin);
                    ArvAlbum *busca = buscaArvSAlbum(raiz->arvAlbum, nome, &achou);
                    if (achou == 1)
                        imprimir_um_album(busca->album);
                    else
                        printf("Album nao encontrado!!\n");
                }
                else if (op_busca == 3)
                {
                    int achou = 0;
                    char nome[50];
                    fflush(stdin);
                    printf("Informe o artista que deseja mostrar a musica: ");
                    scanf("%[^\n]", nome);
                    fflush(stdin);
                    ArvArtista *busca = buscaArvSArtista(raiz, nome, &achou);
                    if (achou == 1)
                    {
                        achou = 0;
                        char nome_album[50];
                        fflush(stdin);
                        printf("Informe o album que deseja mostrar a musica: ");
                        scanf("%[^\n]", nome_album);
                        ArvAlbum *busca_album  = buscaArvSAlbum(busca->arvAlbum, nome_album, &achou);
                        if (achou == 1)
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
                int achou = 0;
                char nome[50];
                fflush(stdin);
                printf("Informe o artista que deseja cadastrar um album: ");
                scanf("%[^\n]", nome);
                fflush(stdin);
                ArvArtista *busca = buscaArvSArtista(raiz, nome, &achou);
                if (achou == 1)
                {
                    
                    int result = insereArvLLRB_album(&busca->arvAlbum, ler_album());

                    if (result == 1)
                    {
                        busca->artista.num_albuns++;
                        printf("Album inserido.\n");
                    }
                    else
                        printf("O album ja esta cadastrado.\n");
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
                    int achou = 0;
                    char nome[50];
                    fflush(stdin);
                    printf("Informe o artista que deseja excluir o album: ");
                    scanf("%[^\n]", nome);
                    fflush(stdin);
                    ArvArtista *busca = buscaArvSArtista(raiz, nome, &achou);
                    if (achou == 1)
                    {
                        char titulo[50];
                        fflush(stdin);
                        printf("Informe o album a ser excluido: ");
                        scanf("%[^\n]", titulo);
                        fflush(stdin);
                        busca->arvAlbum = excluir_album(busca->arvAlbum, titulo);
                        if (busca->arvAlbum != NULL)
                        {
                            busca->artista.num_albuns--;
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
                int achou = 0;
                char nome[50];
                fflush(stdin);
                printf("Informe o artista que deseja mostrar os albuns: ");
                scanf("%[^\n]", nome);
                fflush(stdin);
                ArvArtista *busca = buscaArvSArtista(raiz, nome, &achou);
                if (achou == 1)
                    imprimir_todos_album(busca->arvAlbum);
                else
                    printf("Artista nao encontrado!!\n");
                
                break;
            }
            case 8:
            {
                fflush(stdin);
                int achou = 0;
                char nome[50];
                fflush(stdin);
                printf("Informe o artista que deseja cadastrar a musica: ");
                scanf("%[^\n]", nome);
                fflush(stdin);
                ArvArtista *busca = buscaArvSArtista(raiz, nome, &achou);
                if (achou == 1)
                {
                    achou = 0;
                    char nome_album[50];
                    fflush(stdin);
                    printf("Informe o album que deseja cadastrar musica: ");
                    scanf("%[^\n]", nome_album);
                    ArvAlbum *busca_album  = buscaArvSAlbum(busca->arvAlbum, nome_album, &achou);
                    if (achou == 1)
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
                int achou = 0;
                char nome[50];
                fflush(stdin);
                printf("Informe o artista que deseja excluir a musica: ");
                scanf("%[^\n]", nome);
                fflush(stdin);
                ArvArtista *busca = buscaArvSArtista(raiz, nome, &achou);
                if (achou == 1)
                {
                    achou = 0;
                    char nome_album[50];
                    fflush(stdin);
                    printf("Informe o album que deseja excluir a musica: ");
                    scanf("%[^\n]", nome_album);
                    ArvAlbum *busca_album  = buscaArvSAlbum(busca->arvAlbum, nome_album, &achou);
                    if (achou == 1)
                    {
                        char nome_musica[50];
                        int excluiu = 0;
                        fflush(stdin);
                        printf("Informe a musica que deseja excluir: ");
                        scanf("%[^\n]", nome_musica);
                        excluir_musica(busca_album, nome_musica, &excluiu);
                        if (excluiu == 1)
                        {
                            busca_album->album.quantidade_musica--;
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
                int achou = 0;
                char nome[50];
                fflush(stdin);
                printf("Informe o artista que deseja mostrar a musica: ");
                scanf("%[^\n]", nome);
                fflush(stdin);
                ArvArtista *busca = buscaArvSArtista(raiz, nome, &achou);
                if (achou == 1)
                {
                    achou = 0;
                    char nome_album[50];
                    fflush(stdin);
                    printf("Informe o album que deseja mostrar as musicas: ");
                    scanf("%[^\n]", nome_album);
                    ArvAlbum *busca_album  = buscaArvSAlbum(busca->arvAlbum, nome_album, &achou);
                    if (achou == 1)
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
    
    liberarTodaMemoria(raiz);
    return 0;
}