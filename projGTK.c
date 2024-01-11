#include <gtk/gtk.h>
#include <stdio.h>
#include <unistd.h> 
#include <glib.h>
#include <cairo.h>
#include <stdlib.h> // Pour la fonction rand
#include <time.h>   // Pour initialiser la graine de rand

GtkWidget *window;
GtkWidget *box;
GtkWidget *grid;
GtkWidget *Dgrid;
GtkWidget *paned; 
GtkWidget *button;
GtkWidget *Abutton;
GtkWidget *Dbutton;
GtkWidget *Gobutton;
GtkWidget *entry;
GtkWidget *entry1;
GtkWidget *label;
GtkWidget *label1;
GtkWidget *info;
int dim=-1;
float tab[100];
static int iteration = 0;



gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    double bar_height = (double)GPOINTER_TO_INT(user_data);
    double x, y;
   // gtk_widget_compute_point(Dgrid, 0, 0, &x, &y);
    // Dessiner le rectangle avec la hauteur spécifiée
    cairo_rectangle(cr, 10, 10, 50,50); //(double)gtk_widget_get_width(widget), (double)gtk_widget_get_height(widget));
    cairo_set_source_rgb(cr, 1.0, 0.0, 0.0); // Couleur du rectangle (bleu)
    cairo_fill(cr);
    return FALSE;
}

gboolean delayed_function (gpointer user_data) {
        char str[10];
        gchar *text = g_strdup_printf("%.2f", tab[iteration]);
        GtkWidget *frame = gtk_frame_new(text);
        sprintf(str, "%d", iteration);
        GtkWidget *ind = gtk_label_new(str);   //gtk_frame_new(str);//gtk_label_new(str);



        gtk_grid_attach(GTK_GRID(Dgrid), frame, iteration + 5, 29, 1, 1);
        gtk_grid_attach(GTK_GRID(Dgrid), ind, iteration + 5, 30, 1, 1);
        g_free(text);
        iteration++;  
        if (iteration < dim) {
            g_timeout_add_seconds(0.1, delayed_function, NULL);
        } else {
            iteration=0;
        }

    return G_SOURCE_REMOVE;
}

void displayTab(GtkWidget *widget, int dim, float tab[dim]) {
    char str[10],texte[40];
    gtk_widget_set_visible(GTK_WIDGET(Dgrid),false);
    Dgrid = gtk_grid_new();
    gtk_widget_set_visible(GTK_WIDGET(Dgrid),true);
    gtk_widget_set_hexpand(Dgrid, TRUE);
    gtk_widget_set_vexpand(Dgrid, TRUE);
    gtk_box_append(GTK_BOX(box), Dgrid); 
    gtk_widget_set_visible(GTK_WIDGET(Dgrid),true); 
    for (int i=0;i<dim;i++){
        gchar *text = g_strdup_printf("%.2f", tab[i]);
        GtkWidget *frame = gtk_frame_new(text);
        sprintf(str, "%d", i);
        GtkWidget *ind = gtk_label_new(str);
        gtk_grid_attach(GTK_GRID(Dgrid), ind, i + 5, 20, 1, 1);
        gtk_grid_attach(GTK_GRID(Dgrid), frame, i + 5, 21, 1, 1);
        g_free(text);
    }
}



static void valider (GtkButton *button, gpointer data) {
    entry = GTK_WIDGET(data);
    const gchar *text = gtk_editable_get_text(GTK_EDITABLE(entry));
    dim = atoi(text);
    gtk_widget_set_visible(GTK_WIDGET(label), FALSE);
    gtk_widget_set_visible(GTK_WIDGET(entry), FALSE);
    gtk_widget_set_visible(GTK_WIDGET(Gobutton), FALSE);
    srand(time(NULL));
     for (int i = 0; i < dim; ++i) {
        tab[i] = rand() % 100;   // Valeurs aléatoires entre 0 et 99
     }
    displayTab(GTK_WIDGET(Dgrid),dim, tab);
}

static void svalider (GtkButton *button, gpointer data) {
    entry = GTK_WIDGET(data);
    const gchar *text = gtk_editable_get_text(GTK_EDITABLE(entry));
    char *token;
    double nombre;
    char *copyt = g_strdup(text);
    dim=-1;
    token = strtok(copyt, ",");
    while (token != NULL) {
        nombre = strtod(token, NULL);
        dim++;
        tab[dim] = nombre;
        token = strtok(NULL, ",");
    }
    dim++;
    gtk_widget_set_visible(GTK_WIDGET(label), FALSE);
    gtk_widget_set_visible(GTK_WIDGET(entry), FALSE);
    gtk_widget_set_visible(GTK_WIDGET(info), FALSE);
    gtk_widget_set_visible(GTK_WIDGET(Gobutton), FALSE);
    displayTab(GTK_WIDGET(Dgrid),dim, tab);
}

