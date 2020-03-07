#include "ThreeTuple.h"
#include <stdlib.h>

int main(){
	TripleMatrix *M = (TripleMatrix*)malloc(sizeof(TripleMatrix)),*T = (TripleMatrix*)malloc(sizeof(TripleMatrix));
	CreateTripleMatrix(M);
	PrintTripleMaxtrix(M);
	CopyTripleMatrix(M,T);
	printf("\n\n");
	PrintTripleMaxtrix(T);
	DestoryTripleMatrix(M);
	DestoryTripleMatrix(T);
	return 0;
}