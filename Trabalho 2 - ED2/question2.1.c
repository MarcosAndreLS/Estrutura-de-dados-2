#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct artista {
    char nome[50];
} Artista;

typedef struct arvartista {
    Artista artistas[2];
    int Nkeys;
    struct arvartista *esq, *cen, *dir;
} ArvArtista;

ArvArtista *criaNo(Artista artista1, Artista artista2) {
    ArvArtista *novoNo = (ArvArtista *)malloc(sizeof(ArvArtista));
    novoNo->artistas[0] = artista1;
    novoNo->artistas[1] = artista2;
    novoNo->Nkeys = (artista2.nome[0] != '\0') ? 2 : 1;
    novoNo->esq = novoNo->cen = novoNo->dir = NULL;
    return novoNo;
}

ArvArtista *insereNo(ArvArtista *tree, ArvArtista *novoNo) {
    if (tree == NULL) {
        return novoNo;
    }

    if (strcmp(novoNo->artistas[0].nome, tree->artistas[0].nome) < 0) {
        tree->esq = insereNo(tree->esq, novoNo);
    } else if (strcmp(novoNo->artistas[0].nome, tree->artistas[0].nome) > 0) {
        tree->dir = insereNo(tree->dir, novoNo);
    } else if (novoNo->artistas[1].nome[0] != '\0') {
        tree->cen = insereNo(tree->cen, novoNo);
    }

    return tree;
}

ArvArtista *buscaTestes(ArvArtista *tree, char *codigo, int n) {
    if (tree != NULL) {
        if (strcmp(codigo, tree->artistas[0].nome) == 0) {
            printf("%d-left ", n);
            return tree;
        } else if (tree->Nkeys == 2 && strcmp(codigo, tree->artistas[1].nome) == 0) {
            printf("%d-center ", n);
            return tree;
        } else {
            if (strcmp(codigo, tree->artistas[0].nome) < 0) {
                printf("%d-left ", n);
                return buscaTestes(tree->esq, codigo, n + 1);
            } else if (tree->Nkeys == 1 || strcmp(codigo, tree->artistas[1].nome) < 0) {
                printf("%d-center ", n);
                return buscaTestes(tree->cen, codigo, n + 1);
            } else {
                printf("%d-right ", n);
                return buscaTestes(tree->dir, codigo, n + 1);
            }
        }
    }
    return NULL;
}

void liberaArvore(ArvArtista *tree) {
    if (tree != NULL) {
        liberaArvore(tree->esq);
        liberaArvore(tree->cen);
        liberaArvore(tree->dir);
        free(tree);
    }
}

int main() {
    ArvArtista *tree = NULL;

    char *artistas[30] = {
        "Ana", "Beatriz", "Carlos", "Daniel", "Eduardo", "Fernanda", "Gabriel", "Helena", "Igor",
        "Julia", "Kleber", "Laura", "Marcos", "Natalia", "Otavio", "Patricia", "Quirino", "Rafael",
        "Sabrina", "Tiago", "Ursula", "Vitor", "Wagner", "Ximena", "Yasmin", "Zacarias",
        "Alice", "Bruno", "Cecilia", "Diego"};

    double total_time = 0;

    for (int i = 0; i < 30; i++) {
        Artista artista1, artista2;
        strncpy(artista1.nome, artistas[i], sizeof(artista1.nome) - 1);
        artista1.nome[sizeof(artista1.nome) - 1] = '\0';
        artista2.nome[0] = '\0';

        ArvArtista *novoNo = criaNo(artista1, artista2);
        tree = insereNo(tree, novoNo);

        int n = 0;
        printf("Caminho percorrido para encontrar '%s': ", artistas[i]);

        clock_t start_time = clock();
        ArvArtista *resultado = buscaTestes(tree, artistas[i], n);
        clock_t end_time = clock();

        double elapsed_time = ((double)(end_time - start_time) / CLOCKS_PER_SEC) * 1000000000;
        total_time += elapsed_time;

        printf("\n");

        if (resultado != NULL) {
            printf("'%s' encontrado!\n", artistas[i]);
        } else {
            printf("'%s' nao encontrado.\n", artistas[i]);
        }

        printf("Tempo de execucao: %.2f nanossegundos\n", elapsed_time);
    }
    printf("\nTempo total de execucao: %.2f nanossegundos\n", total_time);
    printf("Media do tempo total de execucao: %.2f nanossegundos\n", total_time/30);

    liberaArvore(tree);

    return 0;
}