void saisie (){
    gtk_grid_set_row_spacing(GTK_GRID(grid), 20);
    label = gtk_label_new("Saisir les données du tableau :");
    gtk_grid_attach(GTK_GRID(grid), label, 1, 5, 2, 1);
    info = gtk_label_new("(utiliser la \",\" comme séparateur et le \".\" pour les décimaux)");
    gtk_grid_attach(GTK_GRID(grid), info, 3, 6, 12, 1);
    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 3, 5, 4, 1);
    Gobutton = gtk_button_new_with_label("Go");
    g_signal_connect(Gobutton, "clicked", G_CALLBACK(svalider), entry);
    gtk_grid_attach(GTK_GRID(grid), Gobutton, 8, 5, 1, 1);
}

void Dimension (){
    gtk_grid_set_row_spacing(GTK_GRID(grid), 70);
    // Créer une étiquette pour expliquer à l'utilisateur
    label = gtk_label_new("Donner la dimension du tableau :");
    gtk_grid_attach(GTK_GRID(grid), label, 1, 5, 2, 1);
    // Créer une entrée pour la saisie de la valeur
    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 3, 5, 1, 1);
    g_signal_connect(entry, "activate", G_CALLBACK(valider), entry);
    // Créer un bouton "Valider"
    Gobutton = gtk_button_new_with_label("Go");

    // Connecter le signal "clicked" à la fonction on_button_clicked
    g_signal_connect(Gobutton, "clicked", G_CALLBACK(valider), entry);
    
    // Ajouter le bouton au grid
    gtk_grid_attach(GTK_GRID(grid), Gobutton, 4, 5, 1, 1);
}


  

static void creation (GtkButton *button, gpointer data) {
  gtk_grid_set_row_spacing(GTK_GRID(grid), 0);
  gtk_widget_set_visible(GTK_WIDGET(Dbutton), TRUE);
  gtk_widget_set_visible(GTK_WIDGET(Abutton), TRUE);
}

static void
createRand (GtkWidget *widget, gpointer data){
     gtk_widget_set_visible(GTK_WIDGET(Dbutton), FALSE);
     gtk_widget_set_visible(GTK_WIDGET(Abutton), FALSE);
     Dimension ();
}

static void
createUser (GtkWidget *widget,
             gpointer   data)
{
gtk_widget_set_visible(GTK_WIDGET(Dbutton), FALSE);
gtk_widget_set_visible(GTK_WIDGET(Abutton), FALSE);
saisie();
}

static void
activate (GtkApplication *app,
          gpointer user_data)
{
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Projet C : Opérations sur les tableaux");
  gtk_window_set_default_size (GTK_WINDOW (window), 800, 600);
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_window_set_child(GTK_WINDOW(window), box);
  grid = gtk_grid_new();
  gtk_widget_set_hexpand(grid, TRUE);
  gtk_widget_set_vexpand(grid, TRUE);
  button = gtk_button_new_with_label ("Création");
  g_signal_connect (button, "clicked", G_CALLBACK (creation), NULL);
  gtk_grid_attach(GTK_GRID (grid), button, 0, 0, 1, 1);
  button = gtk_button_new_with_label ("insertion");        
 
  gtk_grid_attach (GTK_GRID (grid), button, 1, 0, 1, 1);
  button = gtk_button_new_with_label ("Suppression");
 
  gtk_grid_attach (GTK_GRID (grid), button, 2, 0, 1, 1);
  button = gtk_button_new_with_label ("Recherche élément");
 
  gtk_grid_attach (GTK_GRID (grid), button, 3, 0, 1, 1);
  button = gtk_button_new_with_label ("Tri à bulles");
 
  gtk_grid_attach (GTK_GRID (grid), button, 4, 0, 1, 1);
  button = gtk_button_new_with_label ("Quitter");
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_window_destroy), window);
  gtk_grid_attach (GTK_GRID (grid), button, 5, 0, 1, 1);
  Dbutton = gtk_button_new_with_label ("Données utilisateur");
  g_signal_connect (Dbutton, "clicked", G_CALLBACK (createUser), NULL);
  gtk_grid_attach (GTK_GRID (grid), Dbutton, 0, 1, 2, 1);
  gtk_widget_set_visible(GTK_WIDGET(Dbutton), FALSE);
  Abutton = gtk_button_new_with_label ("Données aléatoires");        
  g_signal_connect (Abutton, "clicked", G_CALLBACK (createRand), NULL);
  gtk_grid_attach (GTK_GRID (grid), Abutton, 0, 2, 2, 1);
  gtk_widget_set_visible(GTK_WIDGET(Abutton), FALSE);
  Dgrid = gtk_grid_new ();
  gtk_widget_set_hexpand(Dgrid, TRUE);
  gtk_widget_set_vexpand(Dgrid, TRUE);
  gtk_box_append(GTK_BOX(box), grid);
  gtk_box_append(GTK_BOX(box), Dgrid);
  gtk_window_present (GTK_WINDOW (window));
}


int
main (int argc,char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("project.Algo", G_APPLICATION_DEFAULT_FLAGS);
  //app = gtk_application_new ("project.Algo".G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app,"activate",G_CALLBACK(activate),NULL);
  status = g_application_run(G_APPLICATION(app),argc,argv);
  g_object_unref(app);
  return status;
}