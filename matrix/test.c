#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define ElemType int
#define MAX_ARRAY_DIM 8
#define Status int
#define OK 1
#define ERROR 0
#define overflow 0

typedef struct array{
	int *base;  //数组元素基址
	int dim;		 //数组维数
	int *bounds;     //数组维界基址
	int *constants;  //数组映象函数常量基址
	long int elemtotal;
}Array;

Status InitArray(Array *A,int dim, ...)
{
	int i;
	int elemtotal = 1;
	va_list ap;

	if( dim < 1 || dim > MAX_ARRAY_DIM )
		return ERROR;
	A->dim = dim;
	A->bounds = (int *)malloc(dim * sizeof(int));
	if(!A->bounds)
		exit(overflow);

	va_start(ap,dim);
	for(i = 0;i < dim;++i){
		A->bounds[i] = va_arg(ap,int);
		if(A->bounds[i] < 0)  return ERROR;
		elemtotal *= A->bounds[i];
	}
	A->elemtotal = elemtotal;
	va_end(ap);

	A->base = (ElemType *)malloc(elemtotal * sizeof(ElemType));
	if(!A->base) exit(overflow);
	A->constants = (int *)malloc(dim * sizeof(int));
	if(!A->constants) exit(overflow);
	//元素大小是指元素的内存大小
	A->constants[dim - 1] = sizeof(int);
	for(i = dim - 2;i >= 0;i--)
		A->constants[i] = A->bounds[i+1] * A->constants[i+1];
	return OK;
}

Status DestoryArray(Array *A){
	if(!A->base || !A->bounds || !A->constants)
		return ERROR;
	free(A->base);
	A->base = NULL;
	free(A->bounds);
	A->bounds = NULL;
	free(A->constants);
	A->constants = NULL;
	return OK;
}

Status Locate(Array A,va_list ap,int *offset){
	int i,index;
	*offset = 0;
	for(i = 0;i < A.dim;i++){
		index = va_arg(ap,int);
		if(index < 0 || index >= A.bounds[i])
			return overflow;
		*offset += A.constants[i] * index;
	}
	return OK;
}

Status Value(Array A,ElemType *e,...){
	 int offset;
	 va_list ap;
	 va_start(ap,e);
	 if(!Locate(A,ap,&offset))
		 return ERROR;
	 *e = *(A.base + offset);
	 va_end(ap);
	 return OK;
}

Status Assign(Array *A,ElemType e, ...){
	va_list ap;
	int offset=0,i,num;
	va_start(ap,e);
	if(!Locate(*A,ap,&offset))
		return ERROR;
	*(A->base + offset) = e;
	va_end(ap);
	return OK;
}

Status PrintArray(Array A){
	int i;
	for(i = 0;i < A.elemtotal;i++)
		printf("%d ", *( A.base + i*sizeof(ElemType) ) );
	printf("\n\n");
	return OK;
}

int main()
{
   Array array,*A;
   A = &array;
   InitArray(A,4,3,3,3,3);
   PrintArray(array);
   Assign(A,100,2,2,2,2);
   PrintArray(array);
   DestoryArray(A);
   return 0;
}

