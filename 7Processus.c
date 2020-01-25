#include "0INCLUDE.h"
#include "5Structure.h"
#include "3FixedVariable.h"
#include "4MoniteurVar.h"
#include "11Queue.h"
//---------------------------------------------------- Processus ---------------------------------------------------------------------

 //----------------------------------------------------modification des processus -----------------------------------------------------------------

//modifie un processus
void modif_process(){
	//donne acces au donne des processus en espace de memoire partage
    StructProcess *process;
	int shmid, id, nouvelle_valeur;
	shmid = acces_processus_memoire_partage();
	process = (StructProcess *) shmat(shmid, NULL, 0);
	
	//on selectionne le processu a modifie
	printf("Quel processus voulez-vous modifier ?\n");
	printf("Choix : \t");
	scanf("%d", &id);
	
	int modif_arrive;
	if(process->status[id] != 2){ //verifie que le processus n'est pas deja fini
		if(process->status[id] == 0){//verifie que le processus n'est pas encore arrive (pour la date d'arrive)
			printf("Voulez-vous modifier le quantum d'arrive ?\n"); 
			printf("[1] : Oui\n");
			printf("[2] : Non\n");
			printf("Choix : \t");
			scanf("%d", &modif_arrive); //recupere le choix
			if(modif_arrive == 1){ //ajouter une condition pour verifier que le quantum d'arrive est supperieur au quantum actuel
				printf("Nombre de quantum de temps avant arrive du processus : \t");
				scanf("%d", &nouvelle_valeur);
				process->quantum_arrive[id] = nouvelle_valeur; //mise a jour de la valeur du quantum d'arrive
			}
			
					
			//priorite
			printf("Voulez-vous modifier la priorite ?\n");
			printf("[1] : Oui\n");
			printf("[2] : Non\n");
			printf("Choix : \t");
			scanf("%d", &modif_arrive);
			if(modif_arrive == 1){
				printf("Nouvelle valeur : \t");
				scanf("%d", &nouvelle_valeur);
				if(nouvelle_valeur != process->priorite[id] && nouvelle_valeur >= 0 && nouvelle_valeur<=10){ //verification de la valeur rentrer
					process->priorite[id] = nouvelle_valeur; 
				}
			}	
		}
		
		//temps d'excution
		printf("Voulez-vous modifier le temps d'execution ?\n");
		printf("[1] : Oui\n");
		printf("[2] : Non\n");
		printf("Choix : \t");
		scanf("%d", &modif_arrive);
		if(modif_arrive == 1){
			printf("Nouvelle valeur : \t");
			scanf("%d", &nouvelle_valeur);
			process->temps_exec[id] = nouvelle_valeur;
		}	
			
	}else{//pour un processus deja terminer
		printf("Ce procssus est deja terminer\n");
	}
	
	shmdt(process);//detache la memoire partage
	
}



//---------------------------------------------------- Arriver des processus ---------------------------------------------------------------------

//fonction qui trouve quel(s) processus arrive a un quantum n
void arriver_processus(){

	//donne acces a la structure administratif
	StructAdmin *donnee_admin;
   	int shmid_admin;
	shmid_admin = acces_administratif_memoire_partage();
   	donnee_admin = (StructAdmin *) shmat(shmid_admin, NULL, 0);

	int process_actuel;
	//respectivement le numero du processus que on regarde, la quantum le plus petit de l'intervalle, le quantum le plus grand de l'intervalle

	//donne acces a la structure processus
	StructProcess *process;
	int shmid;
	shmid = acces_processus_memoire_partage();
	process = (StructProcess *) shmat(shmid, NULL, 0);
	
	donnee_admin->nbArrive = 0;//pour le tableau de renvoie
	
	for(process_actuel = 0; process_actuel < donnee_admin->nb_processus; process_actuel++){//parcours tous les processus
		if(process->status[process_actuel] == 0){//ne regarde que ceux qui ne sont pas encore arrive
			if(process->quantum_arrive[process_actuel] == 0){//si le quantum d'arrive est egal a 0, il arrive
				
				process->status[process_actuel] = 1; //on change le status du processus en arriver
				//on indique a l'utilisateur que le processus est arrive
				printf("Le processus %d vient d'arriver, sa priorite est : %d \n",process_actuel,process->priorite[process_actuel]); 
				ranger_processus_file(process_actuel, process->priorite[process_actuel]); //on  met le processus dans la bonne file d'attente
				donnee_admin->IDArrive[donnee_admin->nbArrive] = process_actuel; //on indique l'id du processus arrive
				donnee_admin->nbArrive++; //on incremente le nombre processus arrive a ce quantum
				donnee_admin->nbProcessActif++;
				
			}else{
			
				process->quantum_arrive[process_actuel]--; //on decremente le quantum d'arrive qui est comme une sorte de compte a rebours
	
			}
		}
	}
	
	shmdt(donnee_admin);//detache la memoire partage
	shmdt(process);//detache la memoire partage
	
}

