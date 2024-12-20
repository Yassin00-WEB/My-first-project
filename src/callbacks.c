#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "service.h"

//pour password Yassine

void on_button1_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *Username_input, *Password_input, *window3;
    char Username[21], Password[21];
    char stored_Username[21], stored_Password[21];
    int found = 0;

    Username_input = lookup_widget(GTK_WIDGET(button), "entry_Username");
    Password_input = lookup_widget(GTK_WIDGET(button), "entry_Password");

    if (!Username_input || !Password_input) {
        g_print("Erreur : Widgets introuvables.\n");
        return;
    }

    gtk_entry_set_visibility(GTK_ENTRY(Password_input), FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(Password_input), '*');

    strncpy(Username, gtk_entry_get_text(GTK_ENTRY(Username_input)), sizeof(Username) - 1);
    Username[sizeof(Username) - 1] = '\0';

    strncpy(Password, gtk_entry_get_text(GTK_ENTRY(Password_input)), sizeof(Password) - 1);
    Password[sizeof(Password) - 1] = '\0';

    FILE *f = fopen("utilisateurs.txt", "r");
    if (f == NULL) {
        g_print("Erreur : Impossible d'ouvrir le fichier utilisateurs.txt.\n");
        return;
    }

    while (fscanf(f, "%*s %*s %20s %20s %*s\n", stored_Username, stored_Password) == 2) {
        if (strcmp(Username, stored_Username) == 0 && strcmp(Password, stored_Password) == 0) {
            found = 1;
            break;
        }
    }

    fclose(f);

    GtkWidget *dialog;
    if (found) {
        g_print("Connexion réussie ! Bienvenue %s.\n", Username);
        window3 = create_window3(); 
        gtk_widget_show(window3); 

        dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_INFO,
                                        GTK_BUTTONS_OK,
                                        "Connexion réussie ! Bienvenue %s.", Username);
    } else {
        g_print("Erreur : Nom d'utilisateur ou mot de passe incorrect.\n");

        dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_ERROR,
                                        GTK_BUTTONS_OK,
                                        "Nom d'utilisateur ou mot de passe incorrect.");
    }

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}



void on_button2_clicked(GtkButton *button, gpointer user_data) {
    typedef struct {
        char id_service[21];
        char type_de_transport[50];
        int numero_de_place;
        int numero_de_matricule;
        char type_de_service[50];
    } Service;

    GtkWidget *input3;
    char id_service3[21] = "";
    char buffer[256];  // Déclaration de la variable buffer
    Service serv;
    int id_found = 0;

    input3 = lookup_widget(GTK_WIDGET(button), "entry3");
    if (!input3) {
        g_print("Erreur : Le widget 'entry3' n'a pas été trouvé.\n");
        return;
    }

    strncpy(id_service3, gtk_entry_get_text(GTK_ENTRY(input3)), sizeof(id_service3) - 1);
    g_strstrip(id_service3);
    id_service3[sizeof(id_service3) - 1] = '\0';

    if (strlen(id_service3) == 0) {
        g_print("Erreur : L'entrée ID de service est vide.\n");
        return;
    }

    g_print("ID Service saisi: '%s'\n", id_service3);

    FILE *fichier = fopen("services.txt", "r");
    if (fichier == NULL) {
        g_print("Erreur : Impossible d'ouvrir le fichier 'services.txt'.\n");
        return;
    }

    while (fgets(buffer, sizeof(buffer), fichier) != NULL) {
        if (sscanf(buffer, "%20s %49s %d %d %49s",
                  serv.id_service,
                  serv.type_de_transport,
                  &serv.numero_de_place,
                  &serv.numero_de_matricule,
                  serv.type_de_service) == 5) {
            if (strcmp(serv.id_service, id_service3) == 0) {
                id_found = 1;
                g_print("Service trouvé :\n");
                g_print("ID Service        : %s\n", serv.id_service);
                g_print("Type de Transport : %s\n", serv.type_de_transport);
                g_print("Nombre de Places  : %d\n", serv.numero_de_place);
                g_print("Numéro Matricule  : %d\n", serv.numero_de_matricule);
                g_print("Type de Service   : %s\n", serv.type_de_service);

                GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                           GTK_DIALOG_DESTROY_WITH_PARENT,
                                                           GTK_MESSAGE_INFO,
                                                           GTK_BUTTONS_OK,
                                                           "Service trouvé :\n\n"
                                                           "ID Service        : %s\n"
                                                           "Type de Transport : %s\n"
                                                           "Nombre de Places  : %d\n"
                                                           "Numéro Matricule  : %d\n"
                                                           "Type de Service   : %s",
                                                           serv.id_service,
                                                           serv.type_de_transport,
                                                           serv.numero_de_place,
                                                           serv.numero_de_matricule,
                                                           serv.type_de_service);
                gtk_dialog_run(GTK_DIALOG(dialog));
                gtk_widget_destroy(dialog);
            }
        } else {
            g_print("Erreur : Ligne mal formatée ignorée : %s\n", buffer);
        }
    }

    fclose(fichier);

    if (!id_found) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Aucun service avec cet ID trouvé.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}


