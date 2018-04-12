#include<stdio.h>
#include<stdlib.h>

int inarray(int *a,int n,int no){
	int i,j;
	for(i=0;i<n;i++){
		if(a[i]==no)
			return 1;
	}
	return 0;
}


int main(){
	int a[]={2,4,6,8,10,12,14,16,18,20};
	int i;
	for(i=0;i<20;i++){
		if(inarray(a,20,i+1)){
			printf("%d is in array\n",i);
		}else{
			printf("%d is not in array\n",i);
		}
	}

}