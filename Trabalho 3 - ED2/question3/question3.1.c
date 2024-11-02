#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX101 101
#define MAX150 150

typedef struct func {
    char matricula[7];
} Func;

char* matricula_aleatoria() {
    char* matricula = malloc(7 * sizeof(char));

    for (int i = 0; i < 6; i++) {
        matricula[i] = '0' + rand() % 10;
    }
    matricula[6] = '\0';

    return matricula;
}

void inicializarTabela(Func *f, int MAX) {
    for (int i = 0; i < MAX; i++) {
        strcpy(f[i].matricula, "\0");
    }
}

int colisaoRotacao(int chave, char primeiroDigito, int MAX) {
    return (chave + (primeiroDigito - '0')) % MAX;
}

int funcaoHashStringRotacao(char *str) {
    char chave[7];
    sprintf(chave, "%c%c%s", str[4], str[5], str);
    int d2 = chave[1] - '0';
    int d4 = chave[3] - '0';
    int d6 = chave[5] - '0';
    int valor_hash = d2 * 100 + d4 * 10 + d6;
    return valor_hash % MAX101;
}

void inserirTabelaRotacao(Func *tabela, int *numColisoes, int *countTabela, int MAX, int num) {
    Func f;
    snprintf(f.matricula, sizeof(f.matricula), "%d", num);
    int indice = funcaoHashStringRotacao(f.matricula);
    
    if ((*countTabela) < MAX) {
        if (tabela[indice].matricula[0] != '\0') {
            (*numColisoes)++;
            int novo = colisaoRotacao(indice, f.matricula[0], MAX);
            
            while (tabela[novo].matricula[0] != '\0') {
                (*numColisoes)++;
                novo = colisaoRotacao(novo, f.matricula[0], MAX);   
            }
            tabela[novo] = f;
            (*countTabela)++;
        } else {
            (*countTabela)++;
            tabela[indice] = f;
        }
    } else {
        (*countTabela)++;
        tabela[indice] = f;
    }
}

int colisaoFoldShift(int chave, int MAX) {
    return (chave + 7) % MAX;
}

int funcaoHashStringFoldShift(char *str) {
    int tam = strlen(str);
    unsigned int hash = 0;

    unsigned int aux1 = 0;
    unsigned int aux2 = 0;

    for (int i = 0; i < tam; i++) {
        if (i == 0 || i == 2 || i == 5)
            aux1 = aux1 * 10 + (str[i] - '0');
        else
            aux2 = aux2 * 10 + (str[i] - '0');
    }
    
    hash = (aux1 + aux2) % MAX101;

    return hash;
}

void inserirTabelaFoldShift(Func *tabela, int *numColisoes, int *countTabela, int MAX, int num) {
    Func f;
    snprintf(f.matricula, sizeof(f.matricula), "%d", num);
    int indice = funcaoHashStringFoldShift(f.matricula);
    
    if ((*countTabela) < MAX) {
        if (tabela[indice].matricula[0] != '\0') {
            (*numColisoes)++;
            int novo = colisaoFoldShift(indice, MAX);
            
            while (tabela[novo].matricula[0] != '\0') {
                (*numColisoes)++;
                novo = colisaoFoldShift(novo, MAX);
            }  
            tabela[novo] = f;
            (*countTabela)++;
        } else {
            (*countTabela)++;
            tabela[indice] = f;
        }
    } else {
        (*countTabela)++;
        tabela[indice] = f;
    }
}

void imprimirTabela(Func *tabela, int MAX, const char *tableLabel) {
    printf("\n%s:\n", tableLabel);
    for (int i = 0; i < MAX; i++) {
        printf("%d: %s\n", i, tabela[i].matricula);
    }
}

int main() {
    Func *tabela101 = (Func *)malloc(MAX101 * sizeof(Func));
    Func *tabela150 = (Func *)malloc(MAX150 * sizeof(Func));

    int numColisoesRotacao101 = 0;
    int numColisoesFoldShift101 = 0;
    int numColisoesRotacao150 = 0;
    int numColisoesFoldShift150 = 0;
    int countTabelaRotacao101 = 0;
    int countTabelaRotacao150 = 0;
    int countTabelaFoldShift101 = 0;
    int countTabelaFoldShift150 = 0;

    srand(time(NULL));

    inicializarTabela(tabela101, MAX101);
    inicializarTabela(tabela150, MAX150);

    int i = 0;

    while (i < 1000) {
        int num = rand() % 900000 + 100000;
        inserirTabelaRotacao(tabela101, &numColisoesRotacao101, &countTabelaRotacao101, MAX101, num);     
        inserirTabelaRotacao(tabela150, &numColisoesRotacao150, &countTabelaRotacao150, MAX150, num);
        i++;
        // printf("\n\n\ni : %d\n\n\n", i);
    }

    imprimirTabela(tabela101, MAX101, "Table 101 (Rotacao)");
    imprimirTabela(tabela150, MAX150, "Table 150 (Rotacao)");
    inicializarTabela(tabela101, MAX101);
    inicializarTabela(tabela150, MAX150);
    i = 0;
    while (i < 1000) {
        int num = rand() % 900000 + 100000;
        inserirTabelaFoldShift(tabela101, &numColisoesFoldShift101, &countTabelaFoldShift101, MAX101, num);
        inserirTabelaFoldShift(tabela150, &numColisoesFoldShift150, &countTabelaFoldShift150, MAX150, num);
        i++;
        // printf("\n\n\naaaa : %d\n\n\n", i);
    }

    imprimirTabela(tabela101, MAX101, "Table 101 (FoldShift)");
    imprimirTabela(tabela150, MAX150, "Table 150 (FoldShift)");

    printf("\nColisoes Rotacao 101: %d || Num inseridos: %d\n", numColisoesRotacao101, countTabelaRotacao101);
    printf("Colisoes Fold Shift 101: %d || Num inseridos: %d\n", numColisoesFoldShift101, countTabelaFoldShift101);
    printf("Colisoes Rotacao 150: %d || Num inseridos: %d\n", numColisoesRotacao150, countTabelaRotacao150);
    printf("Colisoes Fold Shift 150: %d || Num inseridos: %d\n\n", numColisoesFoldShift150, countTabelaFoldShift150);

    free(tabela101);
    free(tabela150);

    return 0;
}
