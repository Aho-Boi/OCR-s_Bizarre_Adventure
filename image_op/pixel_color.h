# ifndef PIXEL_COLOR_H_
# define PIXEL_COLOR_H_

# include <stdlib.h>
# include <stdio.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <err.h>

void set_pixel_gray(SDL_Surface *surface);
void binarize_otsu(SDL_Surface *surface);

# endif
