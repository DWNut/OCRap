#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

void pause();
struct entete_struct {
	char signature[2];
	int taille;
	int offset;
	int taille_entete;
	int largeur;
	int longueur;
	int plans;
	int bpp;
	int compression;
	int taille_image;
	int Hresolution;
	int Vresolution;
	int nbr_couleur;
	int nbr_couleur_importante;
}entete;

int hex2dec (unsigned char hex[4],int nombre)
{
	int resultat = 0;
	int i;
	for (i = nombre - 1; i >= 0; i--)
		resultat = resultat * 256 + hex[i];
	return resultat;
}

void lire_fichier (char nom[255])
{
	unsigned char temp[4];
	FILE * fichier;
	fichier = fopen (nom,"r");
	fread (&entete.signature,2,1,fichier);
	fread (&temp,4,1,fichier);
	entete.taille = hex2dec (temp,4);
	fread (&temp,4,1,fichier);
	fread (&temp,4,1,fichier);
	entete.offset = hex2dec (temp,4);
	fread (&temp,4,1,fichier);
	entete.taille_entete = hex2dec (temp,4);
	fread (&temp,4,1,fichier);
	entete.largeur = hex2dec(temp,4);
	fread (&temp,4,1,fichier);
	entete.longueur = hex2dec(temp,4);
	fread (&temp,2,1,fichier);
	entete.plans = hex2dec (temp,2);
	fread (&temp,2,1,fichier);
	entete.bpp = hex2dec (temp,2);
	fread (&temp,4,1,fichier);
	entete.compression = hex2dec (temp,4);
	fread (&temp,4,1,fichier);
	entete.taille_image = hex2dec (temp,4);
	fread (&temp,4,1,fichier);
	entete.Hresolution = hex2dec (temp,4);
	fread (&temp,4,1,fichier);
	entete.Vresolution = hex2dec (temp,4);
	fread (&temp,4,1,fichier);
	entete.nbr_couleur = hex2dec (temp,4);
	fread (&temp,4,1,fichier);
	entete.nbr_couleur_importante = hex2dec (temp,4);
	fclose (fichier);
}

Uint32 obtenirPixel(SDL_Surface *surface, int x, int y)

{
	int nbOctetsParPixel = surface->format->BytesPerPixel;
	Uint8 *p;
	p = (Uint8 *)surface->pixels +
		      y * surface->pitch + x * nbOctetsParPixel;
	switch(nbOctetsParPixel)
	{
		case 1:
			return *p;
		case 2:
		  return *((Uint16 *)p);
		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
				return p[0] << 16 | p[1] << 8 | p[2];

			else
				return p[0] | p[1] << 8 | p[2] << 16;
		case 4:
		  return *((Uint32 *)p);
		default:
			return 0;
	}

}

void definirPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)

{
	int nbOctetsParPixel = surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)surface->pixels +
	  y * surface->pitch + x * nbOctetsParPixel;
	switch(nbOctetsParPixel)
	{
		case 1:
		*p = pixel;
		break;
		case 2:
		*(Uint16 *)p = pixel;
		break;
		case 3:
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
		{
			p[0] = (pixel >> 16) & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = pixel & 0xff;
		}
		else
		{
			p[0] = pixel & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = (pixel >> 16) & 0xff;
		}
		break;
		case 4:
		*(Uint32 *)p = pixel;
		break;
	}
}

void nuance_de_gris(SDL_Surface *ecran,int height, int width){
  SDL_LockSurface(ecran);
	Uint32 pixel;
	Uint8 r, g, b;

	for(int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){
			pixel = obtenirPixel(ecran, i, j);
			SDL_GetRGB(pixel, ecran->format, &r, &g,  &b);
	//printf("r = %u, g = %u, b = %u, a = %u\n", r, g, b, a);
			r = (r/3 + g/3 + b/3);
	//printf("%d\n", r);
			pixel = SDL_MapRGB(ecran->format, r, r, r);
			definirPixel(ecran, i, j, pixel);
		}
	}
	SDL_UnlockSurface(ecran);
	}

void noir_et_blanc(SDL_Surface *ecran, int height, int width){

	SDL_LockSurface(ecran);
	Uint32 pixel;
	Uint8 r, g, b;
        //double ri, gi, bi;
	for(int i = 0; i < width; i++){
		for(int j = 0; j < height; j++){
			pixel = obtenirPixel(ecran, i, j);
			SDL_GetRGB(pixel, ecran->format, &r, &g,  &b);
        //printf("r = %u, g = %u, b = %u, a = %u\n", r, g, b, a);
			r = r > 195 ? 255 : 0;
        //printf("%d\n", r);
			pixel = SDL_MapRGB(ecran->format, r, r, r);
			definirPixel(ecran, i, j, pixel);
		}
	}
	SDL_UnlockSurface(ecran);
	}

