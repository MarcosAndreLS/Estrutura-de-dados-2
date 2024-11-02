#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX101 101
#define MAX150 150

/* Prototypes */
typedef struct func Func;
void imprimirFunc(Func *tabela, int MAX);
void inicializarTabela(Func *f, int MAX);

int colisaoRotacao(int chave, char primeiroDigito, int MAX);
int funcaoHashStringRotacao(char *str, int MAX);
void inserirTabelaRotacao(Func *tabela, int *numColisoes, int *countTabela, int MAX);

int colisaoFoldShift(int chave, int MAX);
int funcaoHashStringFoldShift(char *str, int MAX);
void inserirTabelaFoldShift(Func *tabela, int *numColisoes, int *countTabela, int MAX);

/* Struct */

typedef struct func
{
    char matricula[7];
    char nome[50];
    char funcao[20];
    float salario;
} Func;

/* Imprimir */

void imprimirFunc(Func *tabela, int MAX)
{
    for (int i = 0; i < MAX; i++)
    {
        if (tabela[i].matricula[0] != '\0')
        {
            printf("Matricula: %s\n", tabela[i].matricula);
            printf("Nome: %s\n", tabela[i].nome);
            printf("Funcao: %s\n", tabela[i].funcao);
            printf("Salario: %.2f\n", tabela[i].salario);
            printf("\n");
        }
    }
}

/* Leitura dos dados */

Func lerFunc()
{
    Func f;
    while (strlen(f.matricula) < 6 || strlen(f.matricula) > 6)
    {
        printf("Informe a matricula do funcionario: ");
        scanf(" %[^\n]", f.matricula);
    }
    printf("Informe o nome do funcionario: ");
    scanf(" %[^\n]", f.nome);
    printf("Informe a funcao do funcionario: ");
    scanf(" %[^\n]", f.funcao);
    printf("Informe o salario do funcionario: ");
    scanf("%f", &f.salario);

    return f;
}

/* Funcoes Hash */

void inicializarTabela(Func *f, int MAX)
{
    for (int i = 0; i < MAX; i++)
    {
        strcpy(f[i].matricula, "\0");
    }
}

/*Função hash rotação*/

int colisaoRotacao(int chave, char primeiroDigito, int MAX)
{
    return (chave + (primeiroDigito - '0'))% MAX;
}

int funcaoHashStringRotacao(char *str, int MAX)
{
    char chave[7];
    sprintf(chave, "%c%c%s", str[4], str[5], str);
    int d2 = chave[1] - '0';
    int d4 = chave[3] - '0';
    int d6 = chave[5] - '0';
    int valor_hash = d2 * 100 + d4 * 10 + d6;
    int posicao = valor_hash % MAX;
    return posicao;
}

void inserirTabelaRotacao(Func *tabela, int *numColisoes, int *countTabela, int MAX)
{
    Func f = lerFunc();
    int indice = funcaoHashStringRotacao(f.matricula, MAX);
    if ((*countTabela) < MAX)
    {
        if (tabela[indice].matricula[0] != '\0')
        {
            (*numColisoes)++;
            int novo = colisaoRotacao(indice, f.matricula[0], MAX);
            printf("\n\n\nnovo:%d\n\n\n", novo);
            while (tabela[novo].matricula[0] != '\0')
            {
                (*numColisoes)++;
                novo = colisaoRotacao(novo, f.matricula[0], MAX);   
                
            }
            tabela[novo] = f;
            (*countTabela)++;
        }
        else
        {
            (*countTabela)++;
            tabela[indice] = f;
        }
    }else
    {
        (*countTabela)++;
        tabela[indice] = f;
    }
        
    
}

/*Função hash fold shift*/

int colisaoFoldShift(int chave, int MAX)
{
    return (chave + 7) % MAX;
}

int funcaoHashStringFoldShift(char *str, int MAX)
{
    int tam = strlen(str);
    unsigned int hash = 0;

    unsigned int aux1 = 0;
    unsigned int aux2 = 0;

    for (int i = 0; i < tam; i++)
    {
        if (i == 0 || i == 2 || i == 5)
            aux1 = aux1 * 10 + (str[i] - '0');
        else
            aux2 = aux2 * 10 + (str[i] - '0');
    }
    
    hash = (aux1 + aux2) % MAX;

    return hash;
}

void inserirTabelaFoldShift(Func *tabela, int *numColisoes, int *countTabela, int MAX)
{
    Func f = lerFunc();
    int indice = funcaoHashStringFoldShift(f.matricula, MAX);
    
    if ((*countTabela) < MAX)
    {
        if (tabela[indice].matricula[0] != '\0')
        {
            (*numColisoes)++;
            int novo = colisaoFoldShift(indice, MAX);
            
            while (tabela[novo].matricula[0] != '\0')
            {
                (*numColisoes)++;
                novo = colisaoFoldShift(novo, MAX);
                
            }  
            tabela[novo] = f;
            (*countTabela)++;
        }
        else
        {
            (*countTabela)++;
            tabela[indice] = f;
        }
    }else
    {
        (*countTabela)++;
        tabela[indice] = f;
    }
}

