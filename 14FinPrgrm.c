#include "0INCLUDE.h"
#include "5Structure.h"
#include "3FixedVariable.h"
#include "4MoniteurVar.h"
#include "11Queue.h"
//---------------------------------------------------- fin programme --------------------------------------------------------------------------------

//fonction qui met fin au programme 
void finprgm(){
	
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

//___________________________________________________ libere memoire partage ______________________________________________________________

	shmdt(donnee_admin);//detache la memoire partage
	shmdt(process);//detache la memoire partage
	shmdt(table_cpu);//detache la memoire partage
	shmdt(donnee_utilisateur);
	
	shmctl(donnee_admin,IPC_RMID,NULL); //supprime les memoire partage
	shmctl(process,IPC_RMID,NULL); //supprime les memoire partage
	shmctl(table_cpu,IPC_RMID,NULL); //supprime les memoire partage
	shmctl(donnee_utilisateur,IPC_RMID,NULL);
	
	libere_queue();
	
	exit(0);	
}
