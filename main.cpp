#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>

typedef struct Aluno{
    char nome [40];
    char dataNasc [14];
    unsigned long long int ra;
    char status;
}Aluno;

void mostraMenu();
Aluno * novoElemento(Aluno);
void inserirFila(Aluno **, Aluno **, Aluno *);
Aluno * inserirPilha(Aluno *, Aluno);
void semAlunos();
void mostraAluno(Aluno);
void listar(Aluno *);
Aluno *remover(Aluno *);
Aluno *esvaziar(Aluno *);
void transferir(Aluno **, Aluno **, Aluno **);

int main(){
    setlocale(LC_ALL, "portuguese");
    Aluno *inicio = NULL, *fim, *topo = NULL, **auxiliar;
    char opcao, tipo = 'F';

    do {
        mostraMenu();
        opcao = getche();

        auxiliar = (tipo == 'F') ? &inicio : &topo;
        switch(opcao){
            case '1':
                if(tipo == 'F'){
                    inserirFila(&inicio, &fim, NULL);
                }else{
                    topo = inserirPilha(topo, NULL);
                }
            break;
            case '2':
                listar(*auxiliar);
            break;
            case '3':
                *auxiliar = remover(*auxiliar);
            break;
            case '4':
                *auxiliar = esvaziar(*auxiliar);
            break;
            case '5':
                tipo = tipo == 'F' ? 'P';
                tranferir(&inicio, &fim, &topo);
            break;
            case '6':
                printf("Saindo ...");
                *auxiliar = esvaziar(*auxiliar);
            break;
            default:
                printf("Opção Inválida!\n");
            }
        }
    }while(opcao != '6');

    return 0;
}

void mostraMenu(){
    printf("Menu de Opções:\n");
    printf("1-Inserir:\n");
    printf("2-Listar:\n");
    printf("3-Remover\n");
    printf("4-Esvaziar:\n");
    printf("5-Transferir:\n");
    printf("6-Sair:\n");
    printf("Escolha a opção Desejada: ");
}

void semAlunos(){
    printf("Não existem Alunos cadastrados");
}

void mostraAluno(Aluno aluno){
    printf("Nome: %s\n", aluno.nome);
    printf("R.A: %llu\n", aluno.ra);
    printf("Data de Nascimento: %s\n", aluno.dataNasc);
    printf("Status: %s\n", aluno.status == 'I' ? 'Inativo' : 'Ativo');
}

Aluno * novoElemento(Aluno aluno){
    Aluno novo = (Aluno *) malloc(sizeof(Aluno));
    if(novo == NULL){
        printf("Sem memória.\n");
    } else if(aluno == NULL){
        printf("Digite o nome do Aluno: ");
        fflush(stdin);
        fgets(&novo->nome, 40, stdin);

        printf("Digite a Data de Nascimento do Aluno (dd/mm/yyyy): ");
        fflush(stdin);
        fgets(&novo->dataNasc, 10, stdin);

        printf("Digite o R.A do Aluno: ");
        scanf("%llu", &novo->ra);
        getchar();

        printf("Digite status do Aluno (Ativo (A) - Inativo (I)): ");
        &novo->status = getche();
    } else {
        &novo->nome = aluno.nome;
        &novo->dataNasc = aluno.dataNasc;
        &novo->ra = aluno.ra;
        &novo->status = aluno.status;
    }

    return novo;
}

void inserirFila(Aluno **inicio, Aluno **fim, Aluno *aluno){
    Aluno * novo = novoElemento(*aluno);

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

Aluno * inserirPilha(Aluno * topo, Aluno aluno){
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
        while(inicio != NULL){
            mostraAluno(*inicio);
            inicio = inicio->proximo;
        }
    }
}

Aluno *remover(Aluno *Aluno){
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
    }else if(*topo != NULL){
        while(*inicio != NULL){
            *topo = inserirPilha(*topo,*inicio);
            *inicio = remover(*inicio);
        }
    }else{
        while(*topo != NULL){
            *inicio = inserirFila(inicio,fim,*topo);
            *topo = remover(*topo);
        }
    }
}
