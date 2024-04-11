#include"header.h"
void initQ(Queue* q,int size){
    q->size=size;
    q->A=(ele *)malloc(sizeof(ele)*size);
    q->front=-1;
    q->rear=-1;
    q->length=0;
    return;
}
int isfull(Queue q){
    if (q.rear==q.size-1)
    {
        return 1;
    }
    return 0;     
}
int isEmpty(Queue q){
    if (q.rear==-1)
    {
        return 1;
    }
    return 0;
}
void Enqueue(Queue* q, int val, int x, int y, int z) {
    if (isfull(*q)) {
        return;
    }
    if (isEmpty(*q)) q->front = 0;
    q->A[q->rear].value = val;
    q->A[q->rear].x = x;
    q->A[q->rear].y = y;
    q->A[q->rear].z = z;

    // printf("%d ", q->rear);
    return;
}

ele* Dequeue(Queue* q){
    if (isEmpty(*q))
    {
        return NULL;
    }
    return &(q->A[q->front++]);

}
// void Display(Queue q){
//     if (q.rear==-1)
//     {
//         printf("No elements in Queue \n");
//         return;
//     }
    
//     printf("Elements in queue are :\n");
//     for (int i = q.front; i <= q.rear; i++)
//     {
//         printf("%d ",q.A[i]);   
//     }
//     printf("\n");
//     return;
    
// }
