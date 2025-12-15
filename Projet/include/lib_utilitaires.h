#ifndef _LIBUTILITAIRES_H_ //Verifier l'utilité
#define _LIBUTILITAIRES_H_


typedef struct {
    size_t size;
    size_t capacity;
    int* array;
}tableau_dynamique;

void arrayInit(tableau_dynamique** arr_ptr);
void freeArray(tableau_dynamique* container);

// Basic Operation functions
void insertItem(tableau_dynamique* container, int item);
void updateItem(tableau_dynamique* container, int i, int item);
int getItem(tableau_dynamique* container, int i);
void deleteItem(tableau_dynamique* container, int item);
void printArray(tableau_dynamique* container);
void freeArray(tableau_dynamique* container);



//_______________LOGS_____________________
extern char debug_level; //Moins secu peut altérer le fonctionnement de ma librairie (+ de perf ici car on ne créer pas de fonction pour récup la variable inutilement)

void log_info(char *message,...);
void log_debug(char *message,...);



#endif 
