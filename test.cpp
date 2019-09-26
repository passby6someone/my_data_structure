/*
    9.xx
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
/*
    返回值怎么写？
    我初步想法是，再写个模板成员函数OK（）和ERROR()，需要的时候初始化返回
    btw
    错误判断try catch还没写
*/

#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<stdexcept>
#include<exception>

using namespace std;

const int OK=1;
const int ERROR=0;

//节点类模板
template <typename ElemType>
class LNode {
    public:
        ElemType data;
        LNode *next;
        LNode();
};
//节点类模板构造函数，用于置空指针
template <typename ElemType>
LNode<ElemType>::LNode(){
    this->next=NULL;
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
        Status ClearList();
        template <typename Status>
        Status DestoryList();
        template <typename Status>
        Status InsFirst(LNode<ElemType> *s);
        template <typename Status>
        Status Append(LNode<ElemType> *s);
        template <typename Status>
        Status PrintList();
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
Status LinkList<ElemType>::DestoryList(){
    delete this;
    //delete成功判断？？？
    return OK;
}
//清楚链表
template <typename ElemType>
template <typename Status>
Status LinkList<ElemType>::ClearList(){
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
    return OK;
}
//表头插入
template <typename ElemType>
template <typename Status>
Status LinkList<ElemType>::InsFirst(LNode<ElemType> *s){
    if(this->head!=NULL){
        LNode<ElemType> *node=this->head;
        this->head=s;
        s->next=node;
    }
    else{
        this->head=s;
        this->tail=s;
    }
    return OK;
}
//tail insert node
template <typename ElemType>
template <typename Status>
Status LinkList<ElemType>::Append(LNode<ElemType> *s){
    if(this->tail!=NULL){
        this->tail->next=s;
        this->tail=s;
        return OK;
    }
    else{
        this->tail=s;
        this->head=this->tail;
        return OK;
    }
}
//print for test
template <typename ElemType>
template <typename Status>
Status LinkList<ElemType>::PrintList(){
    if(this->head!=NULL){
        LNode<ElemType> *tmp=new LNode<ElemType>;
        tmp=this->head;
        while (tmp!=NULL)
        {
            cout<<tmp->data<<endl;
            tmp=tmp->next;
        }
        return OK;
    }
    else{
        cout<<"Nothing in LIST"<<endl;
        return OK;
    }
};

int main(){
    int i=666;
    LinkList<int> *List=new LinkList<int> ;
    // List->mdzz();
    LNode<int> *node1=new LNode<int>;
    LNode<int> *node2=new LNode<int>;
    node2->data=node1->data=23;
    // cout<<InitList<int>(List)<<endl;
    // List->InsFirst<int>(node);
    List->InsFirst<int>(node1);
    List->Append<int>(node2);
    List->PrintList<int>();
    List->ClearList<int>();
    List->DestoryList<int>();
    cin>>i;
    return 0;
}

