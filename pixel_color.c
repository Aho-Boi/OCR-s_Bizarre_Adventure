# include "pixel_color.h"

void init_sdl(void) {
  // Init only the video part
  if( SDL_Init(SDL_INIT_VIDEO)==-1 ) {
    // If it fails, die with an error message
    errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
  }
  // We don't really need a function for that ...
}

void wait_for_keypressed(void) {
  SDL_Event             event;
  // Infinite loop, waiting for event
  for (;;) {
    // Take an event
    SDL_PollEvent( &event );
    // Switch on event type
    switch (event.type) {
    // Someone pressed a key -> leave the function
    case SDL_KEYDOWN: return;
    default: break;
    }
  // Loop until we got the expected event
  }
}

SDL_Surface* load_image(char *path) {
  SDL_Surface          *img;
  // Load an image using SDL_image with format detection
  img = IMG_Load(path);
  if (!img)
    // If it fails, die with an error message
    errx(3, "can't load %s: %s", path, IMG_GetError());
  return img;
}

SDL_Surface* display_image(SDL_Surface *img) {
  SDL_Surface          *screen;
  // Set the window to the same size as the image
  screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
  if ( screen == NULL ) {
    // error management
    errx(1, "Couldn't set %dx%d video mode: %s\n",
         img->w, img->h, SDL_GetError());
  }
 
  /* Blit onto the screen surface */
  if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
    warnx("BlitSurface error: %s\n", SDL_GetError());
 
  // Update the screen
  SDL_UpdateRect(screen, 0, 0, img->w, img->h);
 
  // wait for a key
  wait_for_keypressed();
 
  // return the screen for further uses
  return screen;
}

static inline
Uint8* pixelref(SDL_Surface *surf, unsigned x, unsigned y)
{
  int bpp = surf->format->BytesPerPixel;
  return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}
 
Uint32 getpixel(SDL_Surface *surface, unsigned x, unsigned y)
 {
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
  case 1:
    return *p;
  case 2:
    return *(Uint16 *)p;
  case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
      return p[0] << 16 | p[1] << 8 | p[2];
    else
      return p[0] | p[1] << 8 | p[2] << 16;
  case 4:
    return *(Uint32 *)p;
  }
  return 0;
}
 
void putpixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel) 
{
  Uint8 *p = pixelref(surface, x, y);
  switch(surface->format->BytesPerPixel) {
  case 1:
    *p = pixel;
    break;
  case 2:
    *(Uint16 *)p = pixel;
    break;
  case 3:
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
      p[0] = (pixel >> 16) & 0xff;
      p[1] = (pixel >> 8) & 0xff;
      p[2] = pixel & 0xff;
    } else {
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

void set_pixel_black_white(SDL_Surface *surface)
{
 Uint32 black;
 Uint32 white;
 for(int x = 0; x < surface->w; x++)
 {
  for(int y = 0; y < surface->h; y++)
  {
   Uint32 pixel = getpixel(surface, x, y);
   Uint8 r;
   Uint8 g;
   Uint8 b;
   SDL_GetRGB(pixel, surface->format, &r, &g, &b);
   if(r > 128)
   {
        white = SDL_MapRGB(surface->format, 255, 255, 255);
        putpixel(surface, x, y, white);
   }
   else
   {
        black = SDL_MapRGB(surface->format, 0,0, 0);
		putpixel(surface, x, y, black);
	}
  }	
 }
}

void erase_noise(SDL_Surface *surface)
{
 int hist[256];
 int count = 0;
 for(int i = 0; i < 256; i++)
 {
  hist[i] = 0;
 }
 for(int x = 0; x < surface->w; x++)
 {
  for(int y = 0; y < surface->h; y++)
  {
   hist[getpixel(surface, x, y)] += 1;
   count += 1;
  }
 }
 int mid = count / 2;
 int bd = 1/2;
 int ctr = bd / 2;
 int cm = 0;
 while(cm != mid)
 {
  cm = cm + hist[0];
 }
 set_pixel_black_white(surface);
}

void erase_noise_median(SDL_Surface *surface)
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
   int sumr = 0;
   int sumg = 0;
   int sumb = 0;
   int mid = 0;
   if(x - 1 >= 0)
   { 
    Uint32 pixel = getpixel(surface, x - 1, y);
    Uint8 r1;
    Uint8 g1;
    Uint8 b2;
    SDL_GetRGB(pixel, surface->format, &r1, &g1, &b1);
    sumr += 1;
    sumg += 1;
    sumb += 1;
    mid += 1;
   }
   if(x + 1 < surface->w)
   { 
    Uint32 pixel2 = getpixel(surface, x + 1, y);
    Uint8 r2;
    Uint8 g2;
    Uint8 b2;
    SDL_GetRGB(pixel, surface->format, &r2, &g2, &b2);
    sumr += 1;
    sumg += 1;
    sumb += 1;
    mid += 1;
   }
   if(y - 1 >= 0)
   { 
    Uint32 pixel = getpixel(surface, x, y - 1);
    Uint8 r3;
    Uint8 g3;
    Uint8 b3;
    SDL_GetRGB(pixel, surface->format, &r3, &g3, &b3);
    sumr += 1;
    sumg += 1;
    sumb += 1;
    mid += 1;
   }
   if(y + 1 < surface->h)
   { 
    Uint32 pixel = getpixel(surface, x, y + 1);
    Uint8 r4;
    Uint8 g4;
    Uint8 b4;
    SDL_GetRGB(pixel, surface->format, &r4, &g4, &b4);
    sumr += 1;
    sumg += 1;
    sumb += 1;
    mid += 1;
   } 
   if(x - 1 >= 0 && y - 1 >= 0)
   {
    Uint32 pixel = getpixel(surface, x - 1, y - 1);
    Uint8 r5;
    Uint8 g5;
    Uint8 b5;
    SDL_GetRGB(pixel, surface->format, &r5, &g5, &b5);
    sumr += 1;
    sumg += 1;
    sumb += 1;
    mid += 1;
   }
   if(x - 1 >= 0 && y + 1 < surface->h)
   {
    Uint32 pixel = getpixel(surface, x - 1, y + 1);
    Uint8 r6;
    Uint8 g6;
    Uint8 b6;
    SDL_GetRGB(pixel, surface->format, &r6, &g6, &b6);
    sumr += 1;
    sumg += 1;
    sumb += 1;
    mid += 1;
   }
   if(x + 1 < surface->w && y - 1 >= 0)
   {
    Uint32 pixel = getpixel(surface, x + 1, y - 1);
    Uint8 r7;
    Uint8 g7;
    Uint8 b7;
    SDL_GetRGB(pixel, surface->format, &r7, &g7, &b7);
    sumr += 1;
    sumg += 1;
    sumb += 1;
    mid += 1;
   }
   if(x + 1 < surface->w && y + 1 < surface->h)
   {
    Uint32 pixel = getpixel(surface, x + 1, y + 1);
    Uint8 r8;
    Uint8 g8;
    Uint8 b8;
    SDL_GetRGB(pixel, surface->format, &r8, &g8, &b8);
    sumr += 1;
    sumg += 1;
    sumb += 1;
    mid += 1;
   }
   r = sumr / mid;
   g = sumg / mid;
   b = sumb / mid;
   Uint32 new_pixel = SDL_MapRGB(surface->format, r, g, b);
   putpixel(surface, x, y, new_pixel);   
  }
 }
}

int main(int argc, char *argv[])
{
	init_sdl();
	SDL_Surface* image = load_image(argv[1]);
	Set_pixel_black_white(image);
	SDL_Surface* disp = display_image(image);
}


