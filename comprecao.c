#include <stdio.h>
#include <stdlib.h>
#include "comprecao.h"
#include  <string.h>

#define MAX 256
tListaNo * getListaNo(char elemento){
    tListaNo * n;
    n = malloc(sizeof(tListaNo));
    if (n != NULL){
        n->elemento = elemento;
        n->prox = NULL;
    }
    return n;
}

tRepeticao *getRepeticao(char elemento, int rep){
    tRepeticao * r;
    r = malloc(sizeof(tRepeticao));
    if(r != NULL){
        r->elemento = elemento;
        r->repeticao = rep;
        r->proxalfa = NULL;
    }
    return r;
}

tNo *getNo(char elemento, int repeticao){
    tNo * n;
    n = malloc(sizeof(tNo));
    if(n != NULL){
        n->elemento = elemento;
        n->repeticao = repeticao;
        n->dir = NULL;
        n->esq = NULL;
    }
    return n;
}

void IniciaLista(tListaNo **lista){
    *lista = NULL;
}

void IniciaRepeticao(tRepeticao **repeticao){
    *repeticao = NULL;
}

void IniciaArvore(tNo **arvore){
    *arvore = NULL;
}

int InsereElementoEmOrdem(tListaNo **lista, char elemento){
    tListaNo *no1 = *lista;
    tListaNo *no2 = *lista;
    tListaNo *novo = getListaNo(elemento);
    if(*lista == NULL){
        *lista = novo;
        novo->prox = NULL;
        return 0;
    }
    if(no1->elemento >= novo->elemento){
        *lista = novo;
        novo->prox = no1;
        return 0;
    }
    while(novo->elemento > no1->elemento){
        if(no1->prox == NULL){
            no1->prox = novo;
            return 0;
        }
        no1 = no1->prox;
        if(novo->elemento <= no1->elemento){
            no2->prox = novo;
            novo->prox = no1;
            return 0 ;
        }
        no2 = no2->prox;
    }
    return 0;
}


