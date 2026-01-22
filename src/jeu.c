
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "jeu.h"


 /**
  * @brief Initialise les podiums d'un état de jeu.
  * @param[out] e Pointeur vers l'état à initialiser.
  */
void initEtat(EtatJeu* e) {
    initPile(&e->podiumBleu);
    initPile(&e->podiumRouge);
}

/**
 * @brief Libère la mémoire des piles contenues dans un état.
 * @param[in,out] e Pointeur vers l'état à nettoyer.
 */
void libererEtat(EtatJeu* e) {
    detruirePile(&e->podiumBleu);
    detruirePile(&e->podiumRouge);
}

/**
 * @brief Copie le contenu d'un état de jeu source vers un état destination
 * @param[in] src État de jeu source 
 * @param[out] dest État destination 
 */
void copierEtat(const EtatJeu* src, EtatJeu* dest) {
    detruirePile(&dest->podiumBleu);
    detruirePile(&dest->podiumRouge);
    initPile(&dest->podiumBleu);
    initPile(&dest->podiumRouge);


    Cellule* courant = src->podiumBleu.tete;
    char* temp[MAX_ANIMAUX];
    int n = 0;

    while (courant != NULL && n < MAX_ANIMAUX) {
        temp[n++] = courant->valeur;
        courant = courant->suivant;
    }

    for (int i = n - 1; i >= 0; i--) {
        empiler(&dest->podiumBleu, temp[i]);
    }

    courant = src->podiumRouge.tete;
    n = 0;
    while (courant != NULL && n < MAX_ANIMAUX) {
        temp[n++] = courant->valeur;
        courant = courant->suivant;
    }
    for (int i = n - 1; i >= 0; i--) {
        empiler(&dest->podiumRouge, temp[i]);
    }
}

/**
 * @brief Compare deux états de jeu pour savoir s'ils sont identiques
 * @param[in] e1 Premier état de jeu
 * @param[in] e2 Deuxième état de jeu
 * @return int 1 si identiques, 0 sinon
 */
int estMemeEtat(const EtatJeu* e1, const EtatJeu* e2) {
    
    if (taillePile(&e1->podiumBleu) != taillePile(&e2->podiumBleu)) return 0;
    if (taillePile(&e1->podiumRouge) != taillePile(&e2->podiumRouge)) return 0;

    
    Cellule* c1 = e1->podiumBleu.tete;
    Cellule* c2 = e2->podiumBleu.tete;
    while (c1 != NULL) {
        if (strcmp(c1->valeur, c2->valeur) != 0) return 0;
        c1 = c1->suivant;
        c2 = c2->suivant;
    }


    c1 = e1->podiumRouge.tete;
    c2 = e2->podiumRouge.tete;
    while (c1 != NULL) {
        if (strcmp(c1->valeur, c2->valeur) != 0) return 0;
        c1 = c1->suivant;
        c2 = c2->suivant;
    }

    return 1;
}



/**
 * @brief Exécute l'ordre KI 
 * @param[in,out] e État du jeu
 * @return int 1 si succès, 0 si podium bleu vide
 */
int commandeKI(EtatJeu* e) {
    if (pileEstVide(&e->podiumBleu)) return 0;
    empiler(&e->podiumRouge, depiler(&e->podiumBleu));
    return 1;
}

/**
 * @brief Exécute l'ordre LO 
 * @param[in,out] e État du jeu
 * @return int 1 si succès, 0 si podium rouge vide
 */
int commandeLO(EtatJeu* e) {
    if (pileEstVide(&e->podiumRouge)) return 0;
    empiler(&e->podiumBleu, depiler(&e->podiumRouge));
    return 1;
}

/**
 * @brief Exécute l'ordre SO 
 * @param[in,out] e État du jeu
 * @return int 1 si succès, 0 si l'un des podiums est vide
 */
int commandeSO(EtatJeu* e) {
    if (pileEstVide(&e->podiumBleu) || pileEstVide(&e->podiumRouge)) return 0;

    char* valBleu = depiler(&e->podiumBleu);
    char* valRouge = depiler(&e->podiumRouge);

    empiler(&e->podiumBleu, valRouge);
    empiler(&e->podiumRouge, valBleu);
    return 1;
}

/**
 * @brief Effectue une rotation Bas vers Haut sur une pile
 * @param[in,out] p La pile à manipuler
 * @return int 1 si succès, 0 si pile vide
 */
