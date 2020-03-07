/*
    循环队列
*/
#include<stdio.h>
#include<stdlib.h>

#define MAXQSIZE 100

template<typename Elemtype>
struct SqQueue
{
    Elemtype *base;
    int front;
    int rear;
};

template<typename Status,typename Elemtype>
Status InitQueue(SqQueue<Elemtype> &Q){
    Q.base = (Elemtype *)malloc(MAXQSIZE*sizeof(Elemtype));
    if(Q.base == NULL) return false;
    Q.front = Q.rear = 0;
    return true;
}
template<typename Status,typename Elemtype>
int QueueLength(SqQueue<Elemtype> Q){
    return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}
template<typename Status,typename Elemtype>
Status QueueFull(SqQueue<Elemtype> Q){
    return (Q.rear+1)%MAXQSIZE == Q.front ? true:false;
}
template<typename Status,typename Elemtype>
Status EnQueue(SqQueue<Elemtype> &Q,Elemtype e){
    if(QueueFull<bool,int>(Q)) return false;
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MAXQSIZE;
    return true;
}
template<typename Status,typename Elemtype>
Status DeQueue(SqQueue<Elemtype> &Q,Elemtype &e){
    if(Q.front == Q.rear) return false;
    e = Q.base[Q.front];
    Q.front = (Q.front+1) % MAXQSIZE;
    return true;
}
template<typename Status,typename Elemtype>
Status DestoryQueue(SqQueue<Elemtype> &Q){
    try{
        free(Q.base);
        Q.base = NULL;
        Q.front = Q.rear = 0;
        return true;
    }
    catch(...){
        printf("free fail");
        return false;
    }
    // Q.base == NULL;
}
template<typename Status,typename Elemtype>
Status ClearQueue(SqQueue<Elemtype> &Q){
    Q.rear = Q.front;
    return true;
}

int main(){
    SqQueue<int> Q;
    int e;
    InitQueue<bool,int>(Q);
    for (int i = 0; i < 1000; i++)
    {
        EnQueue<bool,int>(Q,i);
    }
    ClearQueue<bool,int>(Q);
    DestoryQueue<bool,int>(Q);
    printf("length:%d\n",QueueLength<bool,int>(Q));
    for (int i = 0; i < 20; i++)
    {
        DeQueue<bool,int>(Q,e);
        printf("%d ",e);
    }
    printf("length:%d\n",QueueLength<bool,int>(Q));
    scanf("%d",&e);
    return 0;
}