#include <stdio.h>
#include <string.h>
#include "Reservation.h"

int ajouter(char *filename, Reservation R) {
    FILE *f = fopen(filename, "a");
    if (f != NULL) {
        fprintf(f, "%s %s %s %s %d %d/%d/%d %f\n", R.CIN, R.ID_Res, R.ID_Park, R.ID_Serv, R.NB_PlaceRes, R.jour, R.mois, R.annee, R.prix);
        fclose(f);
        return 1;
    } else {
        return 0;
    }
}

int modifier(char *filename, char id[10], Reservation nouv) {
    int tr = 0;
    Reservation R;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("nouv.txt", "w");
    if (f != NULL && f2 != NULL) {
        while (fscanf(f, "%s %s %s %s %d %d/%d/%d %f\n", R.CIN, R.ID_Res, R.ID_Park, R.ID_Serv, &R.NB_PlaceRes, &R.jour, &R.mois, &R.annee, &R.prix) != EOF) {
            if (strcmp(R.ID_Res, id) == 0) {
                fprintf(f2, "%s %s %s %s %d %d/%d/%d %f\n", nouv.CIN, nouv.ID_Res, nouv.ID_Park, nouv.ID_Serv, nouv.NB_PlaceRes, nouv.jour, nouv.mois, nouv.annee, nouv.prix);
                tr = 1;
            } else {
                fprintf(f2, "%s %s %s %s %d %d/%d/%d %f\n", R.CIN, R.ID_Res, R.ID_Park, R.ID_Serv, R.NB_PlaceRes, R.jour, R.mois, R.annee, R.prix);
            }
        }
    }
    fclose(f);
    fclose(f2);
    remove(filename);
    rename("nouv.txt", filename);
    return tr;
}

int supprimer(char *filename, char id[10]) {
    int tr = 0;
    Reservation R;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("nouv.txt", "w");
    if (f != NULL && f2 != NULL) {
        while (fscanf(f, "%s %s %s %s %d %d/%d/%d %f\n", R.CIN, R.ID_Res, R.ID_Park, R.ID_Serv, &R.NB_PlaceRes, &R.jour, &R.mois, &R.annee, &R.prix) != EOF) {
            if (strcmp(R.ID_Res, id) == 0) {
                tr = 1;
            } else {
                fprintf(f2, "%s %s %s %s %d %d/%d/%d %f\n", R.CIN, R.ID_Res, R.ID_Park, R.ID_Serv, R.NB_PlaceRes, R.jour, R.mois, R.annee, R.prix);
            }
        }
    }
    fclose(f);
    fclose(f2);
    remove(filename);
    rename("nouv.txt", filename);
    return tr;
}

Reservation chercher(char *filename, char id[10]) {
    Reservation R;
    int tr = 0;
    FILE *f = fopen(filename, "r");
    if (f != NULL) {
        while (tr == 0 && fscanf(f, "%s %s %s %s %d %d/%d/%d %f\n", R.CIN, R.ID_Res, R.ID_Park, R.ID_Serv, &R.NB_PlaceRes, &R.jour, &R.mois, &R.annee, &R.prix) != EOF) {
            if (strcmp(R.ID_Res, id) == 0) {
                tr = 1;
            }
        }
    }
    fclose(f);
    if (tr == 0) {
        strcpy(R.ID_Res, "-1");
    }
    return R;
}

void afficher_reservation(Reservation R) {
    printf("CIN: %s\n", R.CIN);
    printf("ID Reservation: %s\n", R.ID_Res);
    printf("ID Parking: %s\n", R.ID_Park);
    printf("ID Service: %s\n", R.ID_Serv);
    printf("Nombre de places reservees: %d\n", R.NB_PlaceRes);
    printf("Date: %02d/%02d/%04d\n", R.jour, R.mois, R.annee);
    printf("Prix: %.2f\n", R.prix);
}

void afficher_toutes_reservations(char *filename) {
    Reservation R;
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier %s\n", filename);
        return;
    }
    printf("Liste des reservations:\n");
    while (fscanf(f, "%s %s %s %s %d %d/%d/%d %f\n",
                  R.CIN, R.ID_Res, R.ID_Park, R.ID_Serv, &R.NB_PlaceRes,
                  &R.jour, &R.mois, &R.annee, &R.prix) != EOF) {
        afficher_reservation(R);
    }
    fclose(f);
}
