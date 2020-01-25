#include "0INCLUDE.h"
#include "5Structure.h"
#include "3FixedVariable.h"
#include "4MoniteurVar.h"
#include "11Queue.h"
//---------------------------------------------------- Thread ---------------------------------------------------------------------

void *threadFunction (void *arg)
{
//___________________________________________________ recuperation memoire partage ______________________________________________________________
	//donne acces au processus
 	StructProcess *process;
	int shmid;
	shmid = acces_processus_memoire_partage();
	process = (StructProcess *) shmat(shmid, NULL, 0);
 	
 	//acces au donne lier a l'execution
 	StructAdmin *donnee_admin;
   	int shmid_admin;
	shmid_admin = acces_administratif_memoire_partage();
   	donnee_admin = (StructAdmin *) shmat(shmid_admin, NULL, 0);

//___________________________________________________ initialisation du thread ______________________________________________________________
 	
 	//recupere les info du thread
 	int threadNum = (int)arg;
    pid_t tid = syscall(SYS_gettid);
    printf("Je suis le thread numero : %d avec le Thread ID : %d\n",threadNum,(int)tid); //indique a l'utilisateur que le thread a ete creer
    process->tid[threadNum] = tid; //met le tid dans la structure

	//envoie un signal au main pour indiquer que le processus va entrer en sommeil prochainement et qu'il s'ait bien creer
    pthread_cond_signal (&creation_thread[threadNum]);
    
//___________________________________________________ thread en execution ______________________________________________________________
    
    while(process->status[threadNum] == 1){//Tant que le processus est en cours d'execution
    	pthread_cond_signal (&fin_exec[threadNum]); //indique que le thread a fini son quantum
		pthread_cond_wait (&dormir[threadNum], &mutex[threadNum]);//on le met en sommeil en attendant son reveil par l'election 
		
 		changer_priorite(); //le thread change de priorite
 		printf("\n");
	}

//___________________________________________________ fin du thread ______________________________________________________________
	
	donnee_admin->nb_procssus_fini++; //indique que le processus est fini
	
 	printf("Le thread %d se termine\n", threadNum); //indique a l'utilisateur que le thread est terminer
	printf("\n");
    	
 	pthread_cond_signal (&fin_exec[threadNum]); //indique que le thread a fini son quantum
    donnee_admin->nbProcessActif--;
    
    pthread_detach(pthread_self()); //libere le thread
    pthread_exit(NULL); //Sort
}

