// renvoie API et fonctions couleurs

#ifndef LIB_COULEURS_H
#define LIB_COULEURS_H
#define _POSIX_C_SOURCE 200809L

//Attention, nécéssite sudo

/* Prépare les GPIO (export + direction=out) et éteint la LED.
 * Retourne 0 si tout va bien, -1 sinon. */
int led_init(void);

/* Eteint la LED et dés-exporte les broches. Optionnel mais propre. */
void led_shutdown(void);

/* Raccourcis d'état. Retourne 0 si OK, -1 sinon (par exemple si GPIO non accessible). */
int led_set_success(void); /* vert */
int led_set_error(void);   /* rouge */

/* Alterne entre deux couleurs d'exécution (bleu / violet). */
int led_toggle_running(void);

/* Fonctions de couleur. Retourne 0 en cas de succès, -1 en cas d'erreur. */
int turnOff(void);
int white(void);
int red(void);
int green(void);
int blue(void);
int yellow(void);
int purple(void);
int lightBlue(void);

#endif 
