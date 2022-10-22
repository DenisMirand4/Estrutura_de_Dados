#ifndef __fila__
#define __fila__

/* 
    Tad responsavel por cria uma estrutura do tipo FILA
*/

typedef void* Fila;
typedef void* FilaInfo;
/*  CRIA UMA FILA*/
Fila createQueue();
/* Verifica se a fila está vazia*/
int queueIsEmpty(Fila fila);
/* Insere um elemento na fila*/
void enqueue(FilaInfo info, Fila fila);
/* Remove e retorna o inicio da fila*/
FilaInfo dequeue(Fila fila);

#endif