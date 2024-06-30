#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif
#include <gtk/gtk.h>
#include "utilisateur.h"
#include <ctype.h>


enum{
EID,
ENOM,
EPRENOM,
ECIN,
EEMAIL,
ENUMTEL,
EGENRE,
EDATE,
EADRESS,
EROLE,
ECOLUMNS,
};

void afficher_liste_utilsateur(GtkWidget *liste,char *fname ){
    
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;
    Utilisateur u;
    FILE *f;

char date[100];
char role[20];
    store = NULL;
    store = gtk_tree_view_get_model(liste);

    if(store == NULL){
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID",renderer,"text",EID,NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Nom",renderer,"text",ENOM,NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Prénom",renderer,"text",EPRENOM,NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("N°Cin",renderer,"text",ECIN,NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Email",renderer,"text",EEMAIL,NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Num Tel",renderer,"text",ENUMTEL,NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Role",renderer,"text",EROLE,NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Date du Naissance",renderer,"text",EDATE,NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Genre",renderer,"text",EGENRE,NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Adresse",renderer,"text",EADRESS,NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

    }
store = gtk_list_store_new(ECOLUMNS,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
   
   
    f = fopen(fname,"r");
if(f != NULL){
        while(fscanf(f,"%s %s %s %s %s %s %s %s %d/%d/%d %s %d\n",u.id,u.cin,u.nom,u.prenom,u.email,u.mdp,u.numTel,u.genre,&(u.dateNaissance.j),&(u.dateNaissance.m),&(u.dateNaissance.a),u.adresse,&(u.role)) != EOF){


sprintf(date,"%d/%d/%d",u.dateNaissance.j,u.dateNaissance.m,u.dateNaissance.a);
strcpy(role,u.role == 0 ? "ResponsableEts" :u.role == 1 ? "Infermier":"Medicin");
gtk_list_store_append(store,&iter);
            gtk_list_store_set(store,&iter,EID,u.id,ENOM,u.nom,EPRENOM,u.prenom,ECIN,u.cin,EEMAIL,u.email,ENUMTEL,u.numTel,EROLE,role,EDATE,date,EGENRE,u.genre,EADRESS,u.adresse,-1);
           
        }


gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
g_object_unref(store);
        fclose(f);
    }
 
}
/*---------------------------------------------------------------------------------------------------------- */

/*---------------------------------------------------------------------------------------------------------- */

// Fonction pour vérifier si une chaîne contient uniquement des caractères alphabétiques
int estAlpha(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isalpha(str[i]))
        {
            return 0; // Caractère non alphabétique trouvé
        }
    }
    return 1; // Tous les caractères sont alphabétiques
}

// Fonction pour vérifier si une chaîne contient uniquement des chiffres

int estNumerique(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]))
        {
            return 0; // Caractère non numérique trouvé
        }
    }
    return 1; // Tous les caractères sont numériques
}

// Fonction pour obtenir une saisie de numéro de téléphone valide
int saisieNumTel(char *numTel)
{
    do
    {
        if (!estNumerique(numTel) || strlen(numTel) != 8)
        {
            return 0;
        }
    } while (!estNumerique(numTel) || strlen(numTel) != 8);
    return 1;
}
// Fonction pour obtenir une saisie de cin valide
int saisieCin(char *cin)
{
    do
    {
        if (!estNumerique(cin) || strlen(cin) != 8)
        {
            return 0;
        }
    } while (!estNumerique(cin) || strlen(cin) != 8);
    return 1;
}

// Function to check if a given string is a valid email address
#include <ctype.h>

