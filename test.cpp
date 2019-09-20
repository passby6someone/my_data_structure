// #include"ListInSequence.h"
#include<stdlib.h>
#include<stdio.h>
#include<iostream>

using namespace std;

template <typename ElemType>
class LNode {
    public:
        ElemType data;
        LNode *next;
        null();
};
template <typename ElemType>
LNode<ElemType>::null(){
    this.next=NULL;
};

template <typename ElemType>
class LinkList{
    public:
        int len;
        LNode<ElemType> *head,*tail;
        //just a demo
        // template <typename Status>
        // Status mdzz(ElemType);
        InitList();
        template <typename Status>
        Status ClearList(LinkList<ElemType> &L);
};
template <typename ElemType>
LinkList<ElemType>::InitList(){
    this.len=0;
    this.head=NULL;
    this.tail=this.head;
};

template <typename Status,typename ElemType>
Status DestoryList(LinkList<ElemType> *&L){
    delete L;
}


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
}




template <typename Status,typename ElemType>
Status InsFirst(LinkList<ElemType> *h,LNode<ElemType> *s){
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
    InsFirst<void,int>(List,node);
    InsFirst<void,int>(List,node);
    List->ClearList<void>(*List);
    DestoryList<void,int>(List);
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