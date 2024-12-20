#include <stdio.h>
#include <string.h>
#include "service.h"
#include "Reservation.h"
#include <stdlib.h>


void afficher_service(char *filename) {
    FILE *f = fopen("services.txt", "r");
    service serv;

    if (f != NULL) {
        while (fscanf(f, "%d %s %d %d %s %s %s %s %s %s\n", &serv.id_service, serv.type_de_transport, &serv.numero_de_place, &serv.numero_de_matricule, serv.type_de_service, serv.type_de_place, serv.presidentielle, serv.handicap, serv.service, serv.historique_de_reservation) != EOF) {
            printf("%d %s %d %d %s %s %s %s %s %s\n", serv.id_service, serv.type_de_transport, serv.numero_de_place, serv.numero_de_matricule, serv.type_de_service, serv.type_de_place, serv.presidentielle, serv.handicap, serv.service, serv.historique_de_reservation);
        }
        fclose(f);
    } else {
        printf("Erreur lors de l'ouverture du fichier!\n");
    }
}
int ajouter_service(char *filename, service s) { 
    FILE *f = fopen("services.txt", "a");
    if (f != NULL) {
        fprintf(f, "%d %s %d %d %s %s %s %s %s %s\n", s.id_service, s.type_de_transport, s.numero_de_place, s.numero_de_matricule, s.type_de_service, s.type_de_place, s.presidentielle, s.handicap, s.service, s.historique_de_reservation);
        fclose(f);
    } else {
        printf("Erreur lors de l'ouverture du fichier!\n");
    }
}

int modifier_service(char *filename, int id_service, service s,service new_service) {
    FILE *f = fopen(filename, "r+");
    FILE *temp = fopen("temp.txt", "w");
    service S;
    int found = 0;

    if (f != NULL && temp != NULL) {
        while (fscanf(f, "%d %s %d %d %s %s %s %s %s %s\n", &s.id_service, s.type_de_transport, &s.numero_de_place, &s.numero_de_matricule, s.type_de_service, s.type_de_place, s.presidentielle, s.handicap, s.service, s.historique_de_reservation) != EOF) {
            if (s.id_service == id_service) {
                fprintf(temp, "%d %s %d %d %s %s %s %s %s %s\n", new_service.id_service, new_service.type_de_transport, new_service.numero_de_place, new_service.numero_de_matricule, new_service.type_de_service, new_service.type_de_place, new_service.presidentielle, new_service.handicap, new_service.service, new_service.historique_de_reservation);
                found = 1;
            } else {
                fprintf(temp, "%d %s %d %d %s %s %s %s %s %s\n", s.id_service, s.type_de_transport, s.numero_de_place, s.numero_de_matricule, s.type_de_service, s.type_de_place, s.presidentielle, s.handicap, s.service, s.historique_de_reservation);
            }
        }
        fclose(f);
        fclose(temp);
        remove(filename);
        rename("temp.txt", filename);
    } else {
        printf("Erreur lors de l'ouverture du fichier!\n");
        return 0;
    }

    return found;
}



int supprimer_service(char *filename, int id_service)   {
    int tr = 0;
    service s;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("nouv.txt", "w");
    if (f != NULL && f2 != NULL) {
        while (fscanf(f, "%d %s %d %d %s %s %s %s %s %s\n", &s.id_service, s.type_de_transport, &s.numero_de_place, &s.numero_de_matricule, s.type_de_service, s.type_de_place, s.presidentielle, s.handicap, s.service, s.historique_de_reservation) != EOF) {
             if (s.id_service == id_service)  {
                tr = 1;
            } else {
               fprintf(f2, "%d %s %d %d %s %s %s %s %s %s\n", s.id_service, s.type_de_transport, s.numero_de_place, s.numero_de_matricule, s.type_de_service, s.type_de_place, s.presidentielle, s.handicap, s.service, s.historique_de_reservation);
            }
        }
    }
    fclose(f);
    fclose(f2);
    remove(filename);
    rename("nouv.txt", filename);
    return tr;
}
service reserver_service(char *filename, int id_service) {
    FILE *f = fopen(filename, "r");
    service s;
    int found = 0;

    if (f != NULL) {
        while (fscanf(f, "%d %s %d %d %s %s %s %s %s %s\n", &s.id_service, s.type_de_transport, &s.numero_de_place, &s.numero_de_matricule, s.type_de_service, s.type_de_place, s.presidentielle, s.handicap, s.service, s.historique_de_reservation) != EOF) {
            if (s.id_service == id_service) {
                found = 1;
                break;
            }
        }
        fclose(f);
    } else {
        printf("Erreur lors de l'ouverture du fichier!\n");
    }

    if (!found) {
        s.id_service = -1;
    }

    return s;
}

int affecter(char *filename, int id_service, int id_reservation) {
    FILE *f = fopen(filename, "r+");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 0;
    }

    char buffer[20];  
    Reservation r;
    int found = 0;

    while (fscanf(f, "%s %s %s %s %d %d %d %d %f\n", r.CIN, r.ID_Res, r.ID_Park, r.ID_Serv, &r.NB_PlaceRes, &r.jour, &r.mois, &r.annee, &r.prix) != EOF) {
        if (atoi(r.ID_Serv) == id_service) {
            found = 1;

            sprintf(buffer, "%d", id_reservation);
            strncpy(r.ID_Res, buffer, sizeof(r.ID_Res) - 1);  
            r.ID_Res[sizeof(r.ID_Res) - 1] = '\0';  
            fseek(f, -sizeof(Reservation), SEEK_CUR);
            fprintf(f, "%s %s %s %s %d %d %d %d %f\n", r.CIN, r.ID_Res, r.ID_Park, r.ID_Serv, r.NB_PlaceRes, r.jour, r.mois, r.annee, r.prix);
            break;
        }
    }

    fclose(f);
    
    if (!found) {
        printf("Service non trouvé.\n");
    }

    return found;
}




int chercher_service(char *filename, int id_service) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s\n", filename);
        return 0; 
    }

    service serv;
    while (fscanf(file, "%20s %49s %d %d %49s",
                  serv.id_service,
                  serv.type_de_transport,
                  &serv.numero_de_place,
                  &serv.numero_de_matricule,
                  serv.type_de_service) == 5) {
        if (atoi(serv.id_service) == id_service) {
            fclose(file);
            return 1; 
        }
    }

    fclose(file);
    return 0; 
}

