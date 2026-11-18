#include <iostream>
#include <cstdlib>
#include <string>

#include "infoPlayer.h"
#include "tic_tac_toe_stack.h"

/****   créé par Emma    ****/

/*--- Struct de jeux ---*/
//information sur les pion
struct pion{
    char couleur;
    int niv;
    int equipe;
};
//information sur les joueur
struct player{
    int equipe;
    std::string nom;
    int np[3]; int win = 0;
    std::string couleur;
    
};

/*--- Initialisation du jeux ---*/
//initier la grille
void initGrille(int size, pion *tab[]){
    for(int i=0; i<size; i++){
        tab[i]= new pion[size];
        for(int j=0; j<size; j++){
            tab[i][j].couleur = ' ';
            tab[i][j].niv = -1;
            tab[i][j].equipe = 2;
        }
    }
    
}
//donner les pions au joueur
void initPlayer(int Psize, player &p1, player &p2){
    int npion[3];

    //repartir les pions equitablement.
    for(int i=0; i<3; i++){
        npion[i]=((Psize*(Psize+1))/2)/3;
    }
    //rajouer le piont en trop dans le plus faible.
    if((((Psize*(Psize+1))/2)%3) != 0 ){
        npion[0]+=1; 
    }
    // donner les pion au joueur.
    for(int i=0; i<3; i++){
        p1.np[i]=npion[i];
        p2.np[i]=npion[i];
    }
}


/*--- recuperation des information du jeux ---*/
//demande à l'utilisateur la taille de la grille.
void setTailleGrille(int &valeur){
    std::cout<<"taille de la grille : ";
    std::cin>>valeur;
    std::system("cls");
    if (valeur < 2){
        std::cout<<"taille trop petite: ";
        valeur = 2;
    }
    std::cout<<"taille mis a "<<valeur<<std::endl;
    
}
//modifier le nombre de pièece aligner pour gagnierr
void setAlign(int &align, int Psize){
    std::cout<<"combien de piont faut-il alignier : ";
    std::cin>>align;
    std::system("cls");
    if (align < 2){
        std::cout<<"l'alignement trop petite: ";
        align = 2;
    }else if(align > Psize){
        std::cout<<"alignement est plus grande que le plateaux\n";
        setAlign(align, Psize);
    }
    std::cout<<"l'alignement mis a "<<align<<std::endl;
}

/*--- recuperation des information des joueurs ---*/
//recupe donnée des joueur;
void setDataplayer(player & p, Player imp){
    p.nom=imp.pseudo;
    p.couleur=imp.color;
}


/*--- Affichage du jeux ---*/
//afficher la grilles
void afficheGrille(pion *tab[], int size, std::string color[]){
    
    std::cout<<"  ";
    for(int o=0; o<size; o++){
        if(o < 10){
            std::cout<<"   "<<o;
        }else{
            std::cout<<"  "<<o;
        }
    }std::cout<<std::endl;
    for(int i=0; i<size; i++){
        if(i > 9){
            std::cout<<i;
        }else{
            std::cout<<i<<" ";
        }
        for(int j=0; j<size; j++){
            std::cout<<" | "<<color[tab[i][j].equipe]<<tab[i][j].couleur<<"\033[0m";
        }
        std::cout<<" | "<<std::endl;
    }
}
//afficher l'information de chaque joueur
void affichage(pion *tab[], int size, int equipe, int align, player p1, player p2){
    std::string color[3]={p1.couleur, p2.couleur, "\033[0m"};
    std::cout<<"aligniez "<<align<<" pions pour gagner"<<std::endl;
    if(equipe == 1){
        std::cout<<"tour de "<<p2.couleur<<p2.nom<<"\033[0m :"<<std::endl;
        std::cout<<"nombre de pion : o "<<p2.np[0]<<" / 0 "<<p2.np[1]<<" / O "<<p2.np[2]<<std::endl;
    }else{
        std::cout<<"tour de "<<p1.couleur<<p1.nom<<"\033[0m :"<<std::endl;
        std::cout<<"nombre de pion : x "<<p1.np[0]<<" / % "<<p1.np[1]<<" / X "<<p1.np[2]<<std::endl;

    }
    afficheGrille(tab, size, color);
    
}

/*--- Gerer l'action de jeux ---*/
//changer le tour du joueur
bool BackTour(int equipe){
    if (equipe == 1){
        return 0;
    }else{
        return 1;
    }
}
//saisit du joueur
void PlayAction(int & x, int & y, int & niv){
    std::cin.ignore();
    std::cout<<"position x : ";
    std::cin>>x;
    std::cout<<"position y : ";
    std::cin>>y;
    std::cout<<"niveaux du pion : ";
    std::cin>>niv;
    std::system("cls");
}
//vérifier si le joueur à encore le pion qui veux poser
bool restpiece(player p1, player p2, int nivpion, int equipe){
    if(equipe == 1){
        return p2.np[nivpion] <= 0;
    }else{
        return p1.np[nivpion] <= 0;
    }
    
}
//placer une pièce sur le plateau
void placerPiece(pion *tab[], int size, int & equipe, player &p1, player &p2){
    char colo[6] = {'x','%','X','o','0','O'};
    int x, y, nivpion;
    PlayAction(x, y, nivpion);
    nivpion -= 1;
    if(x >= size || y > size || nivpion > 2 || restpiece(p1, p2, nivpion, equipe)){
        std::cout<<"le pion ne peux pas etre pose\n";
    }else{
        if((tab[y][x].niv < nivpion)){
            tab[y][x].niv=nivpion;
            if(equipe == 1){
                tab[y][x].couleur=colo[nivpion+ 3];
                tab[y][x].equipe=1;
                p2.np[nivpion]--;
                equipe = 0;
            }else{
                tab[y][x].couleur=colo[nivpion];
                tab[y][x].equipe=0;
                p1.np[nivpion]--;
                equipe = 1;
            }
        }   
    }
}

 /*-- Detection de victoire---*/
