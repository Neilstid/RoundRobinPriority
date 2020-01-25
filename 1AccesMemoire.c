#include "0INCLUDE.h"
#include "5Structure.h"
#include "3FixedVariable.h"
#include "4MoniteurVar.h"
#include "11Queue.h"

//Attribue l'acces au memoire partage de la structure "Utilisateur"
int acces_utilisateur_memoire_partage(){
	int shmid; //creer l'id
	
	//taille segment
	int TAILLE_SHM;
	TAILLE_SHM = sizeof(StructUtilisateur); //alloue la memoire necessaire
	
	shmid = shmget(key_utilisateur, TAILLE_SHM, 0644 | IPC_CREAT);
	
	return shmid; //retrourne l'id
}


//Attribue l'acces au memoire partage de la structure "administratif"
int acces_administratif_memoire_partage(){
	int shmid; //creer l'id
	
	//taille segment
	int TAILLE_SHM;
	TAILLE_SHM = sizeof(StructAdmin); //alloue la memoire necessaire
	
	shmid = shmget(key_admin, TAILLE_SHM, 0644 | IPC_CREAT);
	
	return shmid; //retrourne l'id
}

int acces_processus_memoire_partage(){
	int shmid; //creer l'id
	
	//taille segment
	int TAILLE_SHM;
	TAILLE_SHM = imple_nb_processus_max*sizeof(StructProcess); //alloue la memoire necessaire
	
	shmid = shmget(key_processus, TAILLE_SHM, 0644 | IPC_CREAT);
	
	return shmid; //retrourne l'id
}

//attribue l'acces a la table cpu
int acces_table_cpu_memoire_partage(){
	int shmid; //creer l'id
	
	//taille segment
	int TAILLE_SHM;
	TAILLE_SHM = 100*sizeof(int); //alloue la memoire necessaire
	
	shmid = shmget(key_cpu, TAILLE_SHM, 0644 | IPC_CREAT);
	
	return shmid; //retrourne l'id
}