//fonction qui range les processus dans leur file d'attente
void ranger_processus_file(int id, int priorite){
	switch(priorite){//selon la priorite du processus
		case 0:
			ajouter(Attente_Priorite0,id); //ajoute a la priorite 0
			break;
		case 1:
			ajouter(Attente_Priorite1,id);
			break;
		case 2:
			ajouter(Attente_Priorite2,id);
			break;
		case 3:
			ajouter(Attente_Priorite3,id);
			break;
		case 4:
			ajouter(Attente_Priorite4,id);
			break;
		case 5:
			ajouter(Attente_Priorite5,id);
			break;
		case 6:
			ajouter(Attente_Priorite6,id);
			break;
		case 7:
			ajouter(Attente_Priorite7,id);
			break;	
		case 8:
			ajouter(Attente_Priorite8,id);
			break;	
		case 9:
			ajouter(Attente_Priorite9,id);
			break;	
		case 10:
			ajouter(Attente_Priorite10,id);
			break;	
		default : //erreur
			printf("Erreur la priorite %d n'existe pas\n", priorite);
			finprgm();
			break;																				
	}
	printf("Le processus a ete ajoute a sa priorite\n");
}


//----------------------------------------------------Affichage des processus -----------------------------------------------------------------

//afiche un processus
void afficher_processus(){

//___________________________________________________ acces au memoire partage ______________________________________________________________
	//donne acces au donne des processus en espace de memoire partage
    StructProcess *process;
	int shmid, id;
	shmid = acces_processus_memoire_partage();
	process = (StructProcess *) shmat(shmid, NULL, 0);
	
	//initialisation des premieres variables et accces au donne pour l'execution
	StructAdmin *donnee_admin;
   	int shmid_admin;
	shmid_admin = acces_administratif_memoire_partage();
   	donnee_admin = (StructAdmin *) shmat(shmid_admin, NULL, 0);
	
	//on selectionne le processus a afficher
	printf("Quel processus voulez-vous afficher ?\n");
	printf("Choix : \t");
	scanf("%d", &id);
	
	printf("Parametre actuel du processus %d :\n", id);
	switch(process->status[id]){
		case 0 :
			printf("Le processus n'est pas encore arrive\n");
			printf("Le processus arrive dans %d quantum, soit au %d quantum\n", process->quantum_arrive[id], process->quantum_arrive[id]+donnee_admin->quantum_actuel);
			break;
		case 1 :
			printf("Le processus est en cours d'execution, il porte le tid %d\n", process->tid[id]);
			break;
		case 2 :
			printf("Le processus a deja terminer son execution\n");
			break;
		default :
			printf("Erreur : Le status du processus %d n'existe pas\n", id);
			finprgm();
			break;
	}
	
	printf("Le temps d'execution restant au processus est %d\n", process->temps_exec[id]);
	printf("La priorite du processus est %d", process->priorite[id]);
	
	shmdt(donnee_admin);//detache la memoire partage
	shmdt(process);//detache la memoire partage
	
}

//----------------------------------------------------Implementation des processus -----------------------------------------------------------------