int ListaRepeticoes(tListaNo **lista, tRepeticao **repeticao){
    if(*lista == NULL){
        printf("Lista Vazia");
        return -1;
    }
    int count = 1;
    tRepeticao *rep2;
    tListaNo *no = *lista;
    if(no->prox == NULL){
        tRepeticao *rep;
        rep = getRepeticao(no->elemento, count);

        *repeticao = rep;
       // return 0;
    }
    while(no->prox != NULL){
        count = 1;
        while(no->prox != NULL && no->elemento == no->prox->elemento){
            count = count + 1;
            no = no->prox;
            if(no->prox == NULL){
                tRepeticao *rep;
                rep = getRepeticao(no->elemento, count);
                if(*repeticao != NULL){
                    rep2->proxalfa = rep;
                    rep2 = rep2->proxalfa;

                }
                if(*repeticao == NULL){
                    *repeticao = rep;
                    rep2 = *repeticao;
                }
            }
        }
        if(no->prox != NULL && no->elemento != no->prox->elemento){
            tRepeticao *rep;
            rep = getRepeticao(no->elemento, count);
            if(*repeticao != NULL){
                rep2->proxalfa = rep;
                rep2 = rep2->proxalfa;
            }
            if(*repeticao == NULL){
                *repeticao = rep;
                rep2 = *repeticao;
            }
            no = no->prox;
        }
        count = 1;
        if(no->prox == NULL && no->elemento != rep2->elemento){
            tRepeticao *rep;
            rep = getRepeticao(no->elemento, count);
            rep2->proxalfa = rep;
            rep2 = rep2->proxalfa;
        }

    }
    tRepeticao *maior, *menor, *anterior, *posterior, *aux, *aux2, *aux3;
    anterior = *repeticao;
    posterior = anterior->proxalfa;
    //ORGANIZA A LISTA EM UMA NOVA LISTA GRAVANDO AS REPETICOES
    while(posterior != NULL){
        if(posterior->repeticao < anterior->repeticao){
            anterior = posterior;
        }
        posterior = posterior->proxalfa;
    }
    //ORGANIZA A LISTA DE REPETICOES EM ORDEM CRESCENTE
    menor = anterior;
    anterior = *repeticao;
    while(anterior->proxalfa != menor && anterior != menor){
        anterior = anterior->proxalfa;
    }

    if(anterior->proxalfa == menor){
        posterior = menor->proxalfa;
        menor->proxalfa = *repeticao;
        *repeticao = menor;
        anterior->proxalfa = posterior;
    }

    anterior = *repeticao;
    if(anterior->proxalfa == NULL)
        return 0;

    if(anterior->proxalfa->proxalfa == NULL)
        return 0;

    anterior = *repeticao;
    anterior = anterior->proxalfa;
    posterior = anterior->proxalfa;
    while(posterior != NULL){
        if(posterior->repeticao > anterior->repeticao){
            anterior = posterior;
        }
        if(posterior->proxalfa == NULL)
            aux = posterior;
        posterior = posterior->proxalfa;
    }
    maior = anterior;
    anterior = *repeticao;
    if(maior->proxalfa != NULL){
        while(anterior->proxalfa != maior){
            anterior = anterior->proxalfa;
        }
        if(anterior->proxalfa == maior){
            anterior->proxalfa = anterior->proxalfa->proxalfa;
            aux->proxalfa = maior;
            maior->proxalfa = NULL;
        }
    }
    anterior = *repeticao;
    anterior = anterior->proxalfa;
    posterior = anterior->proxalfa;
    aux = *repeticao;
    aux3 = *repeticao;
    while(aux->proxalfa != maior){
        while(posterior->proxalfa != NULL && posterior->repeticao > anterior->repeticao && anterior->repeticao > aux->repeticao ){
            posterior = posterior->proxalfa;
        }
        while(posterior->proxalfa != NULL){
            if(posterior->repeticao < anterior->repeticao){
                anterior = posterior;
            }
            posterior = posterior->proxalfa;
            if(anterior == aux->proxalfa && posterior->proxalfa == NULL){
                aux = aux->proxalfa;
                anterior = anterior->proxalfa;
                posterior = anterior->proxalfa;
            }
        }
        if(aux->proxalfa->proxalfa == maior)
            return 0;
        while(aux3->proxalfa != anterior)
            aux3 = aux3->proxalfa;
        menor = anterior;
        aux2 = menor->proxalfa;
        menor->proxalfa = aux->proxalfa;
        aux->proxalfa = menor;
        aux3->proxalfa = aux2;
        aux = aux->proxalfa;
        anterior = aux->proxalfa;
        posterior = anterior->proxalfa;
        menor = aux;
        aux3 = *repeticao;
    }

    return 0;
}

