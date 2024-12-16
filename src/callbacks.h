#include <gtk/gtk.h>

void on_RK_button_ajouter_ajouter_clicked(GtkWidget *objet_graphique, gpointer user_data);
void on_RK_button_afficher_main_clicked(GtkButton *button, gpointer user_data);
void on_RK_button_ajouter_main_clicked(GtkButton *button, gpointer user_data) ;



void on_RK_button_supprimer_afficher_clicked(GtkButton *button, gpointer user_data) ;







void on_RK_button_affecter_main_clicked(GtkButton *button, gpointer user_data) ;

void load_combo_box_from_file(GtkWidget *combobox1, const char *filename);
void RK_combobox_affecter_affecter(GtkWidget *combobox1, const char *filename);
void load_combo_box_from_file_for_agents(GtkWidget *combobox1, const char *filename);

void on_RK_button_affecter_affecter_clicked(GtkWidget *widget, gpointer data);
void on_RK_button_modifier_main_clicked(GtkButton *button, gpointer user_data);






void
on_RK_button_chercher_modifier_clicked (GtkButton       *button,
                                        gpointer         user_data);
void on_RK_button_modifier_modifier_clicked(GtkWidget *button, gpointer user_data);


void on_RK_button_annuler_ajouter_clicked(GtkWidget *button) ;
void on_RK_button_annuler_modifier_clicked(GtkWidget *button);
void on_RK_button_fermer_afficher_clicked(GtkWidget *button);



void on_RK_button_annuler_affecter_clicked(GtkWidget *button) ;
