# include <time.h>
# include <math.h>
# include "neuralNetwork.h"

# define random() (double)rand()/(double)(RAND_MAX)

double expo(double z)
{
  return expf(z);
}

double sigmoid(double z)
{
  return (1/ (1 + expo(z)));
}

double sigDer(double z)
{
  return -(expo(z))/((1 + expo(z))*(1+expo(z)));
}

double rdm(double min, double max)
{
  return (double)rand()/(double)(RAND_MAX)*(max - min) + min;
}
   
struct network *network_init(char c)
{
  struct network *net = malloc(sizeof(struct network));
  net->input = init_mat(16,16);
  net->hidden = init_mat(256*1.5,1);
  net ->character =c;
  net->weight1 = init_mat(256,256*1.5);
  net->weight2 = init_mat(256*1.5,1);
  net->errors = init_mat(257,256*1.5);
  
  for (size_t i = 0; i < net->weight1->lines; ++i)
    {
      net->weight2->mat[i][1] = rdm(-10,10);
      for (size_t j = 0; j < net->weight1->columns; ++j)
	net->weight1->mat[i][j] = rdm(-10,10);
    }
  return net;
}

struct matrix *forward(struct network *net, struct matrix *input)
{
  net->input = input;
  net->hidden = mult_mat(input,net->weight1);
  for (size_t i = 0; i < net->hidden->lines; ++i)
    for (size_t j = 0; j < net->hidden->columns; ++j)
      net->hidden->mat[i][j] = sigmoid(net->hidden->mat[i][j]);
  return net->hidden;
}

int main(void)
{
  struct matrix *m = init_mat(16,16);
  for(size_t i = 0; i < 16; ++i)
    {
      m->mat[i][6] = 1;
      m->mat[i][7] = 1;
      m->mat[5][i] = 1;
    }
  struct network *net = network_init('a');
  struct matrix *o = forward(net, m);
  size_t lines = o->lines;
  size_t columns = o->columns;
  printf("lines = %u and columns = %u", lines, columns);
}
