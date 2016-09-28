/*
** Bitmap.h for OCRap
** 
** Made by Juliette Malassé
** Login   <dwnut@epita.fr>
** 
** Started on  Wed Sep 28 00:19:20 2016 Juliette Malassé
** Last update Wed Sep 28 00:47:20 2016 Juliette Malassé
*/

#ifndef BITMAP_H_
# define BITMAP_H_

# include <stdint.h>

typedef struct
{
  uint16_t		_magic;		// Magic number
  uint32_t		_size;		// Size of file (in bytes)
  uint16_t		_reserved1;
  uint16_t		_reserved2;
  uint32_t		_offset;	// Pixel Array (data) offset
}			BitmapHeader;

typedef struct
{
  uint32_t		_headerSize;	// Size of this header (min 12 bytes)
  uint16_t		_width;		// Width (in pixels)
  uint16_t		_height;	// Height (in pixels)
  uint16_t		_colormapNb;	// Number of color plane (must be 1)
  uint16_t		_bpp;		// Bit per Pixel
}			DIBHeader;

#endif /* !BITMAP_H_ */
