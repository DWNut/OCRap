# ifndef NEURAL_NETWORK_H_
# define NEURAL_NETWORK_H_

# include "mat.h"
# include "mat.c"

struct network
{
  /*neurons*/
  struct matrix *input;
  struct matrix *hidden;

  /*weights*/
  struct matrix *weight1;
  struct matrix *weight2;

  /*errors*/
  struct matrix *errors;

  char character;
  /*cost function for each case
  struct matrix *costs;*/
};

struct network *network_init(char c);

struct matrix *forward(struct network *net, struct matrix *input);

struct matrix *cost_function(struct matrix *output);

void gradient_descent(struct network *net);

void clean_network(struct network *net);

# endif
