
#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <string.h>
#include "callbacks.h"
#include "parking.h" 
#include "interface.h"
#include "support.h"


void on_RK_button_ajouter_main_clicked(GtkButton *button, gpointer user_data) {

    GtkWidget *add_parking_window;

   
    add_parking_window = create_add_parking_window(); 
 
  
    gtk_widget_show(add_parking_window);
}




void on_RK_button_modifier_main_clicked(GtkButton *button, gpointer user_data) {

    GtkWidget *edit_parking_window;

   
    edit_parking_window = create_edit_parking_window();  

    gtk_widget_show(edit_parking_window);
}


void on_RK_button_affecter_main_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *assign_agent_window;

    // Créer la fenêtre d'affectation à partir du fichier Glade
    assign_agent_window = create_assign_agent_window();  // Créer la fenêtre d'affectation



    // Récupérer le combobox depuis l'interface
    GtkWidget *RK_combobox_affecter_affecter = lookup_widget(assign_agent_window, "RK_combobox_affecter_affecter");

    // Charger les éléments du fichier texte dans le combobox
    load_combo_box_from_file(RK_combobox_affecter_affecter, "parking.txt");


   // Récupérer le combobox depuis l'interface
    GtkWidget *RK_comboboxentry2_affecter_affecter = lookup_widget(assign_agent_window, "RK_comboboxentry2_affecter_affecter");

    // Charger les éléments du fichier texte dans le combobox
    load_combo_box_from_file(RK_comboboxentry2_affecter_affecter, "agent.txt");


    // Afficher la fenêtre d'affectation
    gtk_widget_show(assign_agent_window);
}



