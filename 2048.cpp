#include <iostream>
#include <vector>
#include <ncurses.h>
#include <string>


using namespace std;

typedef vector<vector<int>> Plateau;
typedef vector<vector<string>> PlateauString;

int score=0;               //Initialise une variable globale score
int n=0;                   //Initialise une variable globale qui donne le nombre de points a ajouter a chaque tour

int tireDeuxOuQuatre(){
    if ( rand() % 10!=9){  //donne un random entre 0 et 9, si il n'est pas égale à 9
        return 2;         //renvoyer 2 (donc 9 chance sur 10)
    } else {              //sinon
        return 4;         //renvoyer 4 (donc 1 chance sur 10)
    }
}

Plateau plateauVide(){
    Plateau plat = Plateau(4);               //Initialisation et Allocation du Plateau
    for(int i=0; i<plat.size(); i++){
        plat[i]= vector<int>(4) ;            //Allocation de chaque ligne du Plateau
    }
    for(int j=0; j< plat.size(); j++){
        for(int y=0; y<plat[j].size(); y++){
            plat[j][y]=0;                    //Déclaration de chaque tuile du plateau
        }
    }
    return plat;
}


Plateau plateauInitial(){
    Plateau plat=plateauVide();
    int a= rand()%4;                              //Initialisation d'une première abscisse
    int b= rand()%4;                              //Initialisation d'un premier ordonnée
    int c= rand()%4;                              //Initialisation d'une deuxième abscisse
    int d= rand()%4;                              //Initialisation d'un deuxième ordonnée
    while(a==c and b==d){                         //Tant que les coordonnées sont les memes
        a = rand()%4;                             //Changer leur valeur
        b = rand()%4;
    } 
    plat[a][b]= tireDeuxOuQuatre(); //Mettre dans la tuile de coordonnées (a,b) un 2 ou un 4
    plat[c][d]= tireDeuxOuQuatre(); //Mettre dans la tuile de coordonnées (c,d) un 2 ou un 4
    return plat;
}

string dessine(Plateau plat){
    /**initscr();
    init_pair(1, COLOR_RED,COLOR_BLACK);
    init_pair(2, COLOR_BLUE,COLOR_BLACK);
    init_pair(3, COLOR_GREEN,COLOR_BLACK);      tentatives de mettre des couleurs
    init_pair(4, COLOR_YELLOW,COLOR_BLACK);     differentes pour chaques tuiles
    init_pair(5, COLOR_CYAN,COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA,COLOR_BLACK);
    init_pair(7, COLOR_RED,COLOR_WHITE);
    init_pair(8, COLOR_WHITE,COLOR_BLUE);
    init_pair(9, COLOR_RED,COLOR_WHITE);
    init_pair(10, COLOR_MAGENTA,COLOR_RED);
    init_pair(11, COLOR_WHITE,COLOR_YELLOW);
    init_pair(12, COLOR_WHITE,COLOR_BLACK);
    **/
	string p;
    //p+= "\033[1J\033[7;1H";                  autre manière de rafraichir
    p+= "Score: " + to_string(score)+ "\n";
    for(int i=0 ; i< plat.size() ; i++){
        //attron(COLOR_PAIR(1));
		p+="-------------------------\n";
		//attroff(COLOR_PAIR(1));
        for(int j=0; j< plat[i].size() ; j++){
            //attron(COLOR_PAIR(1));
			p+= "|";
			//attroff(COLOR_PAIR(1));
            if(plat[i][j]!=0){                                    //Si la tuile n'est pas vide
                if(to_string(plat[i][j]).length()%2!=0){          //Si la longueur du nombre dans la tuile est paire
                    int a= to_string(plat[i][j]).length(); 
                    for(int k=1; k<= (5-a)/2; k++){
                        p+= " ";
                    }
                    p+= to_string(plat[i][j]);                    //Alors centrer la valeur et mettre des espaces autour
                    for(int k=1; k<= (5-a)/2; k++){
                        p+= " ";
                    }
                }else{                                            //Sinon
                    int a=to_string(plat[i][j]).length();
                    for(int k=1; k <= (5-a)/2; k++){
                        p+= " ";
                    }
                    p+= to_string(plat[i][j]);                    //La valeur sera vers la gauche
                    for(int k=1; k<= (5-a)/2+1; k++){
                        p+= " ";
                    }
                }
            } else {                                             //Si la tuile est vide
                p+= "     ";                                     //Mettre des espaces
            }
        }
    p+= "|\n";
    }
    p+="-------------------------\n";
    return p;
}


