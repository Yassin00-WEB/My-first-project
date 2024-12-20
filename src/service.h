#ifndef service_H_INCLUDED
#define service_H_INCLUDED
#include <stdio.h>


typedef struct {
    int id_service;
    char type_de_transport[30];
    int numero_de_place;
    int numero_de_matricule;
    char type_de_service[30];
    char type_de_place[30];
    char presidentielle[30];
    char handicap[30];
    char service[30];
    char historique_de_reservation[100];
} service;


int ajouter_service(char *filename, service s);
int modifier_service(char *filename, int id_service, service s,service new_service);
int supprimer_service(char *filename, int id_service);
service reserver_service(char *filename, int id_service);
void afficher_service(GtkWidget *treeview_service);
int affecter(char *filename, int id_service, int id_reservation);
service chercher_service(char *filename, int id_service);



 #endif

