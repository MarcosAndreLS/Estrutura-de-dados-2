#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define TAM 81
#define INF 999999

/*Prototipos*/
typedef struct vertice Vertice;
typedef struct grafo Grafo;

/*Structs*/
typedef struct vertice{

    int discos[4];
}Vertice;

typedef struct grafo {
    Vertice *vertices;
    int **arestas;

}Grafo;

/*Declaração das funções*/

Grafo *Criar_Grafo(int n);
void menu();

/*Impressões*/
void Imprimir_Matriz_adjacente(Grafo *G, int n);
void Imprimir_Menor_Caminho_Bellman(int vertices, int destino, int verticeAnterior[], int distancia[]);
void Imprimir_conteudo_do_vertice(Grafo *G, int linha);

void Inserir_vertices_e_arestas(Grafo *G);

void bellmanFord(int **grafo, int vertices, int origem, int destino);

void Liberar_Grafo(Grafo **G, int qtdVertice);

/*Jogo*/
void Vertices_adjacentes(int *vetorVertice, int *vetorResposta, int *cont);
int Verificar_Vitoria(Grafo *G, int vertice, int pinoDesejado);
int Verificar_Movimento_Valido(int *vetorResposta, int vertice);
void jogar(Grafo *G, int vertice);


Grafo *Criar_Grafo(int n){
    // n é o numero de vertices ou configuracoes possiveis
    Grafo *G;

    G = (Grafo *) malloc(sizeof(Grafo));
    
    // Alocação de memoria para o vetor de vertices
    G->vertices = (Vertice *) malloc(n * sizeof(Vertice));
    
    // Alocação de memoria para a matriz de arestas
    G->arestas = (int **) malloc(n * sizeof(int *));
    for(int i = 0; i < n; i++){
        G->arestas[i] = (int *) calloc(n, sizeof(int));
    }

    return G;
}

void Imprimir_Matriz_adjacente(Grafo *G, int n){
    printf("Vertices: \n");
    for(int i = 0; i < n; i++){
        printf(" %d", i);
    }
    printf("\n\n");
    for(int i = 0; i < n; i++){
        printf("%d  ", i);
        for(int j = 0; j < n; j++){
            printf("%d ", G->arestas[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void Inserir_vertices_e_arestas(Grafo *G){
    FILE *verticesEarestas; 

    verticesEarestas = fopen("../torre_hanoi.txt", "r");
    if(verticesEarestas == NULL){
        printf("Error ao localizar o arquivo desejado!!");
    }else{

        int verticeAtual = 0, vermelho, amarelo, verde, rosa, aresta1, aresta2, aresta3;

        // Inserir os valores dos vertices no grafo a partir do arquivo ../
        while (fscanf(verticesEarestas, "%d %d %d %d %d %d %d %d", &verticeAtual, &vermelho, &amarelo, &verde, &rosa, &aresta1, &aresta2, &aresta3) != EOF){

        //preenche os pinos dos vertices
        G->vertices[verticeAtual].discos[0] = vermelho;
        G->vertices[verticeAtual].discos[1] = amarelo;
        G->vertices[verticeAtual].discos[2] = verde;
        G->vertices[verticeAtual].discos[3] = rosa;

        // marca a ligação das arestas na matriz adjacente
        G->arestas[verticeAtual][aresta1] = 1;
        G->arestas[verticeAtual][aresta2] = 1;
        if(aresta3 != 9999)
            G->arestas[verticeAtual][aresta3] = 1;
    }
    }
    
}

void Imprimir_conteudo_do_vertice(Grafo *G, int linha){
    printf("%d: (%d, %d, %d, %d)\n", linha, G->vertices[linha].discos[0], G->vertices[linha].discos[1], G->vertices[linha].discos[2], G->vertices[linha].discos[3]);
}

void bellmanFord(int **grafo, int vertices, int origem, int destino) {
    LARGE_INTEGER start_time, end_time, frequency;
    double elapsed_time_ms;
    int possuiCicloNegativo = 0;
    int *distancia, *verticeAnterior;
    distancia = (int*)malloc(vertices * sizeof(int));
    verticeAnterior = (int*)malloc(vertices * sizeof(int));
    // Os arrays de distância e vértices anteriores são inicializados com valores que indicam a 
    // ausência de ligação(infinito) ou que a posição do vetor ainda não foi utilizada(-1)   
    for (int i = 0; i < vertices; i++) {
        distancia[i] = INF;
        verticeAnterior[i] = -1;
    }
    // A distância do vértice de origem para ele mesmo é zero
    distancia[origem] = 0;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start_time);
    // Encontra o caminho mais curto partindo do vértice de origem para todos os demais vértices
    for (int qtdRelaxamentos = 0; qtdRelaxamentos < vertices - 1; qtdRelaxamentos++) {
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                if (grafo[i][j] && distancia[i] != INF && distancia[i] + grafo[i][j] < distancia[j]) {
                    distancia[j] = distancia[i] + grafo[i][j];
                    verticeAnterior[j] = i;
                }
            }
        }
    }

    // Checa se existe um ciclo negativo no grafo, 
    // caso exista não é possível encontrar o menor caminho no grafo devido ás limitações do algoritmo
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (grafo[i][j] && distancia[i] != INF && distancia[i] + grafo[i][j] < distancia[j]) {
                printf("O grafo contem um ciclo negativo.\n");
                possuiCicloNegativo = 1;
                j = vertices;
                i = j;
            }
        }
    }
    QueryPerformanceCounter(&end_time);
    elapsed_time_ms = ((double)(end_time.QuadPart - start_time.QuadPart) * 1000.0) / frequency.QuadPart;
    printf("Tempo decorrido: %.5f ms\n", elapsed_time_ms);
    // caso não exista um ciclo negativo, imprime o menor caminho
    if(!possuiCicloNegativo)
        Imprimir_Menor_Caminho_Bellman(vertices,destino,verticeAnterior,distancia);
    free(distancia);
    free(verticeAnterior);
}