static int rotationBasVersHaut(Pile* p) {
    if (pileEstVide(p)) return 0;
    if (taillePile(p) == 1) return 1; 

    Pile temp;
    initPile(&temp);

  
    while (taillePile(p) > 1) {
        empiler(&temp, depiler(p));
    }

    char* bas = depiler(p);

    while (!pileEstVide(&temp)) {
        empiler(p, depiler(&temp));
    }

    empiler(p, bas);

    detruirePile(&temp);
    return 1;
}

/**
 * @brief Exécute l'ordre NI 
 * @param[in,out] e État du jeu
 * @return int 1 si succès
 */
int commandeNI(EtatJeu* e) {
    return rotationBasVersHaut(&e->podiumBleu);
}

/**
 * @brief Exécute l'ordre MA 
 * @param[in,out] e État du jeu
 * @return int 1 si succès
 */
int commandeMA(EtatJeu* e) {
    return rotationBasVersHaut(&e->podiumRouge);
}

/**
 * @brief Parse et exécute une séquence de commandes 
 * @param[in,out] e État du jeu à modifier
 * @param[in] seq Chaîne de caractères contenant les ordres 
 * @return int 1 si OK, 0 si mouvement impossible, -1 si ordre inconnu
 */
int executerSequence(EtatJeu* e, const char* seq) {
    int len = strlen(seq);

    if (len % 2 != 0) return 0;

    for (int i = 0; i < len; i += 2) {
        char cmd[3];
        cmd[0] = seq[i];
        cmd[1] = seq[i + 1];
        cmd[2] = '\0';

        int res = 0;

        if (strcmp(cmd, "KI") == 0)      res = commandeKI(e);
        else if (strcmp(cmd, "LO") == 0) res = commandeLO(e);
        else if (strcmp(cmd, "SO") == 0) res = commandeSO(e);
        else if (strcmp(cmd, "NI") == 0) res = commandeNI(e);
        else if (strcmp(cmd, "MA") == 0) res = commandeMA(e);
        else return -1; 

        if (res == 0) return 0; 
    }

    return 1;
}



/**
 * @brief Enregistre une permutation avec une coupure donnée
 * @param[in,out] deck Le deck de cartes à remplir
 * @param[in,out] animaux Tableau des animaux dans l'ordre de la permutation actuelle
 * @param[in] n Nombre total d'animaux
 * @param[in] coupure Index de séparation (0 à n)
 */
static void enregistrerConfiguration(Deck* deck, char** animaux, int n, int coupure) {
    EtatJeu* nouv = &deck->positions[deck->nbPositions];
    initEtat(nouv);

    for (int i = 0; i < coupure; i++) {
        empiler(&nouv->podiumBleu, animaux[i]);
    }


    for (int i = coupure; i < n; i++) {
        empiler(&nouv->podiumRouge, animaux[i]);
    }

    deck->nbPositions++;
}

/**
 * @brief Calcule la factorielle d'un nombre (n!) pour l'algorithme de Heap
 */
static int factorielle(int n) {
    if (n <= 1) return 1;
    int res = 1;
    for (int i = 2; i <= n; i++) res *= i;
    return res;
}

/**
 * @brief Génère toutes les positions possibles du jeu grâce à l'algorithme de Heap
 * @param[in] config Configuration contenant les animaux
 * @param[out] deck Structure Deck à allouer et remplir
 */
void genererToutesPositions(const ConfigJeu* config, Deck* deck) {
    int n = config->nbAnimaux;
    int factN = factorielle(n);
    int capaciteMax = factN * (n + 1);

    deck->positions = (EtatJeu*)malloc(sizeof(EtatJeu) * capaciteMax);
    if (deck->positions == NULL) {
        fprintf(stderr, "Erreur fatale : Memoire insuffisante pour le deck.\n");
        exit(EXIT_FAILURE);
    }
    deck->nbPositions = 0;

    char* A[MAX_ANIMAUX];
    for (int i = 0; i < n; i++) A[i] = config->nomsAnimaux[i];

    int c[MAX_ANIMAUX];
    for (int i = 0; i < n; i++) c[i] = 0;

    for (int k = 0; k <= n; k++) enregistrerConfiguration(deck, A, n, k);

    int i = 0;
    while (i < n) {
        if (c[i] < i) {
            if (i % 2 == 0) {
                char* tmp = A[0]; A[0] = A[i]; A[i] = tmp;
            }
            else {
                char* tmp = A[c[i]]; A[c[i]] = A[i]; A[i] = tmp;
            }

            for (int k = 0; k <= n; k++) enregistrerConfiguration(deck, A, n, k);

            c[i] += 1;
            i = 0;
        }
        else {
            c[i] = 0;
            i += 1;
        }
    }

    deck->estUtilisee = (int*)calloc(deck->nbPositions, sizeof(int));
}

