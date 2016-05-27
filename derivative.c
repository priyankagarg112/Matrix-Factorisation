#include"header.h"
void derivative(float **R,float **U,float **V,int row,int col,int k)
{
    int i,j,count=0,increase=0,loop=1;
    float alpha=0.0003,lambda=0.2,rmse,mae,J,J_new,*error;
    float **VT,**RT,**UT,**sub,**multi,**sub_V,**multi_V;
    float **UVT,**VUT;
    float **U_loss,**V_loss,**U_new,**V_new;
    U_loss=(float **)malloc(sizeof(float*)*row);
    for(i=0;i<row;i++) 
	U_loss[i]=(float*)malloc(sizeof(float)*k);
    V_loss=(float **)malloc(sizeof(float*)*col);
    for(i=0;i<col;i++) 
	V_loss[i]=(float*)malloc(sizeof(float)*k);
    U_new=(float **)malloc(sizeof(float*)*row);
    for(i=0;i<row;i++) 
	U_new[i]=(float*)malloc(sizeof(float)*k);
    V_new=(float **)malloc(sizeof(float*)*col);
    for(i=0;i<col;i++) 
	V_new[i]=(float*)malloc(sizeof(float)*k);
    error=(float *)malloc(sizeof(float)*INC_SLOPE);
    while(loop<=ITERATION && increase<INC_SLOPE){
	VT=transpose(V,col,k);
	UVT=multiply(U,VT,row,k,col);
	sub=subtract(UVT,R,row,col);
	multi=multiply(sub,V,row,col,k);
	for(i=0;i<row;i++){
	    for(j=0;j<k;j++){
		U_loss[i][j]=alpha*(lambda*U[i][j]+(2*multi[i][j]));
		U_new[i][j]=U[i][j]-U_loss[i][j];
	    }
	}
	UT=transpose(U,row,k);
	RT=transpose(R,row,col);
	VUT=multiply(V,UT,col,k,row);
	sub_V=subtract(VUT,RT,col,row);
	multi_V=multiply(sub_V,U,col,row,k);
	for(i=0;i<col;i++){
	    for(j=0;j<k;j++){
		V_loss[i][j]=alpha*(lambda*V[i][j]+(2*multi_V[i][j]));
		V_new[i][j]=V[i][j]-V_loss[i][j];
	    }
	}
	J=error_function(R,U,V,row,col,k,lambda);
	J_new=error_function(R,U_new,V_new,row,col,k,lambda);
	if(J_new<J){
	    increase=0;
	    count=0;	    
    	}
    	else{
	    increase++;
	    error[count++]=J_new;
	}
	for(i=0;i<row;i++){
	    for(j=0;j<k;j++){
		U[i][j]=U_new[i][j];
	    }
	}
	for(i=0;i<col;i++){
	    for(j=0;j<k;j++){
		V[i][j]=V_new[i][j];
	    }
	}
	loop++;
    }
    VT=transpose(V_new,col,k);
    UVT=multiply(U_new,VT,row,k,col);
    for(i=0;i<row;i++){
	for(j=0;j<col;j++){
	    if(UVT[i][j]>=0 && UVT[i][j]<1.5)
		UVT[i][j]=1;
	    else if(UVT[i][j]>=1.5 && UVT[i][j]<2.5)
		UVT[i][j]=2;
	    else if(UVT[i][j]>=2.5 && UVT[i][j]<3.5)
		UVT[i][j]=3;
	    else if(UVT[i][j]>=3.5 && UVT[i][j]<4.5)
		UVT[i][j]=4;
	    else if(UVT[i][j]>=4.5 && UVT[i][j]<6)
		UVT[i][j]=5;
	}
    }
    /*for(i=0;i<row;i++){
	for(j=0;j<col;j++){
	    printf("%f ",UVT[i][j]);
	}
	printf("\n");
    }*/
    rmse=root_mean(R,UVT,row,col);
    printf("\nRMSE is: %f\n",rmse);
    mae=mean_absolute(R,UVT,row,col);
    printf("\nMAE is: %f\n",mae);
}
float** transpose(float **matrix,int row,int col)
{
    int i,j;
    float **mat_t;
    mat_t=(float **)malloc(sizeof(float*)*col);
    for(i=0;i<col;i++) 
	mat_t[i]=(float*)malloc(sizeof(float)*row);
    for(i=0;i<row;i++){
         for(j=0;j<col;j++){
           mat_t[j][i]=matrix[i][j];
         }
    }
    return mat_t;
}
float** multiply(float **U,float **V,int row,int k,int col)
{
    int i,j,l;
    float sum;
    float **UV;
    UV=(float **)malloc(sizeof(float*)*row);
    for(i=0;i<row;i++) 
	UV[i]=(float*)malloc(sizeof(float)*col);
    for(i=0;i<row;i++)
        for(j=0;j<col;j++)
            UV[i][j]=0.0;

    for(i=0;i<row;i++){
        for(j=0;j<col;j++){
            sum=0.0;
            for(l=0;l<k;l++)
                sum=sum+U[i][l]*V[l][j];
            UV[i][j]=sum;
        }
    }
    return UV;
}
float** subtract(float **U,float **V,int row,int col)
{
    int i,j;
    float **sub;
    sub=(float **)malloc(sizeof(float*)*row);
    for(i=0;i<row;i++) 
	sub[i]=(float*)malloc(sizeof(float)*col);
    for(i=0;i<row;i++){
	for(j=0;j<col;j++){
	    sub[i][j]=U[i][j]-V[i][j];
	}
    }
    return sub;
}
float error_function(float **R,float **U,float **V,int row,int col,int k,float lambda)
{
    int i,j;
    float sub,sum=0.0,U_sum=0.0,V_sum=0.0,UV_sum,J;
    float **UVT,**VT;
    VT=transpose(V,col,k);
    UVT=multiply(U,VT,row,k,col);
    for(i=0;i<row;i++){
	for(j=0;j<col;j++){
	    if(R[i][j]!=0){
		sub=R[i][j]-UVT[i][j];
		sum=sum+(pow(sub,2));
	    }
	}
    }
    for(i=0;i<row;i++){
	for(j=0;j<k;j++){
	    U_sum=U_sum+(pow(U[i][j],2));
	}
    }
    for(i=0;i<col;i++){
	for(j=0;j<k;j++){
	    V_sum=V_sum+(pow(V[i][j],2));
	}
    }
    UV_sum=(lambda/2.0)*(U_sum+V_sum);
    J=sum+UV_sum;
    return J;
}
float root_mean(float **R,float **UVT,int row,int col)
{
    float sum=0.0,sub,rmse;
    int observed=0;
    int i,j;
    for(i=0;i<row;i++){
	for(j=0;j<col;j++){
	    if(R[i][j]!=0){
		sub=R[i][j]-UVT[i][j];
		sum=sum+(pow(sub,2));
		observed=observed+1;
	    }
	}
    }
    rmse=sqrt((sum)/(float)observed);
    return rmse;
}
float mean_absolute(float **R,float **UVT,int row,int col)
{
    float sum=0.0,mae;
    int observed=0;
    int i,j;
    for(i=0;i<row;i++){
	for(j=0;j<col;j++){
	    if(R[i][j]!=0){
		sum=sum+abs(R[i][j]-UVT[i][j]);
		observed=observed+1;
	    }
	}
    }
    mae=sum/(float)observed;
    return mae;
}