void on_RK_button_supprimer_afficher_clicked(GtkButton *button, gpointer user_data) {

    GtkWidget *show_parkings_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    GtkWidget *treeview = lookup_widget(show_parkings_window, "RK_treeview_afficherparking_afficher");

    if (!treeview) {
        g_print("Erreur: TreeView non trouvé.\n");
        return;
    }

   
    GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
    GtkTreeModel *model;
    GtkTreeIter iter;

    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
       
        char *id_parking_str;
        gtk_tree_model_get(model, &iter, 0, &id_parking_str, -1);
        g_print("Parking sélectionné avec ID: %s\n", id_parking_str);

     
        int id_parking = atoi(id_parking_str);

      
        int result = supprimer_parking("parking.txt", id_parking);

        if (result) {
            g_print("Le parking avec ID %d a été supprimé avec succès.\n", id_parking);

          
            gtk_list_store_remove(GTK_LIST_STORE(model), &iter);
        } else {
            g_print("Erreur: Parking avec ID %d non trouvé.\n", id_parking);



            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(show_parkings_window),
                                                      GTK_DIALOG_MODAL,
                                                      GTK_MESSAGE_ERROR,
                                                      GTK_BUTTONS_OK,
                                                      "Le parking avec l'ID sélectionné n'a pas été trouvé.");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }

      
        g_free(id_parking_str);
    } else {
 
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(show_parkings_window),
                                                  GTK_DIALOG_MODAL,
                                                  GTK_MESSAGE_ERROR,
                                                  GTK_BUTTONS_OK,
                                                  "Veuillez sélectionner un parking à supprimer.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}




void on_RK_button_ajouter_ajouter_clicked(GtkWidget *objet_graphique, gpointer user_data) {
    GtkWidget *RK_button_ajouter_ajouter;
    RK_button_ajouter_ajouter = lookup_widget(objet_graphique, "RK_button_ajouter_ajouter");

    GtkWidget *input_id, *input_nom, *input_agent, *input_rue, *input_numero, *input_code_postal, *input_ville;
    GtkWidget *check_public, *check_prive, *check_residentiel, *check_commercial;
    GtkWidget *spin_nbr_places, *spin_nbr_placesreserve, *spin_nbr_etages, *input_type_acces;
    GtkWidget *check_camera, *check_alarme, *check_gardien, *check_eclairage;
    GtkWidget *spin_heure_debut, *spin_heure_fin, *combo_statut;
    GtkWidget *label_message;
    parking p;

    // Lookup des widgets
    input_id = lookup_widget(objet_graphique, "RK_entry_id_ajouter");
    input_nom = lookup_widget(objet_graphique, "RK_entry_nomparking_ajouter");
    input_agent = lookup_widget(objet_graphique, "RK_entry_nomagent_ajouter");
    input_rue = lookup_widget(objet_graphique, "RK_entry_rue_ajouter");
    input_numero = lookup_widget(objet_graphique, "RK_entry_num_ajouter");
    input_code_postal = lookup_widget(objet_graphique, "RK_entry_codepostal_ajouter");
    input_ville = lookup_widget(objet_graphique, "RK_entry_ville_ajouter");

    check_public = lookup_widget(objet_graphique, "RK_checkbutton_public_ajouter");
    check_prive = lookup_widget(objet_graphique, "RK_checkbutton_prive_ajouter");
    check_residentiel = lookup_widget(objet_graphique, "RK_checkbutton_residentiel_ajouter");
    check_commercial = lookup_widget(objet_graphique, "RK_checkbutton_commercial_ajouter");

    spin_nbr_places = lookup_widget(objet_graphique, "RK_spinbutton_nbplace_ajouter");
    spin_nbr_placesreserve = lookup_widget(objet_graphique, "RK_spinbutton_nbplacereserve_ajouter");
    spin_nbr_etages = lookup_widget(objet_graphique, "RK_spinbutton_nbetage_ajouter");
    input_type_acces = lookup_widget(objet_graphique, "RK_comboboxentry_typeacces_ajouter");

    check_camera = lookup_widget(objet_graphique, "RK_checkbutton_camera_ajouter");
    check_alarme = lookup_widget(objet_graphique, "RK_checkbutton_alarme_ajouter");
    check_gardien = lookup_widget(objet_graphique, "RK_checkbutton_gardien_ajouter");
    check_eclairage = lookup_widget(objet_graphique, "RK_checkbutton_eclairage_ajouter");

    spin_heure_debut = lookup_widget(objet_graphique, "RK_spinbutton_debut_ajouter");
    spin_heure_fin = lookup_widget(objet_graphique, "RK_spinbutton_fin_ajouter");
    combo_statut = lookup_widget(objet_graphique, "RK_comboboxentry_statut_ajouter");

    // Remplir la structure `parking`
    p.id = atoi(gtk_entry_get_text(GTK_ENTRY(input_id)));
    strcpy(p.nom, gtk_entry_get_text(GTK_ENTRY(input_nom)));
    strcpy(p.rue, gtk_entry_get_text(GTK_ENTRY(input_rue)));
    p.numero = atoi(gtk_entry_get_text(GTK_ENTRY(input_numero)));
    p.code_postal = atoi(gtk_entry_get_text(GTK_ENTRY(input_code_postal)));
    strcpy(p.ville, gtk_entry_get_text(GTK_ENTRY(input_ville)));

  

    // Type de parking
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_public))) {
        strcpy(p.type, "Public");
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_prive))) {
        strcpy(p.type, "Prive");
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_residentiel))) {
        strcpy(p.type, "Residentiel");
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_commercial))) {
        strcpy(p.type, "Commercial");
    }

    // Récupération des valeurs depuis les spinbuttons
    p.nbr_place_disponible = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_nbr_places));
    p.nbr_place_reserve = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_nbr_placesreserve));
    p.nbr_etages = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_nbr_etages));



    const gchar *text_acces = gtk_combo_box_get_active_text(GTK_COMBO_BOX(input_type_acces));
    strcpy(p.type_acces, text_acces ? text_acces : "");

    // Système de sécurité
    char systeme_securite[100] = "";
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_camera))) {
        strcat(systeme_securite, "Cameras ");
    }
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_alarme))) {
        strcat(systeme_securite, "Alarme ");
    }
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_gardien))) {
        strcat(systeme_securite, "Gardien ");
    }
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_eclairage))) {
        strcat(systeme_securite, "Eclairage ");
    }
    strcpy(p.systeme_securite, systeme_securite);



    // Heures
    sprintf(p.heure_debut, "%02d:00", gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_heure_debut)));
    sprintf(p.heure_fin, "%02d:00", gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_heure_fin)));

    // Statut
    const gchar *statut = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_statut));
    strcpy(p.statut_actuel, statut ? statut : "");

    // Agent
    strcpy(p.agent, "agent");


    // Ajout et message
    label_message = lookup_widget(objet_graphique, "RK_label_message_ajouter");

    if (ajouter_parking("parking.txt", p)) {
        gtk_label_set_text(GTK_LABEL(label_message), "Ajout avec succès !");
        printf("DEBUG - Parking ajouté avec succès.\n");
    } else {
        gtk_label_set_text(GTK_LABEL(label_message), "Erreur lors de l'ajout du parking.");
        printf("DEBUG - Échec de l'ajout du parking.\n");
    }
}



