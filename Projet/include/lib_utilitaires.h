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

int verifReallocString(string_dynamique *container, size_t m);
void arrayInit(string_dynamique** arr_ptr);
void freeArray(string_dynamique* container);
int string_set(string_dynamique *container, char *stringInsersion);
void string_clear(string_dynamique *s);
int stringAppend(string_dynamique *container, char *stringAjout);

void longuestInit(tableau_strings_dynamique** arr_ptr);
int verifReallocLonguest(tableau_strings_dynamique *container, size_t m);
int longuestAppend(tableau_strings_dynamique *container, char *stringAjout);
void longuestClear(tableau_strings_dynamique *l);
void longuestFree(tableau_strings_dynamique *container);



//_______________LOGS_____________________
extern char debug_level; //Moins secu peut altérer le fonctionnement de ma librairie (+ de perf ici car on ne créer pas de fonction pour récup la variable inutilement)

void log_info(char *message,...);
void log_debug(char *message,...);



#endif 
