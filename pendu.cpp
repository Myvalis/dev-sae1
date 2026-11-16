#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

/*
lien ou j'ai piqué le bonhomme baton:
https://gist.github.com/chrishorton/8510732aa9a80a03c829b09f12e20d9c
*/

std::string trouverMot(){
    srand(time(0));
    std::ifstream fichier("./listMots/mots.txt");
    if (fichier.is_open()) {
        int t=0,i=0;
        std::string ligne;
        // Lecture ligne par ligne jusqu'à  la fin du fichier
        while (std::getline(fichier, ligne)) {
           t++;
        }
        std::string mots[t];
        fichier.clear();                 // Efface l'état d'erreur (EOF)
        fichier.seekg(0, std::ios::beg); // Replace le curseur à la position 0

        while (std::getline(fichier, ligne)) {
           mots[i]=ligne;
           i++;
        }
        fichier.close(); // Fermeture du fichier
        return mots[std::rand() % t];
    } else {
        std::cerr << "Impossible d'ouvrir le fichier en lecture." << std::endl;
    }
    return "abricot";
}

void initCurrent(std::string mot,std::string &currentMot){
    for(int i=0;i<mot.size();i++){
        currentMot+='_';
    }
}

bool verifLettre(char lettre,int taille,std::string &currentmot,std::string mot, std::string &historique){
    bool trouve=false;
    for(int i=0;i<taille;i++){
        if(mot[i]==lettre){
            currentmot[i]=lettre;
            trouve =true;
        }
    }

    if(trouve){
       return true;
    }

    historique+=lettre;
    return false;

}

bool verifVictoire(int taille,std::string currentmot,std::string mot, int pendu, int difficulte){
    if(currentmot == mot){
        std::system("cls");
        std::cout<<"GG"<<std::endl;
        std::cout<<"Le mot etait:"<<mot<<std::endl;
        return true;
    }else if(pendu>difficulte-1){
        std::system("cls");
        std::cout<<"Vous etes tout mouru\n";
        std::cout<<"Le mot etait:"<<mot<<std::endl;
        return true;
    }
    
    return false;
}

int choixDiff(){
    int reponse;
    std::cout<<"Choisissez la difficule: \n 1 : Facile  2 : Difficile"<<std::endl;
    std::cin>>reponse;
    if(reponse==1){
        return 10;
    }
    return 7;
}
void saisitLettre(char &lettre, std::string historique, std::string currentmot){
    std::cout<<"Donne une lettre"<<std::endl;
    std::cin>>lettre;

    if(lettre > 96 && lettre<123){
        for(int i=0; i<historique.length(); i++){
            if((lettre == historique[i]) || (lettre == currentmot[i])){
                std::cout<<"\033[31mLa lettre "<<lettre<<" a deja ete essayer\033[0m\n";
                saisitLettre(lettre, historique, currentmot);
            }
        }
        for(int j=0; j<currentmot.length(); j++){
            if(lettre == currentmot[j]){
                std::cout<<"\033[31mLa lettre "<<lettre<<" a deja ete essayer\033[0m\n";
                saisitLettre(lettre, historique, currentmot);
            }
        }
    }else{
        std::cout<<"\033[31mla valeur saisit n'est pas accepter\033[0m\n";
        saisitLettre(lettre, historique, currentmot);
    }
}
int replay(){
    int retour;
    std::cin.ignore();
    std::cout<<"Rejouer ?\n1- oui\n0- non \n";
    std::cin>>retour;
    
    std::cin.ignore();
    if(retour != 1){
        retour = 0;
    }
    std::system("cls");
    return retour;
}

int main() {
    std::string DIFFICILE[7] = {"  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========", "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========", "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========", "  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========", "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========", "  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========", "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n========="};
    std::string FACILE[10] = {"       \n       \n       \n       \n       \n       \n=========","      +\n      |\n      |\n      |\n      |\n      |\n=========","  +---+\n      |\n      |\n      |\n      |\n      |\n=========","  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========", "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========", "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========", "  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========", "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========", "  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========", "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n========="};
    std::string mot,currentmot="",historique="";
    char lettre;
    mot=trouverMot();
    std::string currentMot=mot;
    int taille=mot.length(), pendu=0,difficulte=choixDiff();
    initCurrent(mot,currentmot);
    bool fin=false;
    while(fin!=true){
        std::system("cls");
        if(difficulte==7){
            std::cout<<DIFFICILE[pendu]<<" Historique: ";
            for(int i=0; i<historique.length(); i++){
                std::cout<<historique[i]<<", ";
            }
        }else{
            std::cout<<FACILE[pendu]<<" Historique: ";
            for(int i=0; i<historique.length(); i++){
                std::cout<<historique[i]<<", ";
            }

        }
        std::cout<<std::endl;
        std::cout<<currentmot<<std::endl;
        saisitLettre(lettre, historique, currentmot);
        if(verifLettre(lettre,taille,currentmot,mot,historique)==false){
            pendu++;
        }
        fin=verifVictoire(taille,currentmot,mot, pendu, difficulte);
    }
    if(replay()){
        return main();
    }
    return 0;
}