void on_RK_button_afficher_main_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *show_parkings_window;
    GtkWidget *treeview;
    GtkListStore *store;
    GtkTreeIter iter;

    show_parkings_window = create_show_parkings_window();
    gtk_widget_show(show_parkings_window);

    treeview = lookup_widget(show_parkings_window, "RK_treeview_afficherparking_afficher");

    // Créer un GtkListStore avec les 16 colonnes en G_TYPE_STRING pour afficher correctement les valeurs
    store = gtk_list_store_new(16, 
                               G_TYPE_STRING,  // ID
                               G_TYPE_STRING,  // Nom
                               G_TYPE_STRING,  // Rue
                               G_TYPE_STRING,  // Numéro
                               G_TYPE_STRING,  // Code postal
                               G_TYPE_STRING,  // Ville
                               G_TYPE_STRING,  // Type
                               G_TYPE_STRING,  // Nombre de places disponibles
                               G_TYPE_STRING,  // Nombre de places réservées
                               G_TYPE_STRING,  // Nombre d'étages
                               G_TYPE_STRING,  // Type d'accès
                               G_TYPE_STRING,  // Système de sécurité
                               G_TYPE_STRING,  // Heure de début
                               G_TYPE_STRING,  // Heure de fin
                               G_TYPE_STRING,  // Statut actuel
                               G_TYPE_STRING   // Agent
    );

    // Charger les données des parkings à partir du fichier texte
    parking parkings[100];  // Tableau pour stocker jusqu'à 100 parkings
    int count = charger_parkings(parkings, 100);  // Fonction à ajouter dans parking.c

    // Ajouter les parkings au GtkListStore
    for (int i = 0; i < count; i++) {
        gtk_list_store_append(store, &iter);

        // Conversion des entiers en chaînes de caractères
        char id_str[10], numero_str[10], code_postal_str[10], places_dispo_str[10], places_reserve_str[10], etages_str[10];
        snprintf(id_str, sizeof(id_str), "%d", parkings[i].id);
        snprintf(numero_str, sizeof(numero_str), "%d", parkings[i].numero);
        snprintf(code_postal_str, sizeof(code_postal_str), "%d", parkings[i].code_postal);
        snprintf(places_dispo_str, sizeof(places_dispo_str), "%d", parkings[i].nbr_place_disponible);
        snprintf(places_reserve_str, sizeof(places_reserve_str), "%d", parkings[i].nbr_place_reserve);
        snprintf(etages_str, sizeof(etages_str), "%d", parkings[i].nbr_etages);

        // Ajouter les données converties au store
        gtk_list_store_set(store, &iter,
                           0, id_str,
                           1, parkings[i].nom,
                           2, parkings[i].rue,
                           3, numero_str,
                           4, code_postal_str,
                           5, parkings[i].ville,
                           6, parkings[i].type,
                           7, places_dispo_str,
                           8, places_reserve_str,
                           9, etages_str,
                           10, parkings[i].type_acces,
                           11, parkings[i].systeme_securite,
                           12, parkings[i].heure_debut,
                           13, parkings[i].heure_fin,
                           14, parkings[i].statut_actuel,
                           15, parkings[i].agent,
                           -1);
    }

    // Ajouter les colonnes au TreeView
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *column;

    column = gtk_tree_view_column_new_with_attributes("ID", renderer, "text", 0, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", 1, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes("Rue", renderer, "text", 2, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes("Numéro", renderer, "text", 3, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes("Code Postal", renderer, "text", 4, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes("Ville", renderer, "text", 5, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes("Type", renderer, "text", 6, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes("Places Dispo", renderer, "text", 7, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes("Places Réservées", renderer, "text", 8, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes("Étages", renderer, "text", 9, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes("Accès", renderer, "text", 10, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes("Sécurité", renderer, "text", 11, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes("Heure Début", renderer, "text", 12, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes("Heure Fin", renderer, "text", 13, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes("Statut", renderer, "text", 14, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    column = gtk_tree_view_column_new_with_attributes("Agent", renderer, "text", 15, NULL);
    gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

    // Associer le store au TreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
    g_object_unref(store);  // Libérer la mémoire allouée
}