//creation de processus aleatoire
void Implementation_aleatoire(){

//___________________________________________________ acces au memoire partage ______________________________________________________________	
	//acces au processus
    StructProcess *init_process;
	int shmid;
	shmid = acces_processus_memoire_partage();
	init_process = (StructProcess *) shmat(shmid, NULL, 0);

	//acces au donnee lier a l'execution
	StructAdmin *donnee_admin;
   	int shmid_admin;
	shmid_admin = acces_administratif_memoire_partage();
   	donnee_admin = (StructAdmin *) shmat(shmid_admin, NULL, 0);

	//initialisation du pseudo random
	srand(time(NULL));

//___________________________________________________ creation des processus ______________________________________________________________
	
	int nb_processus, id;
	nb_processus = rand()%nb_processus_max_aleatoire+1;
	printf("\nNombre de processus: %d\t\n", nb_processus);

	if(imple_nb_processus_max < nb_processus){
		printf("Erreur : Il y a trop de processus, %d au total",nb_processus); 
	}

    int quantum_arrive_temp[nb_processus], temps_exec_temp[nb_processus], priorite_temp[nb_processus], time_quantum;
   	for(id = 0; id < nb_processus; id++){
   		
   		//parametre de chaque processus
        printf("\nConfiguration du processus %d \n", id);
        
        //date arrive
        quantum_arrive_temp[id] = floor(rand()%Arrive_max);
		printf("Date arrivee du processus: %d\t", quantum_arrive_temp[id]);
 		
 		//temps execution
 		temps_exec_temp[id] = floor(rand()%Temps_exec_max)+1;
        printf("Temps d'execution: %d\t",temps_exec_temp[id]);
        
		//status du processus par default : endomie
		init_process->status[id] = 0;         

        //recupere une priorite
        priorite_temp[id] = round(rand()%10);
        printf("Priorite du processus: %d\n", priorite_temp[id]);
    }
    memcpy(init_process->quantum_arrive, quantum_arrive_temp, sizeof(quantum_arrive_temp));
    memcpy(init_process->temps_exec, temps_exec_temp, sizeof(temps_exec_temp));
	memcpy(init_process->priorite, priorite_temp, sizeof(priorite_temp));

	
	//definition du quantum de temps
	int quantum_temp;
	quantum_temp = round(rand()%Quantum_max)+1;			
    printf("\nTemps d'un quantum: %d\t", quantum_temp);
    
    
    //Creation de la table d'allocation CPU
    printf("\n\nConfigurer la table d'allocation CPU : \n");
    
	//renvoie les parametres au main
	donnee_admin->nb_processus = nb_processus;
	donnee_admin->time_quantum = quantum_temp;
	
	shmdt(donnee_admin);//detache la memoire partage
	shmdt(init_process);//detache la memoire partage
	
}

