#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


void print_mat(int mat[3][3]) {
  for (size_t i = 0; i < 3; ++i) {
    for (size_t j = 0; j < 3; ++j)
      printf("%d ", mat[i][j]);
    printf("\n");
  }
}

int main()
{
  
  FILE *fd = fopen("weights", "w+");
  if (fd == NULL)
  {
    perror("Error opening file :");
    exit(1);
  }

    struct stat  *buf;
  if (fstat(fileno(fd),buf) != 0)
    {
      perror("Error while retrieving file infos :");
      exit(1);
    }
  size_t file_size = (size_t)buf->st_size;
int **mat;
mat = mmap(NULL, file_size, PROT_READ | PROT_WRITE,
	   MAP_SHARED,fileno(fd), 0);
*mat = {
  {1,2,3},
  {4,5,6},
  {7,8,9}
};

  print_mat(mat);
  printf("%zu\n", file_size);
  fclose(fd);
  return 0;
}
