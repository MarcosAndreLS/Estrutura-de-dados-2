#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Tam_bloco;

struct Bloco
{
    int Bloco_I, Bloco_F;
    char status;
};

struct Arv45
{
    struct Bloco info1, info2, info3, info4;
    int Ninfos;
    struct Arv45 *Esq, *Cen_Esq, *Cen, *Cen_Dir, *Dir;
};

typedef struct Bloco Bloco;
typedef struct Arv45 Arv45;

void Cadastra(Arv45 **raiz);
Arv45 *insere(Arv45 **raiz, Bloco valor, Bloco *promove, Arv45 **pai);
Arv45 *criaNo(Bloco valor, Arv45 *filho_esq, Arv45 *filho_cen_esq);
int ehFolha(Arv45 *raiz);
Arv45 *adicionaChave(Arv45 *raiz, Bloco valor, Arv45 *ptr);
Arv45 *quebraNo(Arv45 *raiz, Bloco valor, Bloco *sobe, Arv45 *ptr);
void imprimir(Arv45 *raiz);
void exibirInfo(Bloco *valor);
void AlocaEspacos(Arv45 **raiz, int Qtd);
Bloco ProcuraEspaco(Arv45 **raiz, int Qtd, Arv45 **pai, Arv45 **RAIZAvr, int *ptr);
Arv45 *busca45(Arv45 **raiz, int info);
int remover(Arv45 **raiz, Arv45 **pai, int valor);
int balancear(Arv45 **raiz, Arv45 **pai, int removeu);
int removeInfo2Folha(Arv45 *raiz);
int removeInfo2ComDirFolha(Arv45 *raiz, Arv45 *pai);
Arv45 *obterMenorNo(Arv45 *raiz);
int numeroInfosArv(Arv45 *raiz);
Arv45 *obterMaiorNo(Arv45 *raiz);
int removeInfo2NaoFolha(Arv45 *raiz);
int removeInfo1Folha(Arv45 *raiz, Arv45 *pai);
int removeInfo1NaoFolha(Arv45 *raiz);
void liberarMemoriaArvore(Arv45 *raiz);

int main(){
    Arv45 *raiz = NULL;
    int op, Qtd, aux;

    Cadastra(&raiz);
    printf("\nCadastro Finalizado!\n\n");
    do
    {
        printf("\n---- Menu ----\n1 - Alocar Nos\n2 - Remover blocos\n3 - Imprimir\n0 - Sair\n");
        scanf("%d", &op);
        printf("\n");
        switch (op)
        {
        case 0:
            printf("Saindo!!!\n\n");
            break;
        case 1:
            printf("Alocar Nos\n");
            printf("\nDigite a quantidade de blocos que voce deseja alocar: ");
            scanf("%d", &Qtd);

            while (Qtd <= 0)
            {
                printf("\nDigite uma quantidade de blocos valida, maior que zero: ");
                scanf("%d", &Qtd);
            }

            AlocaEspacos(&raiz, Qtd);
            break;
        case 3:
            // system("cls");
            printf("Imprimindo blocos(Nos)\n");
            imprimir(raiz);
            break;
        default:
            printf("Digite uma opcao valida!\n");
            break;
        }
    } while (op != 0);
    liberarMemoriaArvore(raiz);
    return 0;
}

void Cadastra(Arv45 **raiz)
{
    Arv45 *pai = NULL;
    Bloco info, promove;
    int i = 0;

    system("cls");
    printf("\n\t-------- Cadastro da memoria --------\n");
    printf("\nDigite a quantidade de blocos logicos(Memoria em Mbyte): ");
    scanf("%d", &Tam_bloco);

    while (Tam_bloco <= 0)
    {
        printf("\nDigite uma quantidade de blocos valida, maior que zero: ");
        scanf("%d", &Tam_bloco);
    }

    printf("\nDigite o estado do primeiro bloco(o para ocupado ou l para livre): ");
    scanf(" %c", &info.status);

    while (info.status != 'o' && info.status != 'l')
    {
        printf("\nDigite um estado valido para o primeiro bloco(o para ocupado ou l para livre): ");
        scanf(" %c", &info.status);
    }

    info.Bloco_I = 0;
    info.Bloco_F = 0;

    do
    {
        printf("\nInicio do bloco: %d\n", info.Bloco_I);
        printf("Digite o endereco final para o bloco: ");
        scanf("%d", &info.Bloco_F);

        while (info.Bloco_F >= Tam_bloco || info.Bloco_F < info.Bloco_I)
        {
            printf("Digite um valor valido para o fim do bloco(Fim do bloco: %d): ", Tam_bloco);
            scanf("%d", &info.Bloco_F);
        }

        // vet[i] = info.Bloco_F;
        // i++;

        insere(raiz, info, &promove, &pai);

        if (info.status == 'l')
        {
            info.status = 'o';
        }
        else
        {
            info.status = 'l';
        }

        info.Bloco_I = info.Bloco_F + 1;

    } while (info.Bloco_I != Tam_bloco);
}

Arv45 *insere(Arv45 **raiz, Bloco valor, Bloco *promove, Arv45 **pai){
    Arv45 *MaiorNo;
    MaiorNo = NULL;
    Bloco promove1;

    if (*raiz == NULL){ 
        *raiz = criaNo(valor, NULL, NULL);
    }else{
        if (ehFolha(*raiz)){ // e folha
            if ((*raiz)->Ninfos < 4){                                              // e folha, tem apenas uma informacao
                *raiz = adicionaChave(*raiz, valor, NULL); // adiciona a informacao ao no
                MaiorNo = NULL;
            }
            else
            { // e folha, tem duas informacoes
                MaiorNo = quebraNo(*raiz, valor, promove, NULL);
                if (*pai == NULL){ // cria uma nova raiz para a arvore
                    *raiz = criaNo(*promove, *raiz, MaiorNo);
                    MaiorNo = NULL; // O MaiorNo no recebe null, pois ja foi adicionado na arvore, se isso nao acontecer ela vai inserir o elemento repetidas vezes na arvore
                }
            }
        }else{
            if(valor.Bloco_F < (*raiz)->info1.Bloco_F)
                MaiorNo = insere(&((*raiz)->Esq), valor, promove, raiz);
            else if((*raiz)->Ninfos == 1 || ((*raiz)->Ninfos <= 4 && valor.Bloco_F < (*raiz)->info2.Bloco_F))
                MaiorNo = insere(&((*raiz)->Cen_Esq), valor, promove, raiz);
            else if((*raiz)->Ninfos == 2 || ((*raiz)->Ninfos <= 4 && valor.Bloco_F < (*raiz)->info3.Bloco_F))
                MaiorNo = insere(&((*raiz)->Cen), valor, promove, raiz);
            else if((*raiz)->Ninfos == 3 || ((*raiz)->Ninfos <= 4 && valor.Bloco_F < (*raiz)->info4.Bloco_F))
                MaiorNo = insere(&((*raiz)->Cen_Dir), valor, promove, raiz);
            else
                MaiorNo = insere(&((*raiz)->Dir), valor, promove, raiz);
            
            if (MaiorNo){
                if((*raiz)->Ninfos < 4){
                    *raiz = adicionaChave(*raiz, *promove, MaiorNo);
                    MaiorNo = NULL;
                }else{
                    MaiorNo = quebraNo(*raiz, *promove, &promove1, MaiorNo);
                    // -----
                    *promove = promove1;
                    if(pai == NULL){
                        *raiz = criaNo(promove1, *raiz, MaiorNo);
                        MaiorNo = NULL;
                    }
                }
            }
        }
    }
    return MaiorNo;
}

