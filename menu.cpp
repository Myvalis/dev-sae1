#include <iostream>
#include <cstdlib>


struct importPlayer{
    std::string Name="", Color="";
};

std::string texteRGB(int r, int g, int b) {
    return "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
}

// Fonction pour colorer le FOND en RGB (R, G, B entre 0 et 255)
std::string fondRGB(int r, int g, int b) {
    return "\033[48;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
}

void PlayerName(importPlayer &p1, importPlayer &p2){
    std::string nom;

    std::system("cls");
    for(int i=0; i<2; i++){
        std::cout<<"nom joueur "<<i+1<<": \n";
        std::cin>>nom;
        if(i == 1){
            p2.Name=nom;
        }else{
            p1.Name=nom;
        }
    }
}
//assigner une couleurs
void setColorplayer(importPlayer &p, int chColor){
    switch (chColor) {
        case 1:
            p.Color="\033[31m";
        break;
        case 2:
            p.Color="\033[32m";
        break;
        case 3:
            p.Color="\033[33m";
        break;
        case 4:
            p.Color="\033[34m";
        break;
        case 5:
            p.Color="\033[35m";
        break;
        case 6:
            p.Color="\033[36m";
        break;
        default:
            p.Color="\033[0m";
        break;
    }
}
//choix de la couleurs
void PlayerColor(importPlayer &p1, importPlayer &p2){
    int chColor=0;
    for(int i=0; i<2; i++){
        std::system("cls");
        std::cout<<"0.Blanc\n1.\033[31mRouge\033[0m\n2.\033[32mVert\033[0m\n3.\033[33mJaune\033[0m\n";
        std::cout<<"4.\033[34mBleu\033[0m\n5.\033[35mMagenta\033[0m\n6.\033[36mCyan\033[0m\n";
        if (i==0)
        {
            std::cout<<p1.Name<<" quel couleur veux tu prendre ? :\n";
            std::cin>>chColor;
            setColorplayer(p1, chColor);
        }else{
            std::cout<<p2.Name<<" quel couleur veux tu prendre ? :\n";
            std::cin>>chColor;
            setColorplayer(p2, chColor);
        }
        std::system("cls");
    } 
}
void replay(int action, std::string jeux){
    std::string executable="\""+jeux+"\"";
    if(action == 1){
        system(executable.c_str());
    }
}
void saisit(char & choix){
    std::cout<<"que voulez vous faire: ";
    std::cin>>choix;
    std::system("cls");
}
void affichage(int page){
    if(page == 0){
        std::cout<<"\033[33m@- IUT GAME 2026-2027 -@\033[0m\n";
        std::cout<<"+----------------------+\n";
        std::cout<<"+-+=====- Menu -=====+-+\n";
        std::cout<<"+--   "<<texteRGB(255, 145, 164)<<"Jeux a deux\033[0m    --+\n";
        std::cout<<"|                      |\n";
        std::cout<<"|"<<texteRGB(255, 182, 193)<<"1- Tic tac toe stack\033[0m  |\n";
        std::cout<<"|"<<texteRGB(255, 182, 193)<<"2- Othello\033[0m            |\n";
        std::cout<<"|"<<texteRGB(255, 182, 193)<<"3- Puissance 4\033[0m        |\n";
        std::cout<<"|                      |\n";
        std::cout<<"+--    "<<texteRGB(43, 250, 250)<<"Jeux solo\033[0m     --+\n";
        std::cout<<"|                      |\n";
        std::cout<<"|"<<texteRGB(175, 238, 238)<<"4- Pendu\033[0m              |\n";
        std::cout<<"|"<<texteRGB(175, 238, 238)<<"5- Wordle\033[0m             |\n";
        std::cout<<"|                      |\n";
        std::cout<<"+--   \033[32mAutre action\033[0m   --+\n";
        std::cout<<"|                      |\n";
        std::cout<<"|"<<texteRGB(136,231,136)<<"p- Paramettre         \033[0m|\n";
        std::cout<<"|\033[31mQ- Quitter            \033[0m|\n";
        std::cout<<"+-+==================+-+\n";
        std::cout<<"+----------------------+\n";
    }else{
        std::cout<<"\033[33m@- IUT GAME 2026-2027 -@\033[0m\n";
        std::cout<<"+----------------------+\n";
        std::cout<<"+-+=====- Menu -=====+-+\n";
        std::cout<<"+--    \033[34mParametre\033[0m     --+\n";
        std::cout<<"|                      |\n";
        std::cout<<"|"<<texteRGB(119, 181, 254)<<"1- Noms Joueurs\033[0m       |\n";
        std::cout<<"|"<<texteRGB(119, 181, 254)<<"2- Couleurs Joueurs\033[0m   |\n";
        std::cout<<"|                      |\n";
        std::cout<<"+--   \033[32mAutre action\033[0m   --+\n";
        std::cout<<"|                      |\n";
        std::cout<<"|"<<texteRGB(136,231,136)<<"r- retour             \033[0m|\n";
        std::cout<<"|\033[31mQ- quitter            \033[0m|\n";
        std::cout<<"+-+==================+-+\n";
        std::cout<<"+----------------------+\n";
    }
}
void action(int & page, char & choix, importPlayer &p1, importPlayer &p2){
    
    saisit(choix);

    if(page == 0){
        switch (choix) {
            case '1':
                replay(system("EmmTest.exe"), "EmmTest.exe");
            break;
            case '2':
                system("EmmTest.exe");
            break;
            case '3':
                system("EmmTest.exe");
            break;
            case '4':
                system("EmmTest.exe");
            break;
            case '5':
                replay(system("wordle.exe"), "wordle.exe");
            break;
            case 'p':
                page = 1;
            break;
            case 'Q':
                std::cout<<"Bonne journee :D\n";
            break;
            default:
                std::cout<<"Action "<<choix<<" pas possible\n\n";
            break;
        }
    }else{
        switch (choix) {
            case '1':
                PlayerName(p1, p2);
            break;
            case '2':
                PlayerColor(p1, p2);
            break;
            case 'r':
                page = 0;
            break;
            case 'Q':
                std::cout<<"Bonne journee :D\n";
            break;
            default:
                std::cout<<"Action "<<choix<<" pas possible\n\n";
            break;
        }
    }
}
int main(){
    char choix='0';
    int page=0;
    importPlayer p1, p2;

    

    while(choix !='Q'){
        affichage(page);
        action(page, choix, p1, p2);
    }
    
    return 0;
}