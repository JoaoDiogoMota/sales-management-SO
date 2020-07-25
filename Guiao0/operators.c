#include<stdio.h>
#include<stdlib.h>
#include"operators.h"

void fill(int *vector, int size, int value){

	for(int i=0;i<size;i++){
		vector[i]=value;
	}
}

int find(int *vector, int size, int value){
	int res=0;

	for(int i=0;i<size;i++)
		if(value==vector[i]) res ++;
	return res;
}