

  
// fonction qui la queue en fonction de sa capicite 
struct Queue* createQueue(unsigned);
  
//regarde si la liste est pleine 
int isFull(struct Queue*); 
//regarde si la liste est vide 
int isEmpty(struct Queue*); 
  
// Fonction pour ajouter un element dans la queue   
void ajouter(struct Queue*, int); 

  
// Fonction pour retirer un element(le premier) de la queue 
int retirer(struct Queue* ) ;

  
// Fonction qui renvoie le premier element
int premier_element(struct Queue*); 

  
// Fonction qui renvoie le dernier element
int dernier_element(struct Queue*) ;

//initialisation des queue
void init_queue();

//libere les pointeurs
void libere_queue();

