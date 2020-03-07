#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 12500
#define ElemType int
#define status int
#define OK 1
#define ERROR 0
#define True 1
#define False 0

typedef struct {
	int i,j;
	ElemType e;
}Triple;

typedef struct {
	Triple data[MAXSIZE+1];
	int mu,nu,tu;
}TripleMatrix;

status outOfBounds(int index,int max,int min){
	if(index > max || index < min)
		return True;
	else
		return False;
	//return index > MAXSIZE && index <= 0?True:False;
}

status CreateTripleMatrix(TripleMatrix *M){
	int i = 0,j = 0,e,num = 0,mu,nu;
	M->tu = 0;
	printf("pls input m n:");
	scanf("%d %d",&mu,&nu);
	if(mu > 0 && nu > 0){
		M->mu = mu;
		M->nu = nu;
	}
	else
		exit(ERROR);
	while(!outOfBounds(M->tu,MAXSIZE,0)){
		printf("pls input i j e:");
		scanf("%d %d %d",&i,&j,&e);
		if( !outOfBounds(i,M->mu-1,0) && !outOfBounds(j,M->nu-1,0) ){
			M->data[num].i = i;
			M->data[num].j = j;
			M->data[num].e = e;
			num++;
			M->tu++;
		}
		else{
			break;
		}
	}
	return OK;
}

status DestoryTripleMatrix(TripleMatrix *M){
	if(!M)  free(M);
	return OK;
}

status PrintTripleMaxtrix(TripleMatrix *M){
	int i,j,k,isPrinted = False;
	for(i = 0;i < M->mu;i++){
		for(j = 0;j < M->nu;j++){
			for(k = 0;k < M->tu;k++){
				if(M->data[k].i == i && M->data[k].j == j){
					printf("%d  ",M->data[k].e);
					isPrinted = True;
				}
			}
			if(!isPrinted)
				printf("0  ");
			isPrinted = False;
		}
		printf("\n");
	}
	return OK;
}			

status CopyTripleMatrix(TripleMatrix *M,TripleMatrix *T){
	int i;
	if(!M)
		return ERROR;
	T->tu = M->tu;
	T->mu = M->mu;
	T->nu = M->nu;
	for(i = 0;i < M->tu;i++){
		T->data[i].i = M->data[i].i;
		T->data[i].j = M->data[i].j;
		T->data[i].e = M->data[i].e;
	}
	return OK;
}

status AddTripleMatrix(TripleMatrix *M,TripleMatrix *T,TripleMatrix *Q){
	int i,j,k;
	if( !(M->mu == T->mu && M->nu == T->nu) )
		return ERROR
	CopyTripleMatrix(M,Q);
	for(i = 0;i < T->tu;i++){
		for(j = 0;j < Q->tu;j++){
			if(Q->data[j].i == T->data[i].i && Q->data[j].j == T->data[i].j){
				if(Q->data[j].e + T->data[i].e != 0)
					Q->data[j].e += T->data[i].e;
				else{
					for(k = j;k < Q->tu;k++){
						Q->data[k] = Q->data[j+1];
					}
					Q->tu--;
				}
			}
		}
		T->data[i].i
	}
	return OK;
}

/*
for(i = 0;i < M->tu;i++){
	printf("i = %d,j = %d,e = %d\n",M->data[i].i,M->data[i].j,M->data[i].e);
}
*/