//yassine
void on_button3_clicked(GtkButton *button, gpointer user_data) {

    GtkNotebook *notebook; 
    notebook = GTK_NOTEBOOK(lookup_widget(GTK_WIDGET(button), "notebook1"));
    gtk_notebook_set_current_page(notebook, 3);
}


void
on_button4_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "treeview_service");
    GtkListStore *store;
    GtkTreeModel *model;
    GtkTreeIter iter;
    GtkTreeSelection *selection;
    GtkTreePath *path;

    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));

    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        store = GTK_LIST_STORE(model);
        gtk_list_store_remove(store, &iter);
    } else {
        printf("Aucune ligne sélectionnée pour suppression\n");
    }
}
//yassine
void
on_button5_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
    typedef struct {
        int id_service;
        char type_de_transport[50];
        int numero_de_place;
        int numero_de_matricule;
        char type_de_service[50];
        char type_de_place[50];
        char presidentielle[50];
        char handicap[50];
    } Service;

    GtkWidget *treeview = lookup_widget(GTK_WIDGET(button), "treeview_service");
    GtkListStore *store;
    GtkTreeIter iter;
    Service services;
    FILE *f;
    char buffer[256]; 

    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)));
    if (store != NULL) {
        gtk_list_store_clear(store);
    }

    f = fopen("services.txt", "r");
    if (f == NULL) {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier services.txt\n");
        return;
    }

    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        if (sscanf(buffer, "%d %49s %d %d %49s %49s %49s %49s",
                   &services.id_service, services.type_de_transport, &services.numero_de_place,
                   &services.numero_de_matricule, services.type_de_service,
                   services.type_de_place, services.presidentielle,
                   services.handicap) == 8) {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                               0, services.id_service,
                               1, services.type_de_transport,
                               2, services.numero_de_place,
                               3, services.numero_de_matricule,
                               4, services.type_de_service,
                               5, services.type_de_place,
                               6, services.presidentielle,
                               7, services.handicap,
                               -1);
        } else {
            fprintf(stderr, "Erreur : Ligne mal formatée ignorée : %s\n", buffer);
        }
    }

    fclose(f);
}


//supprimer yassine

void on_button7_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *entry_id_service3;
    char id_service3[21], buffer[256], id_to_check[21];
    int found = 0;

    entry_id_service3 = lookup_widget(GTK_WIDGET(button), "entry_id_service3");
    if (!entry_id_service3) {
        g_print("Erreur : Widget non trouvé.\n");
        return;
    }

    strncpy(id_service3, gtk_entry_get_text(GTK_ENTRY(entry_id_service3)), sizeof(id_service3) - 1);
    id_service3[sizeof(id_service3) - 1] = '\0';
    g_strstrip(id_service3);

    if (strlen(id_service3) == 0) {
        g_print("Erreur : Le champ ID Service est vide.\n");
        return;
    }

    FILE *f = fopen("services.txt", "r");
    FILE *temp = fopen("services_temp.txt", "w");
    if (!f || !temp) {
        g_print("Erreur : Impossible d'ouvrir les fichiers.\n");
        if (f) fclose(f);
        if (temp) fclose(temp);
        return;
    }

    while (fgets(buffer, sizeof(buffer), f)) {
        if (sscanf(buffer, "%s", id_to_check) == 1) {
            if (strcmp(id_service3, id_to_check) == 0) {
                found = 1;
            } else {
                fprintf(temp, "%s", buffer);
            }
        } else {
            fprintf(temp, "%s", buffer);
        }
    }

    fclose(f);
    fclose(temp);
     if (found) {
        if (remove("services.txt") == 0 && rename("services_temp.txt", "services.txt") == 0) {
            g_print("Entrées supprimées avec succès !\n");

            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                       GTK_DIALOG_DESTROY_WITH_PARENT,
                                                       GTK_MESSAGE_INFO,
                                                       GTK_BUTTONS_OK,
                                                       "Le service avec cet ID a été supprimé.");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        } else {
            g_print("Erreur : Impossible de mettre à jour le fichier principal.\n");
            remove("services_temp.txt");
        }
    } else {
        remove("services_temp.txt");
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Aucun service avec cet ID trouvé.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

//yassine
int selection = -1; 
int option = -1;

void on_checkbutton3_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
       option = 0; 
       
    }
}

