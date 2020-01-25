#include "0INCLUDE.h"
#include "5Structure.h"
#include "3FixedVariable.h"
#include "4MoniteurVar.h"
#include "11Queue.h"
// fonction qui la queue en fonction de sa capicite 
struct Queue* createQueue(unsigned capacite) 
{ 
    struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue)); 
    queue->capacite = capacite; 
    queue->premier = queue->taille = 0;  
    queue->dernier = capacite - 1;  // Permet de voir le dernier element
    queue->array = (int*) malloc(queue->capacite * sizeof(int)); 
    return queue; 
} 
  
//regarde si la liste est pleine 
int isFull(struct Queue* queue) 
{  return (queue->taille == queue->capacite);  } 
  
//regarde si la liste est vide 
int isEmpty(struct Queue* queue) 
{  return (queue->taille == 0); } 
  
// Fonction pour ajouter un element dans la queue   
void ajouter(struct Queue* queue, int id_processus) 
{ 
    if (isFull(queue)) 
        return; 
    queue->dernier = (queue->dernier + 1)%queue->capacite; 
    queue->array[queue->dernier] = id_processus; 
    queue->taille = queue->taille + 1; 
} 
  
// Fonction pour retirer un element(le premier) de la queue 
int retirer(struct Queue* queue) 
{ 
    if (isEmpty(queue)) 
        return INT_MIN; 
    int id_processus = queue->array[queue->premier]; 
    queue->premier = (queue->premier + 1)%queue->capacite; 
    queue->taille = queue->taille - 1; 
    return id_processus; 
} 
  
// Fonction qui renvoie le premier element
int premier_element(struct Queue* queue) 
{ 
    if (isEmpty(queue)) 
        return INT_MIN; 
    return queue->array[queue->premier]; 
} 
  
// Fonction qui renvoie le dernier element
int dernier_element(struct Queue* queue) 
{ 
    if (isEmpty(queue)) 
        return INT_MIN; 
    return queue->array[queue->dernier]; 
}

//initialisation des queue
void init_queue(){
    Attente_Priorite0 = createQueue(imple_nb_processus_max);
    Attente_Priorite1 = createQueue(imple_nb_processus_max);
    Attente_Priorite2 = createQueue(imple_nb_processus_max);
    Attente_Priorite3 = createQueue(imple_nb_processus_max);
    Attente_Priorite4 = createQueue(imple_nb_processus_max);
    Attente_Priorite5 = createQueue(imple_nb_processus_max);
    Attente_Priorite6 = createQueue(imple_nb_processus_max);
    Attente_Priorite7 = createQueue(imple_nb_processus_max);
    Attente_Priorite8 = createQueue(imple_nb_processus_max);
    Attente_Priorite9 = createQueue(imple_nb_processus_max);
    Attente_Priorite10 = createQueue(imple_nb_processus_max);
}

//libere les pointeurs
void libere_queue(){
    free(Attente_Priorite0);
    free(Attente_Priorite1);
    free(Attente_Priorite2);
    free(Attente_Priorite3);
    free(Attente_Priorite4);
    free(Attente_Priorite5);
    free(Attente_Priorite6);
    free(Attente_Priorite7);
    free(Attente_Priorite8);
    free(Attente_Priorite9);
    free(Attente_Priorite10);
}