void affichePlateau(Plateau plat){
    cout<< dessine(plat) <<endl;                                   //Afficher le tableau 
}


Plateau deplacementDroite(Plateau plat){
	n=0;                                                      //Ramene le nombre de point qu'il faut ajouter au score a 0
    for (int i = 0; i < plat.size(); i++){                    //Parcours les lignes
        for(int o=0; o<plat[i].size(); o++){                   //Sers à decaler toutes les tuiles non vides le plus à droite possible
            for (int j = 2; j>=0; j--){                      //Parcours les tuiles de la ligne i, on commence a j=2 car on ne peut pas deplacer un element qui est deja tout a droite (j=3) et car 3+1=4 or il n'existe pas de j=4
                if(plat[i][j] > 0 and plat[i][j+1]==0){       //Si la tuile actuelle (plat[i][j]) n'est pas vide et la tuile directement a droite est vide
                    plat[i][j+1]=plat[i][j];                   //Alors deplace la tuile à droite
                    plat[i][j]=0;
                }
            }
        }
        for (int j = 3; j>0; j--){   //Parcours les tuiles de la ligne i, on s'arrete à j>0  car 0-1=-1, or il n'y a pas de tuile j=-1
            if (plat[i][j]==plat[i][j-1] and plat[i][j]!=0){  //Si la tuile actuelle est identique à la tuile a gauche et qu'elles sont toutes les 2 non vides
                n+=plat[i][j]*2;                              //Faire augmenter le nb de points ajoutés au score de la valeur obtenue
				plat[i][j]=plat[i][j]*2;                          //Fusionner les 2 tuiles et mettre la nouvelle tuile à droite
                plat[i][j-1]=0;
            }
        }
        for (int j = 2; j>=0; j--){                               //Sers à redecaler les tuiles à droite pour eviter les espaces vides dus à la fusion
            if(plat[i][j] > 0 and plat[i][j+1]==0){ 
                plat[i][j+1]=plat[i][j];                          //Decale la tuile à droite s'il y a une tuile vide à coté
                plat[i][j]=0;
            }
        }
    }
    return plat;
}

Plateau deplacementBas(Plateau plat){  
	n=0;                                                           //Ramene le nombre de point qu'il faut ajouter au score a 0
    for (int j = 0; j < plat.size(); j++){                       //Parcours les colonnes
        for(int o=0; o<plat.size(); o++){                              //Sers à decaler toutes les tuiles non vides le plus bas possible
            for (int i = 2; i>=0; i--){                          //Parcours les tuiles de la colonne j, on commence a i=2 car on ne peut pas deplacer un element qui est deja tout en bas (i=3) et car 3+1=4 or il n'existe pas de i=4
                if(plat[i][j] > 0 and plat[i+1][j]==0){          //Si la tuile actuelle (plat[i][j]) n'est pas vide et la tuile directement en bas est vide
                    plat[i+1][j]=plat[i][j];                     //Alors deplace la tuile en bas
                    plat[i][j]=0; 
                }
            }
        }
        for (int i = 3; i>0; i--){                               //Parcours les tuiles de la colonne j, on s'arrete à i>0  car 0-1=-1, or il n'y a pas de tuile i=-1
            if (plat[i][j]==plat[i-1][j] and plat[i][j]!=0 ){    //Si la tuile actuelle est identique à la tuile en haut et qu'elles sont toutes les 2 non vides
                n+=plat[i][j]*2;                             //Faire augmenter le nb de points ajoutés au score de la valeur obtenue
				plat[i][j]=plat[i][j]*2;                         //Fusionner les 2 tuiles et mettre la nouvelle tuile en bas
                plat[i-1][j]=0;
            }
        }
        for (int i = 2; i>=0; i--){                              //Sers à redecaler les tuiles en bas pour eviter les espaces vides dus à la fusion
            if(plat[i][j] > 0 and plat[i+1][j]==0){ 
                plat[i+1][j]=plat[i][j];                         //Decale la tuile en bas s'il y a une tuile vide à coté
                plat[i][j]=0;
            }
        }
    }
    return plat;
}

