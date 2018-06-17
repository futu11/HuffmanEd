#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "descompressao.h"

void IniciaLista(tLista **lista){
    *lista = NULL;
}

tLista *getNo(char elemento){
    tLista *n;
    n = malloc(sizeof(tLista));
    if(n != NULL){
        n->prox = NULL;
        n->elemento = elemento;
    }
    return n;
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
        proxchar = getc(fp);
        if(proxchar == 'T')
            break;
    }
    while(proxchar != EOF){
        qLetras++;
        proxchar = getc(fp);
    }
    fclose(fp);
    return qLetras;

}

tLista * LeArquivo(int tam, const char* arq, tLista *lista, char comp[]){
    tLista *l;
    FILE *fp;
    fp = fopen(arq, "r");
    char elemento;
    char cod[10] = {3};
    int j = 0;
    while(1){
        j = 0;
        elemento = getc(fp);
      //  printf("\nelemento:%c\n", elemento);
        if(elemento == 'T')
            break;
        getc(fp);
        while(j < 10){
            cod[j] = 0;
            j++;
        }
        j = 0;
        fgets(cod, 10, fp);
        if(lista != NULL){
            l->prox = getNo(elemento);
            printf("\n");
            printf("%c:", l->prox->elemento);
            l = l->prox;
            while(cod[j] != '\n'){
                l->cod[j] = cod[j];
                j++;
                if(cod[j] == '\n'){
                   // printf("\nJ:%d\n", j);
                    l->cod[j] = '\0';
                    int i = 0;
                    while (l->cod[i] != '\0'){
                        printf("%c", l->cod[i]);
                        i++;
                    }
                    //printf(",%s", l->cod);
                    break;
                }
            }
        }
        if(lista == NULL){
            lista = getNo(elemento);
            printf("%c:", lista->elemento);
            j = 0;
           // printf("\n");
            while(cod[j] != '\n'){
                lista->cod[j] = cod[j];
                //printf("%c", lista->cod[j]);
                j++;
                if(cod[j] == '\n'){
                    lista->cod[j] = '\0';
                   // printf("\nJ:%d\n", j);
                    //printf("%s", lista->cod);
                    int i = 0;
                    while(lista->cod[i] != '\0'){
                        printf("%c", lista->cod[i]);
                        i++;
                    }
                }
            }
            l = lista;
        }

    }
    getc(fp);
    printf("\n");
    j = 0;
    while(j != tam - 2){
        comp[j] = getc(fp);
        printf("%c", comp[j]);
        j++;
    }
    //comp[j] = EOF;
    fclose(fp);
    return lista;
}

int descompressao(tLista *lista, char comprimido[], int tam, const char *arq){
    FILE *fp;
    fp = fopen(arq, "w");
    tLista *l = lista;
    int i = 0;
    int j = 0;
    int r = 1;
    char cmp[10];
    printf("\n");
        while(j != tam - 2){
            l = lista;
            for(i = 0; comprimido[j] != '.'; i++){
                cmp[i] = comprimido[j];
               // printf("j:%d", j);
                j++;
                if(comprimido[j] == '.'){
                    cmp[i + 1] = '\0';
                    j++;
                    break;
                }
            }
            l = lista;
            while(l != NULL){
                r = strcmp(cmp, l->cod);
                if(r == 0){
                    printf("%c", l->elemento);
                   fprintf(fp, "%c", l->elemento);
                }
                l = l->prox;
            }
            i = 0;
            while(i < 10){
                cmp[i] = 0;
                i++;
            }
            i = 0;
        }

        fclose(fp);
        return 0;
}

int main(){

    tLista *lista;
    IniciaLista(&lista);
    int tam = Chars("/Users/win/Documents/ED/Projeto_Final/Comprimido.txt");
   // printf("%d", tam);
    char comp[tam];
    lista = LeArquivo(tam, "/Users/win/Documents/ED/Projeto_Final/Comprimido.txt", lista, comp);
    descompressao(lista, comp, tam, "/Users/win/Documents/ED/Projeto_Final/Descomprimido.txt");
    return 0;
}