Arv45 *criaNo(Bloco valor, Arv45 *filho_esq, Arv45 *filho_cen_esq){
    Arv45 *no;
    no = (Arv45 *)malloc(sizeof(Arv45));
    if (no != NULL){
        no->info1 = valor;
        no->Ninfos = 1;
        no->Esq = filho_esq;
        no->Cen_Esq = filho_cen_esq;
        no->Cen = NULL;
        no->Cen_Dir = NULL;
        no->Dir = NULL;

    }
    return no;
}

int ehFolha(Arv45 *raiz)
{ // verifica se o no e folha
    int ehfolha;
    if (raiz->Esq == NULL)
    { // se a esquerda for nula, significa que o no e folha, pois como nao tem esq, nao tera centro, nem direita
        ehfolha = 1;
    }
    else
    {
        ehfolha = 0;
    }
    return ehfolha; // retorna 1 se for folha e 0 se nao for
}

Arv45 *adicionaChave(Arv45 *raiz, Bloco valor, Arv45 *ptr){
    if ((raiz)->Ninfos == 1){
        if(valor.Bloco_F > raiz->info1.Bloco_F){
            raiz->info2 = valor;
            raiz->Cen = ptr;
        }else{
            raiz->info2 = raiz->info1;
            raiz->info1 = valor;

            raiz->Cen = raiz->Cen_Esq;
            raiz->Cen_Esq = ptr;
        }
        raiz->Ninfos = 2;
    }else if((raiz)->Ninfos ==2){
        if (valor.Bloco_F > raiz->info2.Bloco_F){
            raiz->info3 = valor;
            raiz->Cen_Dir = ptr;
        }else if(valor.Bloco_F > raiz->info1.Bloco_F && valor.Bloco_F < raiz->info2.Bloco_F){
            raiz->info3 = raiz->info2;
            raiz->info2 = valor;

            raiz->Cen_Dir = raiz->Cen;
            raiz->Cen = ptr;

        }else{
            raiz->info3 = raiz->info2;
            raiz->info2 = raiz->info1;
            raiz->info1 = valor;

            raiz->Cen_Dir = raiz->Cen;
            raiz->Cen = raiz->Cen_Esq;
            raiz->Cen_Esq = ptr;
        }
        raiz->Ninfos = 3;
    }else{
        if(valor.Bloco_F > raiz->info3.Bloco_F){
            raiz->info4 = valor;
            raiz->Dir = ptr;

        }else if(valor.Bloco_F > raiz->info2.Bloco_F && valor.Bloco_F < raiz->info3.Bloco_F){
            raiz->info4 = raiz->info3;
            raiz->info3 = valor;

            raiz->Dir = raiz->Cen_Dir;
            raiz->Cen_Dir = ptr;

        }else if (valor.Bloco_F > raiz->info1.Bloco_F && valor.Bloco_F < raiz->info2.Bloco_F){
            raiz->info4 = raiz->info3;
            raiz->info3 = raiz->info2;
            raiz->info2 = valor;

            raiz->Dir = raiz->Cen_Dir;
            raiz->Cen_Dir = raiz->Cen;
            raiz->Cen = ptr;

        }else{
            raiz->info4 = raiz->info3;
            raiz->info3 = raiz->info2;
            raiz->info2 = raiz->info1;
            raiz->info1 = valor;

            raiz->Dir = raiz->Cen_Dir;
            raiz->Cen_Dir = raiz->Cen;
            raiz->Cen = raiz->Cen_Esq;
            raiz->Cen_Esq = ptr;
        }
        raiz->Ninfos = 4;
    }
    return raiz;
}

Arv45 *quebraNo(Arv45 *raiz, Bloco valor, Bloco *sobe, Arv45 *ptr){
    Arv45 *maiorNo;
    if(valor.Bloco_F > raiz->info4.Bloco_F){
        *sobe = raiz->info3;

        maiorNo = criaNo(raiz->info4, raiz->Cen_Dir, raiz->Dir);
        
        maiorNo->info2 = valor;

        maiorNo->Cen = ptr;

        maiorNo->Ninfos = 2;
    }else if(valor.Bloco_F > raiz->info3.Bloco_F){
        *sobe = raiz->info3;

        maiorNo = criaNo(valor, raiz->Cen_Dir, ptr);
        
        maiorNo->info2 = raiz->info4;

        maiorNo->Cen = raiz->Dir;

        maiorNo->Ninfos = 2;
    }else if(valor.Bloco_F > raiz->info2.Bloco_F){
        *sobe = valor;
        
        maiorNo = criaNo(raiz->info3, raiz->Cen, raiz->Cen_Dir);
        
        maiorNo->info2 = raiz->info4;

        maiorNo->Cen = raiz->Dir;

        maiorNo->Ninfos = 2;
    }else if(valor.Bloco_F > raiz->info1.Bloco_F){
        *sobe = raiz->info2;

        maiorNo = criaNo(raiz->info3, raiz->Cen, raiz->Cen_Dir);
        
        maiorNo->info2 = raiz->info4;

        maiorNo->Cen = raiz->Dir;

        maiorNo->Ninfos = 2;

        raiz->info2 = valor;
        raiz->Cen = ptr;
    }else{
        *sobe = raiz->info2;

        maiorNo = criaNo(raiz->info3, raiz->Cen, raiz->Cen_Dir);
        
        maiorNo->info2 = raiz->info4;

        maiorNo->Cen = raiz->Dir;

        maiorNo->Ninfos = 2;

        raiz->info2 = raiz->info1;
        raiz->Cen = raiz->Cen_Esq;
        
        raiz->info1 = valor;
        raiz->Cen_Esq = ptr;
    }
    raiz->Ninfos = 2;
    raiz->Cen_Dir = NULL;
    raiz->Dir = NULL;

    return maiorNo;
}
void exibirInfo(Bloco *valor){
        // printf("cod: %d, tam: %d, qtd: %d, linha: %d, tipo: %s, marca: %s, preco: %.2f\n", info->cod, info->tam, info->qtd, info->linha, info->tipo, info->marca, info->preco);
    printf("-Inicio: %d\n-Final: %d\n-Status: %c\n", valor->Bloco_I, valor->Bloco_F, valor->status);
}

