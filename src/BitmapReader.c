/*
** BitmapReader.c for OCRap
** 
** Made by Juliette Malassé
** Login   <dwnut@epita.fr>
** 
** Started on  Wed Sep 28 23:23:01 2016 Juliette Malassé
** Last update Thu Sep 29 22:19:32 2016 Juliette Malassé
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>


#include "BitmapReader.h"

BitmapFile	*openBitmap(const char *path)
{
  BitmapFile	*out;

  out = malloc(sizeof(BitmapFile));
  if (out == NULL)
    {
      perror("openBitmap: ");
      return NULL;
    }
  memset(out, 0, sizeof(BitmapFile));

  out->_fd = open(path, O_RDONLY);
  if (out->_fd == -1)
    {
      perror("openBitmap: ");
      free(out);
      return NULL;
    }

  if (read(out->_fd, &(out->_header), sizeof(BitmapHeader))
      < (ssize_t)sizeof(BitmapHeader))
    {
      perror("openBitmap: ");
      free(out);
      return NULL;
    }

   if (read(out->_fd, &(out->_DIBHeader), sizeof(DIBHeader))
      < (ssize_t)sizeof(DIBHeader))
    {
      perror("openBitmap: ");
      free(out);
      return NULL;
    }
  
  return out;
}
