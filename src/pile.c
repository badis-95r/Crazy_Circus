

#define _CRT_SECURE_NO_WARNINGS
#include "pile.h"


 /**
  * @brief Initialise une pile vide (délègue l'initialisation à la fonction initListe)
  * @param[out] p Pointeur vers la pile à initialiser
  */
void initPile(Pile* p) {
    initListe(p);
}

/**
 * @brief Vérifie si la pile est vide
 * @param[in] p Pointeur vers la pile
 * @return int 1 si vide, 0 sinon
 */
int pileEstVide(const Pile* p) {
    return listeEstVide(p);
}

/**
 * @brief Empile un élément au sommet 
 * @param[in,out] p Pointeur vers la pile
 * @param[in] val L'élément à ajouter
 */
void empiler(Pile* p, Element val) {
    insererTete(p, val);
}

/**
 * @brief Dépile l'élément du sommet
 * @param[in,out] p Pointeur vers la pile
 * @return Element L'élément retiré
 */
Element depiler(Pile* p) {
    return supprimerTete(p);
}

/**
 * @brief Regarde l'élément au sommet sans le retirer 
 * @param[in] p Pointeur vers la pile
 * @return Element L'élément au sommet
 */
Element sommet(const Pile* p) {
    return teteListe(p);
}

/**
 * @brief Renvoie la hauteur actuelle de la pile
 * @param[in] p Pointeur vers la pile
 * @return int Le nombre d'éléments
 */
int taillePile(const Pile* p) {
    return p->taille;
}

/**
 * @brief Vide la pile et libère la mémoire (délègue le nettoyage à detruireListe)
 * @param[in,out] p Pointeur vers la pile à détruire
 */
void detruirePile(Pile* p) {
    detruireListe(p);
}