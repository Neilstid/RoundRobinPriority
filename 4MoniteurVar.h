//---------------------------------------------------- moniteur de hoare ---------------------------------------------------------------------
pthread_mutex_t mutex[imple_nb_processus_max], mutex2[imple_nb_processus_max], mutex3[imple_nb_processus_max];
pthread_cond_t dormir[imple_nb_processus_max], creation_thread[imple_nb_processus_max], fin_exec[imple_nb_processus_max];
pthread_t thread[imple_nb_processus_max];