//change la priorite du processus
void changer_priorite(){

	//donne acces au processus
 	StructProcess *process;
	int shmid;
	shmid = acces_processus_memoire_partage();
	process = (StructProcess *) shmat(shmid, NULL, 0);

	//donne acces au var lie aa l'excution
	StructAdmin *donnee_admin;
   	int shmid_admin;
	shmid_admin = acces_administratif_memoire_partage();
   	donnee_admin = (StructAdmin *) shmat(shmid_admin, NULL, 0);

	int priorite_a_elir,processus_elu;//respectivement la priorite qui doit etre elu et l'id du processus elu

	priorite_a_elir = process->priorite[donnee_admin->processus_elu];//recupere la priorite du processus

	printf("\n----------------------------  Thread %d  ----------------------------\n", donnee_admin->processus_elu);

//___________________________________________________ priorite du processus ______________________________________________________________

	switch(priorite_a_elir){
		case 0:
			processus_elu = retirer(Attente_Priorite0);//retire le processus de sa file (il est forcement en haut de sa pile)
			printf("Le processus %d a ete elu\n", processus_elu); //affiche celui retirer
			if(process->temps_exec[processus_elu] - donnee_admin->time_quantum > 0){ //si il ne se termine pas 
				ajouter(Attente_Priorite1,processus_elu);//ajoute a la file suivante
				printf("Priorite du processus : %d --> %d\n", process->priorite[processus_elu], process->priorite[processus_elu]+1);
				process->priorite[processus_elu]++;//on incremente sa priorite
				printf("Temps d'execution :     %d --> %d\n", process->temps_exec[processus_elu], process->temps_exec[processus_elu] - donnee_admin->time_quantum);
				process->temps_exec[processus_elu] -= donnee_admin->time_quantum;//on retire de son temps d'exec restant le temps d'un quantum
			}else{//si le processus se termine
				process->temps_exec[processus_elu] -= donnee_admin->time_quantum;//on retire de son temps d'exec restant le temps d'un quantum
				printf("Le processus %d s'est terminee\n", processus_elu); //On indique que le processus est termine
				process->status[processus_elu] = 2; //on change son status a terminer
			}	
			break;
		case 1:
			processus_elu = retirer(Attente_Priorite1);
			printf("Le processus %d a ete elu\n", processus_elu);
			if(process->temps_exec[processus_elu] - donnee_admin->time_quantum > 0){
				ajouter(Attente_Priorite2,processus_elu);
				printf("Priorite du processus : %d --> %d\n", process->priorite[processus_elu], process->priorite[processus_elu]+1);
				process->priorite[processus_elu]++;
				printf("Temps d'execution :     %d --> %d\n", process->temps_exec[processus_elu], process->temps_exec[processus_elu] - donnee_admin->time_quantum);
				process->temps_exec[processus_elu] -= donnee_admin->time_quantum;
			}else{
				process->temps_exec[processus_elu] -= donnee_admin->time_quantum;//on retire de son temps d'exec restant le temps d'un quantum
				printf("Le processus %d s'est terminee\n", processus_elu);
				process->status[processus_elu] = 2;
			}	
			break;
		case 2:
			processus_elu = retirer(Attente_Priorite2);
			printf("Le processus %d a ete elu\n", processus_elu);
			if(process->temps_exec[processus_elu] - donnee_admin->time_quantum > 0){
				ajouter(Attente_Priorite3,processus_elu);
				printf("Priorite du processus : %d --> %d\n", process->priorite[processus_elu], process->priorite[processus_elu]+1);
				process->priorite[processus_elu]++;
				printf("Temps d'execution :     %d --> %d\n", process->temps_exec[processus_elu], process->temps_exec[processus_elu] - donnee_admin->time_quantum);
				process->temps_exec[processus_elu] -= donnee_admin->time_quantum;
			}else{
				process->temps_exec[processus_elu] -= donnee_admin->time_quantum;//on retire de son temps d'exec restant le temps d'un quantum
				printf("Le processus %d s'est terminee\n", processus_elu);
				process->status[processus_elu] = 2;
			}	
			break;
		case 3:
			processus_elu = retirer(Attente_Priorite3);
			printf("Le processus %d a ete elu\n", processus_elu);
			if(process->temps_exec[processus_elu] - donnee_admin->time_quantum > 0){
				ajouter(Attente_Priorite4,processus_elu);
				printf("Priorite du processus : %d --> %d\n", process->priorite[processus_elu], process->priorite[processus_elu]+1);
				process->priorite[processus_elu]++;
				printf("Temps d'execution :     %d --> %d\n", process->temps_exec[processus_elu], process->temps_exec[processus_elu] - donnee_admin->time_quantum);
				process->temps_exec[processus_elu] -= donnee_admin->time_quantum;
			}else{
				process->temps_exec[processus_elu] -= donnee_admin->time_quantum;//on retire de son temps d'exec restant le temps d'un quantum
				printf("Le processus %d s'est terminee\n", processus_elu);
				process->status[processus_elu] = 2;
			}	
			break;
		case 4:
			processus_elu = retirer(Attente_Priorite4);
			printf("Le processus %d a ete elu\n", processus_elu);
			if(process->temps_exec[processus_elu] - donnee_admin->time_quantum > 0){
				ajouter(Attente_Priorite5,processus_elu);
				printf("Priorite du processus : %d --> %d\n", process->priorite[processus_elu], process->priorite[processus_elu]+1);
				process->priorite[processus_elu]++;
				printf("Temps d'execution :     %d --> %d\n", process->temps_exec[processus_elu], process->temps_exec[processus_elu] - donnee_admin->time_quantum);
				process->temps_exec[processus_elu] -= donnee_admin->time_quantum;
			}else{
				process->temps_exec[processus_elu] -= donnee_admin->time_quantum;//on retire de son temps d'exec restant le temps d'un quantum
				printf("Le processus %d s'est terminee\n", processus_elu);
				process->status[processus_elu] = 2;
			}	
			break;
		case 5:
			processus_elu = retirer(Attente_Priorite5);
			printf("Le processus %d a ete elu\n", processus_elu);
			if(process->temps_exec[processus_elu] - donnee_admin->time_quantum > 0){
				ajouter(Attente_Priorite6,processus_elu);
				printf("Priorite du processus : %d --> %d\n", process->priorite[processus_elu], process->priorite[processus_elu]+1);
				process->priorite[processus_elu]++;
				printf("Temps d'execution :     %d --> %d\n", process->temps_exec[processus_elu], process->temps_exec[processus_elu] - donnee_admin->time_quantum);
				process->temps_exec[processus_elu] -= donnee_admin->time_quantum;
			}else{
				process->temps_exec[processus_elu] -= donnee_admin->time_quantum;//on retire de son temps d'exec restant le temps d'un quantum
				printf("Le processus %d s'est terminee\n", processus_elu);
				process->status[processus_elu] = 2;
			}	
			break;
		case 6:
			processus_elu = retirer(Attente_Priorite6);
			printf("Le processus %d a ete elu\n", processus_elu);
			if(process->temps_exec[processus_elu] - donnee_admin->time_quantum > 0){
				ajouter(Attente_Priorite7,processus_elu);
				printf("Priorite du processus : %d --> %d\n", process->priorite[processus_elu], process->priorite[processus_elu]+1);
				process->priorite[processus_elu]++;
				printf("Temps d'execution :     %d --> %d\n", process->temps_exec[processus_elu], process->temps_exec[processus_elu] - donnee_admin->time_quantum);
				process->temps_exec[processus_elu] -= donnee_admin->time_quantum;
			}else{
				process->temps_exec[processus_elu] -= donnee_admin->time_quantum;//on retire de son temps d'exec restant le temps d'un quantum
				printf("Le processus %d s'est terminee\n", processus_elu);
				process->status[processus_elu] = 2;
			}	
			break;
		case 7:
			processus_elu = retirer(Attente_Priorite7);
			printf("Le processus %d a ete elu\n", processus_elu);
			if(process->temps_exec[processus_elu] - donnee_admin->time_quantum > 0){
				ajouter(Attente_Priorite8,processus_elu);
				printf("Priorite du processus : %d --> %d\n", process->priorite[processus_elu], process->priorite[processus_elu]+1);
				process->priorite[processus_elu]++;
				printf("Temps d'execution :     %d --> %d\n", process->temps_exec[processus_elu], process->temps_exec[processus_elu] - donnee_admin->time_quantum);
				process->temps_exec[processus_elu] -= donnee_admin->time_quantum;
			}else{
				process->temps_exec[processus_elu] -= donnee_admin->time_quantum;//on retire de son temps d'exec restant le temps d'un quantum
				printf("Le processus %d s'est terminee\n", processus_elu);
				process->status[processus_elu] = 2;
			}	
			break;	
		case 8:
			processus_elu = retirer(Attente_Priorite8);
			printf("Le processus %d a ete elu\n", processus_elu);
			if(process->temps_exec[processus_elu] - donnee_admin->time_quantum > 0){
				ajouter(Attente_Priorite9,processus_elu);
				printf("Priorite du processus : %d --> %d\n", process->priorite[processus_elu], process->priorite[processus_elu]+1);
				process->priorite[processus_elu]++;
				printf("Temps d'execution :     %d --> %d\n", process->temps_exec[processus_elu], process->temps_exec[processus_elu] - donnee_admin->time_quantum);
				process->temps_exec[processus_elu] -= donnee_admin->time_quantum;
			}else{
				process->temps_exec[processus_elu] -= donnee_admin->time_quantum;//on retire de son temps d'exec restant le temps d'un quantum
				printf("Le processus %d s'est terminee\n", processus_elu);
				process->status[processus_elu] = 2;
			}	
			break;
		case 9:
			processus_elu = retirer(Attente_Priorite9);
			printf("Le processus %d a ete elu\n", processus_elu);
			if(process->temps_exec[processus_elu] - donnee_admin->time_quantum > 0){
				ajouter(Attente_Priorite10,processus_elu);
				printf("Priorite du processus : %d --> %d\n", process->priorite[processus_elu], process->priorite[processus_elu]+1);
				process->priorite[processus_elu]++;
				printf("Temps d'execution :     %d --> %d\n", process->temps_exec[processus_elu], process->temps_exec[processus_elu] - donnee_admin->time_quantum);
				process->temps_exec[processus_elu] -= donnee_admin->time_quantum;
			}else{
				printf("Le processus %d s'est terminee\n", processus_elu);
				process->status[processus_elu] = 2;
			}	
			break;
		case 10:
			if(isEmpty(Attente_Priorite10)){
				//ne rien faire
			}else{
				processus_elu = premier_element(Attente_Priorite10);
				printf("Le processus %d a ete elu\n", processus_elu);
				if(process->temps_exec[processus_elu] - donnee_admin->time_quantum > 0){
					printf("Priorite du processus : %d\n", process->priorite[processus_elu]);
					printf("Temps d'execution :     %d --> %d\n", process->temps_exec[processus_elu], process->temps_exec[processus_elu] - donnee_admin->time_quantum);
					process->temps_exec[processus_elu] -= donnee_admin->time_quantum;
				}else{
					process->temps_exec[processus_elu] -= donnee_admin->time_quantum;//on retire de son temps d'exec restant le temps d'un quantum
					printf("Le processus %d s'est terminee\n", processus_elu);
					processus_elu = retirer(Attente_Priorite10);
					process->status[processus_elu] = 2;
				}	
			}
			break;
		default :
			printf("Erreur la priorite %d n'existe pas\n", priorite_a_elir);
			finprgm();
			break;																				
	}
	printf("Le processus %d s'est bien execute\n", processus_elu);
}


