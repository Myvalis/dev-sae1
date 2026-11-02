#include <iostream>
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
void initialisation(int size, char *tab[]){
    for(int i=0; i<size; i++){
        tab[i]= new char[size];
        for(int j=0; j<size; j++){
            tab[i][j]= ' ';
        }
    }
}
void afficheGrille(char *tab[], int size){
    for(int i=0; i<size; i++){
        for(int j=0; j<size; j++){
            std::cout<<tab[i][j]<<"|";
        }
        std::cout<<std::endl;
        std::cout<<"_____\n";
    }
}
int main(){
    int Psize = 3;
    setTailleGrille(Psize);
    char *tab[Psize];
    initialisation(Psize, tab);
    afficheGrille(tab, Psize);






    delete[] tab;
    return 0;
}