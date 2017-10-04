#include <stdlib.h>
#include </usr/include/SDL/SDL.h>

void init_sdl(void)
{
	if(SDL_Init(SDL_INIT_VIDEO) == - 1)
		printf("Error");
}

SDL_Surface* load_image(char *path)
{
	SDL_Surface *picture;
	picture = IMG_Load(path);
	if(!img)
		printf("Error");
	return picture;
}
