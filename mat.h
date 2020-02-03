# ifndef MAT_H_
# define MAT_H_

# include <stdlib.h>
# include <stdio.h>

struct matrix
{
  size_t lines;
  size_t columns;
  double **mat;
};

struct matrix *init_mat(size_t lines, size_t columns);

void print_mat(struct matrix *m);

void clean_mat(struct matrix *m);

struct matrix *mult_mat(struct matrix *a, struct matrix *b);

struct matrix *transpose_mat(struct matrix *m);

void mat_apply(double (*func)(double), struct matrix *mat);
  
# endif 
