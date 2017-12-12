#include <dirent.h>
#include <err.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

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

GtkWidget * g_resOCR;
GtkWidget * g_lbl_filename;
gchar * filename;

int main (int argc, char *argv[])
{
  GtkBuilder * gtkBuilder;
  GtkWidget * window;
  //GtkWidget * dialogBox;
  gtk_init(&argc, &argv);

  gtkBuilder = gtk_builder_new();
  gtk_builder_add_from_file(gtkBuilder, "glade_OCR.glade", NULL);
  window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "window1"));
  //dialogBox = GTK_FILECHOOSER(gtk_builder_get_object(gtkBuilder, "filechooserdialog1"));  
  g_lbl_filename = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "lbl_res"));
  g_resOCR = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "resOCR"));
  //filename =  gtk_file_chooser_get_filename(dialogBox);
  gtk_builder_connect_signals(gtkBuilder,NULL);
  g_object_unref(G_OBJECT(gtkBuilder));
  gtk_widget_show(window);
  gtk_main();

  return 1;
}

char* from_path_to_file (char * path)
{
  size_t i = strlen(path);
  path += i;
  while (*path != '/')
  { 
    path -= 1;
  }
  return path;
}

void on_buttonStart_clicked(){
  char * result = ocr(filename);
  gtk_label_set_text(GTK_LABEL(g_resOCR), result);
}


void on_buttonSelect_clicked(GtkBuilder *builder, GtkWidget *Win)
{
  builder = builder;
  gtk_widget_show(Win);
}


void on_buttonQuit_clicked()
{
  gtk_main_quit();
}

void on_Cancel_clicked(GtkBuilder *builder, GtkWidget *Win)
{
  builder = builder;
  gtk_widget_hide(Win);
}


void on_Selection_clicked(GtkBuilder *builder, GtkWidget *FileChoose)
{
  builder = builder;
  filename = gtk_file_chooser_get_filename(FileChoose);
  filename = from_path_to_file(filename);
  gtk_label_set_text(GTK_LABEL(g_lbl_filename), filename);
  gtk_widget_hide(FileChoose);
}

