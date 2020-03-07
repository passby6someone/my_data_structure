#include<stdio.h>
#include<stdlib.h>

#define OK 1;
#define ERROR 0;
/*
9.4 因为各种各样原因，我把写了很多sizeof(ElemType),看起来可能很抽象，所以可以将所有sizeof(ElemType)替换成Size
#define Size sizeof(ElemType)
*/


//因为书上是抽象数据结构，未对函数类型与数据类型作出定义，故使用typeof重定义
typedef int Status;
typedef int ElemType;

typedef struct ListInSequence 
{
    ElemType *elem;
    int length;
    int ListSize;
}SList;

//初始化顺序线性表
Status InitSList(SList* L){
    //跟书上不同，要多少请求多少
    int number;
    printf("input List size=");
    scanf("%d",&number);

    L->elem=(ElemType*)malloc(number*sizeof(ElemType));
    //判断是否请求到内存
    if (!L->elem)
    {
        return ERROR;
    }
    L->length=0;
    L->ListSize=number;
    printf("List has been initialized\n");
    return OK;
}
//清除顺序线性表
Status ClearSList(SList* L){
   ElemType* p;
   for(p= L->elem;(p-L->elem)<(L->length*sizeof(ElemType));p+=sizeof(ElemType)){
       *p=0;
   }
   printf("List has been cleared\n");
   return OK;
}
//删除线性表（释放空间）
//！！！9.5 free有问题我解决不了，目前猜测跟编译器有关
Status DestoryList(SList*L){
    ElemType *p=L->elem;
    free(p);
    L->elem=NULL;
    return OK;
}
//检测线性表空否
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
//返回线性表数据元素个数
Status ListLength(SList*L){
    printf("List length=%d\n",L->length);
    return L->length;
}
//返回第i个元素的值
/*因为书上使用到了引用，但是这是c++的特性，所以只能使用指针实现*/
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
//与输入数据满足某种关系的元素
/*感觉跟js的高阶函数sort（compare（））差不多,随便写了个比较大小的demo*/
//9.4 根据后面章节的意思来说这个是找到相应值的位置的意思，所以应该是相等
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
        return (p-L->elem)/sizeof(ElemType)+1;  //9.4 返回位置
        // return p;  返回地址
    }
    //return p2=L->elem+L->length*sizeof(ElemType)?ERROR:OK;
}
//测试用：输出全部数据
Status PrintList(SList*L){
    ElemType *p,a;
    for ( p= L->elem;(p-L->elem)<(L->ListSize*sizeof(ElemType));p+=sizeof(ElemType))
    {
        printf("第%d个=%d\n",(p-L->elem)/sizeof(ElemType)+1,*p);
    }
    return OK;
}
//测试用：充填测试数据
Status InitData(SList*L){
    ElemType*p;
    printf("Please input data with whitespace\n");
    for (p=L->elem;p-L->elem< L->ListSize*sizeof(ElemType);p+=sizeof(ElemType))    //读取到10086停止
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