void load_combo_box_from_file(GtkWidget *combobox1, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        g_print("Erreur: Impossible d'ouvrir le fichier %s\n", filename);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // Supprimer le '\n' de la fin de chaque ligne
        line[strcspn(line, "\n")] = 0;

        // Extraire le premier élément avant la virgule
        char *token = strtok(line, ",");  // On sépare par la virgule

        if (token) {
            // Ajouter la première colonne dans le ComboBox
            gtk_combo_box_append_text(GTK_COMBO_BOX(combobox1), token);
        }
    }

    fclose(file);
}





void load_combo_box_from_file_for_agents(GtkWidget *combobox1, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        g_print("Erreur: Impossible d'ouvrir le fichier %s\n", filename);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // Supprimer le '\n' de la fin de chaque ligne
        line[strcspn(line, "\n")] = 0;

        // Extraire le premier élément avant la virgule
        char *token = strtok(line, ",");  // On sépare par la virgule

        if (token) {
            // Ajouter la première colonne dans le ComboBox
            gtk_combo_box_append_text(GTK_COMBO_BOX(combobox1), token);
        }
    }

    fclose(file);
}



void on_RK_button_affecter_affecter_clicked(GtkWidget *widget, gpointer data) {
    // Récupérer les widgets
    GtkComboBox *combo_parking = GTK_COMBO_BOX(lookup_widget(widget, "RK_combobox_affecter_affecter"));
    GtkComboBox *combo_agent = GTK_COMBO_BOX(lookup_widget(widget, "RK_comboboxentry2_affecter_affecter"));
    GtkWidget *label_message = lookup_widget(widget, "RK_label_message_affecter");

    if (combo_parking == NULL || combo_agent == NULL || label_message == NULL) {
        g_print("Erreur: Widgets non récupérés.\n");
        return;
    }

    // Récupérer les sélections
    const char *parking_id = gtk_combo_box_get_active_text(combo_parking);
    const char *agent_name = gtk_combo_box_get_active_text(combo_agent);

    if (parking_id == NULL || agent_name == NULL || strlen(parking_id) == 0 || strlen(agent_name) == 0) {
        gtk_label_set_text(GTK_LABEL(label_message), "Erreur : Sélectionnez un parking et un agent.");
        return;
    }

    // Appeler la fonction d'affectation
    int result = affecter_agent_au_parking(parking_id, agent_name);

    // Gestion des résultats
    if (result == 1) {
        gtk_label_set_text(GTK_LABEL(label_message), "Affectation réussie : L'agent a été assigné au parking.");
    } else if (result == -1) {
        gtk_label_set_text(GTK_LABEL(label_message), "Erreur : L'agent est déjà affecté à un autre parking.");
    } else {
        gtk_label_set_text(GTK_LABEL(label_message), "Erreur : Impossible d'affecter l'agent au parking.");
    }
}



void on_RK_button_chercher_modifier_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *entry_id_modifier; 
    GtkWidget *label_result_modifier;
    const char *id_value;
    char buffer[256];
    int found = 0;

    // Récupération des widgets
    entry_id_modifier = lookup_widget(GTK_WIDGET(button), "RK_entry_id_modifier");
    label_result_modifier = lookup_widget(GTK_WIDGET(button), "RK_label_label_modifier");

    if (entry_id_modifier && label_result_modifier) {
        id_value = gtk_entry_get_text(GTK_ENTRY(entry_id_modifier));

        if (id_value && strlen(id_value) > 0) {
            FILE *file = fopen("parking.txt", "r");
            if (file) {
                while (fgets(buffer, sizeof(buffer), file)) {
                    char id[256];
                    sscanf(buffer, "%255[^,]", id); // Lire l'ID de la première colonne
                    if (strcmp(id, id_value) == 0) {
                        found = 1;
                        break;
                    }
                }
                fclose(file);
            } else {
                printf("Erreur: Impossible d'ouvrir le fichier parking.txt\n");
            }

            if (found) {
                // Afficher un message de succès dans le label
                gtk_label_set_text(GTK_LABEL(label_result_modifier), "ID trouvé : Veuillez modifier le parking.");

                printf("ID trouvé : Veuillez modifier le parking.\n");

                // Vérifier si le signal est déjà connecté pour éviter les doublons
                if (!g_signal_handlers_block_matched(button, G_SIGNAL_MATCH_FUNC, 0, 0, NULL, G_CALLBACK(on_RK_button_modifier_modifier_clicked), NULL)) {
                    gpointer user_data_id = g_strdup(id_value);  // Allouer une copie de l'ID
                    g_signal_connect(button, "clicked", G_CALLBACK(on_RK_button_modifier_modifier_clicked), user_data_id);
                }
            } else {
                // Afficher un message d'erreur dans le label
                gtk_label_set_text(GTK_LABEL(label_result_modifier), "ID non trouvé.");
                
                printf("ID non trouvé.\n");
            }
        } else {
            // Afficher un message d'erreur dans le label si l'ID est vide
            gtk_label_set_text(GTK_LABEL(label_result_modifier), "Veuillez entrer un ID valide.");
            
            printf("Veuillez entrer un ID valide.\n");
        }
    } else {
        printf("Erreur: Impossible de récupérer les widgets.\n");
    }
}


