#include <iostream>
#include <stddef.h>
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

void matvec_unrolled(size_t n,float** mat_a, float* vec_b)
{
	int i,j;
	clock_t start = clock();
	for(i=0;i<n;i++){
		v[i]=0.0;
		for(j=0;j<n;j+=4){
			v[i] += mat_a[i][j+0]*vec_b[j+0]
						+ mat_a[i][j+1]*vec_b[j+1]
						+ mat_a[i][j+2]*vec_b[j+2]
						+ mat_a[i][j+3]*vec_b[j+3];
		}
	}
	cout << "time taken ="<< clock() - start << endl;

}


int main()
{
  float** MAT = rand_mat_gen(N_row,M_col);
  float* VEC = rand_vec_gen(M_col);
  matvec_unrolled(N_row,MAT,VEC);
  return 0;
}
