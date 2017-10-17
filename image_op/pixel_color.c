# include "pixel_color.h"
# include "load_picture.h"
# include "SDL/SDL.h"
# include "SDL_image.h"

void set_pixel_gray(SDL_Surface *surface)
{
 for(int x = 0; x < surface->w; x++)
 {
  for(int y = 0; y < surface->h; y++)
  {
   Uint32 pixel = getpixel(surface, x, y);
   Uint8 r;
   Uint8 g;
   Uint8 b;
   SDL_GetRGB(pixel, surface->format, &r, &g, &b);
   Uint8 gray_pixel = 0.299 * r + 0.587 * g + 0.114 * b;
   Uint32 gray = SDL_MapRGB(surface->format, gray_pixel, gray_pixel, gray_pixel);
   putpixel(surface, x, y, gray);
  }
 }
}

void binarize_otsu(SDL_Surface *surface)
{
 int hist[256];
 int total = 0;
 for(int x = 0; x < surface->w; x++)
 {
  for(int y = 0; y < surface->h; y++)
  {
   Uint32 pixel = getpixel(surface, x, y);
   Uint8 r;
   Uint8 g;
   Uint8 b;
   SDL_GetRGB(pixel, surface->format, &r, &g, &b);
   hist[r] += 1;
  }
 }
 for(int i = 0; i < 256; i++)
 {
  total += hist[i];
 }
 int w1 = 0, w2 = 0;
 for(int i = 0; i < 128; i++)
 	w1 += hist[i]/total;
 for(int i = 128; i < 256;  i++)
 	w2 += hist[i]/total;
 int m1 = 0;	
 int m2 = 0;
 for(int i = 0; i < 128; i ++)
 	m1 = (hist[i] * (hist[i]/total)) / w1;		
 for(int i = 128; i < 256; i ++)
 	m2 = (hist[i] * (hist[i]/total)) / w2;
 int sig1 = 0, sig2 = 0;		
 for(int i = 128; i < 256; i ++)
 	sig2 = (((hist[i] - m2) * (hist[i]/total)) * ((hist[i] - m2) * (hist[i]/total))) / w2;	
 for(int i = 0; i < 128; i ++)
 	sig1 = (((hist[i] - m1) * (hist[i]/total)) * ((hist[i] - m1) * (hist[i]/total))) / w1;
 Uint8 sig = w1 * sig1 * sig1 + w2 * sig2 * sig2;
 for(int x = 0; x < surface->w; x++)
 { 
  for(int y = 0; y < surface->h; y++)
  {
   Uint32 pixel = getpixel(surface, x, y);
   Uint8 r;
   Uint8 g;
   Uint8 b;
   Uint32 bin_value;
   SDL_GetRGB(pixel, surface->format, &r, &g, &b);
   if(r > sig)
    bin_value  = SDL_MapRGB(surface->format, 255, 255, 255);
   else
    bin_value = SDL_MapRGB(surface->format, 0, 0, 0);
   putpixel(surface, x, y, bin_value);

  }
 }
}



