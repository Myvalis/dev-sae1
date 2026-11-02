#include <iostream>
#include <cstdlib>

struct pion{
    char couleur;
    int niv;
    bool equipe;
};

//demande à l'utilisateur la taille de la grille.
void setTailleGrille(int &valeur){
    std::cout<<"taille du de la grille : ";
    std::cin>>valeur;
    if (valeur < 3){
        std::cout<<"taille trop petite: ";
        valeur = 3;
    }
    std::cout<<"taille mis a "<<valeur<<std::endl;
    
}
void initialisation(int size, pion *tab[]){
    for(int i=0; i<size; i++){
        tab[i]= new pion[size];
        for(int j=0; j<size; j++){
            tab[i][j].couleur = ' ';
            tab[i][j].niv = -1;
        }
    }
}
void afficheGrille(pion *tab[], int size, bool equipe){
    std::system("cls");

    std::cout<<"tour de joueur "<<equipe<<std::endl;
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            std::cout<<" | "<<tab[i][j].couleur;
        }
        std::cout<<" | "<<std::endl;
    }
}
void placerPiece(pion *tab[], int size, bool & equipe, int nivpion, int x, int y){
    char colo[6] = {'x','%','X','o','0','O'};
    
    if(x > size){
        x= x%size;
    }else if (y > size){
        y= y%size;
    }

    if(tab[y][x].niv < nivpion){
        tab[y][x].niv=nivpion;
        if(equipe){
            tab[y][x].couleur=colo[nivpion];
            tab[y][x].equipe=true;
            equipe = false;
        }else{
            tab[y][x].couleur=colo[nivpion + 3];
            tab[y][x].equipe=false;
            equipe = true;
        }
    }else{
        std::cout<<"TU ES FAIBLE\n";
    }

}
void PlayAction(int & x, int & y, int & niv){
    std::cin.ignore();
    std::cout<<"position x : ";
    std::cin>>x;
    std::cout<<"position y : ";
    std::cin>>y;
    std::cout<<"niveaux du pion : ";
    std::cin>>niv;
}



int main(){
    int x, y, niv, equipeWin;

    bool equipe=false;
    int niveau[3]={0 , 1 , 2};
    // initier le tableaux avec une valeur de base de 3
    int Psize = 3;
    setTailleGrille(Psize);
    pion *tab[Psize];
    initialisation(Psize, tab);


    afficheGrille(tab, Psize, equipe);
    PlayAction(x, y, niv);
    placerPiece(tab, Psize, equipe, niv, x, y);
    for(int i=0; i<10; i++){
        afficheGrille(tab, Psize, equipe);
        PlayAction(x, y, niv);
        placerPiece(tab, Psize, equipe, niv, x, y);
    }
    




    delete[] *tab;
    return 0;
}