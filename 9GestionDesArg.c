#include "0INCLUDE.h"
#include "5Structure.h"
#include "3FixedVariable.h"
#include "4MoniteurVar.h"
#include "11Queue.h"

//fonction qui s'execute si l'utilisateur a mis un argument
void argument_execution(){
	
	//recuperation acces a la structure administratif
	StructAdmin *donnee_admin;
	int shmid_admin;
	shmid_admin = acces_administratif_memoire_partage();
	donnee_admin = (StructAdmin *) shmat(shmid_admin, NULL, 0);
	
	//recupere l'acces a la structure utilisateur
	StructUtilisateur *donnee_utilisateur;
	int shmid_utilisateur;
	shmid_utilisateur = acces_utilisateur_memoire_partage();
	donnee_utilisateur = (StructUtilisateur *) shmat(shmid_utilisateur, NULL, 0);
	
	int choix, valeur;

	printf("Que souhaitez-vous faire ?\n");
	printf("[1] : Creer un modele de fichier processus\n");
	printf("[2] : Modifier temps d'affichage entre les processus\n");
	printf("[3] : Modifier le choix de la priorite si aucun processus n'a ete trouve pour la priorite\n");
	printf("Choix :\t");
	
	scanf("%d",&choix);//respectivement le choix de l'utilisateur et la nouvelle valeur
	
	switch(choix){
		case 1 ://creer un makefile
			printf("Creation d'un modele de fichier processus en cours\n");
			//creation du makefile
			crea_makefile();//fonction creant le makefile
			break;
		case 2 : //modification du temps entre chaque quantum
			printf("Temps (en seconde) entre chaque processus : \t");
			scanf("%d", &valeur);
			donnee_utilisateur->temps_affichage = valeur;
			break;
		case 3 : //modification du type execution
			modif_type_exec();
			break;
		default : //erreur
			printf("Erreur : choix non reconnue\n");
			break;
	}
	
	shmdt(donnee_admin);//detache la memoire partage
	shmdt(donnee_utilisateur);
}

//fonction creant le makefile
void crea_makefile(){

	//creer ou supprime le contenu puis accede au fichier
	FILE* fichier = NULL;
    fichier = fopen("processus.txt", "w+");
    
    //on verifie que le fichier s'est ouvert
    if (fichier != NULL)
    {
        // On peut lire et écrire dans le fichier
        printf("Le fichier s'est ouvert correctement\n");
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier processus.txt \n");
    }
    
    fprintf(fichier, "Quantum_de_temp \nNombre_de_processus \nQuantum_arrive Temps_execution Priorite \ntemps_affichage");//ecriture dans le fichier
    
    fclose(fichier); //fermeture du fichier
    printf("Le modele fichier processus s'est bien creer\n");    
}