void lignes(SDL_Surface *ecran, int width, int height){

	SDL_LockSurface(ecran);
	int inter;
	Uint32 pixel;
	Uint8 r, g, b;
	int i;
	int j;
	for(i = 0; i < height; i++){
		for(j = 0; j < width; j++){
			pixel = obtenirPixel(ecran, j, i);
			SDL_GetRGB(pixel, ecran->format, &r, &g,  &b);
			if (r != 255)
				break;
			r = 100;
			g = 20;
			b = 20;
			pixel = SDL_MapRGB(ecran->format, r, g, b);
			definirPixel(ecran, j, i, pixel);
		}
        //printf("r : %d\n i : %d\n j : %d\n\n ", r, i, j);
		if (j != width){
			inter = j;
			j = 0;
			while (j < inter){
			  pixel = SDL_MapRGB(ecran->format, 255, 255, 255);
				definirPixel(ecran, j, i, pixel);
				++j;
			}
		}
	}
	SDL_UnlockSurface(ecran);
}

void colonnes(SDL_Surface *ecran, int width, int height)
{
	SDL_LockSurface(ecran);
	int inter;
	Uint32 pixel;
	Uint8 r, g, b;
	int i;
	int j;
	for(i = 0; i < width; i++){
		for(j = 0; j < height; j++){
			pixel = obtenirPixel(ecran, i, j);
			SDL_GetRGB(pixel, ecran->format, &r, &g,  &b);
			if (r == 0)
				break;
			r = 100;
			g = 20;
			b = 20;
			pixel = SDL_MapRGB(ecran->format, r, g, b);
			definirPixel(ecran, i, j, pixel);
		}
        //printf("r : %d\n i : %d\n j : %d\n\n ", r, i, j);
		if (j != height){
			inter = j;
			j = 0;
			while (j < inter){
				pixel = SDL_MapRGB(ecran->format, 255, 255, 255);
				definirPixel(ecran, i, j, pixel);
				j++;
			}
		}
	}
	SDL_UnlockSurface(ecran);
}

void caracteres(SDL_Surface *ecran, int width, int height){
	SDL_LockSurface(ecran);

	int k = 0;
	int boo = 1;
	int inter;
	Uint32 pixel;

	Uint8 r, g, b;

	int i = 0;
	int j = 0;

	while (k < height)
	{

	  for(; j < width; j++)
	    {
	      if (boo)
		{

		  for (; i < height; i++)
		    {
		      pixel = obtenirPixel(ecran, j, i);
		      SDL_GetRGB(pixel, ecran->format, &r, &g,  &b);

		      if (r != 100)
			break;
		    }

		  inter = i;

		  for (; i < height; i++)
		    {
		      pixel = obtenirPixel(ecran, j, i);
		      SDL_GetRGB(pixel, ecran->format, &r, &g,  &b);

		      if (r != 255)
			break;

		      pixel = SDL_MapRGB(ecran->format, 100, 20, 20);
		      definirPixel(ecran, j, i, pixel);
		    }

		  pixel = obtenirPixel(ecran, j, i);
		  SDL_GetRGB(pixel, ecran->format, &r, &g,  &b);

		  if (r != 100)
		    {
		      boo = 0;
		      j--;
		    }
		}

	      else
		{

		  for(i = 0; i < height;i++)
		    {
		      pixel = obtenirPixel(ecran, j, i);
		      SDL_GetRGB(pixel, ecran->format, &r, &g, &b);

		      if (r != 100)
			break;

		      pixel = SDL_MapRGB(ecran->format, 255, 255, 255);
		      definirPixel(ecran, j, i, pixel);
		    }

		  boo = 1;

		}

	   k = i;
	   i = inter;

	    }

	}

	for (; k < height; k++)
	  {
	    pixel = obtenirPixel(ecran, j, i);
	    SDL_GetRGB(pixel, ecran->format, &r, &g,  &b);

	    if (r != 100)
	      break;
	  }

	SDL_UnlockSurface(ecran);
}

void pause()
{
	int continuer = 1;
	SDL_Event event;
	while (continuer)
	{
		SDL_WaitEvent(&event);
		switch(event.type)
		{
			case SDL_QUIT:
				continuer = 0;
				break;
		}
	}
}


int main()
{
	lire_fichier("Test.bmp");
	printf ("longueur : %d\n", entete.longueur);
	printf ("largeur : %d\n", entete.largeur);
	SDL_Surface *ecran = NULL, *img = NULL;
	SDL_Rect positionFond;
	positionFond.x = 0;
	positionFond.y = 0;
	SDL_Init(SDL_INIT_VIDEO);
	img = SDL_LoadBMP("Test.bmp");
	ecran = SDL_SetVideoMode(entete.largeur, entete.longueur, 32, SDL_HWSURFACE);
	nuance_de_gris(ecran, entete.longueur, entete.largeur);
	noir_et_blanc(ecran, entete.largeur, entete.longueur);
    //colonnes(img, entete.largeur, entete.longueur);
	lignes(ecran, entete.largeur, entete.longueur);
    //colonnes(img, entete.largeur, entete.longueur);
    //printf("bonjour");
	caracteres(ecran, entete.largeur, entete.longueur);
	SDL_WM_SetCaption("Ok", NULL);
	SDL_BlitSurface(ecran, NULL, ecran, &positionFond);
    //SDL_UpdateRect(ecran, 0, 0, 0, 0);
	SDL_Flip(ecran);
	//	pause();
	SDL_FreeSurface(img);
	SDL_Quit();
	return EXIT_SUCCESS;
}