void menu_tabela()
{
    printf("========== MENU ==========\n");
    printf("1 - Tabela de 101 posicoes\n");
    printf("2 - Tabela de 150 posicoes\n");
    printf("0 - Sair                  \n");
    printf("==========================\n");
}

void menu_hash()
{
    printf("========== MENU ==========\n");
    printf("1 - Hash rotacao          \n");
    printf("2 - Hash fold shift       \n");
    printf("0 - Sair                  \n");
    printf("==========================\n");
}
void menu_opcoes()
{
    printf("========== MENU ==========\n");
    printf("1 - Inserir funcionarios  \n");
    printf("2 - Imprimir funcionarios \n");
    printf("3 - Colisoes totais       \n");
    printf("0 - Voltar                \n");
    printf("==========================\n");
}

int main()
{
    Func *tabela101 = (Func *)malloc(MAX101 * sizeof(Func));
    Func *tabela150 = (Func *)malloc(MAX150 * sizeof(Func));
    int numColisoes101 = 0;
    int numColisoes150 = 0;
    int countTabela101 = 0;
    int countTabela150 = 0;
    int op = -1;

    while(op != 0)
    {
        menu_tabela();
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            {
                menu_hash();
                scanf("%d", &op);
                switch (op)
                {
                case 1:
                    inicializarTabela(tabela101, MAX101);
                    op = -1;
                    while (op != 0)
                    {
                        op = -1;
                        menu_opcoes();          
                        scanf("%d", &op);
                        switch (op)
                        {
                        case 1:
                            inserirTabelaRotacao(tabela101, &numColisoes101, &countTabela101, MAX101);
                            break;
                        case 2:
                            imprimirFunc(tabela101, MAX101);
                            break;
                        case 3:
                            printf("Numero total de colisoes: %d\n", numColisoes101);
                            break;
                        default:
                            break;
                        }
                    }
                    numColisoes101 = 0;
                    countTabela101 = 0;
                    op = -1;
                    break;
                case 2:
                    inicializarTabela(tabela101, MAX101);
                    while (op != 0)
                    {
                        op = -1;
                        menu_opcoes();          
                        scanf("%d", &op);
                        switch (op)
                        {
                        case 1:
                            inserirTabelaFoldShift(tabela101, &numColisoes101, &countTabela101, MAX101);
                            break;
                        case 2:
                            imprimirFunc(tabela101, MAX101);
                            break;
                        case 3:
                            printf("Numero total de colisoes: %d\n", numColisoes101);
                            break;
                        default:
                            break;
                        }
                    }
                    numColisoes101 = 0;
                    countTabela101 = 0;
                    op = -1;
                    break;
                default:
                    break;
                }
            }
            op = -1;
            break;
        case 2:
            {
                menu_hash();
                scanf("%d", &op);
                switch (op)
                {
                case 1:
                    inicializarTabela(tabela150, MAX150);
                    op = -1;
                    while (op != 0)
                    {
                        op = -1;
                        menu_opcoes();          
                        scanf("%d", &op);
                        switch (op)
                        {
                        case 1:
                            inserirTabelaRotacao(tabela150, &numColisoes150, &countTabela150, MAX150);
                            break;
                        case 2:
                            imprimirFunc(tabela150, MAX150);
                            break;
                        case 3:
                            printf("Numero total de colisoes: %d\n", numColisoes150);
                            break;
                        default:
                            break;
                        }
                    }
                    numColisoes150 = 0;
                    countTabela150 = 0;
                    op = -1;
                    break;
                case 2:
                    inicializarTabela(tabela150, MAX150);
                    while (op != 0)
                    {
                        op = -1;
                        menu_opcoes();          
                        scanf("%d", &op);
                        switch (op)
                        {
                        case 1:
                            inserirTabelaFoldShift(tabela150, &numColisoes150, &countTabela150, MAX150);
                            break;
                        case 2:
                            imprimirFunc(tabela150, MAX150);
                            break;
                        case 3:
                            printf("Numero total de colisoes: %d\n", numColisoes150);
                            break;
                        default:
                            break;
                        }
                    }
                    numColisoes150 = 0;
                    countTabela150 = 0;
                    op = -1;
                    break;
                default:
                    break;
                }
            }
                
        default:
            break;
        }
    }

    free(tabela101);
    free(tabela150);
    
    return 0;
}

