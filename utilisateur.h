#ifndef __UTILISATEUR__H__
#define __UTILISATEUR__H__
#include <stdio.h>
typedef struct{
    int j;
    int m;
    int a;
}date;
typedef struct{
    char id[20];
    char cin[20];
    char nom[30];
    char prenom[30];
    char email[40];
    char mdp[30];
    char numTel[20];
    char genre[20];
    date dateNaissance;
    char adresse[30];
    int role; // 0 :ResponsableEts , 1:Infermier , 2:Medicin
}Utilisateur;

/*---------------------------------------------*/
void ajouter_utilsateur(Utilisateur u);
void supprimer_utilsateur(char id[]);
void modifier_utilsateur(Utilisateur ut);
void afficher_liste_utilsateur(GtkWidget *liste, char *fname);

int nombre_total_utilisateurs();
int nombre_utlisateur_par_genre(char genre[]);
int estEmailValide(char *email);
int estNumerique(char *str);
int estAlpha(char *str);
int saisieCin(char *cin);
int saisieNumTel(char *numTel);
void filtre_utilisateurs_par_role(int role);

/*-----------------------------------------------------*/

int utilsateurExist(char id[]);
Utilisateur trouver_utilsateur(char id[]);
int utilisateurlogin(char * filename, char  idr[] , char   mdpr[]);

#endif
