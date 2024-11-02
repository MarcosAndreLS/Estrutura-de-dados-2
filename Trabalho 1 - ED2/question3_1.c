#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*Prototipos*/
typedef struct arvtemporada ArvTemporada; //Arvore
typedef struct arvserie ArvSerie; //Arvore
typedef struct serie Serie;
typedef struct temporada Temporada;
typedef struct participantes Participantes;



ArvSerie* criaArvSerie();
ArvTemporada* criaArvTemp();
ArvSerie* buscaArvSerie(ArvSerie *raiz, int cod);
ArvSerie* buscaArvTempSerie(ArvSerie *raiz, int temp);

ArvTemporada* buscaArvTemp(ArvTemporada *raiz, int temporada);
void imprimirTodosArtistasPersonagem(ArvSerie *raiz, char *personagem);

Serie ler_serie();
Temporada ler_temporada(int temp);

void imprimirSerie(Serie s);
void imprimirTemp(Temporada t);
void inserirArvSerie(ArvSerie **raiz, Serie s);
void imprimirArvTemp(ArvTemporada *raiz);

int alturaNOArvSerie(ArvSerie* raiz);
int fbArvSerie(ArvSerie* raiz);
int maiorArvSerie(int a, int b);
void rotacaoDEDArvSerie(ArvSerie **raiz);
void rotacaoDDEArvSerie(ArvSerie **raiz);
void rotacaoSDArvSerie(ArvSerie **raiz);
void rotacaoSEArvSerie(ArvSerie **raiz);

int alturaNOArvTemp(ArvTemporada* raiz);
int fbArvTemp(ArvTemporada* raiz);
int maiorArvTemp(int a, int b);
void rotacaoSDArvTemp(ArvTemporada **raiz);
void rotacaoSEArvTemp(ArvTemporada **raiz);
void rotacaoDEDArvTemp(ArvTemporada **raiz);
void rotacaoDDEArvTemp(ArvTemporada **raiz);


/*Structs*/

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

typedef struct participantes
{
    char nome_artista[50];
    char nome_personagem[50];
    char descricao_personagem[100];
    struct participantes *prox;
}Participantes;



/*Arvores*/

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
    Participantes *p; //lista
    int alt;
    struct arvtemporada *esq, *dir;
}ArvTemporada;



/*Leituras*/

Serie ler_serie()
{
    Serie s;
    printf("Informe o codigo da serie: ");
    scanf("%d", &s.codigo);
    fflush(stdin);
    printf("Informe o numero de temporadas: ");
    scanf("%d", &s.num_temporadas);
    fflush(stdin);
    printf("Informe o nome da serie: "); 
    scanf("%[^\n]s", s.titulo);
    fflush(stdin);
    return s;
}

Temporada ler_temporada(int temp)
{
    
    Temporada t;
    t.num_temporada = temp;
    printf("Informe o ano da temporada: ");
    scanf("%d", &t.ano);
    fflush(stdin);
    printf("Informe a quantidade de episodios da temporada: ");
    scanf("%d", &t.quantidade_ep);
    fflush(stdin);
    printf("Informe o nome da temporada: ");
    scanf("%[^\n]s", t.titulo_temp);
    fflush(stdin);

    return t;   
}



/*Impressões*/
void imprimirSerie(Serie s)
{
    printf("Codigo da serie: %d\nQuantidade de temporadas: %d\nTitulo da serie: %s\n\n", s.codigo, s.num_temporadas, s.titulo);
}

void imprimirTemp(Temporada t)
{
    printf("Ano: %d\nTemporada: %d\nQuantidade de episodios: %d\nNome da temporada: %s\n\n",t.ano ,t.num_temporada, t.quantidade_ep, t.titulo_temp);
}

void imprimirParticipantes(Participantes* aux) 
{
    printf("Nome do artista: %s\nNome do personagem: %s\nDescricao do personagem: %s\n\n", aux->nome_artista, aux->nome_personagem, aux->descricao_personagem);
}

/*Implementação das Arvores*/

/*Series*/

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
        (*raiz)->arvTemp = NULL;
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

