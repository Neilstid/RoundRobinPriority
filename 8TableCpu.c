#include "0INCLUDE.h"
#include "5Structure.h"
#include "3FixedVariable.h"
#include "4MoniteurVar.h"
#include "11Queue.h"
//---------------------------------------------------- CPU ---------------------------------------------------------------------

const int table_cpu_default[100] = {0,1,2,3,4,5,6,7,8,9,10,0,1,2,3,4,5,0,1,2,3,4,6,0,1,2,3,7,8,0,1,2,9,10,3,4,0,1,6,7,8,5,0,1,3,4,6,7,0,2,4,6,8,9,0,1,3,5,7,10,2,0,1,2,4,6,7,0,1,2,3,4,5,0,1,2,4,6,7,0,1,2,3,4,0,1,2,6,7,8,0,1,2,3,4,0,1,2,4,6}; //table d'alloction cpu par default

//creer la table cpu selon les choix de l'utilisateur
int choix_table_cpu(){
	
	//acces a la table cpu
	int shmid_cpu, *table_cpu;
	shmid_cpu = acces_table_cpu_memoire_partage();
   	table_cpu = (int *) shmat(shmid_cpu, NULL, 0);
	
	//choix de l'utilisateur
	int choix_table_cpu;
	printf("\nComment souhaitez-vous creer la table d'allocation CPU ?\n");
	printf("[1] : Utiliser la table d'allocation CPU par default\n");
	printf("[2] : Modifier puis utiliser la table d'allocation CPU par default\n");
	printf("[3] : Creer une table d'allocation CPU valeur par valeur\n");
	printf("[4] : Creer une table d'allocation CPU a partir d'un pourcentage donnee a chaque priorite\n");
	printf("[5] : Creer une table d'allocation CPU a partir d'un fichier\n");
	printf("Choix : \t");
	scanf("%d", &choix_table_cpu);
	
	switch(choix_table_cpu){
		case 1 ://default
			memcpy(table_cpu,table_cpu_default,sizeof(table_cpu_default)); //copy la table cpu par default a l'address voulu
			afficher_table_cpu(100);//affiche la table
			break;
			
		case 2 ://default avec modif
			memcpy(table_cpu,table_cpu_default,sizeof(table_cpu_default)); //copy la table cpu par default a l'address voulu
			afficher_table_cpu(100);//affiche la table
			printf("Voulez vous modifier cette table ? \n [1] : Oui \n [2] : Non \n Choix : \t");
			
			int Modifier_table;
			scanf("%d", &Modifier_table);
			
			while(Modifier_table == 1){//tant que l'utilisateur veut modifier la table cpu
				int val_modif, temp;
				printf("Quelle element voulez vous modifier ?\n Position : \t");
				scanf("%d", &val_modif);
				
				if(val_modif >= 100){//verifie que la valeur est possible
					printf("Erreur : La valeur cible n'exite pas\n");
					finprgm();
				}
				
				printf("La valeur actuel est %d \n", table_cpu[val_modif]);
				printf("Nouvelle valeur : \t");
				scanf("%d", &temp);
				table_cpu[val_modif] = temp; //mise a jour de la valeur
				printf("Voulez vous encore modifier cette table ? \n [1] : Oui \n [2] : Non \n Choix : \t");
				scanf("%d", &Modifier_table);//boucle si l'utilisateur veut
			}
			
			afficher_table_cpu(100);
			break;
			
		case 3 ://creer table cpu par val
			for(int pos = 0; pos < 100; pos++){
				printf("Valeur a la position %d : \t", pos);
				table_cpu[pos] = scanf("%d"); //mise a jour de la valeur
				if(table_cpu[pos] > 10){
					printf("Erreur : Priorite trop haute");
					finprgm();
				}
			}
			afficher_table_cpu(100);
			break;
			
		case 4 : //creer table par pourcentage
			Crea_Table_CPU();
			afficher_table_cpu(100); //Afiche la table CPU
			break;
		
		case 5 ://a partir d'un fichier
			Crea_Table_CPU_Fichier();
			afficher_table_cpu(100); //Afiche la table CPU
			break;
			
		default : //erreur
			printf("Erreur : le choix %d n'est pas disponible\n", choix_table_cpu);
			finprgm();
			break;
	}
	
	return table_cpu;
}