void imprimir(Arv45 *raiz) {
    if (raiz != NULL) {
        imprimir(raiz->Esq);
        exibirInfo(&raiz->info1);
        if (raiz->Ninfos == 2 || raiz->Ninfos > 2)
            exibirInfo(&raiz->info2);
        if (raiz->Ninfos == 3 || raiz->Ninfos > 3)
            exibirInfo(&raiz->info3);
        if (raiz->Ninfos == 4)
            exibirInfo(&raiz->info4);

        imprimir(raiz->Cen_Esq);
        imprimir(raiz->Cen);
        imprimir(raiz->Cen_Dir);
        imprimir(raiz->Dir);
    }
}

void AlocaEspacos(Arv45 **raiz, int Qtd)
{
    Arv45 *Pai = NULL;
    Bloco aux;
    int ptr = 0, N;
    aux = ProcuraEspaco(&(*raiz), Qtd, &Pai, &(*raiz), &ptr);
    N = aux.Bloco_I;
    if (aux.Bloco_I != -1)
    {
        //remover(&(*raiz), &Pai, N);
    }
    else
    {
        printf("\nNao e possivel alocar essa quantidade de blocos, nao ha espaco suficiente em nenhum bloco!\n");
    }
}

Bloco ProcuraEspaco(Arv45 **raiz, int Qtd, Arv45 **pai, Arv45 **RAIZAvr, int *ptr){
    Arv45 *aux1 = NULL, *aux2 = NULL;
    Bloco aux3;
    aux3.Bloco_I = -1;
    int espaco, aux = 0;

    if (*raiz != NULL){
        espaco = ((*raiz)->info1.Bloco_F - (*raiz)->info1.Bloco_I) + 1;
        if (espaco >= Qtd && (*raiz)->info1.status == 'l'){
            printf("\n---Bloco que foi Ocupado---\n");
            printf("  -Inicio: %d\n  -Final: %d\n  -Status: %c\n", (*raiz)->info1.Bloco_I, (*raiz)->info1.Bloco_F, (*raiz)->info1.status);
            aux = 1;
            if (espaco == Qtd){
                if (ehFolha(*raiz)){
                    if (*pai == NULL){
                        if ((*raiz)->Ninfos == 4){
                            (*raiz)->info1.Bloco_F = (*raiz)->info2.Bloco_F;
                            (*raiz)->info1.status = 'o';
                            
                            (*raiz)->info2.Bloco_I = (*raiz)->info3.Bloco_I;
                            (*raiz)->info2.Bloco_F = (*raiz)->info3.Bloco_F;
                            (*raiz)->info2.status = (*raiz)->info3.status;

                            (*raiz)->info3.Bloco_I = (*raiz)->info4.Bloco_I;
                            (*raiz)->info3.Bloco_F = (*raiz)->info4.Bloco_F;
                            (*raiz)->info3.status = (*raiz)->info4.status;

                            (*raiz)->Ninfos = 3;
                            aux3.Bloco_I = -2;

                        }else if((*raiz)->Ninfos == 3){
                            (*raiz)->info1.Bloco_F = (*raiz)->info2.Bloco_F;
                            (*raiz)->info1.status = 'o';
                            
                            (*raiz)->info2.Bloco_I = (*raiz)->info3.Bloco_I;
                            (*raiz)->info2.Bloco_F = (*raiz)->info3.Bloco_F;
                            (*raiz)->info2.status = (*raiz)->info3.status;

                            (*raiz)->Ninfos = 2;
                            aux3.Bloco_I = -2;

                        }else if ((*raiz)->Ninfos == 2){
                            (*raiz)->info1.Bloco_F = (*raiz)->info2.Bloco_F;
                            (*raiz)->info1.status = 'o';
                            (*raiz)->Ninfos = 1;
                            aux3.Bloco_I = -2;
                        }
                        else
                        {
                            (*raiz)->info1.status = 'o';
                            aux3.Bloco_I = -2;
                        }

                    }else{
                        if ((*raiz)->info1.Bloco_I == 0){
                            aux1 = busca45(RAIZAvr, (*raiz)->info1.Bloco_F + 1);
                            if (aux1->Ninfos == 4){
                                if (aux1->info4.Bloco_I == (*raiz)->info3.Bloco_F + 1){
                                    (*raiz)->info3.Bloco_F = aux1->info4.Bloco_F;
                                    (*raiz)->info3.status = 'o';
                                    aux3 = aux1->info2;

                                    aux3 = aux1->info4;
                                }else if(aux1->info3.Bloco_I == (*raiz)->info2.Bloco_F + 1){
                                    (*raiz)->info2.Bloco_F = aux1->info3.Bloco_F;
                                    (*raiz)->info2.status = 'o';
                                    aux3 = aux1->info2;

                                    aux3 = aux1->info3;
                                }else if(aux1->info2.Bloco_I == (*raiz)->info1.Bloco_F + 1){
                                    (*raiz)->info1.Bloco_F = aux1->info2.Bloco_F;
                                    (*raiz)->info1.status = 'o';
                                    aux3 = aux1->info2;
                                }else{
                                    (*raiz)->info1.Bloco_F = aux1->info1.Bloco_F;
                                    (*raiz)->info1.status = 'o';
                                    aux3 = aux1->info1;
                                }
                            }else if(aux1->Ninfos == 3){
                                if (aux1->info3.Bloco_I == (*raiz)->info2.Bloco_F + 1){
                                    (*raiz)->info2.Bloco_F = aux1->info3.Bloco_F;
                                    (*raiz)->info2.status = 'o';

                                    aux3 = aux1->info3;
                                }else if(aux1->info2.Bloco_I == (*raiz)->info1.Bloco_F + 1){
                                    (*raiz)->info1.Bloco_F = aux1->info2.Bloco_F;
                                    (*raiz)->info1.status = 'o';
                                    aux3 = aux1->info2;
                                }else{
                                    (*raiz)->info1.Bloco_F = aux1->info1.Bloco_F;
                                    (*raiz)->info1.status = 'o';
                                    aux3 = aux1->info1;
                                }
                            }else if(aux1->Ninfos == 2){
                                if (aux1->info2.Bloco_I == (*raiz)->info1.Bloco_F + 1)
                                {
                                    (*raiz)->info1.Bloco_F = aux1->info2.Bloco_F;
                                    (*raiz)->info1.status = 'o';
                                    aux3 = aux1->info2;
                                }else{
                                    (*raiz)->info1.Bloco_F = aux1->info1.Bloco_F;
                                    (*raiz)->info1.status = 'o';
                                    aux3 = aux1->info1;
                                }
                            }else{
                                (*raiz)->info1.Bloco_F = aux1->info1.Bloco_F;
                                (*raiz)->info1.status = 'o';
                                aux3 = aux1->info1;
                            }
                        }else if ((*raiz)->info1.Bloco_F + 1 == Tam_bloco){
                            aux1 = busca45(RAIZAvr, (*raiz)->info1.Bloco_I - 1);
                            if (aux1->Ninfos == 4){
                                if(aux1->info4.Bloco_F == (*raiz)->info3.Bloco_I - 1){
                                    aux1->info4.Bloco_F = (*raiz)->info3.Bloco_F;
                                    aux1->info4.status = 'o';
                                    aux3 = (*raiz)->info3;
                                }else if(aux1->info3.Bloco_F == (*raiz)->info2.Bloco_I - 1){
                                    aux1->info3.Bloco_F = (*raiz)->info2.Bloco_F;
                                    aux1->info3.status = 'o';
                                    aux3 = (*raiz)->info2;
                                }else if(aux1->info2.Bloco_F == (*raiz)->info1.Bloco_I - 1){
                                    aux1->info2.Bloco_F = (*raiz)->info1.Bloco_F;
                                    aux1->info2.status = 'o';
                                    aux3 = (*raiz)->info1;
                                }else{
                                    aux1->info1.Bloco_F = (*raiz)->info1.Bloco_F;
                                    aux1->info1.status = 'o';
                                    aux3 = (*raiz)->info1;
                                }
                            }else if(aux1->Ninfos ==3){
                                if(aux1->info4.Bloco_F == (*raiz)->info3.Bloco_I - 1){
                                    aux1->info3.Bloco_F = (*raiz)->info2.Bloco_F;
                                    aux1->info3.status = 'o';
                                    aux3 = (*raiz)->info2;
                                }else if(aux1->info2.Bloco_F == (*raiz)->info1.Bloco_I - 1){
                                    aux1->info2.Bloco_F = (*raiz)->info1.Bloco_F;
                                    aux1->info2.status = 'o';
                                    aux3 = (*raiz)->info1;
                                }else{
                                    aux1->info1.Bloco_F = (*raiz)->info1.Bloco_F;
                                    aux1->info1.status = 'o';
                                    aux3 = (*raiz)->info1;
                                }
                            }else if (aux1->Ninfos == 2){
                                if (aux1->info2.Bloco_F == (*raiz)->info1.Bloco_I - 1)
                                {
                                    aux1->info2.Bloco_F = (*raiz)->info1.Bloco_F;
                                    aux1->info2.status = 'o';
                                    aux3 = (*raiz)->info1;
                                }
                                else
                                {
                                    aux1->info1.Bloco_F = (*raiz)->info1.Bloco_F;
                                    aux1->info1.status = 'o';
                                    aux3 = (*raiz)->info1;
                                }
                            }
                            else{
                                aux1->info1.Bloco_F = (*raiz)->info1.Bloco_F;
                                aux1->info1.status = 'o';
                                aux3 = (*raiz)->info1;
                            }
                        }else{
                            aux1 = busca45(RAIZAvr, (*raiz)->info1.Bloco_I - 1);
                            if (aux1->Ninfos == 4){
                                if(aux1->info4.Bloco_F == (*raiz)->info3.Bloco_I - 1){
                                    aux1->info4.Bloco_F = (*raiz)->info3.Bloco_F;
                                    aux1->info4.status = 'o';
                                }else if(aux1->info3.Bloco_F == (*raiz)->info2.Bloco_I - 1){
                                    aux1->info3.Bloco_F = (*raiz)->info2.Bloco_F;
                                    aux1->info3.status = 'o';
                                }else if(aux1->info2.Bloco_F == (*raiz)->info1.Bloco_I - 1){
                                    aux1->info2.Bloco_F = (*raiz)->info1.Bloco_F;
                                    aux1->info2.status = 'o';
                                }else
                                {
                                    aux1->info1.Bloco_F = (*raiz)->info1.Bloco_F;
                                    aux1->info1.status = 'o';
                                }
                            }else if(aux1->Ninfos == 3){
                                if(aux1->info3.Bloco_F == (*raiz)->info2.Bloco_I - 1){
                                    aux1->info3.Bloco_F = (*raiz)->info2.Bloco_F;
                                    aux1->info3.status = 'o';
                                }else if(aux1->info2.Bloco_F == (*raiz)->info1.Bloco_I - 1){
                                    aux1->info2.Bloco_F = (*raiz)->info1.Bloco_F;
                                    aux1->info2.status = 'o';
                                }else
                                {
                                    aux1->info1.Bloco_F = (*raiz)->info1.Bloco_F;
                                    aux1->info1.status = 'o';
                                }
                            }else if (aux1->Ninfos == 2){
                                if (aux1->info2.Bloco_F == (*raiz)->info1.Bloco_I - 1){
                                    aux1->info2.Bloco_F = (*raiz)->info1.Bloco_F;
                                    aux1->info2.status = 'o';
                                }
                                else
                                {
                                    aux1->info1.Bloco_F = (*raiz)->info1.Bloco_F;
                                    aux1->info1.status = 'o';
                                }
                            }else{
                                aux1->info1.Bloco_F = (*raiz)->info1.Bloco_F;
                                aux1->info1.status = 'o';
                            }
                            //
                            if (aux1->Ninfos == 2)
                            {
                                if (aux1->info2.Bloco_F == (*raiz)->info1.Bloco_F)
                                {
                                    aux2 = busca45(RAIZAvr, aux1->info2.Bloco_F + 1);
                                    if (aux2->Ninfos == 2)
                                    {
                                        if (aux2->info2.Bloco_I == aux1->info2.Bloco_F + 1)
                                        {
                                            aux1->info2.Bloco_F = aux2->info2.Bloco_F;
                                            aux1->info2.status = 'o';
                                            aux3 = aux2->info2;
                                        }
                                        else
                                        {
                                            aux1->info2.Bloco_F = aux2->info1.Bloco_F;
                                            aux1->info2.status = 'o';
                                            aux3 = aux2->info1;
                                        }
                                    }
                                    else
                                    {
                                        aux1->info2.Bloco_F = aux2->info1.Bloco_F;
                                        aux1->info2.status = 'o';
                                        aux3 = aux2->info1;
                                    }
                                }
                                else
                                {
                                    aux2 = busca45(RAIZAvr, aux1->info1.Bloco_F + 1);
                                    if (aux2->Ninfos == 2)
                                    {
                                        if (aux2->info2.Bloco_I == aux1->info1.Bloco_F + 1)
                                        {
                                            aux1->info1.Bloco_F = aux2->info2.Bloco_F;
                                            aux1->info1.status = 'o';
                                            aux3 = aux2->info2;
                                        }
                                        else
                                        {
                                            aux1->info1.Bloco_F = aux2->info1.Bloco_F;
                                            aux1->info1.status = 'o';
                                            aux3 = aux2->info1;
                                        }
                                    }
                                    else
                                    {
                                        aux1->info1.Bloco_F = aux2->info1.Bloco_F;
                                        aux1->info1.status = 'o';
                                        aux3 = aux2->info1;
                                    }
                                }
                            }
                            else
                            {
                                aux2 = busca45(RAIZAvr, aux1->info1.Bloco_F + 1);
                                if (aux2->Ninfos == 2)
                                {
                                    if (aux2->info2.Bloco_I == aux1->info1.Bloco_F + 1)
                                    {
                                        aux1->info1.Bloco_F = aux2->info2.Bloco_F;
                                        aux1->info1.status = 'o';
                                        aux3 = aux2->info2;
                                    }
                                    else
                                    {
                                        aux1->info1.Bloco_F = aux2->info1.Bloco_F;
                                        aux1->info1.status = 'o';
                                        aux3 = aux2->info1;
                                    }
                                }
                                else
                                {
                                    aux1->info1.Bloco_F = aux2->info1.Bloco_F;
                                    aux1->info1.status = 'o';
                                    aux3 = aux2->info1;
                                }
                            }
                            remover(RAIZAvr, NULL, (*raiz)->info1.Bloco_I);
                            //
                        }
                    }
                }else{
                    aux1 = busca45(RAIZAvr, (*raiz)->info1.Bloco_I - 1);
                    if (aux1->Ninfos == 2)
                    {
                        if (aux1->info2.Bloco_F == (*raiz)->info1.Bloco_I - 1)
                        {
                            aux1->info2.Bloco_F = (*raiz)->info1.Bloco_F;
                            aux1->info2.status = 'o';
                        }
                        else
                        {
                            aux1->info1.Bloco_F = (*raiz)->info1.Bloco_F;
                            aux1->info1.status = 'o';
                        }
                    }
                    else
                    {
                        aux1->info1.Bloco_F = (*raiz)->info1.Bloco_F;
                        aux1->info1.status = 'o';
                    }

                    if (aux1->Ninfos == 2)
                    {
                        if (aux1->info2.Bloco_F == (*raiz)->info1.Bloco_F)
                        {
                            aux2 = busca45(RAIZAvr, aux1->info2.Bloco_F + 1);
                            if (aux2->Ninfos == 2)
                            {
                                if (aux2->info2.Bloco_I == aux1->info2.Bloco_F + 1)
                                {
                                    aux1->info2.Bloco_F = aux2->info2.Bloco_F;
                                    aux1->info2.status = 'o';
                                    aux3 = aux2->info2;
                                }
                                else
                                {
                                    aux1->info2.Bloco_F = aux2->info1.Bloco_F;
                                    aux1->info2.status = 'o';
                                    aux3 = aux2->info1;
                                }
                            }
                            else
                            {
                                aux1->info2.Bloco_F = aux2->info1.Bloco_F;
                                aux1->info2.status = 'o';
                                aux3 = aux2->info1;
                            }
                        }
                        else
                        {
                            aux2 = busca45(RAIZAvr, aux1->info1.Bloco_F + 1);
                            if (aux2->Ninfos == 2)
                            {
                                if (aux2->info2.Bloco_I == aux1->info1.Bloco_F + 1)
                                {
                                    aux1->info1.Bloco_F = aux2->info2.Bloco_F;
                                    aux1->info1.status = 'o';
                                    aux3 = aux2->info2;
                                }
                                else
                                {
                                    aux1->info1.Bloco_F = aux2->info1.Bloco_F;
                                    aux1->info1.status = 'o';
                                    aux3 = aux2->info1;
                                }
                            }
                            else
                            {
                                aux1->info1.Bloco_F = aux2->info1.Bloco_F;
                                aux1->info1.status = 'o';
                                aux3 = aux2->info1;
                            }
                        }
                    }
                    else
                    {
                        aux2 = busca45(RAIZAvr, aux1->info1.Bloco_F + 1);
                        if (aux2->Ninfos == 2)
                        {
                            if (aux2->info2.Bloco_I == aux1->info1.Bloco_F + 1)
                            {
                                aux1->info1.Bloco_F = aux2->info2.Bloco_F;
                                aux1->info1.status = 'o';
                                aux3 = aux2->info2;
                            }
                            else
                            {
                                aux1->info1.Bloco_F = aux2->info1.Bloco_F;
                                aux1->info1.status = 'o';
                                aux3 = aux2->info1;
                            }
                        }
                        else
                        {
                            aux1->info1.Bloco_F = aux2->info1.Bloco_F;
                            aux1->info1.status = 'o';
                            aux3 = aux2->info1;
                        }
                    }
                    remover(RAIZAvr, NULL, (*raiz)->info1.Bloco_I);
                }
            }
        }else{
            if (*pai == NULL)
            {
                if ((*raiz)->Ninfos == 2)
                {
                    if (ehFolha(*raiz))
                    {
                        (*raiz)->info1.Bloco_F -= Qtd;
                        (*raiz)->info2.Bloco_I -= Qtd;
                        aux3.Bloco_I = -2;
                    }
                    else
                    {
                        aux1 = busca45(RAIZAvr, (*raiz)->info1.Bloco_F + 1);
                        (*raiz)->info1.Bloco_F -= Qtd;
                        aux1->info1.Bloco_I -= Qtd;
                        aux3.Bloco_I = -2;
                    }
                }
                else
                {
                    if (ehFolha(*raiz))
                    {
                        (*raiz)->info1.Bloco_F -= Qtd;
                        (*raiz)->Ninfos = 2;
                        (*raiz)->info2.Bloco_I = (*raiz)->info1.Bloco_F + 1;
                        (*raiz)->info2.Bloco_F = Tam_bloco - 1;
                        (*raiz)->info2.status = 'o';
                        aux3.Bloco_I = -2;
                    }
                    else
                    {
                        aux1 = busca45(RAIZAvr, (*raiz)->info1.Bloco_F + 1);
                        (*raiz)->info1.Bloco_F -= Qtd;
                        aux1->info1.Bloco_I -= Qtd;
                        aux3.Bloco_I = -2;
                    }
                }
            }
            else
            {
                if ((*raiz)->info1.Bloco_F == Tam_bloco - 1)
                {
                    aux1 = busca45(RAIZAvr, (*raiz)->info1.Bloco_I - 1);
                    if (aux1->Ninfos == 2)
                    {
                        if (aux1->info2.Bloco_F == (*raiz)->info1.Bloco_I - 1)
                        {
                            aux1->info2.Bloco_F += Qtd;
                            (*raiz)->info1.Bloco_I += Qtd;
                        }
                        else
                        {
                            aux1->info1.Bloco_F += Qtd;
                            (*raiz)->info1.Bloco_I += Qtd;
                        }
                    }
                    else
                    {
                        aux1->info1.Bloco_F += Qtd;
                        (*raiz)->info1.Bloco_I += Qtd;
                    }
                    aux3.Bloco_I = -2;
                }
                else
                {
                    aux1 = busca45(RAIZAvr, (*raiz)->info1.Bloco_F + 1);
                    if (aux1->Ninfos == 2)
                    {
                        if (aux1->info2.Bloco_I == (*raiz)->info1.Bloco_F + 1)
                        {
                            aux1->info2.Bloco_I -= Qtd;
                            (*raiz)->info1.Bloco_F -= Qtd;
                        }
                        else
                        {
                            aux1->info1.Bloco_I -= Qtd;
                            (*raiz)->info1.Bloco_F -= Qtd;
                        }
                    }
                    else
                    {
                        aux1->info1.Bloco_I -= Qtd;
                        (*raiz)->info1.Bloco_F -= Qtd;
                    }
                    aux3.Bloco_I = -2;
                }
            }
        }
    }else if ((*raiz)->Ninfos == 2){
        espaco = ((*raiz)->info2.Bloco_F - (*raiz)->info2.Bloco_I) + 1;
        if (espaco >= Qtd && (*raiz)->info2.status == 'l')
        {
            printf("\n---Bloco que foi Ocupado---\n");
            printf("  -Inicio: %d\n  -Final: %d\n  -Status: %c\n", (*raiz)->info2.Bloco_I, (*raiz)->info2.Bloco_F, (*raiz)->info2.status);
            aux = 1;
            if (espaco == Qtd)
            {
                if (*pai == NULL)
                {
                    if (ehFolha(*raiz))
                    {
                        (*raiz)->info1.Bloco_F += Qtd;
                        (*raiz)->Ninfos = 1;
                        aux3.Bloco_I = -2;
                    }
                    else
                    {
                        aux1 = busca45(RAIZAvr, (*raiz)->info2.Bloco_F + 1);
                        if (aux1->Ninfos == 1)
                        {
                            aux2 = busca45(RAIZAvr, (*raiz)->info2.Bloco_I - 1);
                            if (aux2->Ninfos == 1)
                            {
                                aux1->info1.Bloco_I = aux2->info1.Bloco_I;
                                aux1->info1.status = 'o';
                                aux3 = aux2->info1;
                            }
                            else
                            {
                                aux1->info1.Bloco_I = aux2->info2.Bloco_I;
                                aux1->info1.status = 'o';
                                aux3 = aux2->info2;
                            }
                        }
                        else
                        {
                            aux2 = busca45(RAIZAvr, (*raiz)->info2.Bloco_I - 1);
                            if (aux2->Ninfos == 1)
                            {
                                aux1->info2.Bloco_I = aux2->info1.Bloco_I;
                                aux1->info2.status = 'o';
                                aux3 = aux2->info1;
                            }
                            else
                            {
                                aux1->info2.Bloco_I = aux2->info2.Bloco_I;
                                aux1->info2.status = 'o';
                                aux3 = aux2->info2;
                            }
                        }
                        remover(RAIZAvr, NULL, (*raiz)->info2.Bloco_I);
                    }
                }
                else
                {
                    if (ehFolha(*raiz))
                    {
                        (*raiz)->info1.Bloco_F += Qtd;
                        (*raiz)->Ninfos = 1;
                        aux3.Bloco_I = -2;
                    }
                    else
                    {
                        aux1 = busca45(RAIZAvr, (*raiz)->info2.Bloco_F + 1);
                        if (aux1->Ninfos == 1)
                        {
                            aux2 = busca45(RAIZAvr, (*raiz)->info2.Bloco_I - 1);
                            if (aux2->Ninfos == 1)
                            {
                                aux1->info1.Bloco_I = aux2->info1.Bloco_I;
                                aux1->info1.status = 'o';
                                aux3 = aux2->info1;
                            }
                            else
                            {
                                aux1->info1.Bloco_I = aux2->info2.Bloco_I;
                                aux1->info1.status = 'o';
                                aux3 = aux2->info2;
                            }
                        }
                        else
                        {
                            aux2 = busca45(RAIZAvr, (*raiz)->info2.Bloco_I - 1);
                            if (aux2->Ninfos == 1)
                            {
                                aux1->info2.Bloco_I = aux2->info1.Bloco_I;
                                aux1->info2.status = 'o';
                                aux3 = aux2->info1;
                            }
                            else
                            {
                                aux1->info2.Bloco_I = aux2->info2.Bloco_I;
                                aux1->info2.status = 'o';
                                aux3 = aux2->info2;
                            }
                        }
                        remover(RAIZAvr, NULL, (*raiz)->info2.Bloco_I);
                    }
                }
            }
            else
            {
                if (*pai == NULL)
                {
                    if (ehFolha(*raiz))
                    {
                        (*raiz)->info1.Bloco_F += Qtd;
                        (*raiz)->info2.Bloco_I += Qtd;
                        aux3.Bloco_I = -2;
                    }
                    else
                    {
                        aux1 = busca45(RAIZAvr, (*raiz)->info2.Bloco_F + 1);
                        if (aux1->Ninfos == 1)
                        {
                            (*raiz)->info2.Bloco_F -= Qtd;
                            aux1->info1.Bloco_I -= Qtd;
                            aux3.Bloco_I = -2;
                        }
                        else
                        {
                            (*raiz)->info2.Bloco_F -= Qtd;
                            aux1->info2.Bloco_I -= Qtd;
                            aux3.Bloco_I = -2;
                        }
                    }
                }
                else
                {
                    if (ehFolha(*raiz))
                    {
                        (*raiz)->info1.Bloco_F += Qtd;
                        (*raiz)->info2.Bloco_I += Qtd;
                        aux3.Bloco_I = -2;
                    }
                    else
                    {
                        aux1 = busca45(RAIZAvr, (*raiz)->info2.Bloco_F + 1);
                        if (aux1->Ninfos == 1)
                        {
                            (*raiz)->info2.Bloco_F -= Qtd;
                            aux1->info1.Bloco_I -= Qtd;
                            aux3.Bloco_I = -2;
                        }
                        else
                        {
                            (*raiz)->info2.Bloco_F -= Qtd;
                            aux1->info2.Bloco_I -= Qtd;
                            aux3.Bloco_I = -2;
                        }
                    }
                }
            }
        }
        if (aux == 0)
        { // percorre a árvore
            aux3 = ProcuraEspaco(&(*raiz)->Esq, Qtd, raiz, RAIZAvr, ptr);
            if (aux3.Bloco_I == -1)
            {
                aux3 = ProcuraEspaco(&(*raiz)->Cen_Esq, Qtd, raiz, RAIZAvr, ptr);
            }
            if (aux3.Bloco_I == -1)
            {
                aux3 = ProcuraEspaco(&(*raiz)->Cen, Qtd, raiz, RAIZAvr, ptr);
            }
            if (aux3.Bloco_I == -1)
            {
                aux3 = ProcuraEspaco(&(*raiz)->Cen_Dir, Qtd, raiz, RAIZAvr, ptr);
            }
            if (aux3.Bloco_I == -1)
            {
                aux3 = ProcuraEspaco(&(*raiz)->Dir, Qtd, raiz, RAIZAvr, ptr);
            }
            // Adapte para a quantidade de filhos da árvore 2-3-4-5
        }
    }
    return aux3;
}