void Imprimir_Menor_Caminho_Bellman(int vertices, int destino, int verticeAnterior[], int distancia[]){
    // Mostrar o caminho mais curto para o vértice de destino como também a distância
    printf("\nCaminho mais curto: ");
    int comprimentocaminho = 0;
    int *caminhovertices; caminhovertices = (int*)malloc(vertices * sizeof(int));

    int verticeatual = destino;

    while (verticeatual != -1) {
        caminhovertices[comprimentocaminho++] = verticeatual;
        verticeatual = verticeAnterior[verticeatual];
    }

    for (int i = comprimentocaminho - 1; i >= 0; i--) {
        printf("%d ", caminhovertices[i]);
        if (i > 0)
            printf("-> ");
    }
    printf("\nDistancia: %d\n", distancia[destino]);
    free(caminhovertices);
}

void Liberar_Grafo(Grafo **G, int qtdVertice){
    for (int i = 0; i < qtdVertice; i++){
        free((*G)->arestas[i]);
        (*G)->arestas[i] = NULL;
    }
    free((*G)->vertices);
    (*G)->vertices = NULL;

    free(*G);
    *G = NULL;
}

// jogo
// verifica resposta informa para quais arestas um vertice pode ir
void Vertices_adjacentes(int *vetorVertice, int *vetorResposta, int *cont){
    *cont = 0;

    for(int i = 0; i < 81; i++){
        if(vetorVertice[i] == 1){
            if(*cont == 0)
                vetorResposta[0] = i;
            if(*cont == 1)
                vetorResposta[1] = i;
            if(*cont == 2)
                vetorResposta[2] = i;
            *cont += 1;
        }
    }
}

// verificar se todos os pinos estão no 3 pino, retorna 4 caso estejam.
int Verificar_Vitoria(Grafo *G, int vertice, int pinoDesejado){
    int incremento = 0;
    for (int i = 0; i < 4; i++){
        if(G->vertices[vertice].discos[i] == pinoDesejado)
        {
            incremento += 1;
        }   
    }
    return incremento; // Retorna 1 se todos os discos estiverem no pino desejado, 0 caso contrário.
}

// verifica se o vertice informado é uma opção para onde ir
int Verificar_Movimento_Valido(int *vetorResposta, int vertice){
    int cont = 1;
    if (vertice == vetorResposta[0]) 
        cont = 0;
    if (vertice == vetorResposta[1])
        cont = 0;
    if (vertice == vetorResposta[2])
        cont = 0;
    
    return cont;
}