//creation des processus via un fichier
void Implementation_fichier(){
//___________________________________________________ recupere memoire partage ______________________________________________________________	
    StructProcess *init_process;
	int shmid;
	shmid = acces_processus_memoire_partage();
	init_process = (StructProcess *) shmat(shmid, NULL, 0);

	StructAdmin *donnee_admin;
   	int shmid_admin;
	shmid_admin = acces_administratif_memoire_partage();
   	donnee_admin = (StructAdmin *) shmat(shmid_admin, NULL, 0);

	//recupere l'acces a la structure utilisateur
	StructUtilisateur *donnee_utilisateur;
	int shmid_utilisateur;
	shmid_utilisateur = acces_utilisateur_memoire_partage();
	donnee_utilisateur = (StructUtilisateur *) shmat(shmid_utilisateur, NULL, 0);
//___________________________________________________ Ouverture du fichier ______________________________________________________________	
	//recupere le nom du fichier
	char nom_fichier[100];
	printf("Entrer le nom du fichier (le nom doit finir par \".txt\") :\t");
	scanf("%s", &nom_fichier);

	//ouvre le fichier
	FILE* fichier = fopen(nom_fichier, "r");

    int time_quantum_temp = 0,nb_process_temp = 0;
	int temps_affichage = 0;
	
    if (fichier != NULL) //verifie que le fichier est bie::n ouvert
    {
        // On peut lire et écrire dans le fichier
        printf("Le fichier s'est ouvert correctement\n");
        
    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier %s \n", nom_fichier);
        finprgm();
    }
    
//___________________________________________________ recuperation des donnee ______________________________________________________________
    // lire le qunatum de temps
    fscanf(fichier,"%d",&time_quantum_temp);
    printf("qunatum de temps : %d\n", time_quantum_temp);
    donnee_admin->time_quantum = time_quantum_temp;
    
    // lire le compteur de temps
    fscanf(fichier,"%d",&nb_process_temp);
	printf("nombre de processus : %d\n", nb_process_temp);
	donnee_admin->nb_processus = nb_process_temp;
	
	int quantum_arrive_temp[nb_process_temp],temps_exec_temp[nb_process_temp],priorite_temp[nb_process_temp];
	//lis les processus
	for(int i = 0; i < nb_process_temp; i++){
	
		fscanf(fichier,"%d %d %d",&quantum_arrive_temp[i],&temps_exec_temp[i],&priorite_temp[i]);
		
		printf("Processus : %d\n\tArrive : %d\n\tTemps execution : %d\n\tPriorite : %d\n\n",i,quantum_arrive_temp[i],temps_exec_temp[i],priorite_temp[i]);
	
		init_process->status[i] = 0;
	}
	
	memcpy(init_process->quantum_arrive, quantum_arrive_temp, sizeof(quantum_arrive_temp));
    memcpy(init_process->temps_exec, temps_exec_temp, sizeof(temps_exec_temp));
	memcpy(init_process->priorite, priorite_temp, sizeof(priorite_temp));
	
	//lis le temps d'affichage
	fscanf(fichier,"%d", &temps_affichage);
	printf("temps affichage : %d\n", temps_affichage);
	donnee_utilisateur->temps_affichage = temps_affichage;
	
	fclose(fichier);
	
    shmdt(donnee_admin);//detache la memoire partage
	shmdt(init_process);//detache la memoire partage
    shmdt(donnee_utilisateur);
}

//creation des processus via le terminal
void Implementation_console(){

//___________________________________________________ access au memoire partage ______________________________________________________________    
    //donne acces au processus
    StructProcess *init_process;
	int shmid;
	shmid = acces_processus_memoire_partage();
	init_process = (StructProcess *) shmat(shmid, NULL, 0);

	//donne acces a la structure admin
	StructAdmin *donnee_admin;
   	int shmid_admin;
	shmid_admin = acces_administratif_memoire_partage();
   	donnee_admin = (StructAdmin *) shmat(shmid_admin, NULL, 0);

//___________________________________________________ creation des processus ______________________________________________________________
	//recupere le nombre de processus
	int nb_processus, id;
	printf("\nEntrer le nombre de processus:\t");
    scanf("%d", &nb_processus);

	//verifie qu'il n'y a pas trop de processus
	if(imple_nb_processus_max < nb_processus){
		printf("Erreur : Il y a trop de processus, %d au total",nb_processus); 
	}


    int quantum_arrive[nb_processus], temps_exec[nb_processus], time_quantum;
   	for(id = 0; id < nb_processus; id++){
   		
   		//parametre de chaque processus
        printf("\nConfiguration du processus %d \n", id);
        
        //Date arrivee
        printf("Date arrivee du processus:\t");
        scanf("%d", &init_process->quantum_arrive[id]);
 		
 		//temps execution
        printf("Temps d'execution:\t");
        scanf("%d", &init_process->temps_exec[id]);
         
        //recupere une priorite
        printf("Priorite du processus (entre 0 et 10):\t");
        scanf("%d", &init_process->priorite[id]);

		//status du processus par default : endomie
		init_process->status[id] = 0;

        if(init_process->priorite[id]>10 || init_process->priorite[id]<0){ //teste si la valeur est correct
         	printf("\n/!\\ %d : Valeur rentree incorect\n", init_process->priorite[id]);
         	finprgm(); //Arrete le programme
        }
    }
	
	//definition du quantum de temps	 		
    printf("\nEntrer le temps d'un quantum:\t");
    scanf("%d", &time_quantum);

	//renvoie les parametres au main
	donnee_admin->nb_processus = nb_processus;
	donnee_admin->time_quantum = time_quantum;

	shmdt(init_process);//detache la memoire partage
	shmdt(donnee_admin);//detache la memoire partage

}