int estEmailValide(char *email)
{
    int atFound = 0;  // Flag to track the '@' symbol
    int dotFound = 0; // Flag to track the '.' symbol

    for (int i = 0; email[i] != '\0'; i++)
    {
        if (email[i] == '@')
        {
            atFound = 1;
        }
        else if (email[i] == '.')
        {
            dotFound = 1;
        }
        else if (!isalnum(email[i]) && email[i] != '_' && email[i] != '-')
        {
            return 0; // Invalid character found in email
        }
    }

    // Check if both '@' and '.' are found
    if (atFound && dotFound)
    {
        return 1; // Valid email
    }
    else
    {
        return 0; // Either '@' or '.' or both are missing
    }
}
//fonction de filtrage par role
void filtre_utilisateurs_par_role(int role){
 Utilisateur u;
    FILE *f;
    FILE *g;
    f = fopen("../database/utilisateur.txt","r");
    g = fopen("filtre.txt","a");
    while(fscanf(f,"%s %s %s %s %s %s %s %s %d/%d/%d %s %d\n",u.id,u.cin,u.nom,u.prenom,u.email,u.mdp,u.numTel,u.genre,&(u.dateNaissance.j),&(u.dateNaissance.m),&(u.dateNaissance.a),u.adresse,&(u.role)) != EOF){
        if(role == u.role){
             fprintf(g,"%s %s %s %s %s %s %s %s %d/%d/%d %s %d\n",u.id,u.cin,u.nom,u.prenom,u.email,u.mdp,u.numTel,u.genre,u.dateNaissance.j,u.dateNaissance.m,u.dateNaissance.a,u.adresse,u.role);
        }
    }
    fclose(f);
    fclose(g);
}

/* --------------------------------------------------------------------------------------------------------- */

void ajouter_utilsateur(Utilisateur u){
   FILE *f;
    f = fopen("../database/utilisateur.txt","a");
    if(f!= NULL){
        fprintf(f,"%s %s %s %s %s %s %s %s %d/%d/%d %s %d\n",u.id,u.cin,u.nom,u.prenom,u.email,u.mdp,u.numTel,u.genre,u.dateNaissance.j,u.dateNaissance.m,u.dateNaissance.a,u.adresse,u.role);
    }
    fclose(f);
}

/* --------------------------------------------------------------------------------------------------------- */

void modifier_utilsateur(Utilisateur ut){
    Utilisateur u;
    FILE *f;
    FILE *g;
    f = fopen("../database/utilisateur.txt","r");
    g = fopen("tmp.txt","a");
    while(fscanf(f,"%s %s %s %s %s %s %s %s %d/%d/%d %s %d\n",u.id,u.cin,u.nom,u.prenom,u.email,u.mdp,u.numTel,u.genre,&(u.dateNaissance.j),&(u.dateNaissance.m),&(u.dateNaissance.a),u.adresse,&(u.role)) != EOF){
        if(strcmp(u.id,ut.id) == 0){
             fprintf(g,"%s %s %s %s %s %s %s %s %d/%d/%d %s %d\n",ut.id,ut.cin,ut.nom,ut.prenom,ut.email,ut.mdp,ut.numTel,ut.genre,ut.dateNaissance.j,ut.dateNaissance.m,ut.dateNaissance.a,ut.adresse,ut.role);
        }
        else{
             fprintf(g,"%s %s %s %s %s %s %s %s %d/%d/%d %s %d\n",u.id,u.cin,u.nom,u.prenom,u.email,u.mdp,u.numTel,u.genre,u.dateNaissance.j,u.dateNaissance.m,u.dateNaissance.a,u.adresse,u.role);
        }
    }
    fclose(f);
    fclose(g);
    remove("../database/utilisateur.txt");
    rename("tmp.txt","../database/utilisateur.txt");
}

/* --------------------------------------------------------------------------------------------------------- */

void supprimer_utilsateur(char id[]){
    Utilisateur u;
    FILE *f;
    FILE *g;
    f = fopen("../database/utilisateur.txt","r");
    g = fopen("tmp.txt","a");
    while(fscanf(f,"%s %s %s %s %s %s %s %s %d/%d/%d %s %d\n",u.id,u.cin,u.nom,u.prenom,u.email,u.mdp,u.numTel,u.genre,&(u.dateNaissance.j),&(u.dateNaissance.m),&(u.dateNaissance.a),u.adresse,&(u.role)) != EOF){
        if(strcmp(u.id,id) != 0){
        fprintf(g,"%s %s %s %s %s %s %s %s %d/%d/%d %s %d\n",u.id,u.cin,u.nom,u.prenom,u.email,u.mdp,u.numTel,u.genre,u.dateNaissance.j,u.dateNaissance.m,u.dateNaissance.a,u.adresse,u.role);
        }
       
    }
    fclose(f);
    fclose(g);
    remove("../database/utilisateur.txt");
    rename("tmp.txt","../database/utilisateur.txt");
}
/* --------------------------------------------------------------------------------------------------------- */

