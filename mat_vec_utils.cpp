float* rand_vec_gen(size_t N)
{
  float *vec =  (float*)malloc(N*sizeof(float));
  int i;
	srand(time(NULL)); // seed the pseudo-random generator
	for(i=0;i<N;i++)
	{
		int number = rand();
		vec[i] = (float)number/(float)pow((double)10,(number%10));
		cout<<vec[i]<<"\t";
	}
	return vec;
}
float** rand_mat_gen(size_t N, size_t M)
{
  float **mat =  new float*[N];
	int i,j;
	srand(time(NULL)); // seed the pseudo-random generator
	for(i=0;i<N;i++){
		mat[i] = new float[M];
		for(j=0;j<M;j++){
			int number = rand();
			mat[i][j] = (float)number/(float)pow((double)10,(number%10));
			cout << mat[i][j] << "\t";
		}
		count << endl;
	}
	return mat;
}