void on_RK_button_modifier_modifier_clicked(GtkWidget *button, gpointer user_data) {
    // Récupérer l'ID du parking depuis le champ de saisie
    GtkWidget *entry_id = lookup_widget(GTK_WIDGET(button), "RK_entry_id_modifier");
    const char *id_recherche = gtk_entry_get_text(GTK_ENTRY(entry_id));

    if (strlen(id_recherche) == 0) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Veuillez entrer un ID valide.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    // Convertir l'ID en entier
    int id_parking = atoi(id_recherche);
    g_print("ID Parking : %d\n", id_parking);  // Débogage : Affichage de l'ID récupéré

    GtkWidget *input_nom, *input_rue, *input_numero, *input_code_postal, *input_ville;
    GtkWidget *check_public, *check_prive, *check_residentiel, *check_commercial;
    GtkWidget *spin_nbr_places,*spin_nbr_placesreserve, *spin_nbr_etages, *input_type_acces;
    GtkWidget *check_camera, *check_alarme, *check_gardien, *check_eclairage;
    GtkWidget *spin_heure_debut, *spin_heure_fin, *combo_statut;
    parking p;

    // Récupération des widgets
    input_nom = lookup_widget(button, "RK_entry_nomparking_modifier");
    input_rue = lookup_widget(button, "RK_entry_rue_modifier");
    input_numero = lookup_widget(button, "RK_entry_num_modifier");
    input_code_postal = lookup_widget(button, "RK_entry_codepostal_modifier");
    input_ville = lookup_widget(button, "RK_entry_ville_modifier");

    check_public = lookup_widget(button, "RK_checkbutton_public_modifier");
    check_prive = lookup_widget(button, "RK_checkbutton_prive_modifier");
    check_residentiel = lookup_widget(button, "RK_checkbutton_residentiel_modifier");
    check_commercial = lookup_widget(button, "RK_checkbutton_commercial_modifier");

    spin_nbr_places = lookup_widget(button, "RK_spinbutton_nbplace_modifier");
    spin_nbr_etages = lookup_widget(button, "RK_spinbutton_nbetage_modifier");
    input_type_acces = lookup_widget(button, "RK_comboboxentry_typeacces_modifier");

    spin_nbr_placesreserve =  lookup_widget(button, "RK_spinbutton_nbplacereservee_modifier");

    check_camera = lookup_widget(button, "RK_checkbutton_camera_modifier");
    check_alarme = lookup_widget(button, "RK_checkbutton_alarme_modifier");
    check_gardien = lookup_widget(button, "RK_checkbutton_gardien_modifier");
    check_eclairage = lookup_widget(button, "RK_checkbutton_eclairage_modifier");

    spin_heure_debut = lookup_widget(button, "RK_spinbutton_debut_modifier");
    spin_heure_fin = lookup_widget(button, "RK_spinbutton_fin_modifier");
    combo_statut = lookup_widget(button, "RK_comboboxentry_statut_modifier");

    // Récupérer les données des widgets pour remplir la structure parking
    strcpy(p.nom, gtk_entry_get_text(GTK_ENTRY(input_nom)));
    g_print("Nom du parking : %s\n", p.nom);  // Débogage : Affichage du nom du parking

    strcpy(p.agent, "agent");  // L'agent est maintenant fixé à "agent"
    strcpy(p.rue, gtk_entry_get_text(GTK_ENTRY(input_rue)));
    g_print("Rue : %s\n", p.rue);  // Débogage : Affichage de la rue

    p.numero = atoi(gtk_entry_get_text(GTK_ENTRY(input_numero)));
    g_print("Numéro : %d\n", p.numero);  // Débogage : Affichage du numéro

    p.code_postal = atoi(gtk_entry_get_text(GTK_ENTRY(input_code_postal)));
    g_print("Code postal : %d\n", p.code_postal);  // Débogage : Affichage du code postal

    strcpy(p.ville, gtk_entry_get_text(GTK_ENTRY(input_ville)));
    g_print("Ville : %s\n", p.ville);  // Débogage : Affichage de la ville

    // Vérification des types
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_public))) {
        strcpy(p.type, "Public");
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_prive))) {
        strcpy(p.type, "Privé");
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_residentiel))) {
        strcpy(p.type, "Résidentiel");
    } else if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_commercial))) {
        strcpy(p.type, "Commercial");
    }
    g_print("Type : %s\n", p.type);  // Débogage : Affichage du type de parking

    p.nbr_place_disponible = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_nbr_places));
    g_print("Nombre de places disponibles : %d\n", p.nbr_place_disponible);  // Débogage : Nombre de places


    p.nbr_place_reserve = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_nbr_placesreserve));

    p.nbr_etages = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_nbr_etages));
    g_print("Nombre d'étages : %d\n", p.nbr_etages);  // Débogage : Nombre d'étages

    const gchar *text_acces = gtk_combo_box_get_active_text(GTK_COMBO_BOX(input_type_acces));
    strcpy(p.type_acces, text_acces);
    g_print("Type d'accès : %s\n", p.type_acces);  // Débogage : Type d'accès

    // Sécurités
    char systeme_securite[100] = "";
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_camera))) {
        strcat(systeme_securite, "Caméras ");
    }
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_alarme))) {
        strcat(systeme_securite, "Alarme ");
    }
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_gardien))) {
        strcat(systeme_securite, "Gardien ");
    }
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_eclairage))) {
        strcat(systeme_securite, "Éclairage ");
    }
    strcpy(p.systeme_securite, systeme_securite);
    g_print("Système de sécurité : %s\n", p.systeme_securite);  // Débogage : Affichage du système de sécurité

    sprintf(p.heure_debut, "%02d:00", gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_heure_debut)));
    sprintf(p.heure_fin, "%02d:00", gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin_heure_fin)));
    g_print("Heure début : %s, Heure fin : %s\n", p.heure_debut, p.heure_fin);  // Débogage : Heures

    const gchar *statut = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo_statut));
    strcpy(p.statut_actuel, statut);
    g_print("Statut actuel : %s\n", p.statut_actuel);  // Débogage : Affichage du statut actuel

    // Appeler la fonction de modification
    if (modifier_parking("parking.txt", id_parking, p)) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_INFO,
                                                   GTK_BUTTONS_OK,
                                                   "Modification réussie !");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    } else {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                   GTK_DIALOG_MODAL,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Erreur lors de la modification.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}






