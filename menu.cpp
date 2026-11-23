#include <iostream>
#include <cstdlib>

#include "infoPlayer.h"
#include "tic_tac_toe_stack.h"
#include "othello.h"

/****   créé par Emma    ****/

std::string texteRGB(int r, int g, int b) {
    return "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
}

// Fonction pour colorer le FOND en RGB (R, G, B entre 0 et 255)
std::string fondRGB(int r, int g, int b) {
    return "\033[48;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
}

void PlayerName(Player &p1, Player &p2){
    std::string nom;

    std::system("cls");
    for(int i=0; i<2; i++){
        std::cout<<"nom joueur "<<i+1<<": \n";
        std::cin>>nom;
        if(i == 1){
            p2.pseudo=nom;
        }else{
            p1.pseudo=nom;
        }
    }
}
void defaultPlayer(Player &p1, Player &p2){
    p1.pseudo="Joueur 1";
    p1.color="\033[31m";
    p2.pseudo="Joueur 2";
    p2.color="\033[34m";
}
void resetScore(Player &p1, Player &p2){
    p1.win=0;
    p2.win=0;
}

//choix de la couleurs
void PlayerColor(Player &p1, Player &p2){
    int r=255, g=255, b=255;
    for(int i=0; i<2; i++){
        std::system("cls");
        std::cout<<"| "<<texteRGB(239,68,68)<<"[239  68  68]\033[0m | "<<texteRGB(249,115,22)<<"[249 115  22]\033[0m | "<<texteRGB(250,204,21)<<"[250 204  21]\033[0m | "<<texteRGB(250,250,250)<<"[250 250 250]\033[0m |\n";
        std::cout<<"| "<<texteRGB(132,204,22)<<"[132 204  22]\033[0m | "<<texteRGB(34,197,94)<<"[ 34 197  94]\033[0m | "<<texteRGB(6,182,212)<<"[  6 182 212]\033[0m | "<<texteRGB(156,163,175)<<"[156 163 175]\033[0m |\n";
        std::cout<<"| "<<texteRGB(59,130,246)<<"[ 59 130 246]\033[0m | "<<texteRGB(139,92,246)<<"[139  92 246]\033[0m | "<<texteRGB(217,70,239)<<"[217  70 239]\033[0m | "<<texteRGB(55,65,81)<<"[ 55  65  81]\033[0m |\n"<<std::endl;;
        
        if (i==0)
        {
            
            std::cout<<p1.pseudo<<" quel couleur veux tu prendre ? (r g b) :";
            std::cin>>r;
            std::cin>>g;
            std::cin>>b;
            
            p1.color=texteRGB(r,g,b);
        }else{
            std::cout<<p2.pseudo<<" quel couleur veux tu prendre ? (r g b) :";
            std::cin>>r;
            std::cin>>g;
            std::cin>>b;
            p2.color=texteRGB(r,g,b);
        }
        std::system("cls");
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
        std::cout<<"|"<<texteRGB(175, 238, 238)<<"6- demineur\033[0m           |\n";
        std::cout<<"|                      |\n";
        std::cout<<"+--   \033[32mAutre action\033[0m   --+\n";
        std::cout<<"|                      |\n";
        std::cout<<"|"<<texteRGB(136,231,136)<<"p- Paramettre         \033[0m|\n";
        std::cout<<"|\033[31mQ- Quitter            \033[0m|\n";
        std::cout<<"+-+==================+-+\n";
        std::cout<<"+----------------------+\n";
    }else if(page == 1){
        std::cout<<"\033[33m@- IUT GAME 2026-2027 -@\033[0m\n";
        std::cout<<"+----------------------+\n";
        std::cout<<"+-+=====- Menu -=====+-+\n";
        std::cout<<"+--    \033[34mParametre\033[0m     --+\n";
        std::cout<<"|                      |\n";
        std::cout<<"|"<<texteRGB(119, 181, 254)<<"1- Noms Joueurs\033[0m       |\n";
        std::cout<<"|"<<texteRGB(119, 181, 254)<<"2- Couleurs Joueurs\033[0m   |\n";
        std::cout<<"|"<<texteRGB(119, 181, 254)<<"3- Score Joueurs\033[0m      |\n";
        std::cout<<"|                      |\n";
        std::cout<<"|"<<texteRGB(119, 181, 254)<<"4- Reset Scores\033[0m       |\n";
        std::cout<<"|                      |\n";
        std::cout<<"+--   \033[32mAutre action\033[0m   --+\n";
        std::cout<<"|                      |\n";
        std::cout<<"|"<<texteRGB(136,231,136)<<"r- retour             \033[0m|\n";
        std::cout<<"|\033[31mQ- quitter            \033[0m|\n";
        std::cout<<"+-+==================+-+\n";
        std::cout<<"+----------------------+\n";
    }
}
void action(int & page, char & choix, Player &p1, Player &p2){
    
    saisit(choix);

    if(page == 0){
        switch (choix) {
            case '1':
                ticTacToeStack(p1, p2);
            break;
            case '2':
                othello(p1, p2);
            break;
            case '3':
            break;
            case '4':
                system("pendu.exe");
            break;
            case '5':
                system("wordle.exe");
            break;
            case '6':
                system("demineur.exe");
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
            case '3':
                std::cout<<p1.color<<p1.pseudo<<"\033[0m a gagne.e "<<p1.win<<" fois\n";
                std::cout<<p2.color<<p2.pseudo<<"\033[0m a gagne.e "<<p2.win<<" fois\n\n";
            break;
            case '4':
                resetScore(p1, p2);
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
    Player p1, p2;
    defaultPlayer(p1, p2);

    while(choix !='Q'){
        affichage(page);
        action(page, choix, p1, p2);
    }
    
    return 0;
}