void on_checkbutton4_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        option = 1;
   
    }
}

//pour la bouton radio yassine

void on_radiobutton3_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        selection = 0; 
      
    }
}

void on_radiobutton4_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        selection = 1; 
        
    }
}

//ajouter yassine
void on_button8_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *input1, *input2, *combo1, *combo2, *spin;
    char id_service[21] = "", matricule[21] = "", type_transport[50] = "Non défini", type_service[50] = "Non défini";
    int valeur_spin = 0;

    input1 = lookup_widget(GTK_WIDGET(button), "entry_id_service1");
    input2 = lookup_widget(GTK_WIDGET(button), "entry_matricule1");
    combo1 = lookup_widget(GTK_WIDGET(button), "combobox3");
    combo2 = lookup_widget(GTK_WIDGET(button), "combobox4");
    spin = lookup_widget(GTK_WIDGET(button), "spinButton_place2");

    if (!input1 || !input2 || !combo1 || !combo2 || !spin) {
        g_print("Erreur : Un ou plusieurs widgets n'ont pas été trouvés.\n");
        return;
    }

    strncpy(id_service, gtk_entry_get_text(GTK_ENTRY(input1)), sizeof(id_service) - 1);
    id_service[sizeof(id_service) - 1] = '\0';

    strncpy(matricule, gtk_entry_get_text(GTK_ENTRY(input2)), sizeof(matricule) - 1);
    matricule[sizeof(matricule) - 1] = '\0';

    const char *text1 = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo1));
    const char *text2 = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo2));

    if (text1 != NULL) {
        strncpy(type_transport, text1, sizeof(type_transport) - 1);
        type_transport[sizeof(type_transport) - 1] = '\0';
    } else {
        g_print("Aucun élément sélectionné dans ComboBox3. Valeur par défaut : 'Non défini'.\n");
    }

    if (text2 != NULL) {
        strncpy(type_service, text2, sizeof(type_service) - 1);
        type_service[sizeof(type_service) - 1] = '\0';
    } else {
        g_print("Aucun élément sélectionné dans ComboBox4. Valeur par défaut : 'Non défini'.\n");
    }

    valeur_spin = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin));

    if (strlen(id_service) == 0 || strlen(matricule) == 0) {
        g_print("Erreur : Les champs 'ID Service' et 'Matricule' doivent être remplis.\n");
        return;
    }

    g_print("ID Service : %s\n", id_service);
    g_print("Matricule : %s\n", matricule);
    g_print("Type de transport : %s\n", type_transport);
    g_print("Type de service : %s\n", type_service);
    g_print("Nombre de places : %d\n", valeur_spin);

    FILE *f = fopen("services.txt", "a");
    GtkWidget *dialog;
    if (f != NULL) {
        fprintf(f, "%s %s %d %s %s ", id_service, type_transport, valeur_spin, matricule, type_service);

        if (selection == 0) {
            fprintf(f, "Premium ");
        } else if (selection == 1) {
            fprintf(f, "Normal ");
        }

        if (option == 0) {
            fprintf(f, "Presidentielle\n");
        } else if (option == 1) {
            fprintf(f, "Handicap\n");
        }
        fclose(f);
        g_print("Ajout enregistré avec succès !\n");

        dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_INFO,
                                        GTK_BUTTONS_OK,
                                        "L'ajout a été enregistré avec succès !");
    } else {
        g_print("Erreur : Impossible d'ouvrir le fichier.\n");

        dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_ERROR,
                                        GTK_BUTTONS_OK,
                                        "Erreur : Impossible d'ouvrir le fichier.");
    }

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
// yassine accée rapide
void on_button10_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *input1, *combo2;
    char id_service[21] = "", type_service[50] = "Non défini";

    input1 = lookup_widget(GTK_WIDGET(button), "YZ_entry11");
    combo2 = lookup_widget(GTK_WIDGET(button), "combobox5");

    if (!input1 || !combo2) {
        g_print("Erreur : Un ou plusieurs widgets n'ont pas été trouvés.\n");
        return;
    }

    strncpy(id_service, gtk_entry_get_text(GTK_ENTRY(input1)), sizeof(id_service) - 1);
    id_service[sizeof(id_service) - 1] = '\0'; 

    const char *text1 = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo2));
    if (text1 != NULL) {
        strncpy(type_service, text1, sizeof(type_service) - 1);
        type_service[sizeof(type_service) - 1] = '\0';
    } else {
        g_print("Aucun élément sélectionné dans ComboBox5. Valeur par défaut : 'Non défini'.\n");
    }

    g_print("ID Service : %s, Type de service : %s\n", id_service, type_service);

    FILE *f = fopen("Accées_Rapide.txt", "a"); 
    if (f == NULL) {
        g_print("Erreur : Impossible d'ouvrir le fichier services.txt.\n");
        return;
    }

    fprintf(f,"%s %s: Réservation_enregistrée_avec_succés\n", id_service, type_service);
    fclose(f);

    g_print("Service réservé et enregistré.\n");
    
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                               GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_INFO,
                                               GTK_BUTTONS_OK,
                                               "Service été enregistrée avec succès !");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