//---------------------------------------------------- Afficher CPU ---------------------------------------------------------------------

//fonction qui affiche la table cpu
void afficher_table_cpu(size_t taille){
	
	//acces a la table cpu
	int shmid_cpu, *table_cpu;
	shmid_cpu = acces_table_cpu_memoire_partage();
   	table_cpu = (int *) shmat(shmid_cpu, NULL, 0);
	
	int priorite, position;
	
	printf("Priorite Quantum| 0\t | 1\t | 2\t | 3\t | 4\t | 5\t | 6\t | 7\t | 8\t | 9\t | 10\t |\n"); //Creer l'entete du tableau
	
	for(position = 0; position<100; position++){ //Pour chauque valeur de la table_cpu
		printf("\t%d \t|", position);
		switch(table_cpu[position]){ //on rempli le tableau en fonction de la valeur trouver
			case 0 : 
				printf(" * \t | \t | \t | \t | \t | \t | \t | \t | \t | \t | \t | \n");
				break;
			case 1 : 
				printf(" \t | * \t | \t | \t | \t | \t | \t | \t | \t | \t | \t | \n");
				break;
			case 2 : 
				printf(" \t |\t | * \t | \t | \t | \t | \t | \t | \t | \t | \t | \n");
				break;
			case 3 : 
				printf(" \t | \t | \t | * \t | \t | \t | \t | \t | \t | \t | \t | \n");
				break;
			case 4 : 
				printf(" \t | \t | \t | \t | * \t | \t | \t | \t | \t | \t | \t | \n");
				break;
			case 5 : 
				printf(" \t | \t | \t | \t | \t | * \t | \t | \t | \t | \t | \t | \n");
				break;
			case 6 : 
				printf(" \t | \t | \t | \t | \t | \t | * \t | \t | \t | \t | \t | \n");
				break;
			case 7 : 
				printf(" \t | \t | \t | \t | \t | \t | \t | * \t | \t | \t | \t | \n");
				break;
			case 8 : 
				printf(" \t | \t | \t | \t | \t | \t | \t | \t | * \t | \t | \t | \n");
				break;
			case 9 : 
				printf(" \t | \t | \t | \t | \t | \t | \t | \t | \t | * \t | \t | \n");
				break;
			case 10 : 
				printf(" \t | \t | \t | \t | \t | \t | \t | \t | \t | \t | * \t | \n");
				break;
			default : //erreur : priorite inexistante
				printf("Erreur : Probleme de prorite, la priorite %d n'existe pas\n", table_cpu[position]);
				finprgm();
				break;
		}
	}
	
	shmdt(table_cpu);//detache la memoire partage
	
}

//----------------------------------------------------Repartion priorite dans CPU---------------------------------------------------------------------

//repartie de maniere la plus homogene possible
void repartir(size_t taille, int *repartition) //fonction pour repartir les priorite
{
	int shmid_cpu, *table_cpu;
	shmid_cpu = acces_table_cpu_memoire_partage();
   	table_cpu = (int *) shmat(shmid_cpu, NULL, 0);

	int tableau_final[taille]; //Creer un table de la meme taille que la table CPU
	//Pour les boucles : le numero de priorite, la position dans le tableau, operation pour repartir, position dans le tableau final
	int priorite_num, position_tableau, compte, position_final; 
	memset(&tableau_final[0], -1, sizeof(tableau_final)); //rempli le tableau de -1
	compte = 0;//demare l'operation a 0

	for(priorite_num = 0;priorite_num <= nb_priorite;priorite_num++){//Pour chacune des priorite
		position_final = priorite_num; //la premiere position est le numero de priorite
		for(position_tableau = compte;position_tableau < compte+repartition[priorite_num];position_tableau++){ //pour chacune des valeurs de la priorite
			while(tableau_final[position_final] != -1){  //On change la valeur de la position si celle ci est deja occupe
				if(position_final < taille){ //On s'assure que la place est inferieur au nombre de place dans la table
					position_final++;  //On incremente la position si la place peut etre apres
				}else{
					position_final = 0; //On revient au debut si aucune place n'a ete trouve 
				}
			}
			tableau_final[position_final] = table_cpu[position_tableau]; //On met a la premiere position trouve la priorite
			position_final+=100/repartition[priorite_num]; //On passe a la prochaine place dans la table CPU
		}
		compte+=repartition[priorite_num]; //On passe a la priorite suivante
	}
	
	memcpy(table_cpu,tableau_final,sizeof(tableau_final)); //On copy le tableau final dans notre tableau de depart pour que la table_cpu soit directement modifier
	
	shmdt(table_cpu);//detache la memoire partage
	
}

