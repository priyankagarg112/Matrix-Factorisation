#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#define rating 5
#define INC_SLOPE 5
#define ITERATION 50
#define MAX 1000
int min(int m,int n);
void derivative(float **,float **,float **,int,int,int);
float** transpose(float **,int,int);
float** multiply(float **,float **,int,int,int);
float** subtract(float **,float **,int,int);
float error_function(float **,float **,float **,int,int,int,float);
float root_mean(float **,float **,int,int);
float mean_absolute(float **,float **,int,int);