Plateau deplacementHaut(Plateau plat){
	n=0;                                                          //Ramene le nombre de point qu'il faut ajouter au score a 0
    for (int j = 0; j < plat.size(); j++){                      //Parcours les colonnes
        for(int o=0; o<2; o++){                                 //Sers à decaler toutes les tuiles non vides le plus haut possible
            for (int i = 1; i<4; i++){                          //Parcours les tuiles de la colonne j, on commence a i=1 car on ne peut pas deplacer un element qui est deja tout en haut (i=0) et car 0-1=-1 or il n'existe pas de i=-1
                if(plat[i][j] > 0 and plat[i-1][j]==0){         //Si la tuile actuelle (plat[i][j]) n'est pas vide et la tuile directement en haut est vide
                    plat[i-1][j]=plat[i][j];                    //Alors deplace la tuile en haut
                    plat[i][j]=0; 
                }
            }
        }
        for (int i = 0; i<plat.size()-1; i++){                  //Parcours les tuiles de la colonne j, on s'arrete à i<plat.size()-1 car 3+1=4, or il n'y a pas de tuile i=4
            if (plat[i][j]==plat[i+1][j] and plat[i][j]!=0 ){   //Si la tuile actuelle est identique à la tuile en bas et qu'elles sont toutes les 2 non vides
                n+=plat[i][j]*2;                            //Faire augmenter le nb de points ajoutés au score de la valeur obtenue
				plat[i][j]=plat[i][j]*2;                        //Fusionner les 2 tuiles et mettre la nouvelle tuile en haut
                plat[i+1][j]=0;
            }
        }
        for (int i = 1; i<4; i++){                              //Sers à redecaler les tuiles en haut pour eviter les espaces vides dus à la fusion
            if(plat[i][j] > 0 and plat[i-1][j]==0){ 
                plat[i-1][j]=plat[i][j];                        //Decale la tuile en haut s'il y a une tuile vide à coté
                plat[i][j]=0; 
            }
        }
    }
    //dessine(plat);
    return plat;
}

Plateau deplacementGauche(Plateau plat){ 
	n=0;                                                            //Ramene le nombre de point qu'il faut ajouter au score a 0
    for (int i = 0; i < plat.size(); i++){                         //Parcours les lignes
        for (int o=0; o<plat[i].size(); o++){                        //Sers à decaler toutes les tuiles non vides le plus à gauche possible
            for (int j = 1; j<plat[i].size(); j++){                //Parcours les tuiles de la ligne i, on commence a j=1 car on ne peut pas deplacer un element qui est deja tout a gauche (j=0) et car 0-1=-1 or il n'existe pas de j=-1
                if(plat[i][j] > 0 and plat[i][j-1]==0){            //Si la tuile actuelle (palt[i][j]) n'est pas vide et la tuile directement a gauche est vide
                    plat[i][j-1]=plat[i][j];                       //Alors deplace la tuile à gauche
                    plat[i][j]=0;                                 
                }
            }
        }
        for (int j = 0; j<plat[i].size()-1; j++){                  //Parcours les tuiles de la ligne j, on s'arrete à j<plat[i].size()-1 car 3+1=4, or il n'y a pas de tuile j=4
            if (plat[i][j]==plat[i][j+1] and plat[i][j]!=0){       //Si la tuile actuelle est identique à la tuile a droite et qu'elles sont toutes les 2 non vides
                n+=plat[i][j]*2;                                 //Faire augmenter le nb de points ajoutés au score de la valeur obtenue
				plat[i][j]=plat[i][j]*2;                           //Fusionner les 2 tuiles et mettre la nouvelle tuile à gauche
                plat[i][j+1]=0;
            }
        }
        for (int j = 1; j<plat[i].size(); j++){                    //Sers à redecaler les tuiles à gauche pour eviter les espaces vides dus à la fusion
            if(plat[i][j] > 0 and plat[i][j-1]==0){                
                plat[i][j-1]=plat[i][j];                           //Decale la tuile à gauche s'il y a une tuile vide à coté
                plat[i][j]=0;
            }
        }
    }
    return plat;
}

