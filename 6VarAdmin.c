#include "0INCLUDE.h"
#include "5Structure.h"
#include "3FixedVariable.h"
#include "4MoniteurVar.h"
#include "11Queue.h"

//---------------------------------------------------- Type execution ---------------------------------------------------------------------

//modifie le choix de la priorite suivante si une queue de priorite est vide
void modif_type_exec(){

	//recupere l'acces a la structure utilisateur
	StructUtilisateur *donnee_utilisateur;
	int shmid_utilisateur;
	shmid_utilisateur = acces_utilisateur_memoire_partage();
	donnee_utilisateur = (StructUtilisateur *) shmat(shmid_utilisateur, NULL, 0);

	//prend le choix de l'utilisateur
	int choix;
	printf("Quel mode de choix de processus voulez-vous utiliser ?\n");
	printf("[1] : Priorite inferieur si aucun processus n'appartient a la priorite donnee par la table CPU\n");
	printf("[2] : Priorite suivante dans la table CPU si aucun processus n'appartient a la priorite donnee par la table CPU\n");
	printf("Choix : \t");
	scanf("%d", &choix);
	
	//verifie que le choix est possible
	if(choix > 2 || choix <= 0){//verification d'une potentiel erreur
		printf("Erreur : La valeur rentre est incorrect\n");
		finprgm();
	} 
	
	donnee_utilisateur->type = choix-1;
	
	//detache la memoire partage
	shmdt(donnee_utilisateur);
}

//initialisation des valeurs lie a l'execution
void initialisation_var_admin(){

	//recupere l'acces a la structure administratif
	StructAdmin *donnee_admin;
	int shmid_admin;
	shmid_admin = acces_administratif_memoire_partage();
	donnee_admin = (StructAdmin *) shmat(shmid_admin, NULL, 0);
	
	//recupere l'acces a la structure utilisateur
	StructUtilisateur *donnee_utilisateur;
	int shmid_utilisateur;
	shmid_utilisateur = acces_utilisateur_memoire_partage();
	donnee_utilisateur = (StructUtilisateur *) shmat(shmid_utilisateur, NULL, 0);
   	
   	donnee_admin->quantum_actuel = 0; //commence au quantum 0
   	donnee_admin->nb_procssus_fini = 0; //le nombre de processus fini est 0 au depart
   	donnee_admin->nbProcessActif = 0;
   	
   	donnee_utilisateur->temps_affichage = 0; //Le temps entre chaque quantum est de 1s par default
   	donnee_utilisateur->type = 0; //defini la methode de choix de la priorite suivante si non trouve par default
   	/*
	Type = 0 <=> si la priorite n'est pas trouve on passe a la priorite inferieur
	Type = 1 <=> si la priorite n'est pas trouve on passe a la priorite suivante dans la table cpu
	*/
   	
   	//detache la memoire partage
   	shmdt(donnee_admin);
   	shmdt(donnee_utilisateur);
}

//fonction pour modifier les parametre de la structure administratif
void modif_parametre_exec(){

	//recupere l'acces a la structure administratif
	StructAdmin *donnee_admin;
	int shmid_admin;
	shmid_admin = acces_administratif_memoire_partage();
	donnee_admin = (StructAdmin *) shmat(shmid_admin, NULL, 0);
	
	//recupere l'acces a la structure utilisateur
	StructUtilisateur *donnee_utilisateur;
	int shmid_utilisateur;
	shmid_utilisateur = acces_utilisateur_memoire_partage();
	donnee_utilisateur = (StructUtilisateur *) shmat(shmid_utilisateur, NULL, 0);
	
	int choix, valeur;//respectivement le choix de l'utilisateur et la nouvelle valeur
	
	printf("Voulez-vous modifier le temps d'un quantum de temps ?\n[1] : Oui\n[2] : Non\n");
	printf("Choix : \t");
	scanf("%d", &choix);
	if(choix == 1){//modification du burst time d'un quantum
		printf("Nouvelle valeur du quantum de temps : \t");
		scanf("%d", &valeur);//recuperation de la nouvelle valeur
		donnee_admin->time_quantum = valeur; //mise a jour de la valeur
	}
	
	printf("Voulez-vous modifier le temps d'affichage entre les processus ?\n[1] : Oui\n[2] : Non\n");
	printf("Choix : \t");
	scanf("%d", &choix);
	if(choix == 1){//temps entre chaque quantum 
		printf("Nouvelle valeur du temps d'affichage (en seconde) : \t");
		scanf("%d", &valeur);//recuperation de la nouvelle valeur
		donnee_utilisateur->temps_affichage = valeur;//mise a jour de la valeur
	}
	
	//modifictaion du changement de priorite rechercher 
	printf("Voulez-vous modifier la methode d'election des processus ?\n[1] : Oui\n[2] : Non\n");
	printf("Choix : \t");
	scanf("%d", &choix);
	if(choix == 1){
		modif_type_exec();
	}
	
	shmdt(donnee_admin);//detache la memoire partage
	shmdt(donnee_utilisateur);
}
