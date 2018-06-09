#include <stdio.h>
#include <stdlib.h>
#include "comprecao.h"
#include <math.h>

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
    printf("%d", arvore->repeticao);
       // printf("%d", (*arv)->repeticao);
        return arvore;
    }
    CriaArvoreAux(ar);
}

int main(){
    tListaNo *lista;
    IniciaLista(&lista);
    tRepeticao *repeticao;
    IniciaRepeticao(&repeticao);
    tListaNo *listateste;
    IniciaLista(&listateste);
    tNo *arvore;
    IniciaArvore(&arvore);

    int i = 0;
    char elemento[256] = {0};
    printf("Insira uma frase para ser comprimida:\n");
    scanf("%s", elemento);
    while(elemento[i] != 0){
        InsereElementoEmOrdem(&lista, elemento[i]);
        i++;
    }
    listateste = lista;
    ListaRepeticoes(&lista, &repeticao);
    CriaArvore(&arvore, &repeticao);
    tNo *arvoreteste;
    IniciaArvore(&arvoreteste);
    arvoreteste = arvore;
    printf("%d", arvore->repeticao);
   // printf("%d", arvoreteste->repeticao);

 /*   while(repeticao->proxalfa != NULL){
        printf("\n%c", repeticao->elemento);
        printf(", %d", repeticao->repeticao);
        repeticao = repeticao->proxalfa;
        if(repeticao->proxalfa == NULL){
            printf("%c\n", repeticao->elemento);
            printf(", %d", repeticao->repeticao);
        }
    }*/
return 0;
}
