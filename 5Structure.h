#include "3FixedVariable.h"


//---------------------------------------------------- Structure processus administrative ---------------------------------------------------------------------

/*Stucture des parametre lier a l'execution 
contient respectivement le temps d'un quantum, le quanctum actuel, le nombre de processus, le nombre de processus fini, le temps entre chaque processus, le dernier processus elu, le nombre de processus arrive au dernier quantum, un tableau contenant les id des processus venant d'arrive
*/

struct processus_administratif 
{ 
    int time_quantum, quantum_actuel, nb_processus, nb_procssus_fini, nbProcessActif, processus_elu, nbArrive; 
    int IDArrive[imple_nb_processus_max];
}; 

typedef struct processus_administratif StructAdmin;

//---------------------------------------------------- Structure choix utilisateur ---------------------------------------------------------------------
//Structure pour des vraiables lier a l'execution du programe et quisont rentre par l'utilisateur et qui ne sont pas directement relier au processus
struct valeur_utilisateur
{
	int temps_affichage, type; 
};

typedef struct valeur_utilisateur StructUtilisateur;

//structure processus
struct processus{
    int quantum_arrive[imple_nb_processus_max]; //Arrive du processus
    int temps_exec[imple_nb_processus_max]; //temps d'execution restant
    int priorite[imple_nb_processus_max]; //Priorite actuelle du processus
    pid_t tid[imple_nb_processus_max]; //pid du processus
    int status[imple_nb_processus_max]; //indique dans quel etat est le processus 0:Pas arrive, 1:Arrive mais pas encore fini 2:execution fini
};

typedef struct processus StructProcess;

/*Stucture de la queue 
le premier element de la queue, le dernier, et la taille de la queue
la capacite de la queue
le tableau avec les valeur
*/
struct Queue 
{ 
    int premier, dernier, taille; 
    unsigned capacite; 
    int* array; 
}; 

typedef struct Queue StructQueue;
//creer les queue de priorite

StructQueue *Attente_Priorite0; 
StructQueue *Attente_Priorite1; 
StructQueue *Attente_Priorite2; 
StructQueue *Attente_Priorite3; 
StructQueue *Attente_Priorite4; 
StructQueue *Attente_Priorite5; 
StructQueue *Attente_Priorite6; 
StructQueue *Attente_Priorite7; 
StructQueue *Attente_Priorite8; 
StructQueue *Attente_Priorite9; 
StructQueue *Attente_Priorite10;  
