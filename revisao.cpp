#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>

/*Desenvolvimento de sistema que permite a transferência entre estruturas simplesmente Encadeadas.
Os dados dos sistemas, deverão ser o RA, Nome, a data de nascimento e o status (A)tivo ou (I)nativo.
Inicia-se por uma fila, onde o usuário poderá inserir, remover, listar, transferir, esvaziar ou sair.
Uma vez transferido, o comportamento de todas as funcionalidades do sistemas deverá ser modificada
para atender as necessidades da nova estrutura, ou seja, se transferiu de uma fila para uma pilha,
a mesma deverá, após a transferência se comportar como uma pilha.*/

/*
    Eder Ferreira de Matos
    0220481813020
*/

typedef struct Aluno{
    char nome [40];
    char dataNasc [14];
    unsigned long long int ra;
    char status;
    Aluno * proximo;
}Aluno;

void mostraMenu();
Aluno * novoElemento(Aluno *);
void inserirFila(Aluno **, Aluno **, Aluno *);
Aluno * inserirPilha(Aluno *, Aluno *);
void semAlunos();
void mostraAluno(Aluno);
void listar(Aluno *);
Aluno *remover(Aluno *);
Aluno *esvaziar(Aluno *);
void transferir(Aluno **, Aluno **, Aluno **);

int main(){
    setlocale(LC_ALL, "portuguese");
    Aluno *inicio = NULL, *fim, *topo = NULL;
    char opcao, tipo = 'F';

    do {
        mostraMenu();
        opcao = getche();

        switch(opcao){
            case '1':
                if(tipo == 'F'){
                    inserirFila(&inicio, &fim, NULL);
                }else{
                    topo = inserirPilha(topo, NULL);
                }
            break;
            case '2':
                if(tipo == 'F'){
                    printf("\n\nVocê está numa fila");
                    listar(inicio);
                }else{
                    printf("\n\nVocê está numa pilha");
                    listar(topo);
                }
            break;
            case '3':
                if(tipo == 'F'){
                    inicio = remover(inicio);
                }else{
                    topo = remover(topo);
                }
            break;
            case '4':
                if(tipo == 'F'){
                    inicio = esvaziar(inicio);
                }else{
                    topo = esvaziar(topo);
                }
            break;
            case '5':
                tipo = tipo == 'F' ? 'P' : 'F';
                transferir(&inicio, &fim, &topo);
            break;
            case '6':
                if(tipo == 'F'){
                    inicio = esvaziar(inicio);
                }else{
                    topo = esvaziar(topo);
                }
                printf("\nSaindo ...");
            break;
            default:
                printf("Opção Inválida!\n");
        }
        printf("\n");
    }while(opcao != '6');

    return 0;
}

void mostraMenu(){
    printf("\nMenu de Opções:\n");
    printf("1-Inserir:\n");
    printf("2-Listar:\n");
    printf("3-Remover\n");
    printf("4-Esvaziar:\n");
    printf("5-Transferir:\n");
    printf("6-Sair:\n");
    printf("Escolha a opção Desejada: ");
}

void semAlunos(){
    printf("\nNão existem Alunos cadastrados\n");
}

void mostraAluno(Aluno aluno){
    printf("Nome: %s", aluno.nome);
    printf("R.A: %llu\n", aluno.ra);
    printf("Data de Nascimento: %s\n", aluno.dataNasc);
    if(toupper(aluno.status) == 'I'){
        printf("Status: Inativo\n");
    } else if(toupper(aluno.status) == 'A'){
        printf("Status: Ativo\n");
    } else {
        printf("Status: Inválido\n");
    }
}

Aluno * novoElemento(Aluno *aluno){
    Aluno * novo = (Aluno *) malloc(sizeof(Aluno));
    if(novo == NULL){
        printf("Sem memória.\n");
    } else if(aluno == NULL){
        printf("\nDigite o nome do Aluno: ");
        fflush(stdin);
        fgets(novo->nome, 40, stdin);

        printf("Digite a Data de Nascimento do Aluno (dd/mm/yyyy): ");
        fflush(stdin);
        fgets(novo->dataNasc, 11, stdin);

        printf("Digite o R.A do Aluno: ");
        scanf("%llu", &novo->ra);
        getchar();

        printf("Digite status do Aluno (Ativo (A) - Inativo (I)): ");
        novo->status = getche();
    } else {
        strcpy(novo->nome, aluno->nome);
        strcpy(novo->dataNasc, aluno->dataNasc);
        novo->ra = aluno->ra;
        novo->status = aluno->status;
    }

    return novo;
}

void inserirFila(Aluno **inicio, Aluno **fim, Aluno *aluno){
    Aluno * novo = novoElemento(aluno);

    if(novo != NULL){
        novo->proximo = NULL;
        if(*inicio == NULL){
            *inicio = novo;
        } else {
            (*fim)->proximo = novo;
        }
        *fim = novo;
    }
}

Aluno * inserirPilha(Aluno * topo, Aluno *aluno){
    Aluno * novo = novoElemento(aluno);
    if(novo != NULL){
        novo->proximo = topo;
    }
    return novo;
}

void listar(Aluno * inicio){
    if(inicio == NULL){
        semAlunos();
    } else {
        printf("\n\n");
        while(inicio != NULL){
            mostraAluno(*inicio);
            printf("\n");
            inicio = inicio->proximo;
        }
    }
}

Aluno *remover(Aluno *aluno){
    if(aluno == NULL){
        semAlunos();
    }else{
        Aluno *aux = aluno->proximo;
        free(aluno);
        aluno = aux;
    }
    return aluno;
}

Aluno *esvaziar(Aluno *inicio){
    if(inicio == NULL){
        semAlunos();
    }else{
        while(inicio != NULL){
            inicio = remover(inicio);
        }
    }
    return inicio;
}

void transferir(Aluno **inicio, Aluno **fim, Aluno **topo){
    if(*inicio == *topo){
        semAlunos();
    }else if(*topo == NULL){
        while(*inicio != NULL){
            *topo = inserirPilha(*topo, *inicio);
            *inicio = remover(*inicio);
        }
        printf("\nTransferido de Fila para Pilha\n");
    }else{
        while(*topo != NULL){
            inserirFila(inicio, fim, *topo);
            *topo = remover(*topo);
        }
        printf("\nTransferido de Pilha para Fila\n");
    }
}
