#include <iostream>
#include <tmmintrin.h>
#include <smmintrin.h>
#include <math.h>

#define N_row 800
#define M_col 800
#define M21 800

using namespace std;

void mat_vec_mul_sse(size_t N, size_t M, float* avec, float** amat);
void mat_mat_mul_sse(size_t N, size_t M1, size_t M2, float** A, float** B);
void mat_mul_simple(size_t N,size_t M1, size_t M2, float** A,float** B);

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

int main(int argc, char **argv) {
   
    float** MAT_A = rand_mat_gen(N_row,M_col);
    float** MAT_B = rand_mat_gen(M_col,M21);
    //float* VEC = rand_vec_gen(M_col);
    //matvec_simple(N_row, MAT,VEC);
    //matvec_unrolled(N_row,MAT,VEC);
    //mat_vec_mul_sse(N_row,M_col,VEC,MAT_A);
    mat_mul_simple(N_row,M_col,M21,MAT_A,MAT_B);
    //mat_mat_mul_sse(N_row, M_col,M21,MAT_A,MAT_B);
    return 0;
}

void mat_vec_mul_sse(size_t N, size_t M, float* avec, float** amat)
{
  
  float* vec = avec;//rand_vec_gen(M_col);
  float** mat = amat; //rand_mat_gen(N_row,M_col);
  cout << "vector size =" <<M<<"x1\n Matrix size="<<N<<"x"<<M<<"\n"<<endl;
  
  __m128 vec_b,vec_mat;

  float c[N]; // store the final result
  
  //clock_t start = clock(); // uncomment to run vector multiplication
  
  for(int i=0;i<N;i++) // for each row of the matrix
  {
    __m128 vec_c = _mm_setzero_ps(); // accumilate the sum of products
 
    for(int j=0;j<M;j+=4) // for each 4 number block in a row
    {
      
      vec_b = _mm_loadu_ps(vec+j);
      vec_mat = _mm_loadu_ps(mat[i]+j);
      vec_c = _mm_add_ps(_mm_dp_ps(vec_mat,vec_b,0xFF),vec_c);
    }
    c[i] = _mm_cvtss_f32(vec_c);
  }
  //cout << "time for mat_vec_mul_sse = " << clock() - start << endl; // uncomment to run vector multiplication
}

void mat_mat_mul_sse(size_t N, size_t M1, size_t M2,float** A,float** B)
{
  float** matA = A;//rand_mat_gen(N,M1); // N x M1
  float** matB = B;//rand_mat_gen(M1,M2); // M1 x M2
  
  cout << "Matrix A size =" <<N<<"x"<<M1<<" Matrix B size="<<M1<<"x"<<M2<<"\n"<<endl;
  
  clock_t start = clock();
  for(int i=0;i<N;i++) // for each row of matA
  {
    float* current_row = matA[i];
    mat_vec_mul_sse(M1,M2,current_row,matB);
  }
  cout << "time taken for matrix multiplication=" << clock() - start << endl;
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
