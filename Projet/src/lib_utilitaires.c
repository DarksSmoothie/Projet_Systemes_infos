#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "lib_utilitaires.h"
#define INITIAL_SIZE 8 //Constante du préprocesseur

//Ici, pour créer un tableau de longueur variable en C
// Nous allons devoir utiliser un système d'allocation dynamique avec malloc, realloc et free


 //Structure pour mon longuest  (tableaux de strigs)
typedef struct {
    size_t size;      //Taille actuelle du tableau (nombred d'éléments dedans/ mémoire utiisée)
    size_t capacity;  //Capacité maximale du tableau avant redimensionnement
    char** array;       //Pointeur vers le premier elem du tableau d'entiers
}tableau_strings_dynamique;


//Structure pour mon valeur (tableaux de char/ string dynamique)
typedef struct {
    size_t size;      
    size_t capacity; 
    char* array;       
}string_dynamique;



//___________________TABLEAUX DYNAMIQUES POUR CHAR (strings dynamiques)_____________________

int verifRealloc(string_dynamique *container, size_t m) {
    if (m + 1 > container->capacity) {      // +1 pour le caractère nul de fin de string
        size_t newcap = container->capacity;                        // nouvelle capacité
        while (newcap < m + 1) newcap *= 2;
        char *tmp = realloc(container->array, newcap);
        if (!tmp) {
            log_debug("Out of Memory, echec de realloc lors de verifRealloc\n");
            return -1;                                                              //ATTENTOION A RAJOUTER LES ERREURS DANS LE MAIN
        }
        container->array = tmp;
        container->capacity = newcap;
        return 0;
    }
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
    container->array[0] = '\0';   
   
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
    if(verifRealloc(container, n)!= 0){return -1;};      // +1 pour le caractère nul de fin de string    
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
    if (verifRealloc(container, container->size + n) != 0) {return -1;}     // +1 pour le caractère nul de fin de string
    memcpy(container->array + container->size, stringAjout, n);
    container->size += n;
    container->array[container->size] = '\0';
    return 0;
}




//___________________TABLEAUX DYNAMIQUES POUR STRINGS_____________________

//  Insertion Operation
int insertItem(string_dynamique* container, char item)
{
    if (container->size == container->capacity) {       
        char *temp = container->array;           // Sauvegarder l'ancienne adresse en cas d'échec de realloc
        container->array = realloc(container->array, (container->capacity * 2) * sizeof *container->array); //“Redimensionne le bloc mémoire pour qu’il puisse contenir capacity entiers.”
        if(!container->array) {                 //echec de realloc
            log_debug("Out of Memory, echec de realloc lors de insertItem\n");
            container->array = temp;
            return -1;                          //On documente si notre code à échoué ou non pour que dans la fonction principale, on puisse arrêter le programme en cas de problème mémoire
        }
        container->capacity <<= 1;              // Double la capacité (même signification que container->capacity = container->capacity * 2;) <<= 1 = décalage binaire à gauche d’un bit équivalent à multiplier par 2
    }
    
    container->array[container->size++] = item; //Insère l'élément et incrémente la taille
    return 0;
}



// Retrieve Item at Particular Index
int getItem(string_dynamique* container, int index)
{
    if(index >= container->size) {
        printf("Index Out of Bounds\n");
        return -1;
    }
    return container->array[index];
}


// Update Operation
void updateItem(string_dynamique* container, int index, char item)
{
    if (index >= container->size) {
        printf("Index Out of Bounds\n");
        return;
    }
    container->array[index] = item;
}



void printArray(string_dynamique* container)
{
    printf("Array elements: ");
    for (int i = 0; i < container->size; i++) {
        printf("%d ", container->array[i]);
    }
    printf("\nSize: ");
    printf("%lu", container->size);
    printf("\nCapacity: ");
    printf("%lu\n", container->capacity);
}

// Freeing the memory allocated to the array
void freeArray(string_dynamique* container)
{
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