Arv45 *busca45(Arv45 **raiz, int info)
{
    Arv45 *aux = NULL;
    if (*raiz != NULL)
    {
        if ((info >= (*raiz)->info1.Bloco_I && info <= (*raiz)->info1.Bloco_F) ||
            (info >= (*raiz)->info2.Bloco_I && info <= (*raiz)->info2.Bloco_F) ||
            (info >= (*raiz)->info3.Bloco_I && info <= (*raiz)->info3.Bloco_F) ||
            (info >= (*raiz)->info4.Bloco_I && info <= (*raiz)->info4.Bloco_F))
        {
            aux = *raiz;
        }
        else if (info < (*raiz)->info1.Bloco_I)
        {
            aux = busca45(&(*raiz)->Esq, info);
        }
        else if ((info > (*raiz)->info1.Bloco_F && info < (*raiz)->info2.Bloco_I) || (*raiz)->Ninfos == 1)
        {
            aux = busca45(&(*raiz)->Cen_Esq, info);
        }
        else if ((info > (*raiz)->info2.Bloco_F && info < (*raiz)->info3.Bloco_I) || (*raiz)->Ninfos == 2)
        {
            aux = busca45(&(*raiz)->Cen, info);
        }
        else if ((info > (*raiz)->info3.Bloco_F && info < (*raiz)->info4.Bloco_I) || (*raiz)->Ninfos == 3)
        {
            aux = busca45(&(*raiz)->Cen_Dir, info);
        }
        else if (info > (*raiz)->info4.Bloco_F && (*raiz)->Ninfos == 4)
        {
            aux = busca45(&(*raiz)->Dir, info);
        }
    }
    return aux;
}

