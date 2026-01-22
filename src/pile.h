#pragma once

#include "liste.h"




/**
* @typedef Pile
 * @brief Le typpe Pile vient un alias du type Liste
 */
typedef Liste Pile;

/**
 * @brief Initialise une pile vide
 * @param[out] p Pointeur vers la structure Pile à initialiser
 */
void initPile(Pile* p);

/**
 * @brief Vérifie si la pile est vide
 * @param[in] p Pointeur vers la pile à tester
 * @return int 1 si la pile ne contient aucun élément, 0 sinon
 */
int pileEstVide(const Pile* p);

/**
 * @brief Empile un élément en l'ajoutant au sommet de la pile
 * @param[in,out] p Pointeur vers la pile
 * @param[in] val La valeur (nom de l'animal) à ajouter au sommet
 */
void empiler(Pile* p, Element val);

/**
 * @brief Dépile un élément, retire l'élement situé au sommet, retire l'élément situé au sommet de la pile et le renvoie.
 * @param[in,out] p Pointeur vers la pile
 * @return Element L'élément qui était au sommet
 */
Element depiler(Pile* p);

/**
 * @brief Consulte le sommet de la pile 
 * @param[in] p Pointeur vers la pile
 * @return Element L'élément au sommet
 */
Element sommet(const Pile* p);

/**
 * @brief Renvoie la taille de la pile
 * @param[in] p Pointeur vers la pile
 * @return int Le nombre d'éléments
 */
int taillePile(const Pile* p);

/**
 * @brief Vide la pile et libère la mémoire.
 * @param[in,out] p Pointeur vers la pile à détruire.
 */
void detruirePile(Pile* p);