#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h> 
#include <string.h>
#include "lib_fonction_principale.h"
#include "lib_utilitaires.h"
#include "lib_couleurs.h"

static void led_progress_cb(void) {
    /* Alterne les couleurs pendant l'exécution (ignore les erreurs GPIO). */
    led_toggle_running();
}



// ------------ FONCTION MAIN -------------

int main(int argc, char *argv[]) { //Argc = nb arguments programme et Argv = tableau avec les arguments
//Le premier argument de argv est toujours le nom du programme
    bool only_longest = false; 
    char *input_path = NULL;
    char *output_path = NULL;
    bool led_ok = false;

    // Parcourir les arguments pour trouver les options
    for(int i =1; i < argc; i++) { 
        if (strcmp(argv[i],"--help")==0) { //On ne peux pas comparer deux strings avec == en C 
            printf("Usage: %s [options]\n", argv[0]);
            printf("Options:\n");
            printf("  --only-longest   Montrer seulement le nombr avec le plus de chiffre différents/ le plus long (si égalité)\n");
            printf("  --debug <level>  Choix du level de debug (0-3)\n");
            printf("  --output <file>  Spécifier le chemin du fichier d'entrée\n");
            printf("  --input <file>   Spécifier le chemin du fichier de sortie\n");
            printf("  --help           Montrer ce memssage d'aide\n");
            return 0;

        }else if (strcmp(argv[i],"--only-longest")==0) {
            only_longest = true;

        } else if (strcmp(argv[i],"--debug")==0)  {
            if (i + 1 >= argc) { fprintf(stderr, "--debug nécessite une valeur\n"); return -1; }
            debug_level = argv[i + 1][0] ;

        } else if (strcmp(argv[i],"--output")==0)  {
            if (i + 1 >= argc) { fprintf(stderr, "--output nécessite une valeur\n"); return -1; }
            output_path = argv[i+1];

        } else if (strcmp(argv[i],"--input")==0)  {
            if (i + 1 >= argc) { fprintf(stderr, "--input nécessite une valeur\n"); return -1; }
            input_path = argv[i+1];
        } 
   }


    FILE *input;
    FILE *output;

    //Ouverture des fichiers et vérification des erreurs si le ficheir ne s'est pas ouvert
   if (input_path != NULL){
        input = fopen(input_path, "r");
        if (input == NULL) { //Message d'erreur si le fichier ne s'ouvre pas
            log_info("Erreur lors de l'ouverture du fichier d'entrée : %s", input_path);
            return -1;
        } 
    }else {input = stdin;}
    
   if (output_path != NULL){
        output = fopen(output_path, "w");
        if (output == NULL) { //Message d'erreur si le fichier ne s'ouvre pas
            log_info("Erreur lors de l'ouverture du fichier de sortie : %s", output_path);
            return -1; 
        }
   }else {output = stdout;} 
     
    
    //Appel de notre fonction 
    if (led_init() == 0) {
        led_ok = true;
        led_toggle_running(); /* première couleur pendant l'exécution */
    }

    int status = solve(input, output, only_longest, led_ok ? led_progress_cb : NULL);

    if (led_ok) {
        if (status == 0) led_set_success();
        else led_set_error();
        led_shutdown();
    }

    if (input != stdin) fclose(input);
    if (output != stdout) fclose(output);
    return status;
    
}