int remover(Arv45 **raiz, Arv45 **pai, int valor){
    int removeu = 0;
    Arv45 *noMenorInfoDir = NULL;
    if (*raiz != NULL)
    {
        if (valor == (*raiz)->info1.Bloco_I || valor == (*raiz)->info2.Bloco_I)
        {
            if (valor == (*raiz)->info1.Bloco_I)
            {
                if (ehFolha(*raiz))
                {
                    removeu = removeInfo1Folha(*raiz, *pai);
                    if (removeu == 3)
                    {
                        free(*raiz);
                        *raiz = NULL;
                    }
                }
                else
                {
                    removeu = removeInfo1NaoFolha((*raiz));
                }
            }
            else
            {
                if (ehFolha(*raiz))
                { // se for folha, so remove o no
                    removeu = removeInfo2Folha(*raiz);
                }
                else if (ehFolha((*raiz)->Dir))
                {
                    removeu = removeInfo2ComDirFolha((*raiz)->Dir, *raiz);
                }
                else
                {
                    if (numeroInfosArv((*raiz)->Dir) > 3)
                    {
                        noMenorInfoDir = obterMenorNo((*raiz)->Dir);
                        (*raiz)->info2 = noMenorInfoDir->info1;
                        removeu = remover(&((*raiz)->Dir), raiz, noMenorInfoDir->info1.Bloco_I);
                    }
                    else
                    {
                        removeu = removeInfo2NaoFolha(*raiz);
                    }
                }
            }
        }
        else if (valor < (*raiz)->info1.Bloco_I)
        {
            removeu = remover(&((*raiz)->Esq), raiz, valor);
        }
        else if (valor < (*raiz)->info2.Bloco_I || (*raiz)->Ninfos == 1)
        {
            removeu = remover(&((*raiz)->Cen), raiz, valor);
        }
        else if (valor > (*raiz)->info2.Bloco_I && (*raiz)->Ninfos == 2)
        {
            removeu = remover(&((*raiz)->Dir), raiz, valor);
        }
        // balancear;
        if (removeu == 2)
        {
            removeu = balancear(&(*raiz), &(*pai), removeu);
        }
    }
    return removeu;
}

