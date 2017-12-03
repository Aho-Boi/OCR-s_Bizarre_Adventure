#include <stdlib.h>
#include <gtk/gtk.h>

print_hello ()
{
  g_print ("Hello World\n");
}

int main(int argc, char **argv)
{
    /* Variables */
    GtkWidget * window;
    GtkWidget * button_box;
    GtkWidget * buttonStart;
    GtkWidget * buttonStop;
    GtkWidget * onglets;
    //GtkWidget * label;

    /* Initialisation de GTK+ */
    gtk_init(&argc, &argv);

    /* Création de la fenêtre */
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "OCR's Bizarre Aventure");
    
    /* Onglets */
    onglets = gtk_notebook_new();
    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(onglets), GTK_POS_TOP);
    gtk_notebook_set_scrollable(GTK_NOTEBOOK(onglets), FALSE);    

    /* Label 
    label = Label();
    label.set_markup('<span color="#c0392b" weight="bold" font="FreeSerif">Je suis rouge, en gras avec une belle police !</span>');
    */
  
    /* Bouton Creation */
    button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
    gtk_container_add (GTK_CONTAINER (window), button_box);
    buttonStart = gtk_button_new_with_label ("Start");
    g_signal_connect(buttonStart, "clicked", G_CALLBACK(print_hello),NULL);
    buttonStop = gtk_button_new_with_label ("Stop");
    g_signal_connect(buttonStop, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_add (GTK_CONTAINER (button_box), buttonStart);
    gtk_container_add (GTK_CONTAINER(button_box), buttonStop);
    
 
    /* Affichage et boucle évènementielle */
    gtk_widget_show_all(window);
    gtk_main();

    /* On quitte.. */
    return EXIT_SUCCESS;
}
