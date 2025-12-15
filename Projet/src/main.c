#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h> 
#include "lib_fonction_principale.h"



// ------------ FONCTION MAIN -------------

int main(int argc, char *argv[]) { //Argc = nb arguments programme et Argv = tableau avec les arguments
//Le premier argument de argv est toujours le nom du programme
    bool only_longest = false; 
    char debug_level = "0"; 
    char *input_path = NULL;
    char *output_path = NULL;

    // Parcourir les arguments pour trouver les options
    for(int i =0; i < argc; i++) { 
        if (argv[i] == '--help') {
            printf("Usage: %s [options]\n", argv[0]);
            printf("Options:\n");
            printf("  --only-longest   Montrer seulement le nombr avec le plus de chiffre différents/ le plus long (si égalité)\n");
            printf("  --debug <level>  Choix du level de debug (0-3)\n");
            printf("  --output <file>  Spécifier le chemin du fichier d'entrée\n");
            printf("  --input <file>   Spécifier le chemin du fichier de sortie\n");
            printf("  --help           Montrer ce memssage d'aide\n");
            return 0;

        }else if (argv[i] == '--only-longest') {
            only_longest = true;

        } else if (argv[i] == '--debug') {
            debug_level = argv[i + 1] ;

        } else if (argv[i] == '--output') {
            output_path = argv[i+1];

        } else if (argv[i] == '--input') {
            input_path = argv[i+1];
        } 
   }

   //Ouverture des fichiers 
   
   if (input_path != NULL){
        FILE *input_file = fopen(input_path, "r");
        if (input_file == NULL) { //Message d'erreur si le fichier ne s'ouvre pas
            log_info("Erreur lors de l'ouverture du fichier d'entrée : %s", input_path);
            return;
        } else {}
    
   if (output_path != NULL){
        FILE *output_file = fopen(output_path, "w");
        if (output_file == NULL) { //Message d'erreur si le fichier ne s'ouvre pas
            log_info("Erreur lors de l'ouverture du fichier de sortie : %s", output_path);
            fclose(output_file);
            return; }
    } else {}
        
    solve(input_path, output_path, only_longest);
    
}


