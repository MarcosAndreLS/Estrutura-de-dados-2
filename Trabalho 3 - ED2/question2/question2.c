#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 1000

/*Prototipos*/
typedef struct aresta Aresta;
typedef struct grafo Grafo;
typedef struct filaprioridade FilaPrioridade;

/*Structs*/
typedef struct aresta{
    int vertice;
    double confiabilidade;
} Aresta;

typedef struct grafo{
    Aresta *arestas;
    int num_arestas;
} Grafo;

typedef struct filaprioridade{
    double confiabilidade;
    int vertice;
} FilaPrioridade;

/*Declaração das funções*/
void Liberar_Grafo(Grafo *grafo, int num_vertices);
Grafo* Criar_Grafo(int num_vertices);
void Imprimir_Caminho_Mais_Confiavel(const int *predecessores, int origem, int destino);
void Liberar_Dijkstra_Memoria(bool *visitados, double *confiabilidade, FilaPrioridade *fp, int *predecessores);
void dijkstra(const Grafo *grafo, int origem, int destino, int num_vertices);
void Inserir_Arestas(Grafo *grafo, int u, int v, double confiabilidade);
void Ler_Arestas_Do_Arquivo(FILE *arquivo, Grafo *grafo, int num_arestas);


// Função para liberar a memória alocada para o grafo
void Liberar_Grafo(Grafo *grafo, int num_vertices) {
    for (int i = 0; i < num_vertices; ++i) {
        free(grafo[i].arestas);
    }
    free(grafo);
}

// Função para preencher o grafo a partir de um arquivo
Grafo* Criar_Grafo(int num_vertices) {
    Grafo *grafo = (Grafo *)malloc(num_vertices * sizeof(Grafo));
    for (int i = 0; i < num_vertices; ++i) {
        grafo[i].num_arestas = 0;
        grafo[i].arestas = NULL;
    }
    return grafo;
}

void Ler_Arestas_Do_Arquivo(FILE *arquivo, Grafo *grafo, int num_arestas) {

    for (int i = 0; i < num_arestas; ++i) {
        int u, v;
        double confiabilidade;
        fscanf(arquivo, "%d %d %lf", &u, &v, &confiabilidade);
        Inserir_Arestas(grafo, u, v, confiabilidade);
    }
}

void Inserir_Arestas(Grafo *grafo, int u, int v, double confiabilidade) {
    grafo[u].arestas = (Aresta *)realloc(grafo[u].arestas, (grafo[u].num_arestas + 1) * sizeof(Aresta));
    grafo[u].arestas[grafo[u].num_arestas++] = (Aresta){v, confiabilidade};
}

// Função para imprimir o caminho mais confiável
void Imprimir_Caminho_Mais_Confiavel(const int *predecessores, int origem, int destino) {
    if (destino == origem) {
        printf("%d", origem);
    } else if (predecessores[destino] == -1) {
        printf("Caminho inexistente entre %d e %d\n", origem, destino);
    } else {
        Imprimir_Caminho_Mais_Confiavel(predecessores, origem, predecessores[destino]);
        printf(" -> %d", destino);
    }
}

// Função para liberar a memória alocada durante o algoritmo de Dijkstra
void Liberar_Dijkstra_Memoria(bool *visitados, double *confiabilidade, FilaPrioridade *fp, int *predecessores) {
    free(visitados);
    free(confiabilidade);
    free(fp);
    free(predecessores);
}

// Função principal do algoritmo de Dijkstra
void dijkstra(const Grafo *grafo, int origem, int destino, int num_vertices) {
    bool *visitados = (bool *)malloc(num_vertices * sizeof(bool));
    double *confiabilidade = (double *)malloc(num_vertices * sizeof(double));
    int *predecessores = (int *)malloc(num_vertices * sizeof(int));

    for (int i = 0; i < num_vertices; ++i) {
        visitados[i] = false;
        confiabilidade[i] = 0.0;
        predecessores[i] = -1;
    }
    confiabilidade[origem] = 1.0;

    FilaPrioridade *fp = (FilaPrioridade *)malloc(num_vertices * sizeof(FilaPrioridade));
    int tamanho_fp = 0;
    fp[tamanho_fp++] = (FilaPrioridade){1.0, origem};

    while (tamanho_fp > 0) {
        FilaPrioridade min_confiab = fp[0];
        int min_idx = 0;
        for (int i = 1; i < tamanho_fp; ++i) {
            if (fp[i].confiabilidade > min_confiab.confiabilidade) {
                min_confiab = fp[i];
                min_idx = i;
            }
        }

        fp[min_idx] = fp[--tamanho_fp];
        visitados[min_confiab.vertice] = true;

        if (min_confiab.vertice == destino) {
            printf("O caminho mais confiavel entre %d e %d tem confiabilidade %.4lf\n", origem, destino, min_confiab.confiabilidade);
            printf("Caminho: ");
            Imprimir_Caminho_Mais_Confiavel(predecessores, origem, destino);
            printf("\n");

            Liberar_Dijkstra_Memoria(visitados, confiabilidade, fp, predecessores);
            return;
        }

        for (int i = 0; i < grafo[min_confiab.vertice].num_arestas; ++i) {
            Aresta aresta = grafo[min_confiab.vertice].arestas[i];
            if (!visitados[aresta.vertice]) {
                double nova_confiab = min_confiab.confiabilidade * aresta.confiabilidade;
                if (nova_confiab > confiabilidade[aresta.vertice]) {
                    confiabilidade[aresta.vertice] = nova_confiab;
                    predecessores[aresta.vertice] = min_confiab.vertice;
                    fp[tamanho_fp++] = (FilaPrioridade){nova_confiab, aresta.vertice};
                }
            }
        }
    }

    printf("Nao ha caminho confiavel entre %d e %d\n", origem, destino);
    Liberar_Dijkstra_Memoria(visitados, confiabilidade, fp, predecessores);
}

int main() {
    FILE *arquivo = fopen("../Grafo.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int num_vertices, num_arestas;
    fscanf(arquivo, "%d %d", &num_vertices, &num_arestas);

    Grafo *grafo = Criar_Grafo(num_vertices);
    Ler_Arestas_Do_Arquivo(arquivo, grafo, num_arestas * 2);
    
    int origem, destino;
    printf("Digite o vertice de origem e o vertice de destino: ");
    scanf("%d %d", &origem, &destino);

    if (origem < 0 || origem >= num_vertices || destino < 0 || destino >= num_vertices) {
        printf("Vertices invalidos. Certifique-se de que os vertices inseridos existem no grafo.\n");
    } else {
        dijkstra(grafo, origem, destino, num_vertices);
    }

    Liberar_Grafo(grafo, num_vertices);

    fclose(arquivo);

    return 0;
}
