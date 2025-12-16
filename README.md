Crazy Circus
Description
Ce projet est une implémentation en C du jeu de société Crazy Circus.

Le but du jeu est de trouver une séquence de commandes pour déplacer des animaux d'une configuration initiale vers une configuration cible.
Auteurs
·	Projet réalisé dans le cadre du cours de programmation.
Prérequis
·	Un compilateur C (gcc recommandé, ou Visual Studio sous Windows).
Compilation
Linux / macOS
Ouvrez un terminal dans le dossier du projet et exécutez la commande suivante :
gcc -o crazy_circus main.c jeu.c pile.c liste.c animal.c

Windows (Visual Studio)
Ouvrez le fichier de solution Crazy_Circus_VEVO.sln avec Visual Studio et lancez la compilation.
Lancement du jeu
Le jeu s'exécute en ligne de commande. Vous devez fournir les noms des joueurs (au moins 2) en arguments.
Syntaxe :
./crazy_circus <NomJoueur1> <NomJoueur2> [NomJoueur3 ...]

Exemple :
./crazy_circus Alice Bob Charlie

Configuration
Le jeu nécessite un fichier de configuration nommé crazy.cfg dans le même répertoire que l'exécutable.
Format du fichier crazy.cfg
Le fichier doit contenir deux lignes :
1.	Liste des animaux (séparés par des espaces). Il faut au moins 3 animaux.
2.	Liste des ordres (séparés par des espaces). Les 5 ordres standards (KI, LO, SO, NI, MA) doivent être présents.
Exemple de contenu valide :
LION OURS ELEPHANT
KI LO SO NI MA

Règles du Jeu
1.	Le jeu affiche deux configurations :
1.	À gauche : La configuration actuelle.
2.	À droite : L'objectif à atteindre.
2.	Les joueurs doivent trouver une séquence de commandes pour transformer la configuration actuelle en l'objectif.
3.	Pour proposer une solution, un joueur doit taper son nom suivi de la séquence de commandes.
1.	Exemple : Alice KILOSO
4.	Si la séquence est correcte, le joueur gagne un point et un nouvel objectif est tiré.
5.	Si la séquence est incorrecte, le joueur ne peut plus jouer pour ce tour.
Commandes disponibles
·	KI : Déplace l'animal du sommet de la pile BLEUE vers le sommet de la pile ROUGE.
·	LO : Déplace l'animal du sommet de la pile ROUGE vers le sommet de la pile BLEUE.
·	SO : Échange les animaux aux sommets des deux piles.
·	NI : Place l'animal du bas de la pile BLEUE au sommet de la pile BLEUE.
·	MA : Place l'animal du bas de la pile ROUGE au sommet de la pile ROUGE.
Fin de partie
Le jeu continue jusqu'à ce que toutes les configurations possibles aient été jouées ou que les joueurs décident d'arrêter (Ctrl+D ou Ctrl+C).

Les scores finaux sont affichés à la fin.
