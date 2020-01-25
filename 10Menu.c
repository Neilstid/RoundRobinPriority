#include "0INCLUDE.h"
#include "5Structure.h"
#include "3FixedVariable.h"
#include "4MoniteurVar.h"
#include "11Queue.h"

//met sur la bonne fonction selon le choix de l'utilisateur
StructProcess Choix_implementation(){

    StructProcess *process;
	int shmid;
	shmid = acces_processus_memoire_partage();
	process = (StructProcess *) shmat(shmid, NULL, 0);

    //choix implémentation processus
    int choix_crea_process; //entree du choix
    printf("\nCommment voulez-vous creer vos processus ?\n"); 
    printf("[1] : Via fichier\n");
    printf("[2] : Via console\n");
    printf("[3] : Aleatoire\n");
    printf("Choix : \t");
    scanf("%d", &choix_crea_process); //recupere l'entree de l'utilisateur
    
    //attribution de la bonne fonction selon le choix
    switch(choix_crea_process){
        case 1 :
            Implementation_fichier();//implemente la structure
            break;
        case 2 : 
        	Implementation_console();//implemente la structure
        	break;
        case 3 :
        	Implementation_aleatoire();//implemente la structure
        	break;
        default : //erreur
        	printf("Il semble que la valeur rentre soit incorect ou une erreur s'est produite\n");
        	finprgm(); //Arrete le programme
        	break;
    }
    
	shmdt(process);//detache la memoire partage
    
}

