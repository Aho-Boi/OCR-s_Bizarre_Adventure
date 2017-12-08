#include <stdlib.h>
#include <gtk/gtk.h>


static void
print_label (GtkWidget * widget, gpointer data)
{
    gtk_label_set_text(GTK_LABEL(data), "New Image");
}


int main(int argc, char **argv)
{
    /* Variables */
    GtkWidget * window;
    //GtkWidget * hbox;
    GtkWidget * buttonStart;
    GtkWidget * buttonStop;
    GtkWidget * onglets;
    GtkWidget * label;
    GtkWidget * table;
    GtkWidget * subtable;

    /* Initialisation de GTK+ */
    gtk_init(&argc, &argv);

    /* Création de la fenêtre */
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "OCR's Bizarre Aventure");
         

    /* Onglets */
    onglets = gtk_notebook_new();
    gtk_notebook_set_tab_pos(GTK_NOTEBOOK(onglets), GTK_POS_TOP);
    gtk_notebook_set_scrollable(GTK_NOTEBOOK(onglets), FALSE);    

    /* Label */ 
    label = gtk_label_new("Test du Label");
    
    /* Table Creation */
    table = gtk_table_new(2,1,1);
    subtable = gtk_table_new(1,2,1);

  
    /* Bouton Creation */
    //hbox = gtk_vbox_new (0,0);
    buttonStart = gtk_button_new_with_label ("Start");
    g_signal_connect(buttonStart, "clicked", G_CALLBACK(print_label),(gpointer)label);
    buttonStop = gtk_button_new_with_label ("Exit");
    g_signal_connect(buttonStop, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    /*gtk_box_pack_start(GTK_BOX(hbox), label, 1,1,1);
    gtk_box_pack_start(GTK_BOX(hbox), buttonStart, 1,1,1);
    gtk_box_pack_start(GTK_BOX(hbox), buttonStop, 1,1,1);*/
 
    /* Table Attachment */
    gtk_table_attach(GTK_TABLE(subtable),buttonStart,0,1,0,1,GTK_EXPAND | GTK_FILL,GTK_EXPAND,0,0);
    gtk_table_attach(GTK_TABLE(subtable),buttonStop,1,2,0,1,GTK_EXPAND | GTK_FILL,GTK_EXPAND,0,0);
    gtk_table_attach(GTK_TABLE(table),subtable,0,1,1,2,GTK_EXPAND | GTK_FILL,GTK_EXPAND | GTK_FILL,0,0);
    gtk_table_attach(GTK_TABLE(table),label,0,1,0,1,GTK_EXPAND | GTK_FILL,GTK_EXPAND,0,0);
    
    gtk_table_set_row_spacing(GTK_TABLE(subtable),0,200);

    /* Container Add*/
    //gtk_container_add (GTK_CONTAINER (window), hbox);
    gtk_container_add(GTK_CONTAINER(window),table);
 
    /* Affichage et boucle évènementielle */
    gtk_widget_show_all(window);
    gtk_main();

    /* On quitte.. */
    return 1;
}
