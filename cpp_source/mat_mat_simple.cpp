#include <iostream>
#include <tmmintrin.h>
#include <smmintrin.h>
#include <math.h>

#define N_row 100
#define M_col 100
#define M21 100

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

void mat_mul_simple(size_t N,size_t M1, size_t M2, float** A,float** B)
{
  float** c = (float**)malloc(N*sizeof(float*));
  
  float** matA = A;
  float** matB = B;
  clock_t start = clock();
  
  for(int i=0;i<N;i++)
  {
    c[i] = (float*)malloc(M1*sizeof(float));
    for(int j=0;j<M1;j++)
    {
	c[i][j]=0;
	for(int k=0;k<M2;k++)
	{
	  c[i][j]+= matA[i][k]*matB[k][j];
	}
    }
  }
  cout << "Time Taken for matvec_simple= " <<clock() - start<<endl;
  
}

int main()
{   
    float** MAT_A = rand_mat_gen(N_row,M_col);
    float** MAT_B = rand_mat_gen(M_col,M21);
    mat_mul_simple(N_row,M_col,M21,MAT_A,MAT_B);
    return 0;
    
}
