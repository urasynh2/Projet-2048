#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> Plateau;
typedef vector<vector<string>> PlateauString;
/** Des fonctions peuvent être ajoutés à ce fichier si besoin est (fonctions pour mettre à jour le score par exemple)
 * //

/** génère aléatoirement un 2 ou un 4 avec des probabilités respectives de 9/10 et 1/10
 *  @return 2 ou 4
 **/
int tireDeuxOuQuatre(); 

/** génère un Plateau de dimensions 4*4 ne contenant que des 0
 *  @return un Plateau vide 
 **/
Plateau plateauVide(); 

/** génère deux nombres sur des cases aléatoires d'un Plateau vide
 *  @return un Plateau en début de jeu 
 **/
Plateau plateauInitial();  

/** Dessine le plateau entrée
 * @param plat le Plateau
 * @return plat un string dessinant le plateau
 **/
string dessine(Plateau plat);

/**Affiche le plateau entrée
* @param plat
**/
void affichePlateau(Plateau plat);

/** déplace les tuiles d'un Plateau vers la droite et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers la droite
 **/
Plateau deplacementDroite(Plateau plat);

/** déplace les tuiles d'un Plateau vers le bas et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers le bas
 **/
Plateau deplacementBas(Plateau plat);

/** déplace les tuiles d'un Plateau vers le haut et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers le haut
 **/
Plateau deplacementHaut(Plateau plat);

/** déplace les tuiles d'un Plateau vers la gauche et les combine si possible
 *  @param plateau le Plateau
 *  @return le Plateau une fois déplacé vers la gauche
 **/
Plateau deplacementGauche(Plateau plat);

/** déplace les tuiles d'un Plateau dans la direction donnée et génère une nouvelle tuile si le déplacement est valide
 *  @param plateau le Plateau
 *  @param direction la direction
 *  @return le Plateau déplacé dans la direction
 **/
Plateau deplacement(Plateau plat, int direction);

/** permet de savoir si une partie est terminée
 *  @param plateau un Plateau
 *  @return true si le plateau est vide, false sinon
 **/
bool estTermine(Plateau plateau); 

/** permet de savoir si une partie est gagnée
 * @param plateau un Plateau
 * @return true si le plateau contient un 2048, false sinon
 **/
bool estGagnant(Plateau plateau);  

/** permet de savoir si une partie est perdue
 * @param plateau un Plateau
 * @return true s'il n'y a auncun mouvement possible, false sinon
 **/
bool game_over(Plateau plateau); 

/** permet de transformer un tableau d'entiers en un tableau de string
* @param plat, un Plateau d'entiers
* @return plats, un Plateau de chaines de caractères
**/
PlateauString int_to_string(Plateau plat); //INUTILE

/** permet de savoir qu'elle est le nombre de chiffres maximum dans le plateau
* @param plat, un Plateau
* @return lmax, le maximum de chiffres contenu dans une tuile
**/
int lengthmax(Plateau plat); //INUTILE

