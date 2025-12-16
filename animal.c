#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "animal.h"

/*
 * Fichier : animal.c
 * Description : Implémentation de la lecture de configuration.
 */

 /* Fonction utilitaire pour dupliquer une chaîne (strdup n'est pas toujours standard C99 strict) */
static char* monStrDup(const char* s) {
    char* d = malloc(strlen(s) + 1);
    if (d == NULL) return NULL;
    strcpy(d, s);
    return d;
}

int chargerConfiguration(ConfigJeu* config, const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        perror("Erreur ouverture fichier config");
        return 0;
    }

    config->nbAnimaux = 0;
    config->nbOrdres = 0;

    char ligne[1024]; /* Tampon de lecture large */

    /* --- Lecture de la première ligne : Les Animaux --- */
    if (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        /* On retire le saut de ligne à la fin si présent */
        ligne[strcspn(ligne, "\n")] = 0;

        /* Découpage par espaces */
        char* token = strtok(ligne, " ");
        while (token != NULL && config->nbAnimaux < MAX_ANIMAUX) {
            config->nomsAnimaux[config->nbAnimaux] = monStrDup(token);
            config->nbAnimaux++;
            token = strtok(NULL, " ");
        }
    }
    else {
        /* Fichier vide ou erreur */
        fclose(fichier);
        return 0;
    }

    /* --- Lecture de la seconde ligne : Les Ordres --- */
    if (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        ligne[strcspn(ligne, "\n")] = 0;

        char* token = strtok(ligne, " ");
        while (token != NULL && config->nbOrdres < MAX_ORDRES) {
            config->ordres[config->nbOrdres] = monStrDup(token);
            config->nbOrdres++;
            token = strtok(NULL, " ");
        }
    }

    fclose(fichier);
    return 1;
}

void libererConfiguration(ConfigJeu* config) {
    for (int i = 0; i < config->nbAnimaux; i++) {
        free(config->nomsAnimaux[i]);
    }
    for (int i = 0; i < config->nbOrdres; i++) {
        free(config->ordres[i]);
    }
}

void afficherConfiguration(const ConfigJeu* config) {
    printf("Animaux (%d) : ", config->nbAnimaux);
    for (int i = 0; i < config->nbAnimaux; i++) {
        printf("[%s] ", config->nomsAnimaux[i]);
    }
    printf("\nOrdres (%d) : ", config->nbOrdres);
    for (int i = 0; i < config->nbOrdres; i++) {
        printf("[%s] ", config->ordres[i]);
    }
    printf("\n");
}

int validerConfiguration(const ConfigJeu* config) {
    /* Règle 1: Au moins 3 animaux */
    if (config->nbAnimaux < 3) {
        printf("Erreur Config: Il faut au moins 3 animaux.\n");
        return 0;
    }

    /* Règle 2: Présence des 5 ordres (KI, LO, SO, NI, MA) */
    /* Le sujet demande de vérifier que les 5 commandes sont présentes */
    const char* ordresRequis[] = { "KI", "LO", "SO", "NI", "MA" };
    int nbRequis = 5;
    int manquant = 0;

    for (int i = 0; i < nbRequis; i++) {
        int trouve = 0;
        for (int j = 0; j < config->nbOrdres; j++) {
            if (strcmp(config->ordres[j], ordresRequis[i]) == 0) {
                trouve = 1;
                break;
            }
        }
        if (!trouve) {
            printf("Erreur Config: L'ordre obligatoire '%s' est manquant.\n", ordresRequis[i]);
            manquant = 1;
        }
    }

    if (manquant) return 0;

    return 1;
}
