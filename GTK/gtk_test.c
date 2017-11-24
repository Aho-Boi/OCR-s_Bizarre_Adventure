#include <stdlib.h>
#include <gtk/gtk.h>

int main(int argc, char **argv)
{
  GtkWidget * MainWindow = NULL;
  MainWindow = gtk_new_window(GTK_WINDOW_TOPLEVEL);
  gtk_init(&argc, &argv);
  gtk_widget_show(MainWindow);
  return EXIT_SUCCESS;
}