//affectation yassine
void on_button11_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *input1, *input2;
    char id_service[21] = "", id_reservation[21] = "";

    input1 = lookup_widget(GTK_WIDGET(button), "YZ_entry12");
    input2 = lookup_widget(GTK_WIDGET(button), "YZ_entry13");

    if (!input1 || !input2) {
        g_print("Erreur : Un ou plusieurs widgets n'ont pas été trouvés.\n");
        return;
    }

    strncpy(id_service, gtk_entry_get_text(GTK_ENTRY(input1)), sizeof(id_service) - 1);
    id_service[sizeof(id_service) - 1] = '\0';

    strncpy(id_reservation, gtk_entry_get_text(GTK_ENTRY(input2)), sizeof(id_reservation) - 1);
    id_reservation[sizeof(id_reservation) - 1] = '\0';

    if (strlen(id_service) == 0 || strlen(id_reservation) == 0) {
        g_print("Erreur : Les champs ne doivent pas être vides.\n");
        return;
    }

    FILE *file = fopen("Affectation.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s %s: Affectation_avec_succés\n", id_service, id_reservation);
        fclose(file);
        g_print("Données enregistrées avec succès.\n");

        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_INFO,
                                                   GTK_BUTTONS_OK,
                                                   "L'affectation a été enregistrée avec succès !");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    } else {
        g_print("Erreur : Impossible d'ouvrir le fichier.\n");
    }
}
//yassine
void on_button12_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *input1, *input2;
    char id_service[21] = "", id_reservation[21] = "";

    input1 = lookup_widget(GTK_WIDGET(button), "YZ_entry12");
    input2 = lookup_widget(GTK_WIDGET(button), "YZ_entry13");

    if (!input1 || !input2) {
        g_print("Erreur : Un ou plusieurs widgets n'ont pas été trouvés.\n");
        return;
    }

    gtk_entry_set_text(GTK_ENTRY(input1), "");
    gtk_entry_set_text(GTK_ENTRY(input2), "");

    g_print("Les champs ont été réinitialisés avec succès.\n");
}

