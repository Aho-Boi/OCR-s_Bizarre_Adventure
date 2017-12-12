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

int my_strcmp(char* s1, char* s2)
{
  for(; (*s1 != '\0' || *s2 != '\0') && *s1 == *s2; ++s1, ++s2)
    continue;
  return (*s1 == '\0' && *s2 == '\0');
}

char* my_intToStr(int x)
{
  char* s = malloc(100 * sizeof(char));
  int i, j;
  for( i = 0; x; x /= 10, ++i)
    s[i] = (char)(x % 10) + '0';
  char* res = malloc(i * sizeof(char));
  i--;
  for(j = 0; i >= 0; --i, ++j)
    res[j] = s[i];
  res[j] = '\0';
  return res;
}

int my_strToInt(char* s, int n)
{
  int res = 0;
  for(int i = 0; i < n; ++i)
    res = res * 10 + ((int)s[i] - '0');
  return res;
}

