#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "lib_utilitaires.h"
#define INITIAL_SIZE 8 //Constante du préprocesseur

    //Ici, pour créer un tableau de longueur variable en C
    // Nous allons devoir utiliser un système d'allocation dynamique avec malloc, realloc et free

typedef struct {
    size_t size;      //Taille actuelle du tableau (nombred d'éléments dedans/ mémoire utiisée)
    size_t capacity;  //Capacité maximale du tableau avant redimensionnement
    int* array;       //Pointeur vers le premier elem du tableau d'entiers
}tableau_dynamique;

//___________________TABLEAUX DYNAMIQUES_____________________


void arrayInit(tableau_dynamique** arr_ptr) //Init une structure et la renvoyer par pointeur de pointeur
{
    tableau_dynamique *container; //pointeur local vers la structure
    container = malloc(sizeof(tableau_dynamique));  //On alloue la mémoire dans le heap 
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

    *arr_ptr = container;
}



//  Insertion Operation
int insertItem(tableau_dynamique* container, int item)
{
    if (container->size == container->capacity) {       
        int *temp = container->array;           // Sauvegarder l'ancienne adresse en cas d'échec de realloc
        container->array = realloc(container->array, container->capacity * sizeof(int)*2); //“Redimensionne le bloc mémoire pour qu’il puisse contenir capacity entiers.”
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
int getItem(tableau_dynamique* container, int index)
{
    if(index >= container->size) {
        printf("Index Out of Bounds\n");
        return -1;
    }
    return container->array[index];
}


// Update Operation
void updateItem(tableau_dynamique* container, int index, int item)
{
    if (index >= container->size) {
        printf("Index Out of Bounds\n");
        return;
    }
    container->array[index] = item;
}

// Delete Item from Particular Index
void deleteItem(tableau_dynamique* container, int index)
{
    if(index >= container->size) {
        printf("Index Out of Bounds\n");
        return;
    }

    for (int i = index; i < container->size; i++) { //On décale tous les éléments après l'index vers la gauche
        container->array[i] = container->array[i + 1];
    }
    container->size--;
}


void printArray(tableau_dynamique* container)
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
void freeArray(tableau_dynamique* container)
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