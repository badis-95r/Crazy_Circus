
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "animal.h"


 /**
  * @brief Duplique une chaîne de caractères 
  * @param[in] s La chaîne de caractères à copier
  * @return char* Un pointeur vers la nouvelle chaîne allouée (ou NULL si échec d'allocation)
  */
static char* monStrDup(const char* s) {
    if (s == NULL) return NULL;
    size_t len = strlen(s);
    char* d = (char*)malloc(len + 1);
    if (d == NULL) return NULL;
    strcpy(d, s);
    return d;
}

/**
 * @brief Charge la configuration du jeu depuis un fichier
 * @param[out] config Pointeur vers la structure ConfigJeu à remplir
 * @param[in] nomFichier Chemin vers le fichier de configuration
 * @return int 1 si le chargement technique est réussi, 0 en cas d'erreur d'ouverture
 */
int chargerConfiguration(ConfigJeu* config, const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        return 0;
    }

    config->nbAnimaux = 0;
    config->nbOrdres = 0;

    char ligne[1024];

    /* Lecture des animaux */
    if (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        ligne[strcspn(ligne, "\n")] = '\0';
        ligne[strcspn(ligne, "\r")] = '\0';

        char* token = strtok(ligne, " ");
        while (token != NULL && config->nbAnimaux < MAX_ANIMAUX) {

            if (strlen(token) > 0) {
                config->nomsAnimaux[config->nbAnimaux] = monStrDup(token);
                config->nbAnimaux++;
            }
            token = strtok(NULL, " ");
        }
    }
    else {
        fclose(fichier);
        return 0;
    }

    /* Lecture des ordres */
    if (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        ligne[strcspn(ligne, "\n")] = '\0';
        ligne[strcspn(ligne, "\r")] = '\0';

        char* token = strtok(ligne, " ");
        while (token != NULL && config->nbOrdres < MAX_ORDRES) {
            if (strlen(token) > 0) {
                config->ordres[config->nbOrdres] = monStrDup(token);
                config->nbOrdres++;
            }
            token = strtok(NULL, " ");
        }
    }

    fclose(fichier);
    return 1;
}

/**
 * @brief Libère la mémoire allouée pour la configuration
 * @param[in,out] config Pointeur vers la structure ConfigJeu à nettoyer
 */
void libererConfiguration(ConfigJeu* config) {
    if (config == NULL) return;

    for (int i = 0; i < config->nbAnimaux; i++) {
        free(config->nomsAnimaux[i]);
        config->nomsAnimaux[i] = NULL;
    }
    config->nbAnimaux = 0;

    for (int i = 0; i < config->nbOrdres; i++) {
        free(config->ordres[i]);
        config->ordres[i] = NULL;
    }
    config->nbOrdres = 0;
}

/**
 * @brief Affiche le contenu de la configuration chargée 
 * @param[in] config Pointeur vers la structure ConfigJeu à afficher
 */
void afficherConfiguration(const ConfigJeu* config) {
    if (config == NULL) return;

    printf("Animaux chargees (%d) : ", config->nbAnimaux);
    for (int i = 0; i < config->nbAnimaux; i++) {
        printf("%s ", config->nomsAnimaux[i]);
    }
    printf("\n");

    printf("Ordres charges (%d)   : ", config->nbOrdres);
    for (int i = 0; i < config->nbOrdres; i++) {
        printf("%s ", config->ordres[i]);
    }
    printf("\n");
}

/**
 * @brief Vérifie les règles imposées par le jeu
 * @param[in] config Pointeur vers la structure ConfigJeu à vérifier
 * @return int 1 si la configuration est valide, 0 sinon
 */
int validerConfiguration(const ConfigJeu* config) {
    /* Les animaux doivent être deux au minimum  */
    if (config->nbAnimaux < 2) {
        printf("Erreur Config : Il faut au moins 2 animaux (trouve : %d).\n", config->nbAnimaux);
        return 0;
    }

    /* Les ordres doivent être au moins trois  */
    if (config->nbOrdres < 3) {
        printf("Erreur Config : Il faut au moins 3 ordres (trouve : %d).\n", config->nbOrdres);
        return 0;
    }

    /* Les ordres sont nécessairement choisis parmi les 5 ordres connus */
    const char* ordresValides[] = { "KI", "LO", "SO", "NI", "MA" };
    int nbValidesConnus = 5;

    for (int i = 0; i < config->nbOrdres; i++) {
        int estReconnu = 0;
        for (int j = 0; j < nbValidesConnus; j++) {
            if (strcmp(config->ordres[i], ordresValides[j]) == 0) {
                estReconnu = 1;
                break;
            }
        }
        if (!estReconnu) {
            printf("Erreur Config : L'ordre '%s' n'est pas un ordre valide (KI, LO, SO, NI, MA).\n", config->ordres[i]);
            return 0;
        }
    }

    return 1;
}