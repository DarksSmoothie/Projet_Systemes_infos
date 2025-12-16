#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

#include "lib_utilitaires.h" //REGLER CA //Fonction utilitaires pour la gestion de tableaux dynamiques

//ATTENTION PENSER A RAJOUTER LES CONDITIONS D'ERREIR ET DE FREE POUR CHAQUE FONCTION DE LIB_UTILITAIRES freeArray(valeur) et freeArray(new_valeur)


// ------------ Ma Fonction -----------------
void solve(FILE *input, FILE *output, bool only_longest) {
    log_info("Nous allons commencer le traitement des données en considérant l'option only_longuest:%d \n", only_longest);   
    tableau_strings_dynamique* longuest = NULL; //Pointeur vers ma structure tableau dynamique (pas directement la structure car sinon sur le stack et ça disparait)
    longuestInit(&longuest); 
    char ligne[4096];         //Initialisation de la structure tableau dynamique (on passe l'adresse du pointeur pour qu'il puisse être modifié dans la fonction)
    // Ici, le arrayInit gère touys seul et quitte le programme s'il y a une erreur

    //----------------------Boucle sur chaque ligner du fichier -----------------------------------------------------
    while(fgets(ligne, sizeof ligne, input)) { //Tant qu'on peut lire une ligne du fichier d'entrée
        char valeur_recup[4096];
        int iteration;


        //V---------------------------6Verification du format de la ligne----------------------------------------------
        if (sscanf(ligne, "%4095s %d", valeur_recup, &iteration) != 2) { //On lit deux entiers par ligne
        fprintf(stderr, "Ligne invalide: %s \n", ligne);
        continue;
        }else {
            log_info("Nous devons appliquer la suite au nombre %s, et ce %d fois \n", valeur_recup, iteration);
        }


        //-------------------------Création de notre char changeable, valeur, sur le heap-------------------------------------
        string_dynamique* valeur = NULL;
        arrayInit(&valeur);
        if (string_set(valeur, valeur_recup)!=0){
            freeArray(valeur);
            freeLonguest(longuest);
            return;
        }; //On initialise notre string dynamique avec la valeur lue dans le fichier
        string_dynamique* new_valeur = NULL;
        arrayInit(&new_valeur); 

        //------------------------Application de la suite--------------------------------------------------------
        for (int i = 0; i < iteration; i++) { //On répète b fois l'opération
            log_info("Itération %d pour le nombre %s \n", i+1, valeur->array);
            string_clear(new_valeur);

            // Nouvelle valeur temporaire


            int j = 0;
            //------------------------------On traite la valeure actuelle----------------------------------------------------
            while(j<valeur->size) { //-1 car on a le /0 à la fin du string
                int j_origine = j;
                char c = valeur->array[j];
                j+=1;
                while(j<valeur->size && valeur->array[j] == c){
                    j+=1;
                }
                
            //--------------------------On ajoute le résultat à new_valeur------------------------------------------------
                int nombre_occurrence = j - j_origine;
                char x[32];
                snprintf(x, sizeof x, "%d", nombre_occurrence); // On transforme le nombre en string
                if (stringAppend(new_valeur, x) != 0) {
                    log_debug("Erreur lors de l'ajout du nombre d'occurrence %d à la nouvelle valeur \n", nombre_occurrence);
                    freeArray(valeur);
                    freeArray(new_valeur);
                    return;
                } 
                char tmp[2]; tmp[0] = c; tmp[1] = '\0'; //on crée un string temporaire pour le caractère c (sinon on aurait du recrer une fonction)
                if (stringAppend(new_valeur, tmp) != 0) {
                    log_debug("Erreur lors de l'ajout du caractère %c à la nouvelle valeur \n", c);
                    freeArray(valeur);
                    freeArray(new_valeur);
                    return;
                }

            log_debug("Après traitement, la nouvelle valeur est %s \n", new_valeur->array);
            }   

            //On met à jour valeur avec new_valeur
             //swap des pointeurs                      
            string_dynamique *tmp = valeur;
            valeur = new_valeur;
            new_valeur = tmp; //On ne free pas ici car on réutilisera new_valeur à la prochaine itération (sinon on doit refaire un malloc à chaque itération de la boucle)
            
//--------------------------------Stockage dans longuest si onption only longuest---------------------------------------------
        }   
        log_info("Le résultat final pour le nombre initial après %d itérations est %s \n",iteration,valeur->array);
        
        if (only_longest) {
            
            if (longuest->size == 0 ) {
                if (longuestAppend(longuest, valeur->array) != 0) //On stocke une copie du strig et pas le string sinon use after free
                {
                    log_debug("Erreur lors de l'ajout du premier element à longuest");
                    freeArray(valeur);
                    freeArray(new_valeur);
                    longuestFree(longuest);
                    return;
                }                 
            } 
            else if (valeur->size > strlen(longuest->array[0])){
                //On free l'ancien longuest
                longuestClear(longuest);
                if (longuestAppend(longuest, valeur->array)!=0){
                    log_debug("Erreur lors de l'ajout d'un nouvel element à longuest plus grand que les anciens");
                    freeArray(valeur);
                    freeArray(new_valeur);
                    longuestFree(longuest);
                    return;}
            }
            else if (valeur->size == strlen(longuest->array[0])){
            if(longuestAppend(longuest, valeur->array)!=0){
                log_debug("Erreur lors de l'ajout d'un nouvel element à longuest de même taille que les anciens");
                freeArray(valeur);
                freeArray(new_valeur);
                longuestFree(longuest);
                return;}
            }

        //On free à la fin d'une ligne
        freeArray(valeur);
        freeArray(new_valeur);
        } else {
            //On écrit directement dans le fichier de sortie
            fprintf(output, "%s\n", valeur->array);
            //On free à la fin d'une ligne
            freeArray(valeur);
            freeArray(new_valeur);
        }
    } //Fin de la boucle sur les lignes du fichier
    if (only_longest) {
        //On écrit le/les longuest(s) dans le fichier de sortie
        for (size_t k = 0; k < longuest->size; k++) {
            fprintf(output, "%s\n", longuest->array[k]);
        }
        
        log_info("Traitement terminé, les résultats ont été écrits dans le fichier de sortie.\n");
    }
    longuestFree(longuest);
    


}


