#include<stdio.h>
#include<stdlib.h>

#define OK 1;
#define ERROR 0;
/*
9.4 ��Ϊ���ָ���ԭ���Ұ�д�˺ܶ�sizeof(ElemType),���������ܺܳ������Կ��Խ�����sizeof(ElemType)�滻��Size
#define Size sizeof(ElemType)
*/


//��Ϊ�����ǳ������ݽṹ��δ�Ժ������������������������壬��ʹ��typeof�ض���
typedef int Status;
typedef int ElemType;

typedef struct ListInSequence 
{
    ElemType *elem;
    int length;
    int ListSize;
}SList;

//��ʼ��˳�����Ա�
Status InitSList(SList* L){
    //�����ϲ�ͬ��Ҫ�����������
    int number;
    printf("input List size=");
    scanf("%d",&number);

    L->elem=(ElemType*)malloc(number*sizeof(ElemType));
    //�ж��Ƿ������ڴ�
    if (!L->elem)
    {
        return ERROR;
    }
    L->length=0;
    L->ListSize=number;
    printf("List has been initialized\n");
    return OK;
}
//���˳�����Ա�
Status ClearSList(SList* L){
   ElemType* p;
   for(p= L->elem;(p-L->elem)<(L->length*sizeof(ElemType));p+=sizeof(ElemType)){
       *p=0;
   }
   printf("List has been cleared\n");
   return OK;
}
//ɾ�����Ա��ͷſռ䣩
//������9.5 free�������ҽ�����ˣ�Ŀǰ�²���������й�
Status DestoryList(SList*L){
    ElemType *p=L->elem;
    free(p);
    L->elem=NULL;
    return OK;
}
//������Ա�շ�
Status ListEmpty(SList* L){
    if (L->elem)
    {
        printf("List isn't empty\n");
        return ERROR;
    }
    else
    {
        printf("List is empty\n");
        return OK;
    }
}
//�������Ա�����Ԫ�ظ���
Status ListLength(SList*L){
    printf("List length=%d\n",L->length);
    return L->length;
}
//���ص�i��Ԫ�ص�ֵ
/*��Ϊ����ʹ�õ������ã���������c++�����ԣ�����ֻ��ʹ��ָ��ʵ��*/
Status GetElem(SList*L,int i,ElemType*p){
    if(i==0){
        printf("input the i=");
        scanf("%d",&i);
    }
    else if(i>L->length||i<0){
        printf("Out of index\n");
        return ERROR;
    }
    else
    {
        *p=*((i-1)*sizeof(ElemType)+L->elem);
        printf("The position value is:%d\n",*p);
        return OK;   
    }
}
//��������������ĳ�ֹ�ϵ��Ԫ��
/*�о���js�ĸ߽׺���sort��compare���������,���д�˸��Ƚϴ�С��demo*/
//9.4 ���ݺ����½ڵ���˼��˵������ҵ���Ӧֵ��λ�õ���˼������Ӧ�������
Status Compare(ElemType a,ElemType b){
    return a==b?1:0;
}
Status LocateElem(SList*L,ElemType e,Status(*compare)(ElemType,ElemType))
{
    if(e==0){
        printf("input the value you want to locate=");
        scanf("%d",&e);
    }
    ElemType*p;
    for(p=L->elem ; !(*compare)(*p,e)&&p<=L->elem+L->length*sizeof(ElemType) ; p+=sizeof(ElemType)){}

    if (p>L->elem+L->length*sizeof(ElemType))
    {
        printf("The value can't be found in SList\n");
        return ERROR;
    }
    else
    {
        printf("the number position is:%d\n",*p);
        return (p-L->elem)/sizeof(ElemType)+1;  //9.4 ����λ��
        // return p;  ���ص�ַ
    }
    //return p2=L->elem+L->length*sizeof(ElemType)?ERROR:OK;
}
//�����ã����ȫ������
Status PrintList(SList*L){
    ElemType *p,a;
    for ( p= L->elem;(p-L->elem)<(L->ListSize*sizeof(ElemType));p+=sizeof(ElemType))
    {
        printf("��%d��=%d\n",(p-L->elem)/sizeof(ElemType)+1,*p);
    }
    return OK;
}
//�����ã������������
Status InitData(SList*L){
    ElemType*p;
    printf("Please input data with whitespace\n");
    for (p=L->elem;p-L->elem< L->ListSize*sizeof(ElemType);p+=sizeof(ElemType))    //��ȡ��10086ֹͣ
    {
        scanf("%d",p);
        if(*p==10086){
            *p=0;
            break;
        }
        L->length++;
    }
    printf("Data have been initialized\n");
    return OK;
}
Status PriorElem(SList* L,ElemType cur_e,ElemType*pre_e){
    Status (*compare)(ElemType,ElemType)=Compare;
    int position=LocateElem(L,cur_e,compare);
    if(position>1){
        *pre_e=*(L->elem+(position-1)*sizeof(ElemType));
        printf("already retrun pre_e\n");
        return OK;
    }
    else if(position==1){
        printf("There is no previous element\n");
    }
    else
    {
        printf("Can't find elem in List\n");
        return ERROR;
    }
}
Status NextElem(SList* L,ElemType cur_e,ElemType* next_e){
    Status (*compare)(ElemType,ElemType)=Compare;
    int position=LocateElem(L,cur_e,compare);
    if(position>0&&position<L->length-1){
        *next_e=*(L->elem+(position-1)*sizeof(ElemType));
        printf("already retrun pre_e\n");
        return OK;
    }
    else if(position==L->length){
        printf("There is no next element\n");
    }
    else
    {
        printf("Can't find elem in List\n");
        return ERROR;
    }
}
Status ListInsert_Sq(SList* L,int i,ElemType e){
    ElemType *p=NULL,*tmp=NULL;
    if (e==0)
    {
        printf("The element you want to insert:");
        scanf("%d",&e);
    }
    if (i==0)
    {
        printf("The position you want to insert:");
        scanf("%d",&i);
    }
    
    p=i>L->length||i<0 ? NULL : i*sizeof(ElemType)+L->elem;
    if(p&&L->ListSize-L->length){
        for(p=L->length*sizeof(ElemType)+L->elem;p>=(i-1)*sizeof(ElemType)+L->elem;p-=sizeof(ElemType)){
            *(p+sizeof(ElemType))=*p;
        }
        *(p+sizeof(ElemType))=e;
        printf("Insert successed");
        return OK;
    }
    else if(p!=NULL)
    {
        tmp=(ElemType*)realloc(L->elem,(L->ListSize+1)*sizeof(ElemType));
        if (!tmp)
        {
            printf("There aren't enough memory\n");
            return ERROR;
        }
        L->elem=tmp;
        *(L->elem+L->length*sizeof(ElemType))=0;
        L->ListSize++;
        L->length++;

        for(p=L->length*sizeof(ElemType)+L->elem;p>=(i-1)*sizeof(ElemType)+L->elem;p-=sizeof(ElemType)){
            *(p+sizeof(ElemType))=*p;
        }
        *(p+sizeof(ElemType))=e;
        printf("Insert successed");
        return OK;
    }
    else
    {
        printf("i is illegal\n");
        return ERROR;
    }
    
    
}
Status ListDelete_Sq(SList* L,int i,ElemType* e){
    ElemType*p;
    if (i==0)
    {
        printf("The position you want to delete:");
        scanf("%d",&i);
    }

    if (i<1||i>L->length)
    {
        printf("i is illegal\n");
        return ERROR;
    }
    p=&L->elem[i-1];
    *e=*p;
    for(;p<L->length*sizeof(ElemType)+L->elem;p+=sizeof(ElemType))
    {
        *p=*(p+sizeof(ElemType));
    }
    printf("Node i has been deleted\n");
    return OK;
    
}