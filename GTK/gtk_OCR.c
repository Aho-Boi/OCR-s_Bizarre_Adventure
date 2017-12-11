#include <gtk/gtk.h>
#include <string.h>
#include "../defense/ocr.h"

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


