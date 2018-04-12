#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int inarray(int *a,int n,int no){
	int i,j;
	for(i=0;i<n;i++){
		//printf("%d,%d,%d\n",a[i],no,a[i]==no);
		if(a[i]==no)
			return 1;
	}
	return 0;
}

void sort1(float **a,int k,int dim){
	int i,j;
	float tmp;
	//printf("k is %d,dim is %d\n",k,dim);
	for(i=0;i<k;i++){
		for(j=0;j<k-i-1;j++){
			if(a[j][0]>a[j+1][0]){
				for(i=0;i<dim;i++){
					tmp=a[j][i];
					a[j][i]=a[j+1][i];
					a[j+1][i]=tmp;
				}
			}else{
				//printf("No exhange\n");
			}
		}
	}
}


int main(){
	int i,j;
	int k,dim,n;
	//In k means k is the number of means
	// d is the dimension of the data.
	//p is the centers of the data.
	//n is the number of points in the dataset

	int mindist,tmpdist;
	int *count;
	int tcount;

	//int **a,int *b,float **old,float **new,int k,int dim,int n
	float **old,**new;
	float **a;
	float dist;
	//int a[4][2]={{0,0},{5,0},{0,10},{5,10}};
	k=2;
	dim=2;
	n=9;

	//srand(time(0));

	int tmp,done;
	int *b;
	b = (int*)malloc(n*sizeof(int));


	a = (float**)malloc(n*sizeof(float*));
	for(i=0;i<n;i++)
		a[i]=(float*)malloc(dim*sizeof(float));

	old = (float**)malloc(k*sizeof(float*));
	new = (float**)malloc(k*sizeof(float*));

	for(i=0;i<k;i++){
		old[i] = (float*)malloc(dim*sizeof(float));
		new[i] = (float*)malloc(dim*sizeof(float));
	}



	FILE *fp;
	fp = fopen("./data.txt", "r");
	for(i=0;i<n;i++){
		fscanf(fp, "%f,%f\n",&a[i][0],&a[i][1]);
	}
	fclose(fp);


	for(i=0;i<k;i++)
		b[i]=-1;
	for(i=0;i<k;i++){
		done =0;
		while(!done){
			tmp = rand()%n;
			//printf("%d is generated and testing result is %d\n",tmp,inarray(c,i,tmp));
			if(!inarray(b,i,tmp)){
				//printf("%d adding to %d\n",tmp,i);
				b[i]=tmp;
				done=1;
				for(j=0;j<dim;j++)
					old[i][j]=a[i][j];
			}
		}
	}


	printf("old centers are :\n");
	for(i=0;i<dim;i++){
		for(j=0;j<dim;j++){
			printf("%f,",old[i][j]);
		}
		printf("\n");
	}
	sort1(old,k,dim);
	int l=1;

	count = (int *)malloc(k*sizeof(int));

	done=0;
	l=0;
	int same=0;
	while(!done){
		printf("Entered kmeans loop \n");
		printf("%f\n",a[0][0]);
		

		for(i=0;i<k;i++){
			for(j=0;j<dim;j++){
				new[i][j]=0;
			}
			count[i]=0;
			printf("%d:%d\n",i,count[i]);
			b[i]=0;
		}

		for(i=0;i<n;i++){
			mindist =99999;
			for(j=0;j<k;j++){
				dist =0;
				for(l=0;l<dim;l++){
					tmp = a[i][l]-old[j][l];
					dist +=tmp*tmp;
				}
				if(dist<mindist){
					mindist = tmp;
					b[i] = j;
				}
			}
			
			/*
			count[b[i]]++;
			*/
			for(l=0;l<dim;l++)
				//new[b[i]][l]+=a[i][l];
			printf("%d is to %d\n",i,b[i]);
		}
		if(l==3){
			done=1;
		}else{
			done =0;
		}
	}
	free(count);

	printf("new centers are :\n");
	for(i=0;i<dim;i++){
		for(j=0;j<dim;j++){
			printf("%f,",new[i][j]);
		}
		printf("\n");
	}

	

}