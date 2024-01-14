#include <gtk/gtk.h>
#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h> // Pour la fonction rand
#include <time.h>   // Pour initialiser la graine de rand
//faire la barre
//faire la progression
//faire le bouton de vitesse
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
int dim=-1,inter=1000;
float tab[100];
static int iteration = 0;
static int iiteration = 0;
static int jiteration = 0;

void displayTab(GtkWidget *widget, int dim, float tab[dim],int pos) {
    char str[10],str1[40],str2[5];
    gtk_widget_set_visible(GTK_WIDGET(Dgrid),false);
    Dgrid = gtk_grid_new();
    gtk_widget_set_visible(GTK_WIDGET(Dgrid),true);
    gtk_widget_set_hexpand(Dgrid, TRUE);
    gtk_widget_set_vexpand(Dgrid, TRUE);
    gtk_box_append(GTK_BOX(box), Dgrid); 
    gtk_widget_set_visible(GTK_WIDGET(Dgrid),true); 
    sprintf(str1, "Affichage du tableau de dimension = %d",dim);
    GtkWidget *labelinfo = gtk_label_new(str1);
    gtk_grid_attach(GTK_GRID(Dgrid), labelinfo, 5, 15, 5, 1);
    for (int i=0;i<dim;i++){
        gchar *text = g_strdup_printf("%.2f", tab[i]);
        GtkWidget *frame = gtk_frame_new(text);
        sprintf(str, "%d", i);
        GtkWidget *ind = gtk_label_new(str);
        const char *str2="\u2191 \u2191 \u2191";  //code ascii de fleche vers le haut
        GtkWidget *indic = gtk_label_new(str2);        
        GtkWidget *blueframe = gtk_frame_new(text);
        GtkWidget *whiteframe = gtk_frame_new(text);
        const char *cssClass = (pos == i ) ? "blueframe" : "whiteframe";
        const char *css = g_strdup_printf("#%s { background-color: %s; }", cssClass, (pos == i) ? "#ADD8E6" : "white");
        GtkCssProvider *provider = gtk_css_provider_new();
        gtk_css_provider_load_from_string(provider, css);  //, -1, NULL);
        gtk_style_context_add_provider_for_display(gdk_display_get_default(), GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
        gtk_widget_set_name(blueframe, cssClass);
        gtk_widget_set_name(whiteframe, cssClass);
        gtk_grid_attach(GTK_GRID(Dgrid), ind, i + 5, 20, 1, 1);
        if (i==pos){
            gtk_grid_attach(GTK_GRID(Dgrid), blueframe, i + 5, 21, 1, 1);
            gtk_grid_attach(GTK_GRID(Dgrid), indic, i + 5, 22, 1, 1);
        }else{
            gtk_grid_attach(GTK_GRID(Dgrid), whiteframe, i + 5, 21, 1, 1);
        }  
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
    displayTab(GTK_WIDGET(Dgrid),dim, tab,-1);
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
    displayTab(GTK_WIDGET(Dgrid),dim, tab,-1);
}

void saisie (){
    gtk_grid_set_row_spacing(GTK_GRID(grid), 20);
    label = gtk_label_new("Saisir les données du tableau :");
    gtk_grid_attach(GTK_GRID(grid), label, 1, 7, 2, 1);
    info = gtk_label_new("(utiliser la \",\" comme séparateur et le \".\" pour les décimaux)");
    gtk_grid_attach(GTK_GRID(grid), info, 3, 8, 12, 1);
    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 3, 7, 4, 1);
    Gobutton = gtk_button_new_with_label("Go");
    g_signal_connect(Gobutton, "clicked", G_CALLBACK(svalider), entry);
    gtk_grid_attach(GTK_GRID(grid), Gobutton, 8, 7, 1, 1);
}

void Dimension (){
    gtk_grid_set_row_spacing(GTK_GRID(grid), 70);
    label = gtk_label_new("Donner la dimension du tableau :");
    gtk_grid_attach(GTK_GRID(grid), label, 1, 7, 2, 1);
    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 3, 7, 1, 1);
    g_signal_connect(entry, "activate", G_CALLBACK(valider), entry);
    Gobutton = gtk_button_new_with_label("Go");
    g_signal_connect(Gobutton, "clicked", G_CALLBACK(valider), entry);
    gtk_grid_attach(GTK_GRID(grid), Gobutton, 4, 7, 1, 1);
}

static void insvalider (GtkButton *button, gpointer data) {
    const gchar *text = gtk_editable_get_text(GTK_EDITABLE(entry));
    const gchar *text1 = gtk_editable_get_text(GTK_EDITABLE(entry1));
    int pos;
    float val;
    pos = atoi(text);
    sscanf(text1,"%f",&val);
    gtk_widget_set_visible(GTK_WIDGET(label), FALSE);
    gtk_widget_set_visible(GTK_WIDGET(label1), FALSE);
    gtk_widget_set_visible(GTK_WIDGET(entry), FALSE);
    gtk_widget_set_visible(GTK_WIDGET(entry1), FALSE);
    gtk_widget_set_visible(GTK_WIDGET(Gobutton), FALSE);
    if (pos < 0 || pos > dim || dim >= 100) {  // 100 max du tableau
        label = gtk_label_new("position invalide ou dimension maximale du tableau est atteinte !");
        gtk_grid_attach(GTK_GRID(grid), label, 1, 7, 6, 1);
    } else {
       for (int i = dim; i > pos; i--) {
        tab[i] = tab[i - 1];
    }
    tab[pos] = val;
    dim++;
    label = gtk_label_new("Valeur ajoutée avec succès !");
    gtk_grid_attach(GTK_GRID(grid), label, 1, 7, 3, 1);
    displayTab(GTK_WIDGET(Dgrid),dim, tab,pos);
  }
}

static void insertion (GtkButton *button, gpointer data) {
    gtk_widget_set_visible(GTK_WIDGET(Dbutton), FALSE);
    gtk_widget_set_visible(GTK_WIDGET(Abutton), FALSE);
    gtk_grid_remove_row(GTK_GRID(grid),7);
    gtk_grid_remove_row(GTK_GRID(grid),8);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 70);
    label = gtk_label_new("Donner la position :");
    gtk_grid_attach(GTK_GRID(grid), label, 1, 7, 3, 1);
    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 4, 7, 1, 1);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 0);
    label1 = gtk_label_new("Donner la valeur à insérer :");
    gtk_grid_attach(GTK_GRID(grid), label1, 1, 8, 3, 1);
    entry1 = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry1, 4, 8, 1, 1);
    Gobutton = gtk_button_new_with_label("Go");
    g_signal_connect(Gobutton, "clicked", G_CALLBACK(insvalider),NULL);
    gtk_grid_attach(GTK_GRID(grid), Gobutton, 5, 8, 1, 1);
}

static void creation (GtkButton *button, gpointer data) {
  gtk_grid_remove_row(GTK_GRID(grid),7);
  gtk_grid_remove_row(GTK_GRID(grid),8);
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

static void activate (GtkApplication *app,gpointer user_data)
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
  g_signal_connect (button, "clicked", G_CALLBACK (insertion), NULL);
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

int main (int argc,char **argv)
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