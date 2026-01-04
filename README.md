# 🔢 Mathematical Suite Solver (Look-and-Say)

## 📌 Contexte académique

Ce projet est un **travail universitaire de groupe** réalisé en 2025 dans le cadre d’un cours d’informatique à la **Faculté Polytechnique de l’Université de Mons (UMONS)**.

Il porte sur l’étude et l’implémentation d’une **suite mathématique de type _look-and-say_**, avec une attention particulière portée à la performance, à la gestion mémoire et à l’interface utilisateur.

---

## 📖 Description du problème

La suite _look-and-say_ est définie de manière itérative : chaque terme est obtenu en décrivant le comptage des chiffres consécutifs du terme précédent.

Exemple :
- `1` → “un 1” → `11`
- `11` → “deux 1” → `21`
- `21` → “un 2, un 1” → `1211`
- puis `111221`, `312211`, etc.

Le programme reçoit un **fichier texte en entrée**
Chaque ligne du fichier contient au maximum **4000 caractères** (espaces inclus).

---

## 🎯 Objectifs du projet

Les objectifs principaux sont :
- générer correctement les termes de la suite après un nombre donné d’itérations ;
- identifier les résultats contenant :
  1. le **plus grand nombre de chiffres différents** ;
  2. et, en cas d’égalité, la **plus grande longueur** ;
- fournir une implémentation **performante en langage C** ;
- garantir l’absence de **fuites mémoire** ;
- permettre l’exécution sur **Raspberry Pi** ;
- proposer un **retour visuel via une LED RGB** indiquant l’état du programme.

---

## ⚙️ Fonctionnalités implémentées

### 🔹 Calcul de la suite
- Génération correcte des suites _look-and-say_
- Gestion de grandes chaînes (jusqu’à 4000 caractères par ligne)
- Implémentation conforme à l’algorithme fourni en Python, avec correction du bug lié au comptage des chiffres différents

---

### 🔹 Options en ligne de commande

Le programme ne possède **aucun argument positionnel obligatoire**, mais accepte les options suivantes :

- `--input PATH`  
  Indique le fichier d’entrée.  
  Si absent, la lecture se fait depuis l’entrée standard.

- `--output PATH`  
  Indique le fichier de sortie.  
  Si absent, l’écriture se fait sur la sortie standard.

- `--only-longest`  
  Affiche uniquement le(s) résultat(s) ayant :
  1. le plus grand nombre de chiffres différents ;
  2. puis, en cas d’égalité, la plus grande longueur.

- `--debug LEVEL`  
  Active les logs :
  - `0` : aucun log (par défaut)
  - `1` : logs partiels
  - `2` : logs complets

➡️ **L’ordre des options est totalement indépendant**, conformément aux spécifications.

---

## ▶️ Exemples d’utilisation

Les commandes suivantes sont équivalentes :

cat input.txt | ./math_suite > output.txt
./math_suite --input input.txt --output output.txt

De même, avec l’option --only-longest :
cat input.txt | ./math_suite --only-longest > output.txt
./math_suite --only-longest --input input.txt --output output.txt


##Indication de l’état via LED RGB

Le programme intègre une LED RGB indiquant son état d’exécution :
	•	Vert : le programme s’est terminé correctement ;
	•	Rouge : une erreur est survenue ;
	•	Alternance de deux couleurs (ni rouge ni verte) : programme en cours d’exécution
(la fréquence et les couleurs sont librement choisies).

Cette interface permet de suivre l’état du programme sans consulter le terminal.
