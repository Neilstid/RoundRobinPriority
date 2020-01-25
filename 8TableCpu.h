//---------------------------------------------------- CPU ---------------------------------------------------------------------



//creer la table cpu selon les choix de l'utilisateur
int choix_table_cpu();
//---------------------------------------------------- Afficher CPU ---------------------------------------------------------------------

//fonction qui affiche la table cpu
void afficher_table_cpu(size_t);

//----------------------------------------------------Repartion priorite dans CPU---------------------------------------------------------------------

//repartie de maniere la plus homogene possible
void repartir(size_t taille, int *repartition); //fonction pour repartir les priorite

//n'est plus utiliser pour le moment
void melanger(int, size_t); //repartis aleatoirement les priorite dans la table CPU


//----------------------------------------------------Creation de la table CPU---------------------------------------------------------------------

//creer une table cpu via le terminal
void Crea_Table_CPU();

//creer une table cpu via un fichier
void Crea_Table_CPU_Fichier();

