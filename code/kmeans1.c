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

int addab(float *a,float *b,int dim){
	int i,j;
	for(i=0;i<dim;i++){
		a[i]+=b[i];
	}
}

void exchange(float *a,float *b,int dim){
	int i;
	float tmp;
	//tmp = (float *)malloc(dim*sizeof(float));
	for(i=0;i<dim;i++){
		tmp=a[i];
		a[i]=b[i];
		b[i]=tmp;
	}
}


void sort1(float **a,int k,int dim){
	int i,j;
	float tmp;
	//printf("k is %d,dim is %d\n",k,dim);
	for(i=0;i<k;i++){
		for(j=0;j<k-i-1;j++){
			//printf("reached here with i=%d,k=%d,j=%d\n",i,k-i,j);
			if(a[j][0]>a[j+1][0]){
				//printf("Exchange\n");
				//exchange(a[j],a[j+1],dim);
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

int compareab(float *a,float *b,int dim){
	int i;
	for(i=0;i<dim;i++){
		if(a[i]!=b[i])
			return 0;
	}
	return 1;
}

int dist(float *a,float *b,int dim){
	int i;
	float dist=0,tmp;
	for(i=0;i<dim;i++){
		tmp = a[i]-b[i];
		dist +=tmp*tmp;
	}
	return dist;
}

int updatecenters(float **a,int *b,float **old,float **new,int k,int dim,int n){
	/*
	k is the number of cluster centers
	dim is the dimensions of the data
	n is the number of samples to be taken
	a is the data array
	b is the array which gives the cluster number to which the data points in a belong to
	old,new are the arrays of the cluster centers
	*/
	
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
	//int a[4][2]={{0,0},{5,0},{0,10},{5,10}};
	k=2;
	dim=2;
	n=9;

	srand(time(0));

	int tmp,done;
	int *b;
	b = (int*)malloc(k*sizeof(int));


	a = (float**)malloc(n*sizeof(float*));
	for(i=0;i<n;i++)
		a[i]=(float*)malloc(dim*sizeof(float));

	a[0][0]=0;a[0][1]=0;
	a[1][0]=5;a[1][1]=0;
	a[2][0]=0;a[2][1]=10;
	a[3][0]=5;a[3][1]=10;

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

		dist =0;
		for(i=0;i<n;i++){
			mindist =9999999;
			for(j=0;j<k;j++){
				//tmp = dist(a[i],old[j],dim);
				dist =0;
				for(l=0;l<dim;l++){
					//printf("%f\n",old[j][l]);
					//printf("Reached here\n");
					tmp = a[i][l]-old[j][l];
					dist +=tmp*tmp;
				}
				
				//printf("dist of (%f,%f) and (%f,%f) is %f\n",a[i][0],a[i][1],old[j][0],old[j][1],dist);
				if(dist<mindist){
					mindist = tmp;
					b[i] = j;
				}
			}
			count[b[i]]++;
			//addab(new[b[i]],a[i],dim);
			for(l=0;l<dim;l++)
				new[b[i]][l]+=a[i][l];
			printf("%d is to %d\n",i,b[i]);
		}


		for(i=0;i<k;i++)
			printf("%d:%d\n",i,count[i]);

		for(i=0;i<k;i++){
			for(j=0;j<dim;j++)
				new[i][j]=new[i][j]/count[i];
		}
		sort1(new,k,dim);
		printf("Old centers are \n");
		for(i=0;i<k;i++){
			printf("%f,%f\n",old[i][0],old[i][1]);
		}	

		printf("new centers are\n");
		for(i=0;i<k;i++){
			printf("%f,%f\n",new[i][0],new[i][1]);
		}

		tcount =0;
		for(i=0;i<k;i++){
			same=0;
			for(j=0;j<dim;j++){
				if(old[i][j]==new[i][j])
					same++;
			}
			if(same==dim)
				tcount++;
		}
		if(tcount==k)
			done=1;
		else
			done=0;
	}
	free(count);

	printf("new centers are :\n");
	for(i=0;i<dim;i++){
		for(j=0;j<dim;j++){
			printf("%f,",new[i][j]);
		}
		printf("\n");
	}

	fclose(fp);

}