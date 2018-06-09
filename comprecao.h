#ifndef COMPRECAO_H_INCLUDED
#define COMPRECAO_H_INCLUDED

typedef struct no{
    char elemento;
    int repeticao;
    struct no *esq;
    struct no *dir;
}tNo;

typedef struct listano{
    char elemento;
    struct listano *prox;
} tListaNo;

typedef struct repet{
    char elemento;
    int repeticao;
    struct repet *proxalfa;
}tRepeticao;


extern tListaNo * getListaNo(char elemento);
extern tRepeticao *getRepeticao(char elemento, int rep);
extern tNo * getNo(char elemento, int repeticao);

extern void IniciaRepeticao(tRepeticao **repeticao);
extern void IniciaLista(tListaNo **lista);
extern int InsereElementoEmOrdem(tListaNo **lista, char elemento);
extern void IniciaArvore(tNo **arv);
extern void CriaArvore(tNo**arv, tRepeticao **repeticao);
extern tNo * CriaArvoreAux(tNo *ar[]);
extern int ListaRepeticoes(tListaNo **lista, tRepeticao **repeticao);
extern void Armazena(tNo **arv, tListaNo *lista);
extern int InsereElementoEmOrdemRepeticao(tRepeticao **repeticao, char elemento , int repet);


#endif // COMPRECAO_H_INCLUDED
