# ifndef PIXEL_COLOR_H_
# define PIXEL_COLOR_H_

# include <stdlib.h>
# include <stdio.h>
# include <err.h>
# include "load_picture.h"

void set_pixel_gray(SDL_Surface *surface);
void binarize_otsu(SDL_Surface *surface);

# endif