Plateau deplacement(Plateau plat, int direction){
    Plateau Copieplat= plat;                                       //Fais une copie du plateau avant d'appliquer le deplacement pour comparer plus tard
    if (direction==1){                                             //Si 1 est entré
        plat= deplacementGauche(plat);                             //Deplacer vers la gauche
    } else if (direction==3){                                      //Si 3 est entré
        plat= deplacementDroite(plat);                             //Deplacer vers la droite
    } else if (direction==2){                                      //Si 2 est entré
        plat= deplacementBas(plat);                                //Deplacer vers le bas
    } else if (direction==5){                                      //Si 5 est entré
        plat= deplacementHaut(plat);                               //Deplacer vers le haut
    }
    if (Copieplat!= plat){                                         //Si le plateau a été modifié
        int a= rand()%4;                                           //Alors initialiser 2 entiers qui correspondent aux "coordonnées" aléatoires de la tuile qui apparait
        int b= rand()%4;
        while (plat[a][b]>0){                                      //Verifie que la tuile de "coordonnées a b" et vide
            a= rand()%4;                                           //Si elle n'est pas vide alors donne des nouvelles coordonnées 
            b= rand()%4;
        }
        plat[a][b]=tireDeuxOuQuatre();                              //Si elle est bien vide, mettre un 2 ou un 4
    }
    return plat;
}

bool estTermine(Plateau plateau){
    return plateau==plateauVide();                 //Si le plateau est vide alors la partie est terminé
}


bool estGagnant(Plateau plateau){
    for(int i=0 ; i<plateau.size() ; i++){
        for(int j=0; j<plateau[i].size() ; j++){
            if (plateau[i][j]==2048){              //Si une des tuiles du plateau contient 2048
                return true;                       //Alors c'est gagné
            }
        }
    }
    return false;                                  //Sinon, bah c'est pas gagné du coup
}

bool game_over(Plateau plat){
    if (deplacementHaut(plat)==plat and deplacementBas(plat)==plat and deplacementGauche(plat)==plat and deplacementDroite(plat)==plat){ //Si on ne peut plus changer le plateau (S'il reste le meme peu importe la direction qu'on utilise)
        return true;                                                                                                                     //Alors c'est perdu
    }else{
        return false;                                                                                                                      //Sinon ce n'est pas perdu
    }
}

int main(){
    initscr();
	keypad(stdscr, true);
    Plateau plat= plateauInitial();
	start_color();
	init_pair(1, COLOR_GREEN,COLOR_BLACK);
    while (not estGagnant(plat) and not game_over(plat) and not estTermine(plat)){
        attron(COLOR_PAIR(1));
		printw(dessine(plat).c_str());
		attroff(COLOR_PAIR(1));
		printw("Utilisez les flèches directionnelles pour fusionner les tuiles et tenter d'obtenir 2048");
        int move;
		move= getch();
        int direct;
        if (move==KEY_UP){
            direct =5;
        } else if(move==KEY_DOWN){
            direct=2;
        } else if(move==KEY_LEFT){
            direct=1;
        } else if(move==KEY_RIGHT){
            direct=3;
        } else {
            direct=4;
        }
        plat = deplacement(plat,direct);
		score+=n;
		clear();
    }
	endwin();
    if (estGagnant(plat)){
        cout<<"Félicitations, tu as gagné le premier prix, voici un chèque de 20 000euros."<<endl;
    }else if (game_over(plat)){
        cout<<"Game Over, va jouer au pendu tu sera peut etre plus à l'aise avec des mots qu'avec des nombres (s/o Kim Nguyen)"<<endl;
    }
	getch();
    return 0;
}

/**    INUTILE
PlateauString int_to_string(Plateau plat){
    PlateauString plats = PlateauString(4);
    for(int i=0; i<plats.size(); i++){
        plats[i]= vector<string>(4) ;
    }
    for(int j=0; j< plats.size(); j++){
        for(int y=0; y<plats[j].size(); y++){
            plats[j][y] =to_string(plat[j][y]);
        }
    }
    return plats;
}
**/

/**   INUTILE
int lengthmax(Plateau plat){
    int lmax=0;
    for(int i=0 ; i<plat.size() ; i++){
        for(int j=0; j<plat[i].size() ; j++){
            if(to_string(plat[i][j]).length()>lmax){
                lmax= to_string(plat[i][j]).length();
            }
        }
    }
    return lmax;
}
**/
