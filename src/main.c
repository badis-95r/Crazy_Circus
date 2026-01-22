

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "jeu.h"


#define MAX_JOUEURS 10
#define LEN_CMD 256
#define CONFIG_FILENAME "crazy.cfg"

/**
 * @struct Joueur
 * @brief Représente un participant à la partie
 */
typedef struct {
    char* nom;  /* Pointeur vers le nom (argv) */
    int score;  /*Score courant */
} Joueur;


/**
 * @brief Fonction de comparaison pour le tri des scores
 */
int compareJoueurs(const void* a, const void* b) {
    const Joueur* j1 = (const Joueur*)a;
    const Joueur* j2 = (const Joueur*)b;

    if (j1->score != j2->score) {
        return j2->score - j1->score;
    }
    return strcmp(j1->nom, j2->nom);
}



int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: %s <Joueur1> <Joueur2> ...\n", argv[0]);
        printf("Erreur : Il faut au moins 2 joueurs pour lancer la partie.\n");
        return EXIT_FAILURE;
    }

    Joueur joueurs[MAX_JOUEURS];
    int nbJoueurs = 0;

    /* Récupération des noms depuis la ligne de commande */
    for (int i = 1; i < argc; i++) {
        if (nbJoueurs >= MAX_JOUEURS) {
            printf("Attention: Nombre maximum de joueurs (%d) atteint. Les suivants sont ignores.\n", MAX_JOUEURS);
            break;
        }

        /* Vérification des doublons de noms */
        int existe = 0;
        for (int k = 0; k < nbJoueurs; k++) {
            if (strcmp(joueurs[k].nom, argv[i]) == 0) {
                existe = 1;
                break;
            }
        }
        if (existe) {
            printf("Erreur: Les noms des joueurs doivent etre distincts (%s).\n", argv[i]);
            return EXIT_FAILURE;
        }

        /* Initialisation du joueur */
        joueurs[nbJoueurs].nom = argv[i];
        joueurs[nbJoueurs].score = 0;
        nbJoueurs++;
    }



    ConfigJeu config;

    if (!chargerConfiguration(&config, CONFIG_FILENAME)) {
        fprintf(stderr, "Erreur fatale : Impossible de lire le fichier de configuration %s.\n", CONFIG_FILENAME);
        return EXIT_FAILURE;
    }
    if (!validerConfiguration(&config)) {
        libererConfiguration(&config);
        return EXIT_FAILURE;
    }


  

    srand((unsigned int)time(NULL)); 

    /* Génération du paquet complet des positions */
    Deck deck;
    genererToutesPositions(&config, &deck);

    /* Affichage des ordres disponibles*/
    afficherOrdresPossibles(&config);

    /* Tirage des états initiaux */
    EtatJeu* courant = tirerNouvelleCarte(&deck); /* Position de départ */
    EtatJeu* objectif = tirerNouvelleCarte(&deck); /* Position objectif */

    if (courant == NULL || objectif == NULL) {
        printf("Erreur : Pas assez de combinaisons pour jouer.\n");
        return EXIT_FAILURE;
    }

    int* peutJouer = (int*)malloc(sizeof(int) * nbJoueurs);
    for (int i = 0; i < nbJoueurs; i++) peutJouer[i] = 1;
    int nbJoueursEnLice = nbJoueurs;


 
    while (objectif != NULL) {

        afficherDuel(courant, objectif);

        int tourTermine = 0;


        while (!tourTermine) {
            char buffer[LEN_CMD];

            if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
                tourTermine = 1;
                objectif = NULL;
                break;
            }
            buffer[strcspn(buffer, "\n")] = 0;

            if (strlen(buffer) == 0) continue;

            char* nomJoueur = strtok(buffer, " ");
            char* sequence = strtok(NULL, " ");

            int idJoueur = -1;
            for (int i = 0; i < nbJoueurs; i++) {
                if (strcmp(joueurs[i].nom, nomJoueur) == 0) {
                    idJoueur = i;
                    break;
                }
            }

            if (idJoueur == -1) {
                printf("Joueur inconnu (%s)\n", nomJoueur);
                continue; 
            }

            if (!peutJouer[idJoueur]) {
                printf("%s ne peut pas jouer durant ce tour\n", nomJoueur);
                continue;
            }

            if (sequence == NULL) {
                continue;
            }



            EtatJeu testState;
            initEtat(&testState);
            copierEtat(courant, &testState);

            int codeRetour = executerSequence(&testState, sequence);

            if (codeRetour == -1) {

                char ordreFaux[3] = "??";
                for (size_t i = 0; i < strlen(sequence); i += 2) {
                    char sub[3];
                    sub[0] = sequence[i];
                    sub[1] = sequence[i + 1];
                    sub[2] = '\0';

                    int estValide = 0;
                    if (strcmp(sub, "KI") == 0 || strcmp(sub, "LO") == 0 ||
                        strcmp(sub, "SO") == 0 || strcmp(sub, "NI") == 0 ||
                        strcmp(sub, "MA") == 0) {
                        estValide = 1;
                    }

                    if (!estValide) {
                        strcpy(ordreFaux, sub);
                        break;
                    }
                }
                printf("L'ordre %s n'existe pas\n", ordreFaux);
            }

            /* Vérification de la victoire */
            int bonneSolution = 0;
            if (codeRetour == 1) {
                if (estMemeEtat(&testState, objectif)) {
                    bonneSolution = 1;
                }
            }

            libererEtat(&testState);

            if (bonneSolution) {
                /* VICTOIRE DU JOUEUR */
                printf("%s gagne un point\n\n", nomJoueur);
                joueurs[idJoueur].score++;
                tourTermine = 1;
            }
            else {

                if (codeRetour != -1) {
                    printf("La sequence ne conduit pas a la situation attendue\n");
                    printf("%s ne peut plus jouer durant ce tour\n", nomJoueur);
                    peutJouer[idJoueur] = 0;
                    nbJoueursEnLice--;
                }


                if (nbJoueursEnLice == 1) {
                    int survivant = -1;
                    for (int i = 0; i < nbJoueurs; i++) {
                        if (peutJouer[i]) {
                            survivant = i;
                            break;
                        }
                    }
                    /* agne par forfait */
                    printf("%s gagne un point car lui seul peut encore jouer durant ce tour\n\n", joueurs[survivant].nom);
                    joueurs[survivant].score++;
                    tourTermine = 1;
                }
                else if (nbJoueursEnLice == 0) {
                    printf("Tous les joueurs ont echoue. Fin du tour sans vainqueur.\n\n");
                    tourTermine = 1;
                }
            }

        } 


        /* Préparation du Tour Suivant */
        if (objectif != NULL) {
            /* L'objectif atteint devient le nouveau point de départ */
            courant = objectif;
             /* Tirage d'un nouvel objectif */
            objectif = tirerNouvelleCarte(&deck);

            /* Réinitialisation des droits de jeu pour tous */
            for (int i = 0; i < nbJoueurs; i++) peutJouer[i] = 1;
            nbJoueursEnLice = nbJoueurs;
        }

    }


    /*Fin de Partie et score */

    /* Tri des joueurs selon le score */
    qsort(joueurs, nbJoueurs, sizeof(Joueur), compareJoueurs);

    /* Affichage du classement final */
    for (int i = 0; i < nbJoueurs; i++) {
        printf("%s %d\n", joueurs[i].nom, joueurs[i].score);
    }



    free(peutJouer);

    for (int i = 0; i < deck.nbPositions; i++) {
        libererEtat(&deck.positions[i]);
    }
    free(deck.positions);
    free(deck.estUtilisee);

    libererConfiguration(&config);

    return EXIT_SUCCESS;
}