// pou ajouter un admin yassine
void on_button13_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *input1, *input2, *input3, *input4, *input5;
    char Nom[21], Prenom[21], Username[21], Password[21], Role[3];

    input1 = lookup_widget(GTK_WIDGET(button), "entry_Nom");
    input2 = lookup_widget(GTK_WIDGET(button), "entry_Prenom");
    input3 = lookup_widget(GTK_WIDGET(button), "entry_Username");
    input4 = lookup_widget(GTK_WIDGET(button), "entry_Password");

    if (!input1 || !input2 || !input3 || !input4) {
        g_print("Erreur : Un ou plusieurs widgets n'ont pas été trouvés.\n");
        return;
    }

    strncpy(Nom, gtk_entry_get_text(GTK_ENTRY(input1)), sizeof(Nom) - 1);
    Nom[sizeof(Nom) - 1] = '\0';

    strncpy(Prenom, gtk_entry_get_text(GTK_ENTRY(input2)), sizeof(Prenom) - 1);
    Prenom[sizeof(Prenom) - 1] = '\0';

    strncpy(Username, gtk_entry_get_text(GTK_ENTRY(input3)), sizeof(Username) - 1);
    Username[sizeof(Username) - 1] = '\0';

    strncpy(Password, gtk_entry_get_text(GTK_ENTRY(input4)), sizeof(Password) - 1);
    Password[sizeof(Password) - 1] = '\0';

    FILE *f = fopen("utilisateurs.txt", "a");
    if (f != NULL) {
        fprintf(f, "%s %s %s %s %s\n", Nom, Prenom, Username, Password, Role);
        fclose(f);
        g_print("Utilisateur ajouté avec succès !\n");
    } else {
        g_print("Erreur : Impossible d'ouvrir le fichier.\n");
    }
}
//yassine
int selection1 = -1; 
int option1 = -1;

void on_YZ_checkbutton1_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
       option1 = 0; 
       
    }
}

void on_YZ_checkbutton2_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        option1 = 1;
   
    }
}

//pour la bouton radio yassine

void on_YZ_radiobutton1_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        selection1 = 0; 
      
    }
}

void on_YZ_radiobutton2_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    if (gtk_toggle_button_get_active(togglebutton)) {
        selection1 = 1; 
        
    }
}
// modifier yassine

void on_button6_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *input1, *input2, *combo1, *combo2, *spin;
    char id_service[21], matricule[21], type_transport[50] = "Non défini", type_service[50] = "Non défini";
    int valeur_spin, found = 0;

    input1 = lookup_widget(GTK_WIDGET(button), "entry_id_service");
    input2 = lookup_widget(GTK_WIDGET(button), "entry_matricule");
    combo1 = lookup_widget(GTK_WIDGET(button), "combobox1");
    combo2 = lookup_widget(GTK_WIDGET(button), "combobox2");
    spin = lookup_widget(GTK_WIDGET(button), "spinButton_place");

    if (!input1 || !input2 || !combo1 || !combo2 || !spin) {
        g_print("Erreur : Widgets manquants.\n");
        return;
    }

    strncpy(id_service, gtk_entry_get_text(GTK_ENTRY(input1)), sizeof(id_service) - 1);
    id_service[sizeof(id_service) - 1] = '\0';

    strncpy(matricule, gtk_entry_get_text(GTK_ENTRY(input2)), sizeof(matricule) - 1);
    matricule[sizeof(matricule) - 1] = '\0';

    const char *selected_transport = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo1));
    const char *selected_service = gtk_combo_box_get_active_text(GTK_COMBO_BOX(combo2));

    if (selected_transport != NULL) {
        strncpy(type_transport, selected_transport, sizeof(type_transport) - 1);
    } else {
        g_print("Erreur : Aucun élément sélectionné dans le ComboBox Transport.\n");
    }

    if (selected_service != NULL) {
        strncpy(type_service, selected_service, sizeof(type_service) - 1);
    } else {
        g_print("Erreur : Aucun élément sélectionné dans le ComboBox Service.\n");
    }

    valeur_spin = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin));

    if (strlen(id_service) == 0) {
        g_print("Erreur : Le champ 'ID Service' est obligatoire.\n");
        return;
    }

    FILE *f = fopen("services.txt", "r");
    FILE *temp = fopen("services_temp.txt", "w");
    if (!f || !temp) {
        g_print("Erreur : Impossible d'ouvrir les fichiers.\n");
        if (f) fclose(f);
        if (temp) fclose(temp);
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), f)) {
        if (strstr(buffer, id_service)) {
            found = 1;
             fprintf(temp, "%s %s %d %s %s ", id_service, type_transport, valeur_spin, matricule, type_service);

            if (selection1 == 0) {
                fprintf(temp, "Premium ");
            } else if (selection1 == 1) {
                fprintf(temp, "Normal ");
            }

            if (option1 == 0) {
                fprintf(temp, "Presidentielle\n");
            } else if (option1 == 1) {
                fprintf(temp, "Handicap\n");
            }


            for (int i = 0; i < 4; i++) {
                if (!fgets(buffer, sizeof(buffer), f)) {
                    g_print("Attention : Fin de fichier ou erreur lors de la lecture.\n");
                    break;
                }
            }
        } else {
            fprintf(temp, "%s", buffer);
        }
    }

      if (!found) {
        fprintf(temp, "%s %s %d %s %s ", id_service, type_transport, valeur_spin, matricule, type_service);

        if (selection1 == 0) {
            fprintf(temp, "Premium ");
        } else if (selection1 == 1) {
            fprintf(temp, "Normal ");
        }

        if (option1 == 0) {
            fprintf(temp, "Presidentielle\n");
        } else if (option1 == 1) {
            fprintf(temp, "Handicap\n");
        }
    }
    fclose(f);
    fclose(temp);

    GtkWidget *dialog;
    if (rename("services_temp.txt", "services.txt") != 0) {
        g_print("Erreur : Impossible de remplacer le fichier services.txt.\n");
        dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_ERROR,
                                        GTK_BUTTONS_OK,
                                        "Erreur : Mise à jour du fichier non effectuée.");
    } else {
        g_print("Fichier mis à jour avec succès.\n");
        dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_INFO,
                                        GTK_BUTTONS_OK,
                                        "Mise à jour du fichier effectuée avec succès.");
    }

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

