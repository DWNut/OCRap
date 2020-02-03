# include "mat.h"

struct matrix *init_mat(size_t lines, size_t columns)
{
  struct matrix *m = malloc(sizeof(struct matrix));
  m->lines = lines;
  m->columns = columns;

  double **mat;
  mat = malloc(lines * sizeof(double *));
  for (size_t i = 0; i < lines; ++i)
    mat[i] = calloc(columns, sizeof(double));
  m->mat = mat;
    return m;
}

void print_mat(struct matrix *m)
{
  for (size_t i = 0; i < m->lines; ++i)
    {
      for (size_t j = 0; j < m->columns; ++j)
	printf("%f ", m->mat[i][j]);
      printf("\n");
    }
}

void clean_mat(struct matrix *m)
{
  for (size_t i = 0; i < m->lines; ++i)
    free(m->mat[i]);
  free(m->mat);
  free(m);
}

struct matrix *mult_mat(struct matrix *a, struct matrix *b)
{
  struct matrix *product = init_mat(a->lines, b->columns);
  for (size_t i = 0; i < product->lines; ++i)
    {
      for (size_t j = 0; j < product->columns; ++j)
	{
	  for(size_t x = 0; x < a->columns; ++x)
	    {
	      product->mat[i][j] += a->mat[i][x] * b->mat[x][j];
	    }
	  
	}
    }
  return product;
}

struct matrix *transpose_mat(struct matrix *m)
{
  struct matrix *tr = init_mat(m->columns, m->lines);
  for (size_t i = 0; i < m->lines; ++i)
    for (size_t j = 0; j < m->columns; ++j)
      tr->mat[j][i] = m->mat[i][j];
  return tr;
}

void mat_apply(double (*func)(double), struct matrix *m)
{
  for (size_t i = 0; i < m->lines; ++i)
    {
      for (size_t j = 0; j < m-> columns; ++j)
	{
	  m->mat[i][j] = (*func)(m->mat[i][j]);
	}
    }
}
/*
int main()
{
  struct matrix *m = init_mat(3,2);
  struct matrix *n = init_mat(2,4);
  struct matrix *p = mult_mat(m,n);
  print_mat(p);
  clean_mat(m);
  clean_mat(n);
  clean_mat(p);
  return 0;
}
*/
