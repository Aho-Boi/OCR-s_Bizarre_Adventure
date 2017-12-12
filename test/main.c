# include <stdlib.h>
# include <stdio.h>
# include "pixel_operations.h"
# include "segmentation.h"
# include <err.h>
# include <SDL.h>
# include <SDL_image.h>



void wait_for_keypressed(void) {
  SDL_Event             event;
  for (;;) {
    SDL_PollEvent( &event );
    switch (event.type) {
    case SDL_KEYDOWN: return;
    default: break;
    }
  }
}

void init_sdl(void) {
  if( SDL_Init(SDL_INIT_VIDEO)==-1 ) {
    errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
  }
}

SDL_Surface* load_image(char *path) {
  SDL_Surface          *img;
  img = IMG_Load(path);
  if (!img)
    errx(3, "can't load %s: %s", path, IMG_GetError());
  return img;
}

SDL_Surface* display_image(SDL_Surface *img) {
  SDL_Surface          *screen;
  screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
  if ( screen == NULL ) {
    errx(1, "Couldn't set %dx%d video mode: %s\n",
         img->w, img->h, SDL_GetError());
  }
  if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
    warnx("BlitSurface error: %s\n", SDL_GetError());
  SDL_UpdateRect(screen, 0, 0, img->w, img->h);
  wait_for_keypressed();
  return screen;
}


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
   Uint8 gp = 0.299 * r + 0.587 * g + 0.114 * b;
   Uint32 gray = SDL_MapRGB(surface->format, gp, gp, gp);
   putpixel(surface, x, y, gray);
  }
 }
}


int*  Otsuuchan(SDL_Surface *img)
{
	float hist[256] = {0.0F};
	Uint8 r,g,b;
	for (int x = 0; x < img->w; x++)
	{
	for (int y = 0; y < img-> h ; y++)
	{
	SDL_GetRGB(getpixel(img,x,y), img->format, &r, &g, &b);
	Uint8 graylevel = r* 0.3+ g* 0.59 + b*0.11;
	hist[graylevel] += 1;				
	}
	}
	int nb_pixel = img->w * img->h;
	for(int i = 0; i<256; i++)
	{
	  hist[i] /= nb_pixel;
	}	
	
	float t =0;
	for (int i=0; i<256; i++)
	{
	  t += i * hist[i];
	} 
	
	int max_k = 0;
	int max_sigma_k_ = 0;

	for (int k = 0; k < 256; k++)
	{
		float wk = 0;
		for (int i = 0; i<= k ; i++)
		{
			wk += hist[i];
		}
		float uk = 0;
		for (int i=0; i<=k;i++)
		{
			uk += i*hist[i];
		}
		
		float sigma_k = 0;
		if(wk != 0 && wk != 1)
		{sigma_k = ((t*wk-uk)*(t*wk- uk))/(wk*(1-wk));}
		
		if (sigma_k > max_sigma_k_)
		{
			max_k = k;
			max_sigma_k_ = sigma_k;
		}
	}
	
	int *bin = malloc(sizeof(int) * nb_pixel);
	int test = 0;
	for(int x = 0; x < img->w;x++)
	{
		for (int y = 0; y < img->h; y++)
		{
			SDL_GetRGB(getpixel(img,x,y), img->format, &r, &g, &b);
			Uint8 graylevel = r * 0.3 + g * 0.59 + b * 0.11;
			
			if (graylevel <max_k)
			{
			   putpixel(img,x,y,SDL_MapRGB(img -> format, 0,0,0));
			   bin[(y*(img->h))+x] = 1;
			}
			else
			{
				putpixel(img,x,y,SDL_MapRGB(img -> format,255,255,255));
				bin[(y*(img->h))+x] = 0;
			}
			test++;
		}
	} 
	printf("test : %d \n" , test);
	return bin;
}

int main(int argc, char* argv[])
{
	if(argc>1)
	{
		SDL_Surface* image = load_image(argv[1]);
		int line = image->h;
		int cols = image->w; 
		int *matbite = malloc(sizeof(int) * line * cols);
		display_image(image);
		set_pixel_gray(image);
		matbite = Otsuuchan(image);
		display_image(image);
		print_mat(matbite,line,cols);
    		int *matbite2 = malloc(sizeof(int)*line*cols);
		matbite2 = resizePixels(matbite , cols ,line, 200,200);
		upp(matbite2, 200, 200);
		SDL_FreeSurface(image);
		free(matbite);
		free(matbite2);
	}
	else
		printf("lol no image!");
	return 0;
}