//yassine
void on_button14_clicked(GtkButton *button, gpointer user_data) {
    typedef struct {
        char id_service[21];
        char type_de_transport[50];
        int numero_de_place;
        int numero_de_matricule;
        char type_de_service[50];
    } service;

    GtkWidget *input1, *input2, *combo1, *combo2, *spin;
    char id_service[21] = "";
    char buffer[256];
    service serv;
    int id_found = 0; 

    input1 = lookup_widget(GTK_WIDGET(button), "entry_id_service");
    input2 = lookup_widget(GTK_WIDGET(button), "entry_matricule");
    combo1 = lookup_widget(GTK_WIDGET(button), "combobox1");
    combo2 = lookup_widget(GTK_WIDGET(button), "combobox2");
    spin = lookup_widget(GTK_WIDGET(button), "spinButton_place");

    if (!input1 || !input2 || !combo1 || !combo2 || !spin) {
        g_print("Erreur : Un ou plusieurs widgets n'ont pas été trouvés.\n");
        return;
    }

    strncpy(id_service, gtk_entry_get_text(GTK_ENTRY(input1)), sizeof(id_service) - 1);
    g_strstrip(id_service);  
    if (strlen(id_service) == 0) {
        g_print("Erreur : L'entrée ID de service est vide.\n");
        return;
    }

    g_print("ID Service saisi: '%s'\n", id_service);

    FILE *chercher = fopen("services.txt", "r");
    if (chercher == NULL) {
        g_print("Erreur : Impossible d'ouvrir le fichier 'services.txt'.\n");
        return;
    }

    while (fgets(buffer, sizeof(buffer), chercher) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        if (sscanf(buffer, "%20s %49s %d %d %49s",
                  serv.id_service,
                  serv.type_de_transport,
                  &serv.numero_de_place,
                  &serv.numero_de_matricule,
                  serv.type_de_service) == 5) {

            g_print("Ligne lue : ID=%s, Transport=%s, Places=%d, Matricule=%d, Service=%s\n",
                    serv.id_service, serv.type_de_transport, serv.numero_de_place,
                    serv.numero_de_matricule, serv.type_de_service);

            if (strcmp(serv.id_service, id_service) == 0) {
                id_found = 1;

                char numero_de_matricule_str[21];
                snprintf(numero_de_matricule_str, sizeof(numero_de_matricule_str), "%d", serv.numero_de_matricule);
                gtk_entry_set_text(GTK_ENTRY(input2), numero_de_matricule_str);

                GtkTreeIter iter;
                GtkListStore *store;

                store = GTK_LIST_STORE(gtk_combo_box_get_model(GTK_COMBO_BOX(combo1)));
                gtk_list_store_clear(store);
                gtk_list_store_append(store, &iter);
                gtk_list_store_set(store, &iter, 0, serv.type_de_transport, -1);
                gtk_combo_box_set_active(GTK_COMBO_BOX(combo1), 0);

                store = GTK_LIST_STORE(gtk_combo_box_get_model(GTK_COMBO_BOX(combo2)));
                gtk_list_store_clear(store);
                gtk_list_store_append(store, &iter);
                gtk_list_store_set(store, &iter, 0, serv.type_de_service, -1);
                gtk_combo_box_set_active(GTK_COMBO_BOX(combo2), 0);

                gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin), serv.numero_de_place);

                break;
            }
        } else {
            g_print("Erreur : Ligne mal formatée ignorée : %s\n", buffer);
        }
    }

    fclose(chercher);

    if (!id_found) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Aucun service avec cet ID trouvé.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

