#include".\ListInSequence.h"
#include<stdlib.h>
#include<stdio.h>

// Status Compare(ElemType a,ElemType b);

int main(){
    int Select;
    SList list;
    SList*p=&list;
    ElemType backVar,*back=&backVar;
    Status (*compare)(ElemType a,ElemType b)=Compare;
    // int c=(*compare)(1,2);
    for (;1;)
    {
        printf("0.Status InitSList(SList* L)\n");
        printf("1.Status ClearSList(SList* L)\n");
        printf("2.Status DestoryList(SList*L)\n");
        printf("3.Status ListEmpty(SList* L)\n");
        printf("4.Status ListLength(SList*L)\n");
        printf("5.Status GetElem(SList*L,ElemType*p,int i=0)\n");
        printf("6.Status Compare(ElemType a,ElemType b)\n");
        printf("7.Status LocateElem(SList*L,ElemType e=0,Status(*compare)(ElemType,ElemType)=Compare)\n");
        printf("8.Status PrintList(SList*L)\n");
        printf("9.Status InitData(SList*L)\n");
        printf("10.Status PriorElem(SList* L,ElemType cur_e,ElemType*pre_e)\n");
        printf("11.Status NextElem(SList *L,ElemType cur_e,ElemType* next_e)\n");
        printf("12.ListInsert(SList* L,int i,ElemType e)\n");
        while (scanf("%d",&Select))
        {
            switch (Select)
            {    
                case 0:InitSList(p);break;
                case 1:ClearSList(p);break;
                // case 2:DestoryList(p);break;
                case 3:ListEmpty(p);break;
                case 4:ListLength(p);break;
                case 5:GetElem(p,0,back);break;
                // // case 6:Compare(ElemType a,ElemType b);break;
                case 7:LocateElem(p,0,compare);break;
                case 8:PrintList(p);break;
                case 9:InitData(p);break;
                case 10:PriorElem(p,0,back);break;
                case 11:NextElem(p,0,back);break;
                case 12:ListInsert_Sq(p,0,0);break;
            }
            if (Select==233)
            {
                system("cls");
                break;
            }
            printf("\n");
        }
    }
    
    return 0;
}