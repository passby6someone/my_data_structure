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
/*
    有些函数未涉及引用，但是我按书上加了引用没改
    现在觉得改起来太麻烦了，算了
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
        Status DelFirst(LNode<ElemType> &q);
        template <typename Status>
        Status Append(LNode<ElemType> *s);
        template <typename Status>
        Status PrintList();
        template <typename Status>
        Status Remove(LNode<ElemType> &p);
        template <typename Status>
        Status InsBefore(LNode<ElemType> *&p,LNode<ElemType> s);
        template <typename Status>
        Status InsAfter(LNode<ElemType> *&p,LNode<ElemType> s);
        template <typename Status>
        Status SetCurElem(LNode<ElemType> *&p,ElemType e);
        ElemType GetCurElem(LNode<ElemType> *p);
        template <typename Status>
        Status ListEmpty();
        int ListLength();
        template <typename Position>
        Position PriorPos(LNode<ElemType> p);
        template <typename Position>
        Position NextPos(LNode<ElemType> p);
        template <typename Status>
        Status LocatePos(int i,LNode<ElemType> *&q);
        template <typename Status,typename FunType>
        Status LocateElem(ElemType e,FunType (*compare)(ElemType x,ElemType y));
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
        while(this->head!=NULL){
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
        this->len++;
        return OK;
    }
    //delete first node
    template <typename ElemType>
    template <typename Status>
    Status LinkList<ElemType>::DelFirst(LNode<ElemType> &q){
        if(this->head!=NULL){
            LNode<ElemType> *tmp=new LNode<ElemType>;
            tmp=this->head;
            q=*tmp;
            this->head=this->head->next;
            delete tmp;
            tmp=NULL;
            this->len--;
            return OK;
        }
        else{
            cout<<"Nothing in List"<<endl;
            return ERROR;
        }
    };
    //tail insert node
    template <typename ElemType>
    template <typename Status>
    Status LinkList<ElemType>::Append(LNode<ElemType> *s){
        if(this->tail!=NULL){
            this->tail->next=s;
            this->tail=s;
        }
        else{
            this->tail=s;
            this->head=this->tail;
        }
        this->len++;
        return OK;
    }
    //remove(change) tail node to p node
    template <typename ElemType>
    template <typename Status>
    Status LinkList<ElemType>::Remove(LNode<ElemType> &p){
        if(this->tail!=NULL){
            LNode<ElemType> *tmp=new LNode<ElemType>;
            tmp=this->tail;
            *(this->tail)=p;
            delete tmp;
            tmp=NULL;
            this->len--;
            return OK;
        }
        else{
            cout<<"Nothing in List"<<endl;
            return ERROR;
        }
    }
    //在p指向的node前插入node
    template <typename ElemType>
    template <typename Status>
    Status LinkList<ElemType>::InsBefore(LNode<ElemType> *&p,LNode<ElemType> s){
        LNode<ElemType> *tmp = new LNode<ElemType>;
        for(LNode<ElemType> *tmp = head;tmp->next != p;tmp = tmp->next)
        s->next = p;
        tmp->next = s;
        this->len++;
        return OK;
    }
    //在p指向的node后插入node
    template <typename ElemType>
    template <typename Status>
    Status LinkList<ElemType>::InsAfter(LNode<ElemType> *&p,LNode<ElemType> s){
        LNode<ElemType> *tmp;
        tmp=p->next;
        p->next=&s;
        s.next=tmp;
        this->len++;
        return OK;
    }
    //修改p指向的node的data
    template <typename ElemType>
    template <typename Status>
    Status LinkList<ElemType>::SetCurElem(LNode<ElemType> *&p,ElemType e){
        p->data=e;
        return OK;
    }
    //返回p指向node的data
    template <typename ElemType>
    ElemType LinkList<ElemType>::GetCurElem(LNode<ElemType> *p){
        return p->data;
    }
    //是否为空
    template <typename ElemType>
    template <typename Status>
    Status LinkList<ElemType>::ListEmpty(){
        return this->head==NULL?ERROR:OK;
    }
    //返回链表长度
    template <typename ElemType>
    int LinkList<ElemType>::ListLength(){
        return this->len;
    }
    //返回前驱
    template <typename ElemType>
    template <typename Position>
    Position LinkList<ElemType>::PriorPos(LNode<ElemType> p){
        if(p==this.head){
            return NULL;
        }
        else if(this->head==NULL){
            return NULL;
        }
        else{
            LNode<ElemType> *tmp;
            tmp=this->head;
            while(tmp!=NULL&&tmp->next!=p){
                tmp=tmp->next;
            }
            return tmp;
        }
    }
    //返回后继
    template <typename ElemType>
    template <typename Position>
    Position LinkList<ElemType>::NextPos(LNode<ElemType> p){
        return p->next!=NULL?p->next:NULL;
    }
    //locate elempos
    template <typename ElemType>
    template <typename Status>
    Status LinkList<ElemType>::LocatePos(int i,LNode<ElemType> *&q){
        if(i==this->len){
            q=this->tail;
            return OK;
        }
        else if(i>0&&i<this->len){
            LNode<ElemType> *tmp= new LNode<ElemType>;
            tmp=this->head;
            for (int j = 1; j < i; j++)
            {
                tmp=tmp->next;
            }
            q=tmp;
            return OK;
        }
        else if(i==1){
            q=this->head;
            return OK;
        }
        else{
            cout<<"Invalid index"<<endl;
            return ERROR;
        }  
    }
    //对满足某关系的node定位
    template <typename ElemType>
    template <typename Status,typename FunType>
    Status LinkList<ElemType>::LocateElem(ElemType e,FunType (*compare)(ElemType x,ElemType y)){
        LNode<ElemType> *tmp=this->head;
        while (tmp!=NULL)
        {
            if((*compare)(tmp->data,e)){
                tmp=tmp->next;
            }
            else{
                return tmp;
            }
        }
        return NULL;
        
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
            return ERROR;
        }
    }

    //visit()，遍历链表对每个node调用
    //TODO；！！！


    //compare函数，用来比较关系
    template <typename Status,typename ElemType>
    Status Compare(ElemType x,ElemType y){
        return x>y?true:false;
    }
    //生成节点函数，测试用
    LNode<int>* NewNodeCreater(){
        static int x=0;
        LNode<int> *node=new LNode<int>;
        node->data=x;
        x++;
        return node;
    }

int main(){
    // int i=666;
    // int (*compare)(int x,int y);
    // compare=Compare<int,int>;
    // LinkList<int> *List=new LinkList<int> ;
    // LNode<int> *q=new LNode<int>;
    // LNode<int> *p=new LNode<int>;
    // LNode<int> *node1=new LNode<int>;
    // node1=NewNodeCreater();
    // for(int i=0;i<5;i++){
    //     List->InsFirst<int>(node1);
    //     node1=NewNodeCreater();
    // }
    // List->DelFirst<int>(*q);
    // q=NULL;
    // List->LocatePos<int>(1,p);
    // List->InsBefore<int>(p,*node1);
    // node1=NewNodeCreater();
    // List->LocatePos<int>(2,p);
    // List->InsAfter<int>(p,*node1);
    // List->Append<int>(node1);
    // List->LocatePos<int>(3,p);
    // List->SetCurElem<int>(p,666);
    // p=List->LocateElem<LNode<int>*,int>(15,compare);
    // List->SetCurElem<int>(p,233);
    // p=NULL;
    // List->PrintList<int>();
    // List->ClearList<int>();
    // List->PrintList<int>();
    // List->DestoryList<int>();
    // cin>>i;
    // return 0;
}

