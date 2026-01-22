#pragma once

#include "pile.h"
#include "animal.h"


/**
 * @struct EtatJeu 
 * @brief Représente l'état du jeu à un instant T. Il contient les deux piles d'animaux représentants les podiums
 */
typedef struct {
    Pile podiumBleu;
    Pile podiumRouge;
} EtatJeu;


/**
 * @struct Deck
 * @brief Structure qui stock toutes les positions possibles (Les cartes objectifs)
 */
typedef struct {
    EtatJeu* positions; /* Tableau dynamique de toutes les positions possibles */
    int nbPositions;    /* Nombre total de positions stockées */
    int* estUtilisee;   /* Tableau de booléens pour savoir si une carte a déjà été tirée */
} Deck;



/**
 * @brief Initialise un état de jeu avec des piles vides
 * @param[out] e Pointeur vers la structure EtatJeu à initialiser
 */
void initEtat(EtatJeu* e);


/**
 * @brief Libère la mémoire d'un état de jeu
 * @param[in,out] e Pointeur vers la structure EtatJeu à nettoyer
 */
void libererEtat(EtatJeu* e);



/**
 * @brief Effectue une copie d'un état vers un autre
 * @param[in] src Pointeur vers la structure EtatJeu source
 * @param[out] dest Pointeur vers la structure EtatJeu de destination
 */
void copierEtat(const EtatJeu* src, EtatJeu* dest);



/**
 * @brief Compare deux états de jeu
 * @param[in] e1 Pointeur vers la strcuture EtatJeu du premier état
 * @param[in] e2 Pointeur vers la strcuture EtatJeu du deuxième état
 * @return 
 */
int estMemeEtat(const EtatJeu* e1, const EtatJeu* e2);


/**
 * @brief Execute l'ordre KI. L'animal au sommet du podium bleu saute vers le sommet du podium rouge
 * @param[in,out] e Pointeur vers l'état du jeu à modifier
 * @return int 1 si le mouvement a été effectué, 0 si c'est impossible
 */
int commandeKI(EtatJeu* e);

/**
 * @brief Execute l'ordre LO. L'animal au sommet du podium rouge saute vers le sommet du podium bleu
 * @param[in,out] e Pointeur vers l'état du jeu à modifier
 * @return int 1 si le mouvement a été effectué, 0 si c'est impossible
 */
int commandeLO(EtatJeu* e);

/**
 * @brief Execute l'ordre SO. Les deux animaux aux sommets des deux podiums échangent leurs places
 * @param[in,out] e Pointeur vers l'état du jeu à modifier
 * @return int 1 si le mouvement a été effectué, 0 si c'est impossible
 */
int commandeSO(EtatJeu* e);

/**
 * @brief Execute l'ordre NI. L'animal tout en bas du podium bleu passe tout en haut de ce même podium
 * @param[in,out] e Pointeur vers l'état du jeu à modifier
 * @return int 1 si le mouvement a été effectué, 0 si c'est impossible
 */
int commandeNI(EtatJeu* e);

/**
 * @brief Execute l'ordre NMA. L'animal tout en bas du podium rouge passe tout en haut de ce même podium
 * @param[in,out] e Pointeur vers l'état du jeu à modifier
 * @return int 1 si le mouvement a été effectué, 0 si c'est impossible
 */
int commandeMA(EtatJeu* e);


/**
 * @brief Execute une séquence de commande donnée sous forme de chaines. Elle appelle les fonctions des commandes tour à tour
 * @param[in,out] e Pointeur vers l'état du jeu qui sera modifié en place
 * @param[in] seq Chaîne de caractères représentant la séquence d'ordres
 * @return int 1 si toute la séquence ets valide, 0 si un ordre est inconnu ou impossible
 */
int executerSequence(EtatJeu* e, const char* seq);



/**
 * @brief Génère l'ensemble des positions possibles du jeu
 * @param[in] config Configuration contenant les animaux disponibles
 * @param[out] deck Pointeur vers le deck à remplir
 */
void genererToutesPositions(const ConfigJeu* config, Deck* deck);

/* Tire une nouvelle position cible al�atoire qui n'a pas encore �t� jou�e */
/* Retourne un pointeur vers l'�tat cible, ou NULL si plus de cartes */

/**
 * @brief Tire une nouvelle carte objectif au hasard parmis celles non utilisés. La carte sera marqué comme tiré arpès
 * @param[in,out] deck Le paquet dans lequel piocher
 * @return EtatJeu* Pointeur vers l'état cible tiré ou NULL si il y a plus de cartes
 */
EtatJeu* tirerNouvelleCarte(Deck* deck);

/**
 * @brief Affiche le duel entre la position actuel et l'objectif
 * @param[in] depart Etat actuel du jeu (Les podiums à gauche)
 * @param[in] arrivee Etat objectif à atteindre (Les podiums à droite)
 */
void afficherDuel(const EtatJeu* depart, const EtatJeu* arrivee);

/** 
* @brief Affiche la liste des ordres possibles au début du jeu
* @param[in] config La configuration qui contient les noms des ordres
*/
void afficherOrdresPossibles(const ConfigJeu* config);