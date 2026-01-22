

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liste.h"


 /**
  * @brief Initialise une liste à l'état vide 
  * @param[out] l Pointeur vers la liste à initialiser
  */
void initListe(Liste* l) {
    l->tete = NULL;
    l->taille = 0;
}

/**
 * @brief Vérifie si la liste ne contient aucun élément
 * @param[in] l Pointeur vers la liste à tester.
 * @return int 1 si la liste est vide, 0 sinon
 */
int listeEstVide(const Liste* l) {
    return (l->tete == NULL);
}

/**
 * @brief Ajoute un élément au début de la liste
 * @param[in,out] l Pointeur vers la liste
 * @param[in] val La valeur à stocker
 */
void insererTete(Liste* l, Element val) {
    Cellule* nouv = (Cellule*)malloc(sizeof(Cellule));

    if (nouv == NULL) {
        fprintf(stderr, "Erreur fatale : Echec d'allocation memoire dans insererTete\n");
        exit(EXIT_FAILURE);
    }

    nouv->valeur = val;       
    nouv->suivant = l->tete;  
    l->tete = nouv;         
    l->taille++;
}

/**
 * @brief Supprime l'élément en tête de liste 
 * @param[in,out] l Pointeur vers la liste
 * @return Element La valeur qui était stockée en tête ou NULL si liste vide
 */
Element supprimerTete(Liste* l) {
    if (listeEstVide(l)) {
        return NULL;
    }

    Cellule* aSupprimer = l->tete;   
    Element valeur = aSupprimer->valeur; 

    l->tete = aSupprimer->suivant;   
    free(aSupprimer);                
    l->taille--;

    return valeur;
}

/**
 * @brief Renvoie l'élément en tête sans le supprimer 
 * @param[in] l Pointeur vers la liste
 * @return Element La valeur située en tête ou NULL si vide
 */
Element teteListe(const Liste* l) {
    if (listeEstVide(l)) {
        return NULL;
    }
    return l->tete->valeur;
}

/**
 * @brief Vide toute la liste et libère la mémoire des cellules
 * @param[in,out] l Pointeur vers la liste à détruire
 */
void detruireListe(Liste* l) {
    while (!listeEstVide(l)) {
        supprimerTete(l);
    }
}