//yassine
void on_button15_clicked(GtkButton *button, gpointer user_data) {
    typedef struct {
        char id_service[21];
        char type_de_transport[50];
        int numero_de_place;
        int numero_de_matricule;
        char type_de_service[50];
    } service;

    GtkWidget *input3;
    char id_service3[21] = "";
    service serv;
    int id_found = 0;
    char buffer[256];

    input3 = lookup_widget(GTK_WIDGET(button), "entry_id_service3");
    if (!input3) {
        g_print("Erreur : Le widget 'entry_id_service3' n'a pas été trouvé.\n");
        return;
    }

    strncpy(id_service3, gtk_entry_get_text(GTK_ENTRY(input3)), sizeof(id_service3) - 1);
    g_strstrip(id_service3);
    id_service3[sizeof(id_service3) - 1] = '\0';

    if (strlen(id_service3) == 0) {
        g_print("Erreur : L'entrée ID de service est vide.\n");
        return;
    }

    g_print("ID Service saisi: '%s'\n", id_service3);

    FILE *fichier = fopen("services.txt", "r");
    if (fichier == NULL) {
        g_print("Erreur : Impossible d'ouvrir le fichier 'services.txt'.\n");
        return;
    }

    while (fgets(buffer, sizeof(buffer), fichier) != NULL) {
        if (sscanf(buffer, "%20s %49s %d %d %49s",
                  serv.id_service,
                  serv.type_de_transport,
                  &serv.numero_de_place,
                  &serv.numero_de_matricule,
                  serv.type_de_service) == 5) {
            if (strcmp(serv.id_service, id_service3) == 0) {
                id_found = 1;
                g_print("Service trouvé :\n");
                g_print("ID Service        : %s\n", serv.id_service);
                g_print("Type de Transport : %s\n", serv.type_de_transport);
                g_print("Nombre de Places  : %d\n", serv.numero_de_place);
                g_print("Numéro Matricule  : %d\n", serv.numero_de_matricule);
                g_print("Type de Service   : %s\n", serv.type_de_service);
                break;
            }
        } else {
            g_print("Erreur : Ligne mal formatée ignorée : %s\n", buffer);
        }
    }

    fclose(fichier);

    if (id_found) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_QUESTION,
                                                   GTK_BUTTONS_NONE,
                                                   "Service trouvé :\n\n"
                                                   "ID Service        : %s\n"
                                                   "Type de Transport : %s\n"
                                                   "Nombre de Places  : %d\n"
                                                   "Numéro Matricule  : %d\n"
                                                   "Type de Service   : %s\n\n"
                                                   "Voulez-vous supprimer ce service ?",
                                                   serv.id_service,
                                                   serv.type_de_transport,
                                                   serv.numero_de_place,
                                                   serv.numero_de_matricule,
                                                   serv.type_de_service);

        gtk_dialog_add_button(GTK_DIALOG(dialog), "Oui", GTK_RESPONSE_YES);
        gtk_dialog_add_button(GTK_DIALOG(dialog), "Non", GTK_RESPONSE_NO);

        gint response = gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);

        if (response == GTK_RESPONSE_YES) {
            FILE *temp_file = fopen("temp_services.txt", "w");
            if (temp_file == NULL) {
                g_print("Erreur : Impossible d'ouvrir le fichier temporaire.\n");
                return;
            }

            fichier = fopen("services.txt", "r");
            if (fichier == NULL) {
                g_print("Erreur : Impossible d'ouvrir le fichier 'services.txt'.\n");
                fclose(temp_file);
                return;
            }

            while (fgets(buffer, sizeof(buffer), fichier) != NULL) {
                if (sscanf(buffer, "%20s %49s %d %d %49s",
                          serv.id_service,
                          serv.type_de_transport,
                          &serv.numero_de_place,
                          &serv.numero_de_matricule,
                          serv.type_de_service) == 5) {
                    if (strcmp(serv.id_service, id_service3) != 0) {
                        fputs(buffer, temp_file);
                    }
                }
            }

            fclose(fichier);
            fclose(temp_file);

            remove("services.txt");
            rename("temp_services.txt", "services.txt");

            g_print("Service supprimé avec succès.\n");
        }
    } else {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(button))),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "Aucun service avec cet ID trouvé.");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}



