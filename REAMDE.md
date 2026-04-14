# Simple Shell

Description:

Ce projet consiste à créer un interpréteur de commandes UNIX simple en langage C.

Il reproduit certaines fonctionnalités du shell standard (/bin/sh), en permettant d’exécuter des commandes en mode interactif et non interactif.

Objectifs:

-Comprendre le fonctionnement d’un shell
-Apprendre à créer des processus avec fork
-Exécuter des programmes avec execve
-Manipuler les variables d’environnement
-Implémenter la gestion du PATH

Compilation:

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

Utilisation:

Mode interactif

./hsh
($) /bin/ls
($) exit

Mode non interactif

echo "/bin/ls" | ./hsh

Fonctionnement:

-Affiche un prompt
-Lit l’entrée utilisateur
-Analyse la commande
-Crée un processus enfant avec fork
-Exécute la commande avec execve
-Attend la fin du processus avec wait

Fichiers:

-main.c → point d’entrée
-shell.c → boucle principale
-parser.c → analyse des commandes
-exec.c → exécution des commandes

Fonctions utilisées:

-fork
-execve
-wait
-getline
-strtok
-access

Gestion des erreurs:

-Affiche une erreur si la commande est introuvable
-Utilise perror pour les erreurs système
-Gère la fin de fichier (Ctrl + D)

Auteurs:

-Pacôme Dutreuil
-Youssef Ben Rahou
