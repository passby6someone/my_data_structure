/*
    这有件非常amazing的事情
    怎么样删除变量？？？
    没法啊，那我怎么删除栈，如果只是置空跟清除栈有什么区别？？？
    所以默认是，置空（NULL）默认是删除，指向空的可用空间为清除
    ````
    emmm stack可以realloc也可以不realloc，所以我写了个stackfull
*/

#include<iostream>
#include<stdio.h>
#include<cstdlib>
#include<exception>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
#define OK true
#define ERROR false

template<typename SElemType>
struct Sqstack
{
    SElemType *base;
    SElemType *top;
    int stacksize;
};
// template<typename SElemType>
// using Sqstack<int>=Sqstacka;

template<typename Status,typename SElemType>
Status InitStack(Sqstack<SElemType> &s){
    s.base=(SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    s.top=s.base;
    s.stacksize=STACK_INIT_SIZE;
}
template<typename Status,typename SElemType>
Status DestoryStack(Sqstack<SElemType> &s){
    s.top=NULL;
    free(s.base);
    s.base=NULL;
    s.stacksize=0;
}
template<typename Status,typename SElemType>
Status ClearStack(Sqstack<SElemType> &s){
    DestoryStack<Status,SElemType>(s);
    InitStack<Status,SElemType>(s);
}
template<typename Status,typename SElemType>
Status StackEmpty(Sqstack<SElemType> &s){
    return s.top==s.base?true:false;
}
// template<typename Status,typename SElemType>
// Status StackFull(Sqstack<SElemType> s){
//     return (s.top-s.base)/sizeof(SElemType)==STACK_INIT_SIZE?true:false;
// }
template<typename SElemType>
int StackLength(Sqstack<SElemType> s){
    SElemType *tmp=s.base;
    int len=0;
    while (tmp!=s.top)
    {
        len++;
        tmp=&(s.base[len]);
    }
    return len;
}
template<typename Status,typename SElemType>
Status GetTop(Sqstack<SElemType> s,SElemType &e){
    e=*(s.base[((s.top-s.base)/sizeof(SElemType))-1]);
}
template<typename Status,typename SElemType>
Status Push(Sqstack<SElemType> &s,SElemType e){
    if(StackFull<SElemType>(s)){
        s.base=(SElemType*)realloc(s.base,(s.stacksize+STACKINCREMENT)*sizeof(SElemType));
    }
    *s.top=e;
    s.top+=sizeof(SElemType);
    return OK;
}
template<typename Status,typename SElemType>
Status Pop(Sqstack<SElemType> &s,SElemType &e){
    if(StackEmpty<SElemType>(s)){
        return ERROR;
    }
    s.top=s.top-sizeof(SElemType);
    e=*s.top;
    return OK;
}

int main(){
    Sqstack<char> a[2];
    int e,i=0;
    char tmp,spc='a';
    bool baifen=false;
    InitStack<void,char>(a[0]);
    InitStack<void,char>(a[1]);
    while (std::cin>>tmp)
    {
        switch (tmp)
        {
            case '/':
                spc=tmp;
                i++;
                break;
            case '.':
                spc=tmp;
                i++;
                break;
            case '%':
                baifen=true;
                break;
            default:
                Push<bool,char>(a[i],tmp);
                break;
        }
    }
    i=0;
    tmp='0';
    int zero=0,num[2],k=0;
    num[0]=StackLength<char>(a[0]);
    num[1]=StackLength<char>(a[1]);
    while (i<=1)
    {
        if(!StackEmpty<bool,char>(a[i])){
            Pop<bool,char>(a[i],tmp);
            if(tmp=='0'){
                zero++;
                if(k!=0&&!StackEmpty<bool,char>(a[i]))
                    std::cout<<tmp;
            }
            else{
                k++;
                std::cout<<tmp;
            }
        }
        else{
            if(zero==num[i]&&num[i]!=0){
                std::cout<<'0';
            }
            i++;
            k=0;
            zero=0;
            if(spc!='a'){
                std::cout<<spc;
                spc='a';
            }
        }
    }
    if(baifen){
        std::cout<<'%'<<std::endl;
    }
    else{
        std::cout<<std::endl;
    }
    scanf("%d",&i);
    return 0;
}