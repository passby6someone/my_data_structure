/*
*说实话我是很纠结的
*函数到底写到成员函数里去还是全局声明
*函数模板到底要不要定义返回值
*类要不要写函数模板
*超级纠结，关键是我c++还不熟练，lambad啊，并发啊，接口啊很多都不会写
*一边写一边纠结，但是书上一些奇妙的设定让我觉得还是写到成员函数里比较好
*比如insfirst，因为插入了数据，但是由于传入参数的局限，并不能对链表的长度进行修改
*但是如果我写到成员函数里去，就可以修改其成员变量
*但是这样又有个问题，我要参数何用？反正成员函数可以修改成员变量。。。
*感觉就是很zz。。。
*最后还是决定写成员函数并按照书上的要传的参数来好了
*btw模板真nm难用
*/
#include<stdlib.h>
#include<stdio.h>
#include<iostream>

using namespace std;

//节点类模板
template <typename ElemType>
class LNode {
    public:
        ElemType data;
        LNode *next;
        null();
};
//节点类模板构造函数，用于置空指针
template <typename ElemType>
LNode<ElemType>::null(){
    this.next=NULL;
};


//链表表头类模板
template <typename ElemType>
class LinkList{
    public:
        int len;
        LNode<ElemType> *head,*tail;
        LinkList();
        // ~ReleaseList (void) {cout<<"nmsl";}
        ~LinkList();
        template <typename Status>
        Status ClearList(LinkList<ElemType> &L);
        template <typename Status>
        Status DestoryList(LinkList<ElemType> *&L);
        template <typename Status>
        Status InsFirst(LinkList<ElemType> *h,LNode<ElemType> *s);
        // int mdzz(){cout<<"nmsl";};
};
//链表表头类模板的构造函数，用于初始化长度和置空指针
template <typename ElemType>
LinkList<ElemType>::LinkList(){
    this->len=0;
    this->head=NULL;
    this->tail=this->head;
};
//链表表头类模板的析构函数，用于在删除表头时检查指向节点空间是否释放
template <typename ElemType>
LinkList<ElemType>::~LinkList(){
    if(this->head!=NULL){
        LNode<ElemType> *tmp=NULL;
        while(this->tail!=this->head){
            tmp=this->head;
            this->head=this->head->next;
            delete tmp;
            tmp=NULL;
        }
        delete this->head;
        this->tail=this->head=NULL;
        this->len=0;
    }
    
};
//删除链表表头
template <typename ElemType>
template <typename Status>
Status LinkList<ElemType>::DestoryList(LinkList<ElemType> *&L){
    delete L;
    L=NULL;
}
//清楚链表
template <typename ElemType>
template <typename Status>
Status LinkList<ElemType>::ClearList(LinkList<ElemType> &L){
    LNode<ElemType> *tmp=NULL;
    while(L.tail!=L.head){
        tmp=L.head;
        L.head=L.head->next;
        delete tmp;
        tmp=NULL;
    }
    delete L.head;
    L.tail=L.head=NULL;
    L.len=0;
}
//表头插入
template <typename ElemType>
template <typename Status>
Status LinkList<ElemType>::InsFirst(LinkList<ElemType> *h,LNode<ElemType> *s){
    if(h->head!=NULL){
        LNode<ElemType> *node=h->head;
        h->head=s;
        s->next=node;
    }
    else{
        h->head=s;
        h->tail=s;
    }
}


template <typename Status,typename ElemType>
Status Append(LinkList<ElemType> L,LNode<ElemType> s){
    
}
template <typename Status,typename ElemType>
Status PrintList(LinkList<ElemType> List);

int main(){
    int i=666;
    LinkList<int> *List=new LinkList<int> ;
    // List->mdzz();
    LNode<int> *node=new LNode<int>;
    node->data=23;
    // cout<<InitList<int>(List)<<endl;
    List->InsFirst<void>(List,node);
    List->InsFirst<void>(List,node);
    List->ClearList<void>(*List);
    List->DestoryList<void>(List);
    cin>>i;
    return 0;
}

template <typename Status,typename ElemType>
Status PrintList(LinkList<ElemType> List){
    for (LNode<ElemType> *i = List.head; i !=NULL; i=i->next)
    {
        cout<<i->data;
    }
}