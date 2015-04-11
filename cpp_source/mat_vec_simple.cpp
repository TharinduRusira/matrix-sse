/*
 * matvec_simple.cpp
 *
 *  Created on: Mar 5, 2015
 *      Author: tharindu
 *      Performs simple matrix-vector multiplication
 */
#include <iostream>
#include <time.h>

#define N_row 100
#define M_col 100

using namespace std;

float* rand_vec_gen(size_t M)
{
   float *vec =  (float*)malloc(M*sizeof(float));
  int i;
	srand(time(NULL)); // seed the pseudo-random generator
	for(i=0;i<M;i++)
	{
		int number = rand();
		vec[i] = (float)number/(float)pow((double)10,(number%10));
		cout<<vec[i]<<"\t";
	}
	return vec;
}

float** rand_mat_gen(size_t N, size_t M)
{
  float **mat =  (float**)malloc(N*sizeof(float*));
	int i,j;
	srand(time(NULL)); // seed the pseudo-random generator
	for(i=0;i<N;i++){
		mat[i] = (float*)malloc(M*sizeof(float));
		for(j=0;j<M;j++){
			int number = rand();
			mat[i][j] = (float)number/(float)pow((double)10,(number%10));
			cout << mat[i][j] << "\t";
		}
		cout << endl;
	}
	return mat;
}


void matvec_simple(size_t n,float** mat_a,float* vec_b){
	int i,j;
	float* c = new float[n];
	clock_t start = clock();
	for(i=0;i<n;i++){
		vec_c[i]=0.0;
		for(j=0;j<n;j++){
			vec_c[i] += mat_a[i][j]*vec_b[j];
		}

	}
	cout<< "time for simple mat_vec_mul=" << clock() - start << endl;

}

int main(){
  float** MAT = rand_mat_gen(N_row,M_col);
  float* VEC = rand_vec_gen(M_col);
  matvec_simple(N_row,MAT,VEC);
  return 0;
  
}