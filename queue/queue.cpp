/*
    队列为空：头指针=尾指针
    头结点不放数据，单纯作为置空判断

    删除：front=rear=NULL
*/
#include<stdio.h>

template<typename Elemtype>
class QNode
{
// private:
public:
    Elemtype data;
    QNode<Elemtype> *next;
    QNode();
    ~QNode();
};

template<typename Elemtype>
QNode<Elemtype>::QNode()
{
    this->next=NULL;
}
template<typename Elemtype>
QNode<Elemtype>::~QNode()
{
}

template<typename Elemtype,typename Status>
class LinkQueue
{
// private:
public:
    QNode<Elemtype> *front;
    QNode<Elemtype> *rear;
    LinkQueue();
    ~LinkQueue();
    Status InitQueue();
    Status DestroyQueue();
    Status ClearQueue();
    Status QueueEmpty();
    int QueueLength();
    Status GetHead(Elemtype &e);
    Status EnQueue(Elemtype e);
    Status DeQueue(Elemtype &e);
};

template<typename Elemtype,typename Status>
LinkQueue<Elemtype,Status>::LinkQueue()
{
}
template<typename Elemtype,typename Status>
LinkQueue<Elemtype,Status>::~LinkQueue()
{
}

template<typename Elemtype,typename Status>
Status LinkQueue<Elemtype,Status>::InitQueue(){
    this->front = this->rear = new QNode<Elemtype>;
    if(!this->front) return false;
    this->front->next = NULL;
    return true;
}

template<typename Elemtype,typename Status>
Status LinkQueue<Elemtype,Status>::DestroyQueue(){
    while (this->front!=NULL)
    {
        this->rear=this->front->next;
        delete this->front;
        this->front=this->rear;
    }
    
    return this == NULL?true:false;
}
template<typename Elemtype,typename Status>
Status LinkQueue<Elemtype,Status>::ClearQueue(){
    if(this->front!=NULL) this->rear=this->front;
    return true;
}
template<typename Elemtype,typename Status>
Status LinkQueue<Elemtype,Status>::QueueEmpty(){
    return this->front==this->rear?true:false;
}
template<typename Elemtype,typename Status>
int LinkQueue<Elemtype,Status>::QueueLength(){
    if(QueueEmpty()) return 0;
    QNode<Elemtype> *p;
    int num=0;
    p=this->front;
    while (p!=NULL)
    {
        p=p->next;
        num++;
    }
    return num-1;
}
template<typename Elemtype,typename Status>
Status LinkQueue<Elemtype,Status>::GetHead(Elemtype &e){
    e=this->front->next->data;
    return true;
}
template<typename Elemtype,typename Status>
Status LinkQueue<Elemtype,Status>::EnQueue(Elemtype e){
    // if(QueueEmpty()) 
    this->rear->next=new QNode<Elemtype>;
    if(this->rear->next==NULL) return false;
    this->rear->next->data=e;
    this->rear->next->next=NULL;
    this->rear=this->rear->next;
    return true;
}
template<typename Elemtype,typename Status>
Status LinkQueue<Elemtype,Status>::DeQueue(Elemtype &e){
    if(QueueEmpty()) return false;
    e=this->front->next->data;
    QNode<Elemtype> *p=this->front->next;
    this->front->next=p->next;
    if(this->rear==p) this->rear=this->front;
    delete p;
    return true;
}

//for test
template<typename Elemtype,typename Status>
bool Print(LinkQueue<Elemtype,Status> Q){
    if(Q.QueueEmpty()) return false;
    QNode<Elemtype> *p;
    p=Q.front->next;
    while (p!=NULL)
    {
        printf("%d",p->data);
        p=p->next;
    }
    return true;
}

int main(){
    LinkQueue<int,bool> Q;
    int e=0;
    Q.InitQueue();
    for (int i = 0; i < 20; i++)
    {
        Q.EnQueue(i);
    }
    for (int i = 0; i < 10; i++)
    {
        Q.DeQueue(e);
        printf("%d ",e);
    }
    for (int i = 0; i < 5; i++)
    {
        Q.EnQueue(i);
    }
    // Q.ClearQueue();
    // Q.DestroyQueue();
    printf("\n");
    Print<int,bool>(Q);
    // int x;
    scanf("%d",&e);
    return 0;
}