int balancear(Arv45 **raiz, Arv45 **pai, int removeu)
{
    if ((*pai) == NULL)
    {
        (*raiz) = (*raiz)->Esq;
        removeu = 1;
    }
    else
    {
        if ((*pai)->Esq == (*raiz))
        {
            if ((*pai)->Cen->Ninfos == 2)
            {
                (*raiz)->info1 = (*pai)->info1;
                (*raiz)->Cen = (*pai)->Cen->Esq;
                (*pai)->info1 = (*pai)->Cen->info1;
                (*pai)->Cen->info1 = (*pai)->Cen->info2;
                (*pai)->Cen->Ninfos = 1;
                (*pai)->Cen->Esq = (*pai)->Cen->Cen;
                (*pai)->Cen->Cen = (*pai)->Cen->Dir;
                (*pai)->Cen->Dir = NULL;
                removeu = 1;
            }
            else
            {
                if ((*pai)->Ninfos == 2)
                {
                    (*raiz)->info1 = (*pai)->info1;
                    (*raiz)->info2 = (*pai)->Cen->info1;
                    (*raiz)->Ninfos = 2;
                    (*raiz)->Cen = (*pai)->Cen->Esq;
                    (*raiz)->Dir = (*pai)->Cen->Cen;
                    free((*pai)->Cen);
                    (*pai)->info1 = (*pai)->info2;
                    (*pai)->Ninfos = 1;
                    (*pai)->Cen = (*pai)->Dir;
                    (*pai)->Dir = NULL;
                    removeu = 1;
                }
                else
                {
                    (*raiz)->info1 = (*pai)->info1;
                    (*raiz)->info2 = (*pai)->Cen->info1;
                    (*raiz)->Ninfos = 2;
                    (*raiz)->Cen = (*pai)->Cen->Esq;
                    (*raiz)->Dir = (*pai)->Cen->Cen;
                    free((*pai)->Cen);
                    (*pai)->Cen = NULL;
                }
            }
        }
        else if ((*pai)->Cen == (*raiz))
        {
            if ((*pai)->Esq->Ninfos == 2)
            {
                (*raiz)->info1 = (*pai)->info1;
                (*pai)->info1 = (*pai)->Esq->info2;
                (*raiz)->Cen = (*raiz)->Esq;
                (*raiz)->Esq = (*pai)->Esq->Dir;
                (*pai)->Esq->Dir = NULL;
                (*pai)->Esq->Ninfos = 1;
                removeu = 1;
            }
            else
            {
                if ((*pai)->Ninfos == 2)
                {
                    (*pai)->Esq->info2 = (*pai)->info1;
                    (*pai)->Esq->Ninfos = 2;
                    (*pai)->Esq->Dir = (*raiz)->Esq;
                    free(*raiz);
                    *raiz = NULL;
                    free((*pai)->Cen);
                    (*pai)->Cen = NULL;
                    (*pai)->info1 = (*pai)->info2;
                    (*pai)->Ninfos = 1;
                    (*pai)->Cen = (*pai)->Dir;
                    (*pai)->Dir = NULL;
                    removeu = 1;
                }
                else
                {
                    (*pai)->Esq->info2 = (*pai)->info1;
                    (*pai)->Esq->Ninfos = 2;
                    (*pai)->Esq->Dir = (*pai)->Cen->Esq;
                    free((*pai)->Cen);
                    (*pai)->Cen = NULL;
                }
            }
        }
        else
        {
            if ((*pai)->Cen->Ninfos == 2)
            {
                (*raiz)->info1 = (*pai)->info2;
                (*raiz)->Cen = (*raiz)->Esq;
                (*raiz)->Esq = (*pai)->Cen->Dir;
                (*pai)->info2 = (*pai)->Cen->info2;
                (*pai)->Cen->Ninfos = 1;
                (*pai)->Cen->Dir = NULL;
            }
            else
            {
                (*pai)->Cen->info2 = (*pai)->info2;
                (*pai)->Cen->Ninfos = 2;
                (*pai)->Cen->Dir = (*raiz)->Esq;
                free(*raiz);
                *raiz = NULL;
                (*pai)->Ninfos = 1;
                free((*pai)->Dir);
                (*pai)->Dir = NULL;
            }
            removeu = 1;
        }
    }
    return removeu;
}

