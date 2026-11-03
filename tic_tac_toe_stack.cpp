#include <iostream>
#include <cstdlib>
#include <string>

struct pion{
    char couleur;
    int niv;
    int equipe;
};
struct player{
    bool equipe;
    std::string nom;
    int np[3];
    std::string couleur;
};

void setPlayerName(player &p1, player &p2, bool equipe){
    std::string name;
    for(int i=0; i<2; i++){
        std::cout<<"nom joueur "<<equipe+1<<": \n";
        std::cin>>name;
        if(equipe){
            p2.equipe=equipe;
            p2.nom=name;
        }else{
            p1.equipe=equipe;
            p1.nom=name;
        }
        equipe =true;
    }
}
void setColorplayer(player &p, int chColor){
    switch (chColor) {
        case 1:
            p.couleur="\033[31m";
        break;
        case 2:
            p.couleur="\033[32m";
        break;
        case 3:
            p.couleur="\033[33m";
        break;
        case 4:
            p.couleur="\033[34m";
        break;
        case 5:
            p.couleur="\033[35m";
        break;
        case 6:
            p.couleur="\033[36m";
        break;
        default:
            p.couleur="\033[0m";
        break;
    }
}
void selectColorPlayer(player &p1, player &p2){
    int chColor=0;
    for(int i=0; i<2; i++){
        std::system("cls");
        std::cout<<"0.Blanc\n1.\033[31mRouge\033[0m\n2.\033[32mVert\033[0m\n3.\033[33mJaune\033[0m\n";
        std::cout<<"4.\033[34mBleu\033[0m\n5.\033[35mMagenta\033[0m\n6.\033[36mCyan\033[0m\n";
        if (i==0)
        {
            std::cout<<p1.nom<<" quel couleur veux tu prendre ? :\n";
            std::cin>>chColor;
            setColorplayer(p1, chColor);
        }else{
            std::cout<<p2.nom<<" quel couleur veux tu prendre ? :\n";
            std::cin>>chColor;
            setColorplayer(p2, chColor);
        }
        std::system("cls");
    } 
}
//demande à l'utilisateur la taille de la grille.
void setTailleGrille(int &valeur){
    std::cout<<"taille du de la grille : ";
    std::cin>>valeur;
    std::system("cls");
    if (valeur < 2){
        std::cout<<"taille trop petite: ";
        valeur = 2;
    }
    std::cout<<"taille mis a "<<valeur<<std::endl;
    
}
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

void givePoinPlayer(player &p, int npion[]){
    for(int i=0; i<3; i++){
        p.np[i]=npion[i];
    }
}

void initPlayer(int Psize, player &p1, player &p2){
    int npion[3];
    for(int i=0; i<3; i++){
        npion[i]=((Psize*(Psize+1))/2)/3;
    }

    if((((Psize*(Psize+1))/2)%3) != 0 ){
        npion[0]+=1; 
    }

    for(int j=0; j<2; j++){
        if(j==0){
            givePoinPlayer(p1, npion);
        }else{
            givePoinPlayer(p2, npion);
        }
    }
}
void afficheGrille(pion *tab[], int size, std::string color[]){
    
    std::cout<<"  ";
    for(int o=0; o<size; o++){
        if(o < 10){
            std::cout<<"   "<<o;
        }else{
            std::cout<<"  "<<o;
        }
        
    }
    std::cout<<std::endl;
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
void affichage(pion *tab[], int size, bool equipe, player p1, player p2){
    std::string color[3]={p1.couleur, p2.couleur, "\033[0m"};
    if(equipe){
        std::cout<<"tour de "<<p2.couleur<<p2.nom<<"\033[0m :"<<std::endl;
        std::cout<<"nombre de pion : o "<<p2.np[0]<<" / 0 "<<p2.np[1]<<" / O "<<p2.np[2]<<std::endl;
    }else{
        std::cout<<"tour de "<<p1.couleur<<p1.nom<<"\033[0m :"<<std::endl;
        std::cout<<"nombre de pion : x "<<p1.np[0]<<" / % "<<p1.np[1]<<" / X "<<p1.np[2]<<std::endl;

    }
    afficheGrille(tab, size, color);
    
}
bool matchNull(player p1, player p2){
    bool null=false;
    for(int i=0; i<3; i++){
        if (p1.np[i] == 0 && p2.np[i]){
            null=true;
        }else{
            null=false;
        }
    }
    return null;
}

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
bool restpiece(player p1, player p2, int nivpion, bool equipe){
    if(equipe){
        return p2.np[nivpion] <= 0;
    }else{
        return p1.np[nivpion] <= 0;
    }
    
}
void placerPiece(pion *tab[], int size, bool & equipe, player &p1, player &p2){
    char colo[6] = {'x','%','X','o','0','O'};
    int x, y, nivpion;
    PlayAction(x, y, nivpion);
    nivpion--;
    if(x >= size || y > size || nivpion > 2 || restpiece(p1, p2, nivpion, equipe)){
        std::cout<<"le pion ne peux pas etre posse\n";
    }else{
        if((tab[y][x].niv < nivpion)){
            tab[y][x].niv=nivpion;
            if(equipe){
                tab[y][x].couleur=colo[nivpion+ 3];
                tab[y][x].equipe=true;
                p2.np[nivpion]--;
                equipe = false;
            }else{
                tab[y][x].couleur=colo[nivpion];
                tab[y][x].equipe=false;
                p1.np[nivpion]--;
                equipe = true;
            }
        }   
    }
}
int main(){
    player p1, p2;
    int equipeWin;
    bool equipe=false;
    int niveau[3]={0 , 1 , 2};
    // initier le tableaux avec une valeur de base de 2
    int Psize = 2, align =2;
    std::cout<<3/3;
    setPlayerName(p1 , p2, equipe);
    selectColorPlayer(p1, p2);
    setTailleGrille(Psize);
    pion *tab[Psize];
    initPlayer(Psize, p1, p2);
    initGrille(Psize, tab);

    while (!matchNull(p1, p2)){
        affichage(tab, Psize, equipe, p1, p2);
        placerPiece(tab, Psize, equipe, p1, p2);
    }
    




    delete[] *tab;
    return 0;
}