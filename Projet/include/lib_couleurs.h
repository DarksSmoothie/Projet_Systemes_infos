// renvoie API et fonctions couleurs

#ifndef LIB_COULEURS_H
#define LIB_COULEURS_H

/*
 * Pilotage d'une LED RGB via les GPIO du Raspberry Pi.
 * Les broches sont actives à l'état bas (LOW allume la LED).
 * Nécessite les permissions d'écriture dans /sys/class/gpio (souvent sudo).
 */

/* Prépare les GPIO (export + direction=out) et éteint la LED.
 * Retourne 0 si tout va bien, -1 sinon. */
int led_init(void);

/* Eteint la LED et dés-exporte les broches. Optionnel mais propre. */
void led_shutdown(void);

/* Fonctions de couleur. Retourne 0 en cas de succès, -1 en cas d'erreur. */
int turnOff(void);
int white(void);
int red(void);
int green(void);
int blue(void);
int yellow(void);
int purple(void);
int lightBlue(void);

#endif /* LIB_COULEURS_H */