int utilsateurExist(char id[]){
 Utilisateur u;
    FILE *f;
    f = fopen("../database/utilisateur.txt","r");

if(f == NULL){
return 0;
}
    while(fscanf(f,"%s %s %s %s %s %s %s %s %d/%d/%d %s %d\n",u.id,u.cin,u.nom,u.prenom,u.email,u.mdp,u.numTel,u.genre,&(u.dateNaissance.j),&(u.dateNaissance.m),&(u.dateNaissance.a),u.adresse,&(u.role)) != EOF){
        if(strcmp(u.id,id) == 0){
return 1;
        }
       
    }
    fclose(f);
return 0;
}

/* --------------------------------------------------------------------------------------------------------- */

Utilisateur trouver_utilsateur(char id[]){
 Utilisateur u;
    FILE *f;
    f = fopen("../database/utilisateur.txt","r");
    while(fscanf(f,"%s %s %s %s %s %s %s %s %d/%d/%d %s %d\n",u.id,u.cin,u.nom,u.prenom,u.email,u.mdp,u.numTel,u.genre,&(u.dateNaissance.j),&(u.dateNaissance.m),&(u.dateNaissance.a),u.adresse,&(u.role)) != EOF){
        if(strcmp(u.id,id) == 0){
return u;
        }
       
    }
    fclose(f);

}

/* --------------------------------------------------------------------------------------------------------- */

int nombre_total_utilisateurs(){
    int nombre = 0;
Utilisateur u;
    FILE *f;
    f = fopen("../database/utilisateur.txt","r");
    while(fscanf(f,"%s %s %s %s %s %s %s %s %d/%d/%d %s %d\n",u.id,u.cin,u.nom,u.prenom,u.email,u.mdp,u.numTel,u.genre,&(u.dateNaissance.j),&(u.dateNaissance.m),&(u.dateNaissance.a),u.adresse,&(u.role)) != EOF){
nombre++;
    }
    fclose(f);
    return nombre;
}

/* --------------------------------------------------------------------------------------------------------- */

int nombre_utlisateur_par_genre(char genre[]){
   int nombre = 0;
Utilisateur u;
    FILE *f;
    f = fopen("../database/utilisateur.txt","r");
    while(fscanf(f,"%s %s %s %s %s %s %s %s %d/%d/%d %s %d\n",u.id,u.cin,u.nom,u.prenom,u.email,u.mdp,u.numTel,u.genre,&(u.dateNaissance.j),&(u.dateNaissance.m),&(u.dateNaissance.a),u.adresse,&(u.role)) != EOF){
        if(strcmp(u.genre,genre) == 0){
nombre++;
        }
       
    }
    fclose(f);
    return nombre;

}

int utilisateurlogin(char * filename, char  idr[] , char   mdpr[]) {
    int found = 5;
    Utilisateur u;
    
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening file for reading.\n");
        exit(1);
    }


    while (fscanf(file, "%s %s %s %s %s %s %s %s %d/%d/%d %s %d\n",u.id,u.cin,u.nom,u.prenom,u.email,u.mdp,u.numTel,u.genre,&(u.dateNaissance.j),&(u.dateNaissance.m),&(u.dateNaissance.a),u.adresse,&(u.role)) != EOF) {    
	if (strcmp(u.id, idr) == 0 && strcmp(u.mdp, mdpr) == 0) {
	/*if(u.role==0){        
	found=0; 
}if(u.role==1){
found=1;
}if(u.role==2)
found=2;
}*/
found=1;
break;}
}
fclose(file);
    return found;


}

