#include <stdio.h>
#include <stdarg.h>
#include "lib_tableaux_dynamiques.h"

    //Ici, pour créer un tableau de longueur variable en C
    // Nous allons devoir utiliser la fonction malloc (allocation dynamique)


void arrayInit();
void freeArray();

void insertItem(int item);
void updateItem(int i, int item);
int getItem(int i);
void deleteItem(int item);
void printArray();



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