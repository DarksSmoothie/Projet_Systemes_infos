#ifndef _LIBUTILITAIRES_H_ //Verifier l'utilité
#define _LIBUTILITAIRES_H_


typedef struct {
    size_t size;      
    size_t capacity;  
    char** array;       
}tableau_strings_dynamique;



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
