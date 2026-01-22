#pragma once

#include "liste.h" 

/**
 * @def MAX_ANIMAUX
 * @brief Nombre maximum d'animaux supportés par le programme.
 */
#define MAX_ANIMAUX 10

 /**
  * @def MAX_ORDRES
  * @brief Nombre maximum d'ordres configurables
  */
#define MAX_ORDRES 10 

  /**
   * @def TAILLE_NOM
   * @brief Taille max pour un nom d'animal
   */
#define TAILLE_NOM 50 

/**
 * @def DEF_FICHIER_CONFIG
 * @brief Nom par défaut du fichier de configuration à charger.
 */
#define DEF_FICHIER_CONFIG "crazy.cfg"

/**
 * @struct ConfigJeu
 * @brief Structure représentant la configuration complète du jeu
 */
typedef struct {
    char* nomsAnimaux[MAX_ANIMAUX]; /* Tableau de chaines pour les noms */
    int nbAnimaux;                  /* Nombre reel d'animaux lus */
    char* ordres[MAX_ORDRES];       /* Tableau de chaines pour les ordres (KI, LO...) */
    int nbOrdres;                   /* Nombre reel d'ordres lus */
} ConfigJeu;



/**
 * @brief Charge la configuration du jeu depuis un fichier et remplit la structure ConfigJeu
 * @param[out] config Pointeur vers la structure ConfigJeu
 * @param[in] nomFichier Chemin du fichier à lire
 * @return int  Renvoie 1 si le chargement est réussi et 0 en cas d'erreur
 */
int chargerConfiguration(ConfigJeu* config, const char* nomFichier);


/**
 * @brief Libère la mémoire allouée dynamiquement pour la configuration
 * @param[in,out] config Pointeur vers la structure ConfigJeu à nettoyer
 */
void libererConfiguration(ConfigJeu* config);


/**
 * @brief Affiche le contenu de la configuration chargée
 * @param[in] config Pointeur vers la structure ConfigJeu à afficher
 */
void afficherConfiguration(const ConfigJeu* config);


/** 
* @brief Vérifie la validité des règles du jeu chargées. Au moins 2 animaux et 3 ordres 
* @param[in] config Pointeur vers la structure ConfigJeu à vérifier
* @return int Renvoie 1 si la configuration est valide, 0 sinon
*/
int validerConfiguration(const ConfigJeu* config);