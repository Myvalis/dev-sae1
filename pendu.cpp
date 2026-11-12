#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

/*
lien ou j'ai piqué le bonhomme baton:
https://gist.github.com/chrishorton/8510732aa9a80a03c829b09f12e20d9c
*/

std::string trouverMot(){
    std::ifstream fichier("mots.txt");
    if (fichier.is_open()) {
        std::string ligne;
        // Lecture ligne par ligne jusqu'Ã  la fin du fichier
        while (std::getline(fichier, ligne)) {
            //std::cout << ligne << '\n';
        }
        fichier.close(); // Fermeture du fichier
    } else {
        std::cerr << "Impossible d'ouvrir le fichier en lecture." << std::endl;
    }
    return "machin";
}

void initCurrent(std::string mot,std::string &currentMot){
    for(int i=0;i<mot.size();i++){
        currentMot+='_';
    }
}

bool verifLettre(char lettre,int taille,std::string &currentmot,std::string mot){
    bool trouve=false;
    for(int i=0;i<taille;i++){
        if(mot[i]==lettre){
            currentmot[i]=lettre;
            trouve=true;
        }
    }
    return trouve;
}

bool verifVictoire(int taille,std::string currentmot,std::string mot){
    for(int i=0;i<taille;i++){
        if(currentmot[i]!=mot[i]){
            return false;
        }
    }
    std::system("cls");
    std::cout<<"GG"<<std::endl;
    std::cout<<"Le mot etait:"<<mot<<std::endl;
    return true;
}

int main() {
    std::string HANGMANPICS[7] = {"  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========", "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========", "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========", "  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========", "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========", "  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========", "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n========="};
    std::string mot,currentmot="";
    char lettre;
    mot=trouverMot();
    std::string currentMot=mot;
    int taille=mot.length(), pendu=0;
    initCurrent(mot,currentmot);
    bool fin=false;
    while(fin!=true){
        std::system("cls");
        std::cout<<HANGMANPICS[pendu]<<std::endl;
        std::cout<<currentmot<<std::endl;
        std::cout<<"Donne une lettre"<<std::endl;
        std::cin>>lettre;
        if(verifLettre(lettre,taille,currentmot,mot)==false){
            pendu++;
        }
        fin=verifVictoire(taille,currentmot,mot);
        if(pendu>6){
            fin=true;
            std::cout<<"Vous etes tout mouru";
        }
    }
}