void on_RK_button_annuler_ajouter_clicked(GtkWidget *button) {
    // Récupérer la fenêtre parente (la fenêtre principale qui contient le bouton)
    GtkWidget *add_parking_window = gtk_widget_get_toplevel(button);
    
    // Vérifier si l'objet est bien une fenêtre
    if (GTK_IS_WINDOW(add_parking_window)) {
        gtk_widget_destroy(add_parking_window); // Fermer la fenêtre
    }
}


void on_RK_button_annuler_modifier_clicked(GtkWidget *button) {
    // Récupérer la fenêtre parente (la fenêtre principale qui contient le bouton)
    GtkWidget *edit_parking_window = gtk_widget_get_toplevel(button);
    
    // Vérifier si l'objet est bien une fenêtre
    if (GTK_IS_WINDOW(edit_parking_window)) {
        gtk_widget_destroy(edit_parking_window); // Fermer la fenêtre
    }
}


void on_RK_button_annuler_affecter_clicked(GtkWidget *button) {
    // Récupérer la fenêtre parente (la fenêtre principale qui contient le bouton)
    GtkWidget *assign_agent_window = gtk_widget_get_toplevel(button);
    
    // Vérifier si l'objet est bien une fenêtre
    if (GTK_IS_WINDOW(assign_agent_window)) {
        gtk_widget_destroy(assign_agent_window); // Fermer la fenêtre
    }
}




void on_RK_button_fermer_afficher_clicked(GtkWidget *button) {
    // Récupérer la fenêtre parente (la fenêtre principale qui contient le bouton)
    GtkWidget *show_parkings_window = gtk_widget_get_toplevel(button);
    
    // Vérifier si l'objet est bien une fenêtre
    if (GTK_IS_WINDOW(show_parkings_window)) {
        gtk_widget_destroy(show_parkings_window); // Fermer la fenêtre
    }
}




