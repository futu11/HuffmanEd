#ifndef DESCOMPRESSAO_H_INCLUDED
#define DESCOMPRESSAO_H_INCLUDED

typedef struct lista{
    char elemento;
    char cod[10];
    struct lista *prox;
}tLista;

extern void IniciaLista(tLista **lista);
extern tLista *getNo(char elemento);
extern int descompressao(tLista *lista, char comp[], int tam, const char *arq);

#endif // DESCOMPRESSAO_H_INCLUDED
