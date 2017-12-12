# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "segmentation.h"

//j'utilise un histograme pour savoir ou decoupe , ensuite je coupe verticalement et horizontalement et j'isole le chara dans une matrice de 0 et de 1 , ca marche pour tt taille normelement mdr.


//decoupe le character horizontalement
int* upp(int *mat, int l, int c)
{	int *res = malloc(2*sizeof(int));
	printf("\n");
	int histo[l];//fait l'histograme
	for (int i = 0; i < l; i++)
	{	
		histo[i] = 0;
	}
	for (int i = 0; i < l; i++)
	{
	 int j = 0;
	 while (j < c && mat[j+i*c]!=1)
	 {
	   j++;	
	 }
	 if (j<c)
	 {
	   histo[i] = 1;
	 }
	 printf("%d", histo[i]);
	}
	printf("\n\n  ");
	int i = 0;
	while(i < l)
	{
	 if(histo[i]==1) 
	  {
	   int begin = i;
	   int acc = 0;
		while(i!=l && histo[i]==1)
		{
		acc ++;
		i += 1;
		}
		int *mat_line = malloc(sizeof(int) * c * acc);
		int end = begin + acc;
			int k = 0;
			for(; begin < end; begin++)
			{
			  for(int n = 0; n < c; n++)
			  {
			    mat_line[n + k * c] = mat[n + begin * c];
			   }
			k++;
			}
			print_mat(mat_line, acc , c);
			res[0] = acc;
			printf("\n\n");
			upp2(mat_line, acc , c, res);
			
			free(mat_line);
			
		}
		i++;
		
	}
	 printf(" %d \n",res[0]);
         printf(" %d \n",res[1]);
	 return res;
}

//decoupe de chara vercticalement
void upp2(int *mat, int l, int c, int* res)
{
	int hist[c];
	for (int i = 0; i < c; i++)
		hist[i] = 0;
	for (int j = 0; j < c; j ++)
	{
		int i = 0;
		while(i < l && mat[j+i*c]!=1)
		{
		  i++;
		}
		if(i< l)
		   hist[j] = 1;
		printf("%d", hist[j]);
	}
	printf("\n\n");

	int j = 0;
	while(j < c)
	{
		if (hist[j] == 1)
		{
			
			int begin = j;
			int acc = 0;
			while(j!= c && hist[j] == 1)
			{
				j++;
				acc++;
			}
			
			int *chara = malloc(sizeof(int) * l * acc);
			int k = 0;
			int end = begin + acc;
			for(; begin < end ; begin ++)
			{
				for(int a = 0 ; a < l ; a++)
				{
				chara[k+a*acc] = mat[begin+a *c];
				}
				k++;
			}
			print_mat(chara, l , acc);
			//res[1] = acc;
			res[1] = c;
			printf("\n");
			free(chara);
		}
		j++;
	}
}

int* resizePixels(int *pixels, int w1, int h1, int w2, int h2)
{
	if(w2*h2 == 0){
		printf("rip u fucktard");
		return 0;
	}
	int *result = malloc(sizeof(int)*w2*h2);
	double x_ratio = w1/(double)w2;
	double y_ratio = h1/(double)h2;
	int x;
	int y;
	for(int i = 0; i < h2; i++)
	{
	  for(int j = 0; j < w2; j++)
	  {
	    x = floor(j*x_ratio);
	    y = floor(i*y_ratio);
	    result[(i*w2)+j] = pixels[(int)(y*w1)+x];
	   }
	}
      return result;
}


void print_mat(int *mat, int line, int col)
{
   for (int i = 0; i< line; i++)
   {
     for (int j = 0; j < col; j++)
	{
	  printf("%d", mat[j+i*col]);
	}
     printf("\n");
    }	
}