int removeInfo2Folha(Arv45 *raiz)
{
    raiz->Ninfos = 1;
    return 1;
}

int removeInfo2ComDirFolha(Arv45 *raiz, Arv45 *pai)
{
    int removeu = 0;
    if (raiz->Ninfos == 2)
    {
        pai->info2 = raiz->info1;
        raiz->info1 = raiz->info2;
        raiz->Ninfos = 1;
        removeu = 1;
    }
    else
    {
        if (pai->Cen->Ninfos == 2)
        {
            pai->info2 = pai->Cen->info2;
            pai->Cen->Ninfos = 1;
            removeu = 1;
        }
        else
        {
            pai->Cen->info2 = raiz->info1;
            pai->Cen->Ninfos = 2;
            pai->Ninfos = 1;
            free(raiz);
            pai->Dir = NULL;
            removeu = 1;
        }
    }
    return removeu;
}

Arv45 *obterMenorNo(Arv45 *raiz)
{
    Arv45 *aux = NULL;
    aux = raiz;
    if (raiz->Esq != NULL)
    {
        aux = obterMenorNo(raiz->Esq);
    }
    return aux;
}

int numeroInfosArv(Arv45 *raiz)
{
    int cont = 0;
    if (raiz != NULL)
    {
        cont += 1;
        if (raiz->Ninfos == 2)
        {
            cont += 1;
        }
        cont += numeroInfosArv(raiz->Esq);
        cont += numeroInfosArv(raiz->Cen);
        cont += numeroInfosArv(raiz->Dir);
    }
    return cont;
}

