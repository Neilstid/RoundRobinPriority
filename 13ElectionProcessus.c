#include "0INCLUDE.h"
#include "5Structure.h"
#include "3FixedVariable.h"
#include "4MoniteurVar.h"
#include "11Queue.h"
//---------------------------------------------------- Election des processus ---------------------------------------------------------------------

//fonction qui decide quel processus sera elu
void Election_des_processus(){

	//donne acces a la structure administratif
	StructAdmin *donnee_admin;
   	int shmid_admin;
	shmid_admin = acces_administratif_memoire_partage();
   	donnee_admin = (StructAdmin *) shmat(shmid_admin, NULL, 0);

	//recupere le quantum actuel dans une variable interne a la fonction
	int quantum_actuel;
	quantum_actuel = donnee_admin->quantum_actuel;

	int priorite_a_elir, processus_elu, Nb_elu, nb_boucle;//respectivement la priorite indique par la table d'allocation cpu, le processus elu, si la fonction a elue ou non un processus, le nombre de boucle effectue pour trouver un processus a elir
	
	//donne acces a la structure processus
	StructProcess *process;
	int shmid;
	shmid = acces_processus_memoire_partage();
	process = (StructProcess *) shmat(shmid, NULL, 0);
	
	//donne acces a la table cpu
	int shmid_cpu, *table_cpu;
	shmid_cpu = acces_table_cpu_memoire_partage();
   	table_cpu = (int *) shmat(shmid_cpu, NULL, 0);
	
	//recupere l'acces a la structure utilisateur
	StructUtilisateur *donnee_utilisateur;
	int shmid_utilisateur;
	shmid_utilisateur = acces_utilisateur_memoire_partage();
	donnee_utilisateur = (StructUtilisateur *) shmat(shmid_utilisateur, NULL, 0);
	
	//adapte le quantum actuel si celui ci est superieur a 100
	while(quantum_actuel>=100){
		quantum_actuel -= 100;
	}
	
	//initialisation des variables
	priorite_a_elir = table_cpu[quantum_actuel]; //determine la priorite a elir selon la position du quantum dans la table cpu
	
	Nb_elu = 0; //aucun processus n'est elu pour le moment
	nb_boucle = 0; //aucune boucle n'a ete effectue
	
	int nb_boucle_max;
	if(donnee_utilisateur->type == 0){ //la priorite suivante est la priorite inferieur
		nb_boucle_max = 11; //le nombre de boucle maximum pour parcourir toute la table
	}else{ //la priorite suivante est la priorite suivante dans la table cpu
		nb_boucle_max = 100; //le nombre de boucle maximum pour parcourir toute la table
	}
	
	while(nb_boucle <= nb_boucle_max && Nb_elu == 0){ //On s'assure que on a pas encore parcourus toute la table cpu et que aucun processus n'a ete elu
		switch(priorite_a_elir){
			case 0:
				if(isEmpty(Attente_Priorite0)){//si la queue de priorite est vide
					//ne rien faire
				}else{
					//donnee_admin->Election = 1;
					Nb_elu = 1; //Un processus a ete elu
					processus_elu = premier_element(Attente_Priorite0); //on recupere l'element
					printf("Le processus %d a ete elu\n", processus_elu); //on affiche a l'utilisateur le processus elu
					donnee_admin->processus_elu = processus_elu; //indique a tous le processus elu
					pthread_cond_signal (&dormir[processus_elu]); //envoie un signal pour debloquer le processus elu
					pthread_cond_wait (&fin_exec[processus_elu], &mutex3[processus_elu]); //attend que le thread renvoie un signal indiquant qu'il a finit
				}
				break;
			case 1:
				if(isEmpty(Attente_Priorite1)){
					//ne rien faire
				}else{
					//donnee_admin->Election = 1;
					Nb_elu = 1;
					processus_elu = premier_element(Attente_Priorite1);
					printf("Le processus %d a ete elu\n", processus_elu);
					donnee_admin->processus_elu = processus_elu;
					pthread_cond_signal (&dormir[processus_elu]);
					pthread_cond_wait (&fin_exec[processus_elu], &mutex3[processus_elu]);
				}
				break;
			case 2:
				if(isEmpty(Attente_Priorite2)){
					//ne rien faire
				}else{
					//donnee_admin->Election = 1;
					Nb_elu = 1;
					processus_elu = premier_element(Attente_Priorite2);
					printf("Le processus %d a ete elu\n", processus_elu);
					donnee_admin->processus_elu = processus_elu;
					pthread_cond_signal (&dormir[processus_elu]);
					pthread_cond_wait (&fin_exec[processus_elu], &mutex3[processus_elu]);
				}
				break;
			case 3:
				if(isEmpty(Attente_Priorite3)){
					//ne rien faire
				}else{
					//donnee_admin->Election = 1;
					Nb_elu = 1;
					processus_elu = premier_element(Attente_Priorite3);
					printf("Le processus %d a ete elu\n", processus_elu);
					donnee_admin->processus_elu = processus_elu;
					pthread_cond_signal (&dormir[processus_elu]);
					pthread_cond_wait (&fin_exec[processus_elu], &mutex3[processus_elu]);
				}
				break;
			case 4:
				if(isEmpty(Attente_Priorite4)){
					//ne rien faire
				}else{
					//donnee_admin->Election = 1;
					Nb_elu = 1;
					processus_elu = premier_element(Attente_Priorite4);
					printf("Le processus %d a ete elu\n", processus_elu);
					donnee_admin->processus_elu = processus_elu;
					pthread_cond_signal (&dormir[processus_elu]);
					pthread_cond_wait (&fin_exec[processus_elu], &mutex3[processus_elu]);
				}
				break;
			case 5:
				if(isEmpty(Attente_Priorite5)){
					//ne rien faire
				}else{
					//donnee_admin->Election = 1;
					Nb_elu = 1;
					processus_elu = premier_element(Attente_Priorite5);
					printf("Le processus %d a ete elu\n", processus_elu);
					donnee_admin->processus_elu = processus_elu;
					pthread_cond_signal (&dormir[processus_elu]);
					pthread_cond_wait (&fin_exec[processus_elu], &mutex3[processus_elu]);
				}
				break;
			case 6:
				if(isEmpty(Attente_Priorite6)){
					//ne rien faire
				}else{
					//donnee_admin->Election = 1;
					Nb_elu = 1;
					processus_elu = premier_element(Attente_Priorite6);
					printf("Le processus %d a ete elu\n", processus_elu);
					donnee_admin->processus_elu = processus_elu;
					pthread_cond_signal (&dormir[processus_elu]);
					pthread_cond_wait (&fin_exec[processus_elu], &mutex3[processus_elu]);
				}
				break;
			case 7:
				if(isEmpty(Attente_Priorite7)){
					//ne rien faire
				}else{
					//donnee_admin->Election = 1;
					Nb_elu = 1;
					processus_elu = premier_element(Attente_Priorite7);
					printf("Le processus %d a ete elu\n", processus_elu);
					donnee_admin->processus_elu = processus_elu;
					pthread_cond_signal (&dormir[processus_elu]);
					pthread_cond_wait (&fin_exec[processus_elu], &mutex3[processus_elu]);
				}
				break;	
			case 8:
				if(isEmpty(Attente_Priorite8)){
					//ne rien faire
				}else{
					//donnee_admin->Election = 1;
					Nb_elu = 1;
					processus_elu = premier_element(Attente_Priorite8);
					printf("Le processus %d a ete elu\n", processus_elu);
					donnee_admin->processus_elu = processus_elu;
					pthread_cond_signal (&dormir[processus_elu]);
					pthread_cond_wait (&fin_exec[processus_elu], &mutex3[processus_elu]);
				}
				break;
			case 9:
				if(isEmpty(Attente_Priorite9)){
					//ne rien faire
				}else{
					//donnee_admin->Election = 1;
					Nb_elu = 1;
					processus_elu = premier_element(Attente_Priorite9);
					printf("Le processus %d a ete elu\n", processus_elu);
					donnee_admin->processus_elu = processus_elu;
					pthread_cond_signal (&dormir[processus_elu]);
					pthread_cond_wait (&fin_exec[processus_elu], &mutex3[processus_elu]);
				}
				break;	
			case 10:
				if(isEmpty(Attente_Priorite10)){
					//ne rien faire
				}else{
					//donnee_admin->Election = 1;
					Nb_elu = 1;
					processus_elu = premier_element(Attente_Priorite10);
					printf("Le processus %d a ete elu\n", processus_elu);
					donnee_admin->processus_elu = processus_elu;
					pthread_cond_signal (&dormir[processus_elu]);
					pthread_cond_wait (&fin_exec[processus_elu], &mutex3[processus_elu]);
				}
				break;
			default : //erreur
				printf("Erreur la priorite %d n'existe pas\n", priorite_a_elir);
				finprgm();
				break;																				
		}
		nb_boucle++; //on incremente le nombre de boucle
		if(donnee_utilisateur->type == 0){
			priorite_a_elir++;//on actualise la priorite
			if(priorite_a_elir > 10){ //si la priorite est superieur on repasse a 0
				priorite_a_elir = 0;
			}
		}else{
			quantum_actuel++; //on passe au quantum suivnat
			if(quantum_actuel >= 100){ //si le qauntum est superieur ou egal a 100 on a fini la table cpu
				quantum_actuel = 0; //on remet le quantum a 0
			}
			priorite_a_elir = table_cpu[quantum_actuel]; //on actualise la priorite a elir
		}
		if(donnee_admin->nbProcessActif > 0 && nb_boucle == nb_boucle_max){//tant que on a rien trouve on recommence
			nb_boucle = 0;
		}
	}
	printf("\n"); 
	
	shmdt(donnee_admin);//detache la memoire partage
	shmdt(process);//detache la memoire partage
	shmdt(table_cpu);//detache la memoire partage
	shmdt(donnee_utilisateur);
}


