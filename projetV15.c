/*

Fonctionnement :

Voici les etapes d'execution :
I) Initialisation :
	1) Creation des differente structure et initialisation de leur variable
	2) Test si il y a un argument et demande a l'utilisateur de choisir ce qu'il veut faire
	3) Creation des processus selon la methode voulu par l'utilisateur (Par fichier, console ou aleatoire)
	4) Creation des file d'attente de priorite
II) Execution du round robin avec priorite
	1) Regarde les processus qui ne sont pas arrive et determine ceux qui arrive a ce quantum de temps
	2) Pour chaque nouveau processus creer un thread
	3) Election des processus
		a) Regarde la table cpu et la priorite qui est associe au quantum
		b) Regarde si la queue associe a la priorite n'est vide
			->Si non vide prend alors le premier element dans la queue
			->Si vide alors on passe a la valeur suivante dans la table
		c) Reveil le thread elu si un a ete trouve sinon passe au quantum suivant
	4) Le thread elu decremente sa priorite et se change de file et indique a l'utilisateur qu'il a ete elu
	5) Quand tous les processus sont termine, arrete l'execution
	
Fait par :
	Neil Farmer
	Brandon Jedd

Dernier changement : 
	01/01/2020
	
*/

//---------------------------------------------------- Importation des bibliotheque ------------------------------------------------------------

#include "0INCLUDE.h"
#include "1AccesMemoire.h"
#include "2GestionDesSignaux.h"
#include "3FixedVariable.h"
#include "4MoniteurVar.h"
#include "5Structure.h"
#include "6VarAdmin.h"
#include "7Processus.h"
#include "8TableCpu.h"
#include "9GestionDesArg.h"
#include "10Menu.h"
#include "11Queue.h"
#include "12GestionDesThreads.h"
#include "13ElectionProcessus.h"
#include "14FinPrgrm.h"




//---------------------------------------------------- Main --------------------------------------------------------------------------------

int main(int argc, char *argv[]){

	signal(SIGFPE, Gerer_Erreur);//gestion des erreurs : Pas encore complet car beaucoup de type d'erreur possible

//___________________________________________________ Access au memoire partage ______________________________________________________________

	//initialisation des premieres variables et accces au donne pour l'execution
	StructAdmin *donnee_admin;
   	int shmid_admin;
	shmid_admin = acces_administratif_memoire_partage();
   	donnee_admin = (StructAdmin *) shmat(shmid_admin, NULL, 0);
	initialisation_var_admin();

	//acces au processus
	struct processus *process; //creation de la structure de mes processus
	int shmid;
	shmid = acces_processus_memoire_partage();
	process = (StructProcess *) shmat(shmid, NULL, 0);

	//access a la table CPU
	int *table_cpu, shmid_cpu;
	shmid_cpu = acces_table_cpu_memoire_partage();
   	table_cpu = (int *) shmat(shmid_cpu, NULL, 0);

	//recupere l'acces a la structure utilisateur
	StructUtilisateur *donnee_utilisateur;
	int shmid_utilisateur;
	shmid_utilisateur = acces_utilisateur_memoire_partage();
	donnee_utilisateur = (StructUtilisateur *) shmat(shmid_utilisateur, NULL, 0);
//___________________________________________________ Implementation ______________________________________________________________
   
   
   	//regarde l'argument
   	if(argc>=2){
   		argument_execution();
   	}
   
    //Implementation processus et cpu
	Choix_implementation();
	choix_table_cpu();
   
    /*Gestion du signal ctrl+c pour modifier des parametres pendant l'execution, redirige en cas de ctrl+c vers Gerer_sigint
    La pause via ctrl+c n'est disponible que apres la creation des processus et de la table CPU*/
    signal(SIGINT, Gerer_sigint); 
    
    init_queue();
    
//___________________________________________________ Execution du round robin ______________________________________________________________
	
	int num_thread;
	
	while(donnee_admin->nb_procssus_fini < donnee_admin->nb_processus){//
		printf("Quantum de temps :  _____________________________________  %d  _____________________________________\n", donnee_admin->quantum_actuel);
		
		printf("\nArrive :\n");
    	arriver_processus();//appele les nouveaux processus arriver
    	
    	//creer un thread par processus arriver
    	for(int nbThread = 0; nbThread < donnee_admin->nbArrive; nbThread++){ //pour chaque processus arrive on fait
    		num_thread = donnee_admin->IDArrive[nbThread];//le numero du thread est l'id du processus
    		if(pthread_create(&thread[num_thread],NULL,threadFunction,(int *)num_thread)!=0){ //creer le thread
    			printf("Erreur : La creation du thread a echoue\n"); //en cas d'erreur
    			finprgm();
    		}
    		pthread_cond_wait (&creation_thread[num_thread], &mutex2[num_thread]); //attend le signal de retrour du thread
    	}
    	
    	usleep(11); //temps max entre le signal renvoye par le thread et la mise en attente de ce dernier
    	
    	printf("\nProcessus Elu :\n");
    	Election_des_processus();//eli un processus
    	
    	sleep(donnee_utilisateur->temps_affichage);//dors le nombre de seconde voulu par l'utilisateur
    	donnee_admin->quantum_actuel++;//incremente le quantum actuel
	}
	
	printf("Le programme s'est execute normalement\nTous les processus ont pu se terminer\n");
	
	shmdt(donnee_admin);//detache la memoire partage
	shmdt(process);//detache la memoire partage
	shmdt(table_cpu);//detache la memoire partage
	shmdt(donnee_utilisateur);
	
	shmctl(donnee_admin,IPC_RMID,NULL); //supprime les memoire partage
	shmctl(process,IPC_RMID,NULL); //supprime les memoire partage
	shmctl(table_cpu,IPC_RMID,NULL); //supprime les memoire partage
	shmctl(donnee_utilisateur,IPC_RMID,NULL);
	
	libere_queue();
	
   	return 0;
}