/**
 * @brief Tire une carte objectif aléatoire non encore jouée
 * @param[in,out] deck Le paquet de cartes
 * @return EtatJeu* Pointeur vers l'état cible, ou NULL si le deck est épuisé
 */
EtatJeu* tirerNouvelleCarte(Deck* deck) {
    int dispo = 0;
    /* Compter les cartes restantes */
    for (int i = 0; i < deck->nbPositions; i++) {
        if (!deck->estUtilisee[i]) dispo++;
    }

    if (dispo == 0) return NULL;

    /* Tirage au sort parmi les disponibles */
    int choix = rand() % dispo;
    int compteur = 0;

    for (int i = 0; i < deck->nbPositions; i++) {
        if (!deck->estUtilisee[i]) {
            if (compteur == choix) {
                deck->estUtilisee[i] = 1; /* Marquer comme utilisée */
                return &deck->positions[i];
            }
            compteur++;
        }
    }
    return NULL;
}




/**
 * @brief Affiche la liste des ordres disponibles
 * @param[in] config le fichier de configuration
 */
void afficherOrdresPossibles(const ConfigJeu* config) {
    for (int i = 0; i < config->nbOrdres; i++) {
        char* o = config->ordres[i];
        printf("%s ", o);

        if (strcmp(o, "KI") == 0)      printf("(B -> R)");
        else if (strcmp(o, "LO") == 0) printf("(B <- R)");
        else if (strcmp(o, "SO") == 0) printf("(B <-> R)");
        else if (strcmp(o, "NI") == 0) printf("(B ^)");
        else if (strcmp(o, "MA") == 0) printf("(R ^)");

        if (i < config->nbOrdres - 1) printf(" | ");
    }
    printf("\n\n");
}


/**
 * @brief  Convertit une pile en tableau pour faciliter l'affichage
 * @param[in] p Constante d'un Pointeur vers une pile
 * @param[in,out] tab pointeur d'un tableau de chaine de caractères
 * @return int
 */
static int pileVersTableau(const Pile* p, char* tab[]) {
    int h = 0;
    Cellule* c = p->tete;
    while (c != NULL) {
        tab[h++] = c->valeur;
        c = c->suivant;
    }
    return h;
}

/**
 * @brief Affiche le duel 
 * @param[in] depart État actuel du joueur
 * @param[in] arrivee État objectif à atteindre
 */
void afficherDuel(const EtatJeu* depart, const EtatJeu* arrivee) {
    char* b1[MAX_ANIMAUX]; int hB1 = pileVersTableau(&depart->podiumBleu, b1);
    char* r1[MAX_ANIMAUX]; int hR1 = pileVersTableau(&depart->podiumRouge, r1);

    char* b2[MAX_ANIMAUX]; int hB2 = pileVersTableau(&arrivee->podiumBleu, b2);
    char* r2[MAX_ANIMAUX]; int hR2 = pileVersTableau(&arrivee->podiumRouge, r2);

    /* Calcul de la hauteur maximale pour l'affichage */
    int maxH = 0;
    if (hB1 > maxH) maxH = hB1;
    if (hR1 > maxH) maxH = hR1;
    if (hB2 > maxH) maxH = hB2;
    if (hR2 > maxH) maxH = hR2;

    int colW = 12; /* Largeur de colonne fixe pour l'alignement */

    for (int k = maxH - 1; k >= 0; k--) {
        /* Partie Gauche */

        /* Podium Bleu  */
        if (k < hB1) printf("%-*s", colW, b1[hB1 - 1 - k]);
        else         printf("%-*s", colW, "");

        /* Podium Rouge */
        if (k < hR1) printf("%-*s", colW, r1[hR1 - 1 - k]);
        else         printf("%-*s", colW, "");

        /* Espacement central */
        printf("          ");

        /* Partie Droite */

        /* Podium Bleu */
        if (k < hB2) printf("%-*s", colW, b2[hB2 - 1 - k]);
        else         printf("%-*s", colW, "");

        /* Podium Rouge */
        if (k < hR2) printf("%s", r2[hR2 - 1 - k]);

        printf("\n");
    }

    /* Affichage des socles et de la flèche centrale */
    printf("%-*s%-*s   ==>    %-*s%-*s\n", colW, "----", colW, "----", colW, "----", colW, "----");
    printf("%-*s%-*s          %-*s%-*s\n", colW, "BLEU", colW, "ROUGE", colW, "BLEU", colW, "ROUGE");
    printf("\n");
}