void CriaArvore(tNo **arv, tRepeticao **repeticao){

    int i = 0;
    tNo *leafarray[100] = {NULL};
    for(i = 0; (*repeticao)->proxalfa != NULL; i++){
        leafarray[i] = getNo((*repeticao)->elemento, (*repeticao)->repeticao);
        (*repeticao) = (*repeticao)->proxalfa;
            if((*repeticao)->proxalfa == NULL){
                    i++;
                leafarray[i] = getNo((*repeticao)->elemento, (*repeticao)->repeticao);
            }

    }
   *arv = CriaArvoreAux(leafarray);


}
tNo * CriaArvoreAux(tNo *ar[]){

    int i, count;
    tNo *no;
    no = malloc(sizeof(tNo));

    no->esq = ar[0];
    no->dir = ar[1];
    if(ar[1] != NULL){
        no->repeticao = ar[0]->repeticao + ar[1]->repeticao;
    }else{
    no->repeticao = ar[0]->repeticao;
    }
    for(i = 2; ar[i] != NULL; i++){
        ar[i - 2] = ar[i];
    }
    ar[i - 2] = NULL;
    ar[i - 1] = NULL;
    count = 0;
    while(ar[count] != NULL && no->repeticao >= ar[count]->repeticao){
        count++;
    }
    while(ar[count] != NULL && count < i){
        ar[i - 1] = ar[i - 2];
        i --;
    }
    ar[count] = no;
    if(ar[1] == NULL){
        tNo *arvore = malloc(sizeof(tNo));
        arvore = ar[0];
       // printf("%d", (*arv)->repeticao);
        return arvore;
    }
    CriaArvoreAux(ar);
}
void CodificaArvore(tNo *arv, int ar[], int aux) {
    int i;
    if(arv != NULL) {
        printf("%d\n",arv->repeticao);
        if(arv->esq == NULL && arv->dir == NULL){
            i = 0;
            while(i != 9){
                arv->cod[i] = ar[i];
                i++;
            }
            i = 0;
            printf("O codigo eh:");
            while(arv->cod[i] != 3){
                printf("%d", arv->cod[i]);
               // EscreveArquivo(arv->cod[i], "/Users/win/Documents/ED/Projeto_Final/Comprimido.txt");
                i++;
            }
            printf("\nO elemento eh: %c", arv->elemento);
            printf("\n");
        }
        if(arv->esq != NULL)
            ar[aux] = 0;

        CodificaArvore(arv->esq, ar, aux + 1);
        if(arv->dir != NULL)
            ar[aux] = 1;

        CodificaArvore(arv->dir, ar, aux + 1);
    }
}
int CodificaLista(tNo *arv, char elemento[], int aux, int i, int cod){
    if(arv != NULL){
        if(arv != NULL && arv->elemento == elemento[i]){
            int i = 0;
            while(arv->cod[i] != 3){
                printf("%d", arv->cod[i]);
                i++;
            }

        }
        CodificaLista(arv->esq, elemento, aux + 1, i, cod);
        CodificaLista(arv->dir, elemento, aux + 1, i, cod);
    }
    if(arv != NULL && aux == 0 && elemento[i + 1] != 0){
            i = i + 1;
        CodificaLista(arv, elemento, aux, i, cod);
    }
    if(elemento[i] == 0)
        return cod;
}

int Chars(const char* arq){
    int qLetras = 0;
    FILE *fp;
    char proxchar;
    fp = fopen(arq, "r");
    if (fp == NULL){
        puts("arquivo nao encontrado");
        exit(1);
    }
    proxchar = getc(fp);
    while(proxchar != EOF){
        qLetras ++;
        proxchar = getc(fp);
    }
    fclose(fp);
    return qLetras;

}

void LeArquivo(int tam, char elemento[], const char* arq){
    FILE *fp;
    fp = fopen(arq, "r");
    if(fp == NULL){
        puts("arquivo nao encontrado");
        exit(1);
    }
    fgets(elemento, tam + 1, fp);
    fclose(fp);

}

void EscreveArquivo(char cod, FILE* fp){
    fputc(cod, fp);
}
int main(){
    int r;
    r = Chars("/Users/win/Documents/ED/Projeto_Final/Texto.txt");
    printf("%d\n", r);
    char elemento[r + 1];
    LeArquivo(r, elemento, "/Users/win/Documents/ED/Projeto_Final/Texto.txt");
    tListaNo *lista;
    IniciaLista(&lista);
    tRepeticao *repeticao;
    IniciaRepeticao(&repeticao);
    tListaNo *listateste;
    IniciaLista(&listateste);
    tNo *arvore;
    IniciaArvore(&arvore);

    int i = 0;
    while(i < r){
        InsereElementoEmOrdem(&lista, elemento[i]);
        i++;
    }
    listateste = lista;
    ListaRepeticoes(&lista, &repeticao);
    CriaArvore(&arvore, &repeticao);
    int ar[10];
    i = 0;
    while(i != 9){
        ar[i] = 3;
        i++;
    }
    int cod = 0;
    int aux = 0;
    CodificaArvore(arvore, ar, aux);
    aux = 0;
    i = 0;
    CodificaLista(arvore, elemento, aux, i, cod);
    char a = 'a';
    char b = 'b';
    FILE *fp;
    fp = fopen("/Users/win/Documents/ED/Projeto_Final/Comprimido.txt", "w");
    EscreveArquivo(b, fp);
    EscreveArquivo(a, fp);
    fclose(fp);
return 0;
}
