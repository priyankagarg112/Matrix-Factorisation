#include"header.h"
int main()
{
    srand(time(NULL));
    //char *line;
    int i,j,k;
    int row,col;
    float ran;
    float **matrix_r;
    float **matrix_u,**matrix_v;
    //float r;
    matrix_r=(float **)malloc(sizeof(float*)*MAX);
    for(i = 0; i < MAX; i++) 
	matrix_r[i] = (float*)malloc(sizeof(float)*MAX);
    matrix_u=(float **)malloc(sizeof(float*)*MAX);
    for(i = 0; i < MAX; i++) 
	matrix_u[i] = (float*)malloc(sizeof(float)*MAX);
    matrix_v=(float **)malloc(sizeof(float*)*MAX);
    for(i = 0; i < MAX; i++) 
	matrix_v[i] = (float*)malloc(sizeof(float)*MAX);
    
    FILE *fstream = fopen("matrix.txt","r");
    if(fstream == NULL){
	printf("\n file opening failed ");
	return -1 ;
    }
    row=100;
    col=500;
    //printf("%d%d\n",row,col);
    for(i=0;i<row;i++){
	for(j=0;j<col;j++){
	    if(!fscanf(fstream,"%f",&matrix_r[i][j]))
		break;
	    //printf("%d ",matrix_r[i][j]);
	}
    }
    fclose(fstream);
    /*for(i=0;i<m;i++){
	for(j=0;j<n;j++){
	    //srand(time(NULL));
	    //r=rand()%(rating+1);
	    matrix_r[i][j]=r;
	}
    }*/
    k=min(row,col);
    //printf("%d ",k);
    for(i=0;i<row;i++){
	for(j=0;j<k;j++){
	    //srand(time(NULL));
	    ran=(float)rand()/(float)(RAND_MAX);
	    matrix_u[i][j]=ran;
	    //printf("%f ",matrix_u[i][j]);
	}
    }
    for(i=0;i<col;i++){
	for(j=0;j<k;j++){
	    //srand(time(NULL));
	    ran=(float)rand()/(float)(RAND_MAX);
	    matrix_v[i][j]=ran;
	    //printf("%f ",matrix_v[i][j]);
	}
    }
    /*printf("MATRIX R\n");
    for(i=0;i<row;i++){
	for(j=0;j<col;j++){
	   printf("%d ",matrix_r[i][j]);
	}
	printf("\n");
    }
    printf("MATRIX U\n");
    for(i=0;i<row;i++){
	for(j=0;j<k;j++){
	   printf("%f ",matrix_u[i][j]);
	}
	printf("\n");
    }
    printf("MATRIX V\n");
    for(i=0;i<col;i++){
	for(j=0;j<k;j++){
	   printf("%f ",matrix_v[i][j]);
	}
	printf("\n");
    }*/
    derivative(matrix_r,matrix_u,matrix_v,row,col,k);
    return 0;
}
int min(int m,int n)
{
    int k=0;
    while(k==0){
	if(m<=n)
	    k=rand()%m;
	else
	    k=rand()%n;
    }
    printf("K is %d\n",k);
    return k;
}
