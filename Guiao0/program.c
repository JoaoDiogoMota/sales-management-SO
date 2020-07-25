#include<stdio.h>
#include<stdlib.h>
#include"operators.h"


int main(){
	int *vetor = malloc(sizeof(int)*4);
	fill(vetor,1000,5);
	for(int i=0;i<100;i++) printf("%d\n",vetor[i]);

	int x =find(vetor+100,100,5);
	printf("%d\n",x);
	free(vetor);
	return 0;
}



