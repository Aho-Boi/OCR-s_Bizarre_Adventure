# include <stdlib.h>
# include <err.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include "pixel_color.h"
# include "picture_operations.h"

void wait_for_keypressed(void)
{
  SDL_Event             event;
  for (;;) {
    SDL_PollEvent( &event );
    switch (event.type) {
    case SDL_KEYDOWN: return;
    default: break;
    }
  }
}

void init_sdl(void)
{
	if(SDL_Init(SDL_INIT_VIDEO) == - 1)
		printf("Error");
}

SDL_Surface* load_image(char *path)
{
	SDL_Surface *picture;
	picture = IMG_Load(path);
	if(!picture)
		printf("Error");
	return picture;
}

SDL_Surface* display_image(SDL_Surface *img) 
{
  SDL_Surface          *screen;
  screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
  if ( screen == NULL ) {
    errx(1, "Couldn't set %dx%d video mode: %s\n",
         img->w, img->h, SDL_GetError());
  }
 
  if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
    warnx("BlitSurface error: %s\n", SDL_GetError());
 
  // Update the screen
  SDL_UpdateRect(screen, 0, 0, img->w, img->h);
 
  // wait for a key
  wait_for_keypressed();
 
  // return the screen for further uses
  return screen;
}


int main(int argc, char *argv[])
{
  if(argc != 2)
    printf("Error: wrong number of args");
  init_sdl();
  SDL_Surface* image = load_image(argv[1]);
  set_pixel_gray(image);
  display_image(image);
  binarize_otsu(image);
  display_image(image);
  Tree T = surface_to_tree(image);
  y_cut(T, 1);
  display_cut(T);
  return 0;
}
