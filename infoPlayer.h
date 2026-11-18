#ifndef INFOPLAYER_H
#define INFOPLAYER_H

#include <string>

struct Player // Structure du joueur
{
    std::string pseudo =""; // Pseudo du joueur
    std::string color; // Couleur du Joueur
    int win = 0; // Nombre de victoire du joueur
};

#endif