void
on_treeview_service_row_activated      (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
}
//yassine
typedef struct {
    int id_service;
    char type_de_transport[50];
    int numero_de_place;
    int numero_de_matricule;
    char type_de_service[50];
    char type_de_place[50];
    char presidentielle[50];
    char handicap[50];
} Service ;

void on_button16_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *treeview;
    GtkListStore *store;
    GtkTreeIter iter;
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    FILE *f;

    treeview = lookup_widget(GTK_WIDGET(button), "treeview_service");

    if (gtk_tree_view_get_model(GTK_TREE_VIEW(treeview)) == NULL) {
        renderer = gtk_cell_renderer_text_new();

        column = gtk_tree_view_column_new_with_attributes("ID Service", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        column = gtk_tree_view_column_new_with_attributes("Type de Transport", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        column = gtk_tree_view_column_new_with_attributes("Numéro de Place", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        column = gtk_tree_view_column_new_with_attributes("Numéro de Matricule", renderer, "text", 3, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        column = gtk_tree_view_column_new_with_attributes("Type de Service", renderer, "text", 4, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        column = gtk_tree_view_column_new_with_attributes("Type de place", renderer, "text", 5, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        column = gtk_tree_view_column_new_with_attributes("Catégorie de place", renderer, "text", 6, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    }

    store = gtk_list_store_new(7, G_TYPE_INT, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

    Service services;

    f = fopen("services.txt", "r");
    if (f == NULL) {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier services.txt\n");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        memset(&services, 0, sizeof(services));

        int result = sscanf(buffer, "%d %49s %d %d %49s %49s %49s %49s",
                            &services.id_service, services.type_de_transport, &services.numero_de_place,
                            &services.numero_de_matricule, services.type_de_service,
                            services.type_de_place, services.presidentielle,
                            services.handicap);

        if (result == 7) {
            printf("Ligne lue : ID=%d, Transport=%s, Places=%d, Matricule=%d, Service=%s, Place=%s, Présidentielle=%s, Handicap=%s\n",
                   services.id_service, services.type_de_transport, services.numero_de_place,
                   services.numero_de_matricule, services.type_de_service, services.type_de_place,
                   services.presidentielle, services.handicap);

            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter,
                               0, services.id_service,
                               1, services.type_de_transport,
                               2, services.numero_de_place,
                               3, services.numero_de_matricule,
                               4, services.type_de_service,
                               5, services.type_de_place,
                               6, services.presidentielle,
                               -1);
        } else {
            fprintf(stderr, "Erreur : Ligne mal formatée ignorée : %s", buffer);
        }
    }

    fclose(f);
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(store));
    g_object_unref(store);
}


//yassine
void
on_button17_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkNotebook *notebook; 
    notebook = GTK_NOTEBOOK(lookup_widget(GTK_WIDGET(button), "notebook1"));
    gtk_notebook_set_current_page(notebook, 0);
}



void
on_button18_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{

    GtkWidget *input1, *input2, *combo1, *combo2, *spin;

    input1 = lookup_widget(GTK_WIDGET(button), "entry_id_service1");
    input2 = lookup_widget(GTK_WIDGET(button), "entry_matricule1");
    combo1 = lookup_widget(GTK_WIDGET(button), "combobox3");
    combo2 = lookup_widget(GTK_WIDGET(button), "combobox4");
    spin = lookup_widget(GTK_WIDGET(button), "spinButton_place2");

    gtk_entry_set_text(GTK_ENTRY(input1), "");
    gtk_entry_set_text(GTK_ENTRY(input2), "");

    gtk_combo_box_set_active(GTK_COMBO_BOX(combo1), -1);
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo2), -1);

    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin), 0);

    g_print("Les champs ont été réinitialisés.\n");
}



