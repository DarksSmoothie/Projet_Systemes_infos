#ifndef _LIBUTILITAIRES_H_ //Verifier l'utilité
#define _LIBUTILITAIRES_H_


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


void arrayInit(string_dynamique** arr_ptr);
void freeArray(string_dynamique* container);

// Basic Operation functions
void insertItem(string_dynamique* container, int item);
void updateItem(string_dynamique* container, int i, int item);
int getItem(string_dynamique* container, int i);
void deleteItem(string_dynamique* container, int item);
void printArray(string_dynamique* container);
void freeArray(string_dynamique* container);



//_______________LOGS_____________________
extern char debug_level; //Moins secu peut altérer le fonctionnement de ma librairie (+ de perf ici car on ne créer pas de fonction pour récup la variable inutilement)

void log_info(char *message,...);
void log_debug(char *message,...);



#endif 
