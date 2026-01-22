#pragma once

/**
 * @typedef Element
 * @brief Type des données dans la liste
 */
typedef char* Element;

/**
* @struct Cellule
 * @brief Structure représentant un maillon de la liste
 */
typedef struct Cellule {
    Element valeur;          /* La donnee stockee (le nom de l'animal) */
    struct Cellule* suivant; /* Pointeur vers le maillon suivant */
} Cellule;

/**
* @struct Liste
 * @brief Structure representant la liste en elle-meme
 */
typedef struct {
    Cellule* tete; /* Pointeur vers le sommet de la liste */
    int taille;    /* Nombre d'elements dans la liste */
} Liste;



/**
 * @brief Initialise une liste vide en mettant la taille à 0 et la tete à NULL
 * @param[out] l Pointeur vers la structure Liste à initialiser
 */
void initListe(Liste* l);


/**
 * @brief Vérifie si la liste est vide
 * @param[in] l Constante du pointeur vers la liste
 * @return int 1 si la liste ne contient aucun élément, sinon 0
 */
int listeEstVide(const Liste* l);

/**
 * @brief Insère un nouvel élement en tête de liste
 * @param[in,out] l Pointeur vers la liste
 * @param[in] val La valeur (une chaine de caractères) à ajouter
 */
void insererTete(Liste* l, Element val);

/**
 * @brief Supprime l'élément en tete de liste et le renvoie
 * @param[in,out] l Pointeur vers la liste
 * @return Element La valeur qui était en tête (le nom de l'animal)
 */
Element supprimerTete(Liste* l);

/**
 * @brief Consulte l'élement de tete sans le supprimer
 * @param[in] l Constante du pointeur vers la liste
 * @return Element La valeur située en tête
 */
Element teteListe(const Liste* l);

/**
* @brief Vide la liste pour libérer la mémoire
* @param[in,out] l Pointeur vers la liste à détruire
*/
void detruireListe(Liste* l);