#include <iostream>
#include <fstream>
#include <string>


std::string trouverMot(){
    std::ifstream fichier("C:/Users/Rebec/Documents/GitHub/dev-sae1/mots.txt");

    if (fichier.is_open()) {
        std::string ligne;
        // Lecture ligne par ligne jusqu'à la fin du fichier
        while (std::getline(fichier, ligne)) {
            //std::cout << ligne << '\n';
        }
        fichier.close(); // Fermeture du fichier
    } else {
        std::cerr << "Impossible d'ouvrir le fichier en lecture." << std::endl;
    }
    return "machin";
}

void initTab(std::string mot,char currentTab[],char resultTab[]){
    for(int i=0;i<mot.size();i++){
        currentTab[i]='_';
        resultTab[i]=mot[i];
    }
}

void affichTab(int taille,char tab[]){
    for(int i=0;i<taille;i++){
        std::cout<<tab[i];
    }
}

bool verrifLettre(char lettre,int taille,char currentTab[],char resultTab[]){
    bool trouve=false;
    for(int i=0;i<taille;i++){
        if(resultTab[i]==lettre){
            currentTab[i]=lettre;
            trouve=true;
        }
    }
    return trouve;
}

int main() {
    std::string mot;
    mot=trouverMot();
    int taille=mot.length();
    char currentTab[taille], resultTab[taille];
    initTab(mot,currentTab,resultTab);
    affichTab(taille,currentTab);
    affichTab(taille,resultTab);
}
