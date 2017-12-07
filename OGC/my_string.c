#include <stdio.h>
#include <stdlib.h>

int my_strlen(char* s)
{
  int i = 0;
  for(; *s != '\0'; ++i, ++s)
    continue;
  return i;
}

char* my_strcon(char* s1, char* s2)
{
  int size1 = my_strlen(s1), size2 = my_strlen(s2);
  char *tmp = malloc((size1 + size2 + 1) * sizeof(char));
  if(!tmp)
    exit(71);
  char *s = tmp;
  for(; s < tmp + size1; ++s, ++s1)
    *s = *s1;
  for(; s < tmp + size1 + size2; ++s, ++s2)
    *s = *s2;
  *s = '\0';
  return tmp;
}
