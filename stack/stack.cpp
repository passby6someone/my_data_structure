/*
    NULL为删除
    空可用为置空
*/

#include<iostream>
#include<stdio.h>
#include<cstdlib>
#include<exception>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10


template<typename ElemType>
struct StackNode
{
    StackNode *next;
    ElemType data;
};

template<typename ElemType>
struct Stack
{
    StackNode<ElemType> *base;
    StackNode<ElemType> *top;
    int stacksize;
};
//初始化STACK_INIT_SIZE个可用节点，无返回
template<typename Status,typename ElemType>
Status InitStack(Stack<ElemType> &s){
    StackNode<ElemType> *preNode = new StackNode<ElemType>;
    s.base=preNode;
    s.top=s.base;
    StackNode<ElemType> *node;
    for (int i = 0; i < STACK_INIT_SIZE; i++)
    {
        node = new StackNode<ElemType>;
        preNode -> next = node;
        preNode = node;
    }
    preNode -> next = NULL;
    s.stacksize = STACK_INIT_SIZE;
}
//删除栈，返回Boolean；
template<typename Status,typename ElemType>
Status DestoryStack(Stack<ElemType> &s){
    if(s.base == NULL){
        return true;
    }
    else
    {
        StackNode<ElemType> *cur;
        while(s.base != NULL)
        {
            cur = s.base;
            s.base = s.base -> next;
            delete cur;
        }
        s.top = s.base;
        return true;
    }
}
//清除栈 => 将栈顶指针等于栈底指针所指，无返回
template<typename Status,typename ElemType>
Status ClearStack(Stack<ElemType> &s){
    s.top = s.base;
}
//栈空？ => 判断栈顶是否等于栈底，返回boolean；
template<typename Status,typename ElemType>
Status StackEmpty(Stack<ElemType> &s){
    return s.top == s.base ? true : false;
}
//栈长度 => 返回int；
template<typename ElemType>
int StackLength(Stack<ElemType> s){
    int num = 0;
    StackNode<ElemType> *node = s.base;
    while (node != s.top)
    {
        node = node ->next;
        num++;
    }
    return num;
}
//返回栈顶元素值 => 返回boolean
template<typename Status,typename ElemType>
Status GetTop (Stack<ElemType> &s,ElemType &e){
    e = s.top -> data;
    return true;
}
//入栈 => 返回Boolean
template<typename Status,typename ElemType>
Status Push (Stack<ElemType> &s,ElemType e){
    if(s.top != NULL){
        s.top -> data = e;
        s.top = s.top -> next;
        return true;
    }
    else{
        return false;
    }
}
//出栈 => 返回boolea
template<typename Status,typename ElemType>
Status Pop (Stack<ElemType> &s,ElemType &e){
    if(s.top == s.base){
        return false;
    }
    else
    {
        StackNode<ElemType> *node = s.base;
        while (node -> next != s.top)
        {
            node = node -> next;
        }
        e = node -> data;
        s.top = node;
        return true;
    }
}

//测试用，生成节点数据，返回int
template<typename Status>
Status CreatNewNodeData(){
    static int x = 0;
    x++;
    return x;
}
//测试用，输出所有数据
template<typename ElemType>
void PrintStack(Stack<ElemType> s){
    StackNode<ElemType> *node = s.base;
    while (node != s.top)
    {
        std::cout << node -> data << "\n";
        node = node -> next;
    }
    
}

// int main(){
//     Stack<int> s;
//     InitStack<void,int>(s);
//     for (int i = 0; i < 10; i++)
//     {
//         Push<bool,int>(s,CreatNewNodeData<int>());
//     }
//     int e;
//     Pop<bool,int>(s,e);
//     std::cout<<"pop = "<<e<<"\n";
//     Pop<bool,int>(s,e);
//     std::cout<<"pop = "<<e<<"\n";
//     GetTop<bool,int>(s,e);
//     std::cout<<"top = "<<e<<"\n";
//     PrintStack<int>(s);
//     int x;
//     std::cin>>x;
//     return 0;
// }