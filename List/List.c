#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0

typedef int Status;
typedef int ElemType;

#define ElemTypeSize sizeof(ElemType)
#define StatusSize sizeof(Status)

typedef struct List
{
    ElemType data;
    struct List *next;

}List;

Status InitList(List &L){
    List *next=NULL,*cur=NULL;
    int num,i;
    scanf("%d",&num);
    if (i>1)
    {
        cur=&L;
        for ( i = 0; i < num; i++)
        {
            next=new List;
            cur->next=next;
            cur=next;
        }
        cur->next=NULL;
    }
    else if(i==1)
    {
        next=new List;
        L.next=next;
        L.next->next=NULL;
    }
    else if(i==0)
    {
        L.next=NULL;
    }
    else
    {
        printf("invalid number");
    }
    return L.next?TRUE:FALSE;
}
Status EmptyList(List &L){
    if (L.next!=NULL)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}
Status DestoryList(List &L){
    if (EmptyList(L))
    {
        return TRUE;
    }
    else
    {
        List *cur= L.next,*nextNode=cur->next;
        while (nextNode!=NULL)
        {
            delete cur;
            cur=nextNode;
            nextNode=cur->next;
        }
        return TRUE;
    }
}

int main(){
    List L;
    // printf("%d",InitList(L));
    // printf("%d",StatusSize);
    InitList(L);
    DestoryList(L);
    if (EmptyList(L))
    {
        printf("OK");
    }
    
    int z;
    scanf("%d",&z);
    return 0;
}

