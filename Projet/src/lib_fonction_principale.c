#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "lib_tableaux_dynamiques.h" //REGLER CA //Fonction utilitaires pour la gestion de tableaux dynamiques



// ------------ Ma Fonction -----------------
void solve(char *input_path, char *output_path, bool only_longest) {
    log_info("Nous allons considérer le fichier %s en entrée et %s en sortie", input_path, output_path);
    
    FILE *input_file = fopen(input_path, "r");
    if (input_file == NULL) { //Message d'erreur si le fichier ne s'ouvre pas
        log_info("Erreur lors de l'ouverture du fichier d'entrée : %s", input_path);
        return;}
    
    FILE *output_file = fopen(output_path, "w");
    if (output_file == NULL) { //Message d'erreur si le fichier ne s'ouvre pas
        log_info("Erreur lors de l'ouverture du fichier de sortie : %s", output_path);
        fclose(input_file);
        return; }
}


