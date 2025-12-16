#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "lib_utilitaires.h"
#define INITIAL_SIZE 8 //Constante du préprocesseur

//Ici, pour créer un tableau de longueur variable en C
// Nous allons devoir utiliser un système d'allocation dynamique avec malloc, realloc et free


//___________________TABLEAUX DYNAMIQUES POUR CHAR (strings dynamiques)_____________________

int verifReallocString(string_dynamique *container, size_t m) {
    if (m + 1 > container->capacity) {      // +1 pour le caractère nul de fin de string
        size_t newcap = container->capacity;                        // nouvelle capacité
        while (newcap < m + 1) newcap *= 2;
        char *tmp = realloc(container->array, newcap* sizeof *tmp);
        if (!tmp) {
            log_debug("Out of Memory, echec de realloc lors de verifReallocString\n");
            return -1;                                                              //ATTENTOION A RAJOUTER LES ERREURS DANS LE MAIN
        }
        container->array = tmp;
        container->capacity = newcap;
        return 0;
    } return 0;
}


void arrayInit(string_dynamique** arr_ptr) //Init une structure et la renvoyer par pointeur de pointeur
{
    string_dynamique *container; //pointeur local vers la structure
    container = malloc(sizeof(string_dynamique));  //On alloue la mémoire dans le heap 
    if(!container) {
        printf("First memory Allocation Failed\n");
        exit(0);
    }

    container->size = 0;                    //Taille initiale du tableau est 0
    container->capacity = INITIAL_SIZE;     //Capacité initiale du tableau (décris en haut du fichier)
       
   
    container->array = malloc(INITIAL_SIZE * sizeof *container->array);   //“Je veux assez de mémoire pour stocker INITIAL_SIZE entiers, stoque moi son adresse dans container->array.”
    if (!container->array){                 //Si malloc échoue
        log_debug("Memory Allocation Failed\n");
        free(container);                    //On libère la mémoire allouée à la structure (pas obligé mais bonne pratique)
        *arr_ptr = NULL;                    // ATTENTION à ne pas oublier de mettre le pointeur à NULL, sinon il pointera vers une adresse invalide, déjà libérée
        exit(EXIT_FAILURE);
    }

    container->array[0] = '\0';   // IMPORTANT : string vide valide
    *arr_ptr = container;
}

//Fonction pour set notre string dynamique à partir d'un string classique
int string_set(string_dynamique *container, char *stringInsersion) {
    size_t n = strlen(stringInsersion);                     // longueur de du string à insérer
    if(verifReallocString(container, n)!= 0){return -1;};      // +1 pour le caractère nul de fin de string    
    memcpy(container->array, stringInsersion, n + 1);
    container->size = n;
    return 0;
}



// libération de la mémoire allouée au tableau dynamique
void freeArray(string_dynamique* container)
{
    free(container->array);
    free(container);
}

void string_clear(string_dynamique *s)
{
    s->size = 0;
    s->array[0] = '\0';
}



int stringAppend(string_dynamique *container, char *stringAjout) {
    size_t n = strlen(stringAjout);                     // longueur de du string à insérer
    if (verifReallocString(container, container->size + n) != 0) {return -1;}     // +1 pour le caractère nul de fin de string
    memcpy(container->array + container->size, stringAjout, n);
    container->size += n;
    container->array[container->size] = '\0';
    return 0;
}





//___________________TABLEAUX DYNAMIQUES POUR STRINGS (longuest)_____________________


void longuestInit(tableau_strings_dynamique** arr_ptr) {//même chose que pour string dynamique
    tableau_strings_dynamique *container; 
    container = malloc(sizeof(tableau_strings_dynamique));   
    if(!container) {
        printf("First memory Allocation Failed\n");
        exit(0);
    }

    container->size = 0;                    
    container->capacity = INITIAL_SIZE;     
       
   
    container->array = malloc(INITIAL_SIZE * sizeof *container->array);   
    if (!container->array){                 
        log_debug("Memory Allocation Failed\n");
        free(container);                    
        *arr_ptr = NULL;                    
        exit(EXIT_FAILURE);
    }
    *arr_ptr = container;
}


int verifReallocLonguest(tableau_strings_dynamique *container, size_t m) {  
    if (m > container->capacity) {

        size_t newcap = container->capacity;                        // nouvelle capacité
        while (newcap < m ) {newcap *= 2;}                          //ON double cette nouvelle capacité tant que on a pas assez de place
        char **tmp = realloc(container->array, newcap* sizeof *tmp);
        if (!tmp) {
            log_debug("Out of Memory, echec de realloc lors de verifReallocString\n");
            return -1;                                                              //ATTENTOION A RAJOUTER LES ERREURS DANS LE MAIN
        }
        container->array = tmp;
        container->capacity = newcap;
        return 0;
    } 
    return 0; //Si pas besoin de realloc
}



int longuestAppend(tableau_strings_dynamique *container, char *stringAjout) {
    if (!container || !stringAjout) return -1;

    //Verification de la capacité et realloc si besoin                   
    if (verifReallocLonguest(container, container->size +1) != 0) {return -1;}     
    container->array[container->size] = strdup(stringAjout); //On duplique le string pour éviter les problèmes de pointeurs
    if (!container->array[container->size]) {return -1;}
    container->size += 1;
    return 0;
}

void longuestClear(tableau_strings_dynamique *l) {
    for (size_t k = 0; k < l->size; k++) free(l->array[k]);
    l->size = 0;
}


void longuestFree(tableau_strings_dynamique *container)
{
    if (!container) return;
    for (size_t i = 0; i < container->size; i++) {
        free(container->array[i]);
        container->array[i] = NULL; 
    }
    free(container->array);
    free(container);
}



//_______________LOGS_____________________


void log_info(char *message,...){
    if (debug_level < '1'){
        return;
    }
    va_list args; // liste d'aguments passés en plus dans ma fonction 
    va_start(args, message); // initialisation de la liste d'arguments avec message etant le dernier argument connu
    
    fprintf(stderr, "[INFO] "); // Juste le 'INFO'
    vfprintf(stderr, message, args); // Affichage du message avec les arguments (vfprintf prend comme argument une liste d'arguments)
    
    fprintf(stderr, "\n"); // Nouvelle ligne
    va_end(args); // Nettoyage de la liste d'arguments
}



void log_debug(char *message,...){
    if (debug_level < '2'){
        return;
    } 
    va_list args; 
    va_start(args, message); 
    
    fprintf(stderr, "[DEBUG] ");
    vfprintf(stderr, message, args); 
    
    fprintf(stderr, "\n");
    va_end(args); 
}