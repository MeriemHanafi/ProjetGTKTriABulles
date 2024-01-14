# ProjetGTKTriABulles

Ce code est une application en GTK ecrite en langage C qui permet de realiser les differentes operations d'un tableau , telles que la creation , supression, recherche elements et enfin le tri à bulles , tout en utilisant les bibliotheque graphique de GTK pour créer des interfaces utilisateur graphiques.

Déclarations des bibliothèques :
Les bibliothèques inclues fournissent les fonctionnalités nécessaires pour travailler avec GTK, la gestion du temps, les entrées/sorties, et l'allocation dynamique de mémoire.
#include <gtk/gtk.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

Déclarations des widgets GTK :
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
Ces variables représentent différents éléments de l'interface graphique tels que la fenêtre, la boîte, la grille, les boutons, les entrées, et les étiquettes

Variables globales:
int dim = -1, inter = 1000;
float tab[100];
static int iteration = 0;
static int iiteration = 0;
static int jiteration = 0;
Ces variables globales sont utilisées pour stocker la dimension du tableau (dim), l'intervalle pour le délai d'animation (inter), le tableau lui-même (tab), et des indices pour les itérations de tri (iteration, iiteration, jiteration).

Fonctions d'affichage de tableau: 
void displayTab(GtkWidget *widget, int dim, float tab[dim], int pos);
void displayTabAnim(GtkWidget *widget, int dim, float tab[dim], int p, int j);
Ces fonctions sont utilisées pour afficher le tableau dans l'interface graphique avec des animations lors du tri à bulles.

Fonction de permutation: 
void permute(float *a, float *b);
Cette fonction est utilisée pour échanger les valeurs de deux éléments du tableau lors du tri à bulles.

Gestionnaires d'événements: 
gboolean delayed_animation(gpointer user_data);
gboolean delayed_i(gpointer user_data);
gboolean delayed_permute(gpointer user_data);
Ces fonctions sont appelées avec un délai pour simuler les étapes du tri à bulles.

Fonction de tri à bulles:
static void trier(GtkButton *button, gpointer data);
static void trier(GtkButton *button, gpointer data);
Cette fonction est appelée lorsqu'on clique sur le bouton "Tri à bulles". Elle initialise les variables et lance le processus de tri à bulles en appelant les fonctions de gestion d'événements.

Fonction de recherche :
static void rechvalider(GtkButton *button, gpointer data);
Cette fonction est appelée lorsqu'on clique sur le bouton "Go" après avoir saisi une valeur pour la recherche. Elle recherche la valeur dans le tableau et affiche le résultat.

Fonction de suppression:
static void suppvalider(GtkButton *button, gpointer data);
Cette fonction est appelée lorsqu'on clique sur le bouton "Go" après avoir saisi une valeur pour la suppression. Elle supprime la valeur du tableau et met à jour l'affichage.

Fonction d'insertion: 
static void insvalider(GtkButton *button, gpointer data);
Cette fonction est appelée lorsqu'on clique sur le bouton "Go" après avoir saisi la position et la valeur pour l'insertion. Elle insère la valeur à la position spécifiée dans le tableau.

Fonction de création du tableau avec des données aléatoires: 
static void createRand(GtkWidget *widget, gpointer data);

Fonction de création du tableau avec des données utilisateur: 
static void createUser(GtkWidget *widget, gpointer data);

Fonction principale:
int main(int argc, char **argv);
La fonction principale crée une application GTK, connecte les signaux aux gestionnaires d'événements, et lance l'application.