//detecter si la partie est est en Match Null
bool matchNull(player p1, player p2){
    bool null=false;
    for(int i=0; i<3; i++){
        if (p1.np[i] == 0 && p2.np[i] == 0){
            null=true;
        }else{
            null=false;
        }
    }
    return null;
}
//detecter si un des deux joueurs on alignier asser de point
bool victoire(int psize, pion *tab[], int aligne, bool &equipeWin, int equipe){
    int nPAlign=0;
    
    for(int y=0; y< psize; y++){
        for(int x=0; x< psize; x++){
            //horizontal
            for(int horiz=0; horiz < aligne; horiz++){
                if((((x+horiz) < psize))&& (tab[y][x+horiz].equipe == equipe)){
                    nPAlign ++;
                    if(nPAlign == aligne ){
                     equipeWin = equipe;
                        return true;
                    }
                }else{
                    nPAlign = 0;
                }
            }nPAlign = 0;
            //vertical
            for(int verti=0; verti < aligne; verti++){
                if((((y+verti) < psize)) && tab[y+verti][x].equipe == equipe){
                    nPAlign ++;
                    if(nPAlign == aligne ){
                     equipeWin = equipe;
                        return true;
                    }
                }else{
                    nPAlign = 0;
                }
            }nPAlign = 0;
            //Diagonal left
            for(int Diagl=0; Diagl < aligne; Diagl++){
                if((((x+Diagl) < psize) && ((y+Diagl) < psize)) && tab[y+Diagl][x+Diagl].equipe == equipe){
                    nPAlign ++;
                    if(nPAlign == aligne ){
                     equipeWin = equipe;
                        return true;
                    }
                }else{
                    nPAlign = 0;
                }
            }nPAlign = 0;
            //Diagonal Right
            for(int Diagl=0; Diagl < aligne; Diagl++){
                if(((((psize-1)-(x+Diagl)) > 0) && ((y+Diagl) < psize)) && (tab[y+Diagl][(psize-1)-(x+Diagl)].equipe == equipe)){
                    nPAlign ++;
                    if(nPAlign == aligne ){
                     equipeWin = equipe;
                        return true;
                    }
                }else{
                    nPAlign = 0;
                }
            }nPAlign = 0;
        }
    }
    return false;
}

//verifie si une des deux condition de fin de partie est vrais
bool fin2Parti(player p1, player p2, int psize, pion *tab[], int aligne, bool &equipeWin, int equipe){
    bool fin = false;
    if(victoire(psize, tab, aligne, equipeWin, equipe)){
        fin = true;
        if(equipeWin){
            std::cout<<p2.couleur<<p2.nom<<"\033[0m a gagner"<<std::endl;
        }else{
            std::cout<<p1.couleur<<p1.nom<<"\033[0m a gagner"<<std::endl;
        }
    }else if(matchNull(p1, p2)){
        fin = true;
        std::cout<<"Match Null\n";
    }else{
        fin = false;
    }

    return fin;
}
void giveWin(Player & imp1, Player & imp2, bool equipeWin){
    if(equipeWin){
        imp2.win+=1;
    }else{
        imp1.win+=1;
    }
}
int end(Player & imp1, Player & imp2, bool equipeWin, pion *tab[], int size){
    std::string color[3]={imp1.color, imp2.color, "\033[0m"};
    int retour;

    giveWin(imp1, imp2, equipeWin);
    afficheGrille(tab, size, color);
    
    std::cin.ignore();
    std::cout<<"Rejouer ?\n1- oui\n0- non \n";
    std::cin>>retour;
    
    if(retour != 1){
        retour = 0;
    }
    std::system("cls");
    return retour;
}

void ClearTab(pion *tab[], int psize){
    for(int i=psize-1; i>=0; i-- ){
        for(int j=psize-1; j>=0; j-- ){
            delete &tab[i][j];
        }
        delete[] tab[i];
    }
}
void ticTacToeStack(Player & imp1, Player & imp2){
    
    player p1, p2;
    bool equipeWin;
    int equipe= 0;
    // initier le tableaux avec une valeur de base de 2
    int Psize = 2, align =2;

    /*--- recuperation des information du jeux---*/
    setTailleGrille(Psize);
    setAlign(align, Psize);
    pion *tab[Psize];

    
    /*--- recuperation des information des joueurs ---*/
    setDataplayer(p1, imp1);
    setDataplayer(p2, imp2);

    /*--- Initialisation du jeux ---*/
    initPlayer(Psize, p1, p2);
    initGrille(Psize, tab);

    while (!fin2Parti(p1, p2, Psize, tab, align, equipeWin, BackTour(equipe))){
        affichage(tab, Psize, equipe, align, p1, p2);
        placerPiece(tab, Psize, equipe, p1, p2);
        
    }
    
    if(end(imp1, imp2, equipeWin, tab, Psize) == 1){
        ClearTab(tab, Psize);
        ticTacToeStack(imp1, imp2);
    }
    ClearTab(tab, Psize);   
}
