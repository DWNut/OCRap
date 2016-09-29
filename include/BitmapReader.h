/*
** BitmapReader.h for OCRap
** 
** Made by Juliette Malassé
** Login   <dwnut@epita.fr>
** 
** Started on  Wed Sep 28 00:19:20 2016 Juliette Malassé
** Last update Thu Sep 29 20:26:50 2016 Juliette Malassé
*/

#ifndef BITMAP_READER_H_
# define BITMAP_READER_H_

# include <stdint.h>

typedef struct __attribute__((packed))
{
  uint16_t		_magic;		/* Magic number */
  uint32_t		_size;		/* Size of file (in bytes) */
  uint32_t		_reserved;
  uint32_t		_offset;	/* Pixel Array (data) offset */
}			BitmapHeader;

typedef struct __attribute__((packed))
{
  uint32_t		_headerSize;	/* Size of this header (min 12 bytes) */
  uint16_t		_width;		/* Width (in pixels) */
  uint16_t		_height;	/* Height (in pixels) */
  uint16_t		_colormapNb;	/* Number of color plane (must be 1) */
  uint16_t		_bpp;		/* Bit per Pixel */
}			DIBHeader;


typedef struct
{
  BitmapHeader		_header;	/* File header */
  DIBHeader		_DIBHeader;	/* Image header */
  int			_fd;		/* File descriptor */
}			BitmapFile;

typedef struct
{
  uint8_t		_blue;		/* Blue component */
  uint8_t		_green;		/* Green component */
  uint8_t		_red;		/* Red component */
}			Pixel;

typedef struct
{
  unsigned int		_width;		/* Width (in pixels) */
  unsigned int		_height;	/* Height (in pixels) */
  Pixel			**_data;	/* Pointer to an array of Pixel */
}			BitmapData;

/*
** FUNCTION PROTOTYPES
*/
BitmapFile		*openBitmap(const char *path);

#endif /* !BITMAP_READER_H_ */
