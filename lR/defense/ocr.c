#include <dirent.h>
#include <err.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../ocr/my_string.h"
#include "loadOcr.h"
//#include "ocr.h"

char* ocr(char *argv)
{
  srand(time(NULL));

  char *pics;
  int nbInput = 52;
  char *training = "training";
  if(my_strcmp(argv,"/img1.jpg"))
    pics = "../bs/im1/";
  else if(my_strcmp(argv, "/img2.jpg"))
    pics = "../bs/im2/";
  else
  {
    pics = "../bs/im3/";
    training = "KlingonTraining";
    nbInput = 26;
  }
  DIR *loli = opendir(pics);
  if(!loli)
    errx(1, "Could not load picture");
  struct dirent *lolia;
  char **file = malloc(100 * sizeof(char *));
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
  i++;
  char *res = malloc(sizeof(char) * i);
  int r = 0;
  for(; j < i - 1; ++j)
  {
    if (*(*(file + j) + 3) == 's')
    {
      res[my_strToInt(*(file + j), 2)] = ' ';
      continue;
    }
    r = launchOCR(my_strcon(pics, *(file + j)), training);
    if (r > 25)
      res[my_strToInt(*(file + j), 2)] = 'A' + (char)r - 26;
    else
      res[my_strToInt(*(file + j), 2)] = 'a' + (char)r;
  }
  res[i - 1] = '\0';

  return res;
}

int main(void)
{
/*
  for(int i = 61; i > 9; --i)
  {
    char* l1 = my_strcon("mv ../bs/im1/", my_intToStr(i));
    char* l4 = my_strcon(l1, "_s");
    char* l2 = my_strcon(l4, " ../bs/im1/");
    l1 = my_strcon(l2, my_intToStr(i + 1));
    l2 = my_strcon(l1, "_s");
    system(l2);
  }
*/
  char *loli = ocr("/img1.jpg");
  printf("%s\n", loli);
  loli = ocr("/img2.jpg");
  printf("%s\n", loli);
  loli = ocr("/img3.jpg");
  printf("%s", loli);
}
