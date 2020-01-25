//cles pour les espaces de memoire partage
#define key_processus 1234 //defini une cle pour l'espace memoire partage processus
#define key_cpu 5678 //defini une cle pour l'espace memoire partage pour la table cpu
#define key_admin 11 //defini une cle pour l'espace memoire partage pour les donne lie a l'execution
#define key_utilisateur 2468 //defini une cle pour l'espace memoire partage pour les donne lie a l'execution et rentre par l'utilisateur

#define imple_nb_processus_max 100 //defini le nombre maximum de processus pouvant etre creer
#define TAILLE_MAX 100 //defini le nombre de charactere max pouvant etre lu

//pour processus aleatoire
#define Arrive_max 100 //arriver maximum pour les processus creer aleatoirement
#define Temps_exec_max 10 //temps d'execution maximum pour les processus creer aleatoirement
#define Quantum_max 3 //defini le quantum maximum pour l'aleatoire, rentre a la main aucune limite
#define nb_processus_max_aleatoire 10 //defini le nombre maximum de processus pouvant etre implemente en aleatoire, doit etre inferieur ou egal a imple_nb_processus_max

//Ne doit surtout pas etre modifier, pourrait creer des erreurs (notement surr l'affichage de la table cpu)
#define nb_priorite 10 //defini le nombre de priorite 