// Essa função permite que o usuário jogue o jogo
void jogar(Grafo *G, int vertice){
    int numMovimentos = 0;
    int vetorResposta[3], cont, flagParada = 1;
       
    do{
         // Esse while continuar até que o usuário ganhe ou desista
        printf("\nVertice atual e conteudo.\n ");
        Imprimir_conteudo_do_vertice(G, vertice);
        printf("Possibilidades de para onde pode ir: \n");

        // zera o vetor de resposta
        memset(vetorResposta, 0, sizeof(vetorResposta));

        // verifica resposta informa para quais arestas um vertice pode ir
        Vertices_adjacentes(G->arestas[vertice], vetorResposta, &cont);
        
        Imprimir_conteudo_do_vertice(G, vetorResposta[0]);
        Imprimir_conteudo_do_vertice(G, vetorResposta[1]);
        
        if(cont == 3){
            Imprimir_conteudo_do_vertice(G, vetorResposta[2]);
        }

        printf("Deseja continuar jogando? 1 - sim, 0 - nao: ");
        scanf("%d", &flagParada);

        // entra nesse if se o usuário deseja continuar jogando, se não entrar isso significa que ele desistiu.
        if(flagParada == 1){
            
            printf("\nDigite o indice do vertice que deseja ir: ");
            scanf("%d", &vertice);

            while ((vertice < 0 || vertice > 80) || (Verificar_Movimento_Valido(vetorResposta, vertice))){
                printf("Indice de vertice nao existe ou foi informado um vertice que nao tem ligacao com o vertice atual.\n");
                printf("Digite novamente o vertice que deseja ir: ");
                scanf("%d", &vertice);
            }
            numMovimentos++;
        }else if(flagParada == 0){
            printf("Voce desistiu em %d movimentos\n", numMovimentos);
        }else{
            printf("Opcao invalida\n");
        }
    }while((Verificar_Vitoria(G, vertice, 1) != 4) && (Verificar_Vitoria(G, vertice, 2) != 4) && (Verificar_Vitoria(G, vertice, 3) != 4) && (flagParada != 0));
    

    if(flagParada == 1)
        printf("Voce venceu em %d movimentos\n", numMovimentos);
}

void menu()
{
    printf("======================================MENU=======================================\n");
    printf(": 1 - Imprimir valores de todos os vertices                                     :\n");
    printf(": 2 - Imprimir um vertice                                                       :\n");
    printf(": 3 - Imprimir matriz adjacente arestas                                         :\n");
    printf(": 4 - Imprimir para onde as arestas de vertice estao ligadas                    :\n");
    printf(": 5 - Ford-Moore-Bellman                                                        :\n");
    printf(": 6 - Jogar                                                                     :\n");
    printf(": 0 - Sair                                                                      :\n");
    printf("=================================================================================\n");
}

int main(){
    Grafo *G;
    int op, vertice, opJogo, cont, vetorResposta[3], origem, destino;

    G = Criar_Grafo(81);

    Inserir_vertices_e_arestas(G);

    do{
        menu();
        scanf("%d", &op);

        switch (op){
        case 0:
            printf("Saindo...\n");
            break;
        case 1:
            for(int i = 0; i < TAM; i++)
                Imprimir_conteudo_do_vertice(G, i); // imprimir valores dos vertices
            break;
        case 2:
            printf("Digite o indice do vertice: ");
            scanf("%d", &vertice);
            if(vertice >= 0 && vertice <= 80)
                Imprimir_conteudo_do_vertice(G, vertice);
            else
                printf("Indice de vertice nao existe.\n");
            break;
        case 3:
            Imprimir_Matriz_adjacente(G, TAM); //imprimir arestas
            break;
        case 4:
            cont = 0;
            printf("Digite o indice do vertice: ");
            scanf("%d", &vertice);

            if(vertice >= 0 && vertice <= 80){
                Vertices_adjacentes(G->arestas[vertice], vetorResposta, &cont);
                
                Imprimir_conteudo_do_vertice(G, vetorResposta[0]);
                Imprimir_conteudo_do_vertice(G, vetorResposta[1]);
                
                if(cont == 3){
                    Imprimir_conteudo_do_vertice(G, vetorResposta[2]);
                }
                memset(vetorResposta, 0, sizeof(vetorResposta));
                
            }else
                printf("Indice de vertice nao existe.\n");
            break;
        case 5:
            printf("Ford-Moore-Bellman\n");
            printf("Digite o vertice de origem: ");
            scanf("%d", &origem);
            printf("Digite o vertice de destino: ");
            scanf("%d", &destino);

            if((origem >= 0 && origem <= 80) && (destino >= 0 && destino <= 80) )
                bellmanFord(G->arestas, TAM, origem, destino);
            else
                printf("Verifique se os vertices informados existem\n");
            break;
        case 6:
            printf("\nDeseja comecar de algum vertice? 1 - sim, 2 - nao: ");
            scanf("%d", &opJogo);

            if(opJogo == 1){
                printf("\nDigite o indice do vertice: ");
                scanf("%d", &vertice);

                if(vertice >= 0 && vertice <= 80)
                    jogar(G, vertice);
                else
                    printf("\nIndice de vertice nao existe.\n");
            }else if(opJogo == 2)
                jogar(G, 0);
            else
                printf("\nOpcao invalida\n");
            break;
        default:
            printf("Opcao invalida.\n");
            break;
        }
    }while (op != 0);
    Liberar_Grafo(&G, 81);
    return 0;
}
