#include "0INCLUDE.h"
#include "5Structure.h"
#include "3FixedVariable.h"
#include "4MoniteurVar.h"
#include "11Queue.h"

//pas utiliser pour le moment
void Gerer_Erreur(int signal){ //Gestion d'erreur
	printf("\n Une erreur inconnue s'est produite");
	finprgm();
}

//permet de faire pause pendant l'execution
void Gerer_sigint(int signal){

	//acces table cpu
	int shmid_cpu, *table_cpu;
	shmid_cpu = acces_table_cpu_memoire_partage();
   	table_cpu = (int *) shmat(shmid_cpu, NULL, 0);

//___________________________________________________ Choix utilsisateur ______________________________________________________________

    //choix implémentation processus
    int choix_crea_process; //entree du choix
    printf("\n-------------------------------------------Pause-------------------------------------------\n"); 
    printf("[1] : Arreter l'execution\n");
    printf("[2] : Reprendre l'execution\n");
    printf("[3] : Afficher la table d'allocation CPU\n");
    printf("[4] : Modifier la table d'allocation CPU\n");
    printf("[5] : Afficher les propriete d'un processus\n");
    printf("[6] : Modifier les propriete d'un processus\n");
    printf("[7] : Modifier les parametres de l'execution\n");
    printf("Choix : \t");
    scanf("%d", &choix_crea_process); //recupere l'entree de l'utilisateur

//___________________________________________________ Redirection selon choix ______________________________________________________________
    
    //attribution de la bonne fonction selon le choix
    switch(choix_crea_process){
        case 1 : //arret du programme
            printf("\nLe programme s'arrete\n");
            finprgm();
            break;
            
        case 2 : //reprise du programme
            printf("\nReprise de l'execution du prgramme\n");
        	break;
        	
        case 3 :
        	printf("Affichage de la table CPU...\n");
        	afficher_table_cpu(100); //fonction qui permet d'afficher la table cpu
        	break;
        	
        case 4 : 
        	printf("Modification de la table d'allocation CPU\n");
        	afficher_table_cpu(100); //fonction qui permet d'afficher la table cpu
			printf("Voulez vous modifier cette table ? \n [1] : Oui \n [2] : Non \n Choix : \t");
			int Modifier_table;
			scanf("%d", &Modifier_table); //recuperation du choix de l'utilisateur
			
			while(Modifier_table == 1){ //Tant que l'utilisateur souhaite modifier la table
				int val_modif, temp; //respectivement l'element a modifier et sa valeur
				printf("Quelle element voulez vous modifier ?\n Position : \t");
				scanf("%d", &val_modif); //recuperation de l'element a modifier
				if(val_modif >= 100){ //Verfication qu'il existe dans la table
					printf("Erreur : La valeur cible n'exite pas\n");
					finprgm();
				}
				printf("La valeur actuel est %d \n", table_cpu[val_modif]);
				printf("Nouvelle valeur : \t");
				scanf("%d", &temp); //recuperation de la valeur
				table_cpu[val_modif] = temp; //on modifie la table cpu
				printf("Voulez vous encore modifier cette table ? \n [1] : Oui \n [2] : Non \n Choix : \t");
				scanf("%d", &Modifier_table); //on boucle si l'utilisateur veut continuer a modifier sinon on sort
			}
			afficher_table_cpu(100); //on affiche la nouvelle table
        	break;
        	
        case 5 : //affiche processus
        	afficher_processus(); //fonction permettant d'afficher les processus
        	break;
        case 6 :  //modification d'un processus
        	printf("Modification des propriete d'un processus\n");
        	modif_process(); //fonction permettant de modifier les processus 
        	break;
        case 7 : //modification des paramete lier a l'execution
        	modif_parametre_exec(); //fonction pour modifier les paramtre d'execution
        	break;
        default : //erreur
        	printf("Il semble que la valeur rentre soit incorect ou une erreur s'est produite : Le choix %d n'est pas disponible dans la pause.\n");
        	finprgm(); //Arrete le programme
        	break;
    }
    shmdt(table_cpu);//detache la memoire partage
    
    return 0;
}
