#include <gtk/gtk.h>
#include "callbacks.h"
#include "interface.h"
#include "support.h"

#include <locale.h>
int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "fr_FR.UTF-8");  // Définit la locale en UTF-8
    GtkWidget *window;
  
  

    GtkWidget *RK_button_ajouter;
    GtkWidget *RK_button_afficher;
    GtkWidget *RK_button_affecter;
     GtkWidget *RK_button_modifier;
   
   
   
   
    


    // Initialiser GTK
    gtk_init(&argc, &argv);

    // Charger l'interface à partir du fichier Glade
    window = create_main_window();  // Cette fonction crée la fenêtre principale (main_window)
  
    RK_button_ajouter = lookup_widget(window, "RK_button_ajouter_main");
    RK_button_afficher = lookup_widget(window, "RK_button_afficher_main");
    RK_button_affecter=  lookup_widget(window,"RK_button_affecter_main");
       RK_button_modifier=  lookup_widget(window,"RK_button_modifier_main");

    

    // Afficher la fenêtre principale
    gtk_widget_show(window);
   


    // Démarrer la boucle principale de GTK
    gtk_main();

    return 0;
}