//n'est plus utiliser pour le moment
void melanger(int *array, size_t taille) //repartis aleatoirement les priorite dans la table CPU
{
	srand(time(NULL)); //lancement pseudo random
    if (taille > 1) //verifie qu'il y a plusieur element dans le tableau
    {
        size_t position_array;
        for (position_array = 0; position_array < taille - 1; position_array++) 
        {
          size_t position_aleatoire = position_array + rand() / (RAND_MAX / (taille - position_array) + 1);
          int memoire_position = array[position_aleatoire];
          array[position_aleatoire] = array[position_array];
          array[position_array] = memoire_position;
        }
    }
}






//----------------------------------------------------Creation de la table CPU---------------------------------------------------------------------

//creer une table cpu via le terminal
void Crea_Table_CPU(){
	//acces a la memoire partage de la table cpu
	int shmid_cpu, *table_cpu;
	shmid_cpu = acces_table_cpu_memoire_partage();
   	table_cpu = (int *) shmat(shmid_cpu, NULL, 0);

    //nombre de priorite
    int priorite_accorde[nb_priorite], somme_pourcentage;
    somme_pourcentage = 0;//initialisation de la variable somme
    
    int priorite_num; //variable permettant de se deplacer dans les priorite pour les boucles
	int repartition = 10;

    for(priorite_num = 0; priorite_num <= nb_priorite; priorite_num++){ //pour chaque priorite
        printf("Pourcentage allocation a la priorite %d : \t", priorite_num);
        scanf("%d", &priorite_accorde[priorite_num]); //rentre la valeur dans notre tableau pour creer plus tard la table CPU
        somme_pourcentage += priorite_accorde[priorite_num]; //servira a verifier qu'il n'y a pas d'erreur

		for(repartition = (somme_pourcentage - priorite_accorde[priorite_num]); repartition < somme_pourcentage; repartition++){//met le nombre de priorite choisi
			table_cpu[repartition] = priorite_num;		
		}

        if(priorite_num>0 && priorite_accorde[priorite_num]>priorite_accorde[priorite_num-1]){//verification que les priorité sont dans l'ordre
            printf("Erreur la priorite %d est superieur a la priorite %d\n", priorite_num, priorite_num-1);
            finprgm(); //arrete le programme
        }
    }

	if(somme_pourcentage != 100){
		printf("Erreur le pourcentage est different de 100\n");
	}
	repartir(100,priorite_accorde);//repartie les priorite de facon homogene
	
	shmdt(table_cpu);//detache la memoire partage
	
}

//creer une table cpu via un fichier
void Crea_Table_CPU_Fichier(){

	//acces a la memoire partage pour la table cpu
	int shmid_cpu, *table_cpu;
	shmid_cpu = acces_table_cpu_memoire_partage();
   	table_cpu = (int *) shmat(shmid_cpu, NULL, 0);
   	
	//recupere le nom du fichier
	char nom_fichier[100];
	printf("Entrer le nom du fichier (le nom doit finir par \".txt\") :\t");
	scanf("%s", &nom_fichier);

	//ouvre le fichier
	FILE* fichier = fopen(nom_fichier, "r");
	
	int position; //position dans la table cpu
	
    if (fichier != NULL) //verifie que le fichier est bien ouvert
    {

        // On peut lire et écrire dans le fichier
        printf("Le fichier s'est ouvert correctement\n");
	
		printf("Table d'allocation cpu : [");
		//recupere la table cpu du fichier
		for(position = 0; position < 100; position++){
			fscanf(fichier,"%d",&table_cpu[position]);//met la val du fichier dans la table cpu
			printf("%d,",table_cpu[position]);
		}
		printf("]\n");
		
	}else{//erreur
		// On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier %s \n", nom_fichier);
        finprgm();
	}
	
	shmdt(table_cpu);//detache la memoire partage
	
}

