#include "FilaDePrioridade.h"

PFILA criarFila(int max){
    PFILA res = (PFILA) malloc(sizeof(FILADEPRIORIDADE));
    res->maxRegistros = max;
    res->arranjo = (PONT*) malloc(sizeof(PONT)*max);
    res->heap = (PONT*) malloc(sizeof(PONT)*max);
    int i;
    for (i=0;i<max;i++) {
        res->arranjo[i] = NULL;
        res->heap[i] = NULL;
    }
    res->elementosNoHeap = 0;
    return res;
}

bool exibirLog(PFILA f){
    printf("Log [elementos: %i]\n", f->elementosNoHeap);
    PONT atual;
    int i;
    for (i=0;i<f->elementosNoHeap;i++){
        atual = f->heap[i];
        printf("[%i;%f;%i] ", atual->id, atual->prioridade, atual->posicao);
    }
    printf("\n\n");
    return true;
}

int tamanho(PFILA f){
    return f->elementosNoHeap;
    return 0;
}

int pai(int i){
    return i/2;
}

int filhoEsquerda(int i){
    return 2*i;
}

int filhoDireita(int i){
    return 2*i + 1;
}

void refazHeapMaximo(PFILA f, PONT atual){
    if(atual == NULL) return;
    if(f->heap[pai(atual->posicao)] != NULL && f->heap[pai(atual->posicao)]->prioridade >= atual->prioridade) return;
    f->heap[atual->posicao] = f->heap[pai(atual->posicao)];
    f->heap[atual->posicao]->posicao = atual->posicao;
    f->heap[pai(atual->posicao)] = atual;
    atual->posicao = pai(atual->posicao);
    refazHeapMaximo(f, f->heap[atual->posicao]);
}
bool inserirElemento(PFILA f, int id, float prioridade){
    if(id < 0 || id > f->maxRegistros -1) return false;
    PONT novo = (PONT) malloc(sizeof(REGISTRO));
    f->arranjo[id] = novo;
    novo->id = id;
    novo->prioridade = prioridade;
    novo->posicao = f->elementosNoHeap;
    f->heap[novo->posicao] = novo;
    f->elementosNoHeap++;
    refazHeapMaximo(f, novo);
    return true;
}

bool aumentarPrioridade(PFILA f, int id, float novaPrioridade){
    if(id < 0 || id > f->maxRegistros) return  false;
    if(f->arranjo[id] == NULL) return false;
    if(f->arranjo[id]->prioridade >= novaPrioridade) return false;
    f->arranjo[id]->prioridade = novaPrioridade;
    refazHeapMaximo(f, f->arranjo[id]);
    return true;
}

PONT verificaFilhoMaior(PFILA f, int posicao){ //verificar qual filho é maior
    if(f->heap[filhoDireita(posicao)] == NULL) return f->heap[filhoEsquerda(posicao)];
    if(f->heap[filhoEsquerda(posicao)] == NULL) return f->heap[filhoDireita(posicao)];
    if(f->heap[filhoDireita(posicao)] -> prioridade>= f->heap[filhoEsquerda(posicao)] ->prioridade)
        return f->heap[filhoDireita(posicao)];
    return f->heap[filhoEsquerda(posicao)];
}
void reduzirPrioridadeAux2(PFILA f, PONT atual){
    if(atual == NULL) return;
    PONT filho = verificaFilhoMaior(f, atual->posicao);
    if(filho != NULL && filho->prioridade <= atual->prioridade) return;
    if(filho == NULL) return;
    //sou menor que meu filho, posso fazer.
    int temp = filho->posicao;
    if(filho->posicao == f->heap[filhoEsquerda(atual->posicao)]->posicao){
        f->heap[filhoEsquerda(atual->posicao)]->posicao = atual->posicao;
        f->heap[atual->posicao] = f->heap[filhoEsquerda(atual->posicao)];
        f->heap[temp] = atual;
        atual->posicao = temp;
    }
    else{
    f->heap[filhoDireita(atual->posicao)]->posicao = atual->posicao;
    f->heap[atual->posicao] = f->heap[filhoDireita(atual->posicao)];
    atual->posicao = temp;
    f->heap[temp] = atual;
    }
    reduzirPrioridadeAux2(f, f->heap[temp]);
}
bool reduzirPrioridade(PFILA f, int id, float novaPrioridade){
    if(f->arranjo[id] == NULL) return false;
    if(f->arranjo[id]->prioridade <= novaPrioridade) return false;
    if(id < 0 || id > f->maxRegistros) return false;
    f->arranjo[id]->prioridade = novaPrioridade;
    reduzirPrioridadeAux2(f, f->arranjo[id]);
    return true;
}

PONT removerElemento(PFILA f){
    if(f->elementosNoHeap == 0) return NULL; //fila vazia
    PONT apagar = f->heap[0];
    f->arranjo[f->heap[0]->id] = NULL;
    f->heap[0] = f->heap[f->elementosNoHeap - 1];
    f->elementosNoHeap--;
    if(f->heap[0] != NULL)
    f->heap[0]->posicao = 0;
    reduzirPrioridadeAux2(f, f->heap[0]);
    return apagar;
}

bool consultarPrioridade(PFILA f, int id, float* resposta){
    if(id < 0 || id >f->maxRegistros) return false;
    if(f->elementosNoHeap == 0)
    return false;
    if(f->arranjo[id] != NULL){
    *resposta = f->arranjo[id]->prioridade;
    return true;
    }
    return false;
}