Arv45 *obterMaiorNo(Arv45 *raiz)
{
    Arv45 *aux = NULL;
    aux = raiz;
    if (raiz->Dir != NULL)
    {
        aux = obterMaiorNo(raiz->Dir);
    }
    else
    {
        if (raiz->Cen != NULL)
        {
            aux = obterMaiorNo(raiz->Cen);
        }
    }
    return aux;
}

int removeInfo2NaoFolha(Arv45 *raiz)
{
    int removeu = 0;
    Arv45 *noMaiorInfoCen = NULL;
    noMaiorInfoCen = obterMaiorNo(raiz->Cen);

    if (noMaiorInfoCen->Ninfos == 2)
    {
        raiz->info2 = noMaiorInfoCen->info2;
        removeu = remover(&(raiz->Cen), &raiz, noMaiorInfoCen->info2.Bloco_I);
    }
    else
    {
        raiz->info2 = noMaiorInfoCen->info1;
        removeu = remover(&(raiz->Cen), &raiz, noMaiorInfoCen->info1.Bloco_I);
    }
    return removeu;
}

int removeInfo1Folha(Arv45 *raiz, Arv45 *pai)
{
    int removeu = 0;
    if (raiz->Ninfos == 2)
    {
        raiz->info1 = raiz->info2;
        raiz->Ninfos = 1;
        removeu = 1;
    }
    else if (pai == NULL)
    {
        removeu = 3;
    }
    else
    {
        if (pai->Esq == raiz)
        {
            if (pai->Cen->Ninfos == 2)
            {
                raiz->info1 = pai->info1;
                pai->info1 = pai->Cen->info1;
                pai->Cen->info1 = pai->Cen->info2;
                pai->Cen->Ninfos = 1;
                removeu = 1;
            }
            else if (pai->Ninfos == 2)
            {
                raiz->info1 = pai->info1;
                raiz->info2 = pai->Cen->info1;
                raiz->Ninfos = 2;
                free(pai->Cen);
                pai->info1 = pai->info2;
                pai->Ninfos = 1;
                pai->Cen = pai->Dir;
                pai->Dir = NULL;
                removeu = 1;
            }
            else
            {
                removeu = 2;
            }
        }
        else if (pai->Cen == raiz)
        {
            if (pai->Esq->Ninfos == 2)
            {
                raiz->info1 = pai->info1;
                pai->info1 = pai->Esq->info2;
                pai->Esq->Ninfos = 1;
                removeu = 1;
            }
            else if (pai->Ninfos == 2)
            {
                if (pai->Dir->Ninfos == 2)
                {
                    raiz->info1 = pai->info2;
                    pai->info2 = pai->Dir->info1;
                    pai->Dir->info1 = pai->Dir->info2;
                    pai->Dir->Ninfos = 1;
                    removeu = 1;
                }
                else
                {
                    raiz->info1 = pai->info2;
                    raiz->info2 = pai->Dir->info1;
                    raiz->Ninfos = 2;
                    pai->Ninfos = 1;
                    free(pai->Dir);
                    pai->Dir = NULL;
                    removeu = 1;
                }
            }
            else
            {
                removeu = 2;
            }
        }
        else
        {
            if (pai->Cen->Ninfos == 2)
            {
                raiz->info1 = pai->info2;
                pai->info2 = pai->Cen->info2;
                pai->Cen->Ninfos = 1;
                removeu = 1;
            }
            else
            {
                pai->Cen->info2 = pai->info2;
                pai->Cen->Ninfos = 2;
                pai->Ninfos = 1;
                free(pai->Dir);
                pai->Dir = NULL;
                removeu = 1;
            }
        }
    }
    return removeu;
}

int removeInfo1NaoFolha(Arv45 *raiz)
{
    int removeu = 0;
    Arv45 *noMaiorInfoEsq = NULL;
    noMaiorInfoEsq = obterMaiorNo(raiz->Esq);

    if (noMaiorInfoEsq->Ninfos == 2)
    {
        raiz->info1 = noMaiorInfoEsq->info2;
        removeu = remover(&(raiz->Esq), &raiz, noMaiorInfoEsq->info2.Bloco_I);
    }
    else
    {
        raiz->info1 = noMaiorInfoEsq->info1;
        removeu = remover(&(raiz->Esq), &raiz, noMaiorInfoEsq->info1.Bloco_I);
    }
    return removeu;
}

void liberarMemoriaArvore(Arv45 *raiz) {
    if (raiz != NULL) {
        liberarMemoriaArvore(raiz->Esq);
        liberarMemoriaArvore(raiz->Cen_Esq);
        liberarMemoriaArvore(raiz->Cen);
        liberarMemoriaArvore(raiz->Cen_Dir);
        liberarMemoriaArvore(raiz->Dir);
        free(raiz);
    }
}