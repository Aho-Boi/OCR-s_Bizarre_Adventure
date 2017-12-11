#include <dirent.h>
#include <err.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../OGC_planB/my_string.h"
#include "loadOcr.h"
#include "ocr.h"

char* ocr(char *argv)
{
  srand(time(NULL));

  char *pics;
  if(my_strcmp(argv,"/img1.jpg"))
    pics = "../bs/im1/";
  else if(my_strcmp(argv, "/"))
    pics = "../bs//";
  else
    pics = "../bs//";

  DIR *loli = opendir(pics);
  if(!loli)
    errx(1, "Could not load picture");
  struct dirent *lolia;
  char **file = malloc(50 * sizeof(char *));
  int i, j = 0;
  for(i = 0; (lolia = readdir(loli)) != NULL;)
  {
    if(lolia->d_name[0] == '.')
      continue;
    *(file + i) = malloc(5 * sizeof(char));
    memmove(*(file + i), lolia->d_name, 4);
    (*(file + i))[4] = '\0';
    i++;
  }

  char *res = malloc(sizeof(char) * i);
  char *training = my_strcon(pics, "training");
  int r = 0;
  for(; j < i - 1; ++j)
  {
    if (*(*(file + j) + 3) == 's')
    {
      res[my_strToInt(*(file + j), 2)] = ' ';
      continue;
    }
    r = launchOCR(my_strcon(pics, *(file + j)), training);
    if(*(*(file + j) + 3) == 'm')
      res[my_strToInt(*(file + j), 2)] = 'a' + (char)r;
    else
      res[my_strToInt(*(file + j), 2)] = 'A' + (char)r;
  }
  res[i - 1] = '\0';
  free(training);

  return res;
}

int main(void)
{
  char *loli = ocr("/img1.jpg");
  printf("%s", loli);
}