ArvSerie* buscaArvSerie(ArvSerie *raiz, int cod)
{
    while (raiz)
    {
        if (raiz->serie.codigo > cod)
            raiz = raiz->esq;
        else if(raiz->serie.codigo < cod)
            raiz = raiz->dir;
        else  
            return raiz; 
    }

    return NULL; 
}

ArvSerie* buscaArvTempSerie(ArvSerie *raiz, int temp)
{
    for (int i = 1; i <= raiz->serie.num_temporadas; i++)
    {
        if (i == temp)
        {
            return raiz;
        }
        
    }
    
    return NULL;
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


void imprimirArvSerie(ArvSerie *raiz)
{
    if (raiz)
    {
        imprimirArvSerie(raiz->esq);
        imprimirSerie(raiz->serie);
        imprimirArvSerie(raiz->dir);
    }
    
}

/*Temporada*/

ArvTemporada* criaArvTemp()
{
    return NULL;
}

void inserirArvTemp(ArvTemporada **raiz, Temporada t)
{
    if (*raiz == NULL)
    {
        *raiz = (ArvTemporada*)malloc(sizeof(ArvTemporada));
        (*raiz)->temp = t;
        (*raiz)->alt = 0;
        (*raiz)->esq = NULL;
        (*raiz)->dir = NULL;
        (*raiz)->p = NULL;
    }
    else if (t.num_temporada < (*raiz)->temp.num_temporada)
    {
        inserirArvTemp(&(*raiz)->esq, t);
    }
    else if (t.num_temporada > (*raiz)->temp.num_temporada)
    {
        inserirArvTemp(&(*raiz)->dir, t);
    }

    
    (*raiz)->alt = maiorArvTemp(alturaNOArvTemp((*raiz)->esq), alturaNOArvTemp((*raiz)->dir)) + 1;

    
    int fb = fbArvTemp(*raiz);
    if (fb == 2)
    {
        if (fbArvTemp((*raiz)->esq) == 1)
            rotacaoSDArvTemp(raiz);
        else
            rotacaoDEDArvTemp(raiz);
    }
    else if (fb == -2)
    {
        if (fbArvTemp((*raiz)->dir) == -1)
            rotacaoSEArvTemp(raiz);
        else
            rotacaoDDEArvTemp(raiz);
    }
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

void imprimirArvTemp(ArvTemporada *raiz)
{
    if (raiz)
    {
        imprimirArvTemp(raiz->esq);
        imprimirTemp(raiz->temp);
        imprimirArvTemp(raiz->dir);
    }
    
}

int alturaNOArvTemp(ArvTemporada* raiz)
{
    if (raiz == NULL) 
        return -1;
    else 
        return raiz->alt;
}

int fbArvTemp(ArvTemporada* raiz)
{
    return alturaNOArvTemp(raiz->esq) - alturaNOArvTemp(raiz->dir);
}

int maiorArvTemp(int a, int b) 
{
    return (a > b) ? a : b;
}

void rotacaoSDArvTemp(ArvTemporada **raiz)
{
    ArvTemporada *aux = (*raiz)->esq;
    (*raiz)->esq = aux->dir;
    aux->dir = *raiz;
    (*raiz)->alt = maiorArvTemp(alturaNOArvTemp((*raiz)->esq), alturaNOArvTemp((*raiz)->dir)) + 1;
    aux->alt = maiorArvTemp(alturaNOArvTemp(aux->esq), (*raiz)->alt) + 1;
    *raiz = aux;
}

void rotacaoSEArvTemp(ArvTemporada **raiz)
{
    ArvTemporada *aux = (*raiz)->dir;
    (*raiz)->dir = aux->esq;
    aux->esq = *raiz;
    (*raiz)->alt = maiorArvTemp(alturaNOArvTemp((*raiz)->esq), alturaNOArvTemp((*raiz)->dir)) + 1;
    aux->alt = maiorArvTemp(alturaNOArvTemp(aux->dir), (*raiz)->alt) + 1;
    *raiz = aux;
}

void rotacaoDEDArvTemp(ArvTemporada **raiz)
{
    rotacaoSEArvTemp(&(*raiz)->esq);
    rotacaoSDArvTemp(raiz);
}

void rotacaoDDEArvTemp(ArvTemporada **raiz)
{
    rotacaoSDArvTemp(&(*raiz)->dir);
    rotacaoSEArvTemp(raiz);
}

/*Implementação da lista*/

/*Participantes*/

ArvTemporada* criarLista()
{
    return NULL;
}

void inserirLista(ArvTemporada* lista, int temp) 
{
    ArvTemporada* temp_serie = buscaArvTemp(lista, temp);
    if (temp_serie != NULL) 
    {
        Participantes* aux = (Participantes*)malloc(sizeof(Participantes));
        printf("Informe o nome do artista: ");
        fflush(stdin);
        scanf("%[^\n]s", aux->nome_artista);
        printf("Informe o nome do personagem: ");
        fflush(stdin);
        scanf("%[^\n]s", aux->nome_personagem);
        printf("Informe uma descricao sobre o personagem: ");
        fflush(stdin);
        scanf("%[^\n]s", aux->descricao_personagem);
        if (temp_serie->p == NULL || strcmp(aux->nome_artista, temp_serie->p->nome_artista) < 0)
        {
            aux->prox = temp_serie->p;
            temp_serie->p = aux;
        }else 
        {
            while (temp_serie->p->prox != NULL && strcmp(aux->nome_artista, temp_serie->p->prox->nome_artista) > 0)
            {
                temp_serie->p = temp_serie->p->prox;
            }
            aux->prox = temp_serie->p->prox;
            temp_serie->p->prox = aux;
        }
        
    } else {
        printf("Temporada nao encontrada.\n");
    }
}


void imprimirTodosParticipantes(ArvTemporada *temp_serie_busca, int temporada) 
{
    ArvTemporada *aux = buscaArvTemp(temp_serie_busca, temporada);
    if (aux != NULL) {
        Participantes *participante = aux->p;
        while (participante != NULL) 
        {
            imprimirParticipantes(participante);
            participante = participante->prox;
        }
    } else 
    {
        printf("Essa temporada nao existe.\n");
    }
}

void imprimirTodosArtistasPersonagem(ArvSerie *raiz, char *personagem) 
{
    ArvTemporada *temporada = raiz->arvTemp;
    int i = 1;
    while (temporada != NULL) {
        Participantes *participante = temporada->p;
        printf("\nTEMPORADA %d\n\n", i);
        while (participante != NULL) 
        {
            if (strcmp(participante->nome_personagem, personagem) == 0) {
                printf("Nome do artista: %s\n\n", participante->nome_artista);
            }
            participante = participante->prox;
        }
        i++;
        temporada = temporada->dir;
    }
}


void liberarArvTemp(ArvTemporada *raiz) {
    if (raiz) {
        liberarArvTemp(raiz->esq);
        liberarArvTemp(raiz->dir);
        Participantes *p = raiz->p;
        while (p) {
            Participantes *temp = p;
            p = p->prox;
            free(temp);
        }
        free(raiz);
    }
}

/* Libera a memória de uma árvore de séries */
void liberarArvSerie(ArvSerie *raiz) {
    if (raiz) {
        liberarArvTemp(raiz->arvTemp);  // Libera a árvore de temporadas associada à série
        liberarArvSerie(raiz->esq);
        liberarArvSerie(raiz->dir);
        free(raiz);
    }
}

/* Função para liberar a memória de todas as séries */
void liberarTodasSeries(ArvSerie *raiz) {
    liberarArvSerie(raiz);
}

void libera_lista(Participantes *lista)
{
    Participantes *aux = lista;
    while (aux != NULL)
    {
        free(aux);
        aux = aux->prox; 
    }
    
}



/*MENU...*/
void menu()
{
    printf("----------------------MENU----------------------\n");
    printf("| 1 - CADASTRAR SERIE                          |\n");
    printf("| 2 - CADASTRAR TEMPORADA                      |\n");
    printf("| 3 - CADASTRAR PARTICIPANTE                   |\n");
    printf("| 4 - IMPRIMIR SERIES                          |\n");
    printf("| 5 - IMPRIMIR TODAS TEMPORADAS                |\n");
    printf("| 6 - IMPRIMIR PERSONAGENS                     |\n");
    printf("| 7 - IMPRIMIR ARTISTAS                        |\n");
    printf("| 0 - SAIR                                     |\n");
    printf("------------------------------------------------\n");

}


int main() 
{
    ArvSerie *raiz_s = criaArvSerie();

    int op = -1;
    int codigo;
    int temp;

    while (op != 0) {
        menu();
        scanf("%d", &op);
        switch (op) {
            case 1:
                inserirArvSerie(&raiz_s,ler_serie());
                break;
            case 2: {
                printf("Informe o codigo da serie: ");
                scanf("%d", &codigo);
                ArvSerie *b = buscaArvSerie(raiz_s, codigo);
                                
                if (b != NULL) {
                    printf("\nSerie encontrada =)\n\n");
                    printf("Informe o numero da temporada: ");
                    scanf("%d", &temp);
                    ArvSerie* encontrou = buscaArvTempSerie(b ,temp);
                    if (encontrou != NULL)
                    { 
                        
                        inserirArvTemp(&(b->arvTemp), ler_temporada(temp));
                    }else
                        printf("Temporada nao existe.\n");                                      
                } else {
                    printf("Esta serie nao existe.\n");
                }
                break;
            }
            case 3: {
                printf("Informe o codigo da serie: ");
                scanf("%d", &codigo);
                ArvSerie *b = buscaArvSerie(raiz_s, codigo);
                if (b != NULL) {
                    printf("\nSerie encontrada =)\n\n");
                    printf("Informe a temporada: ");
                    scanf("%d", &temp);
                    ArvTemporada *temp_serie = buscaArvTemp(b->arvTemp, temp);
                    if (temp_serie != NULL) {
                        inserirLista(temp_serie, temp);
                        printf("Personagem inserido na temporada.\n");
                    } else {
                        printf("Essa temporada nao existe.\n");
                    }
                } else {
                    printf("Esta serie nao existe.\n");
                }
                break;
            }
            case 4:
                imprimirArvSerie(raiz_s);
                break;
            case 5: {
                printf("Informe o codigo da serie: ");
                scanf("%d", &codigo);
                ArvSerie *b = buscaArvSerie(raiz_s, codigo);
                if (b != NULL) {
                    imprimirArvTemp(b->arvTemp);
                } else {
                    printf("Esta serie nao existe.\n");
                }
                break;
            }
            case 6: {
                printf("Informe o codigo da serie: ");
                scanf("%d", &codigo);
                ArvSerie *busca = buscaArvSerie(raiz_s, codigo);
                if (busca != NULL) {
                    printf("\nSerie encontrada =)\n");
                    printf("Informe a temporada: ");
                    scanf("%d", &temp);
                    ArvSerie *temp_serie_busca = buscaArvTempSerie(raiz_s, temp);
                    if (temp_serie_busca != NULL) {
                        imprimirTodosParticipantes(temp_serie_busca->arvTemp, temp);
                    } else {
                        printf("Essa temporada nao existe.\n");
                    }
                } else {
                    printf("Esta serie nao existe.\n");
                }
                break;
            }
            case 7:
                printf("Informe o codigo da serie: ");
                scanf("%d", &codigo);
                fflush(stdin);
                ArvSerie *busca = buscaArvSerie(raiz_s, codigo);
                if (busca != NULL) {
                    char personagem[50];
                    printf("Informe o nome do personagem: "); 
                    scanf("%[^\n]s", personagem);
                    fflush(stdin);
                    imprimirTodosArtistasPersonagem(busca, personagem);
                } else {
                    printf("Esta serie nao existe.\n");
                }
                break;  
            default:
                if (op != 0)
                    printf("Opcao invalida!\n");
                
                break;
        }
    }

    liberarTodasSeries(raiz_s);
    libera_lista(raiz_s->arvTemp->p);

    return 0;
}