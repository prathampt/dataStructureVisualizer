#include<stdio.h>
#include<limits.h>
#include<stdlib.h>
typedef struct node
{
    int x,y,z,value;   
}ele;

typedef struct Queue
{
    int front,rear;
    int length,size;
    ele *A;
}Queue;
void initQ(Queue* q,int size);
void Enqueue(Queue* q,int val,int x, int y, int z);
int Dequeue(Queue* q);
// void Display(Queue q);