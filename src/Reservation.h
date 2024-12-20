#ifndef RESERVATION_H_INCLUDED
#define RESERVATION_H_INCLUDED

#include <stdio.h>

typedef struct
{
    char CIN[10];
    char ID_Res[10];
    char ID_Park[10];
    char ID_Serv[10];
    int NB_PlaceRes;
    int jour;
    int mois;
    int annee;
    float prix;
} Reservation;

int ajouter(char *, Reservation);
int modifier(char *, char[], Reservation);
int supprimer(char *filename, char id[10]);
Reservation chercher(char *, char[]);
void afficher_reservation(Reservation);
void afficher_toutes_reservations(char *filename);

#endif
