
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

const int LIGNES = 6;
const int COLONNES = 7;
const char VIDE = '.';
const char JOUEUR = 'X';
const char ORDINATEUR = 'O';

class Puissance4 {
private:
    vector<vector<char>> grille;

public:
    Puissance4() {
        grille.resize(LIGNES, vector<char>(COLONNES, VIDE));
    }

    void afficher() const {
        cout << "\n";
        cout << "       PUISSANCE 4\n\n";

        for (int i = 0; i < LIGNES; i++) {
            cout << "  ";

            for (int j = 0; j < COLONNES; j++) {
                if (grille[i][j] == JOUEUR)
                    cout << "\033[31mX\033[0m";
                else if (grille[i][j] == ORDINATEUR)
                    cout << "\033[33mO\033[0m";
                else
                    cout << ".";

                cout << "   ";
            }

            cout << "\n";
        }

        cout << "\n  1   2   3   4   5   6   7\n\n";
    }

    bool jouer(int colonne, char symbole) {
        if (colonne < 0 || colonne >= COLONNES)
            return false;

        for (int i = LIGNES - 1; i >= 0; i--) {
            if (grille[i][colonne] == VIDE) {
                grille[i][colonne] = symbole;
                return true;
            }
        }

        return false;
    }

    void annuler(int colonne) {
        for (int i = 0; i < LIGNES; i++) {
            if (grille[i][colonne] != VIDE) {
                grille[i][colonne] = VIDE;
                return;
            }
        }
    }

    bool colonneValide(int colonne) const {
        return colonne >= 0 && colonne < COLONNES
            && grille[0][colonne] == VIDE;
    }

    vector<int> coupsPossibles() const {
        vector<int> coups;

        for (int j = 0; j < COLONNES; j++) {
            if (colonneValide(j))
                coups.push_back(j);
        }

        return coups;
    }

    bool victoire(char symbole) const {
        for (int i = 0; i < LIGNES; i++) {
            for (int j = 0; j < COLONNES; j++) {

                if (grille[i][j] != symbole)
                    continue;

                if (j + 3 < COLONNES &&
                    grille[i][j+1] == symbole &&
                    grille[i][j+2] == symbole &&
                    grille[i][j+3] == symbole)
                    return true;

                if (i + 3 < LIGNES &&
                    grille[i+1][j] == symbole &&
                    grille[i+2][j] == symbole &&
                    grille[i+3][j] == symbole)
                    return true;

                if (i + 3 < LIGNES && j + 3 < COLONNES &&
                    grille[i+1][j+1] == symbole &&
                    grille[i+2][j+2] == symbole &&
                    grille[i+3][j+3] == symbole)
                    return true;

                if (i + 3 < LIGNES && j - 3 >= 0 &&
                    grille[i+1][j-1] == symbole &&
                    grille[i+2][j-2] == symbole &&
                    grille[i+3][j-3] == symbole)
                    return true;
            }
        }

        return false;
    }

    bool pleine() const {
        return coupsPossibles().empty();
    }

    int evaluerFenetre(char a, char b, char c, char d) const {
        char cases[4] = {a, b, c, d};

        int nbIA = 0;
        int nbJoueur = 0;
        int nbVides = 0;

        for (char x : cases) {
            if (x == ORDINATEUR)
                nbIA++;
            else if (x == JOUEUR)
                nbJoueur++;
            else
                nbVides++;
        }

        int score = 0;

        if (nbIA == 4) score += 100000;
        else if (nbIA == 3 && nbVides == 1) score += 100;
        else if (nbIA == 2 && nbVides == 2) score += 10;

        if (nbJoueur == 3 && nbVides == 1) score -= 120;
        else if (nbJoueur == 2 && nbVides == 2) score -= 10;

        return score;
    }

    int evaluer() const {
        int score = 0;

        for (int i = 0; i < LIGNES; i++) {
            if (grille[i][COLONNES / 2] == ORDINATEUR)
                score += 6;
        }

        for (int i = 0; i < LIGNES; i++) {
            for (int j = 0; j < COLONNES; j++) {

                if (j + 3 < COLONNES)
                    score += evaluerFenetre(
                        grille[i][j], grille[i][j+1],
                        grille[i][j+2], grille[i][j+3]);

                if (i + 3 < LIGNES)
                    score += evaluerFenetre(
                        grille[i][j], grille[i+1][j],
                        grille[i+2][j], grille[i+3][j]);

                if (i + 3 < LIGNES && j + 3 < COLONNES)
                    score += evaluerFenetre(
                        grille[i][j], grille[i+1][j+1],
                        grille[i+2][j+2], grille[i+3][j+3]);

                if (i + 3 < LIGNES && j - 3 >= 0)
                    score += evaluerFenetre(
                        grille[i][j], grille[i+1][j-1],
                        grille[i+2][j-2], grille[i+3][j-3]);
            }
        }

        return score;
    }

    int minimax(int profondeur, int alpha, int beta,
                bool maximisant, int niveau) {

        if (victoire(ORDINATEUR))
            return 100000 + profondeur;

        if (victoire(JOUEUR))
            return -100000 - profondeur;

        vector<int> coups = coupsPossibles();

        if (profondeur == 0 || coups.empty())
            return evaluer();

        // Priorite aux colonnes centrales
        sort(coups.begin(), coups.end(), [](int a, int b) {
            return abs(a - 3) < abs(b - 3);
        });

        if (maximisant) {
            int meilleur = numeric_limits<int>::min();

            for (int colonne : coups) {
                jouer(colonne, ORDINATEUR);

                int valeur = minimax(
                    profondeur - 1, alpha, beta, false, niveau);

                annuler(colonne);

                meilleur = max(meilleur, valeur);
                alpha = max(alpha, meilleur);

                if (alpha >= beta)
                    break;
            }

            return meilleur;
        }
        else {
            int meilleur = numeric_limits<int>::max();

            for (int colonne : coups) {
                jouer(colonne, JOUEUR);

                int valeur = minimax(
                    profondeur - 1, alpha, beta, true, niveau);

                annuler(colonne);

                meilleur = min(meilleur, valeur);
                beta = min(beta, meilleur);

                if (alpha >= beta)
                    break;
            }

            return meilleur;
        }
    }

    int meilleurCoup(int niveau) {
        vector<int> coups = coupsPossibles();

        if (coups.empty())
            return -1;

        int profondeur;

        if (niveau == 1)
            profondeur = 2;
        else if (niveau == 2)
            profondeur = 4;
        else
            profondeur = 6;

        int meilleurScore = numeric_limits<int>::min();
        int meilleurColonne = coups[0];

        // Recherche des coups les plus intéressants
        sort(coups.begin(), coups.end(), [](int a, int b) {
            return abs(a - 3) < abs(b - 3);
        });

        for (int colonne : coups) {
            jouer(colonne, ORDINATEUR);

            int score = minimax(
                profondeur - 1,
                numeric_limits<int>::min(),
                numeric_limits<int>::max(),
                false, niveau);

            annuler(colonne);

            if (score > meilleurScore) {
                meilleurScore = score;
                meilleurColonne = colonne;
            }
        }

        // Niveau facile : choix parmi les coups possibles
        if (niveau == 1 && rand() % 100 < 45) {
            return coups[rand() % coups.size()];
        }

        return meilleurColonne;
    }
};

class Jeu {
private:
    int victoiresJoueur = 0;
    int victoiresOrdinateur = 0;
    int matchsNuls = 0;

    void afficherScores() const {
        cout << "\n====== SCORES ======\n";
        cout << "Joueur : " << victoiresJoueur << "\n";
        cout << "Ordinateur : " << victoiresOrdinateur << "\n";
        cout << "Matchs nuls : " << matchsNuls << "\n";
        cout << "====================\n";
    }

    int demanderColonne() {
        int colonne;

        while (true) {
            cout << "Choisissez une colonne (1-7) : ";

            if (cin >> colonne && colonne >= 1 && colonne <= 7)
                return colonne - 1;

            cout << "Entree incorrecte.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    void partie(bool contreIA, int niveau) {
        Puissance4 jeu;
        char joueurActuel = JOUEUR;

        while (true) {
            jeu.afficher();

            int colonne;

            if (contreIA && joueurActuel == ORDINATEUR) {
                cout << "L'ordinateur reflechit...\n";

                colonne = jeu.meilleurCoup(niveau);

                if (colonne == -1)
                    break;

                cout << "L'ordinateur joue colonne "
                     << colonne + 1 << "\n";
            }
            else {
                cout << "Tour du joueur " << joueurActuel << "\n";

                colonne = demanderColonne();

                if (!jeu.jouer(colonne, joueurActuel)) {
                    cout << "Cette colonne est pleine !\n";
                    continue;
                }
            }

            if (contreIA && joueurActuel == ORDINATEUR) {
                if (!jeu.jouer(colonne, ORDINATEUR)) {
                    cout << "Erreur de placement.\n";
                    break;
                }
            }

            if (jeu.victoire(joueurActuel)) {
                jeu.afficher();

                if (joueurActuel == JOUEUR) {
                    cout << "Le joueur X a gagne !\n";
                    victoiresJoueur++;
                }
                else {
                    cout << "L'ordinateur a gagne !\n";
                    victoiresOrdinateur++;
                }

                return;
            }

            if (jeu.pleine()) {
                jeu.afficher();
                cout << "Match nul !\n";
                matchsNuls++;
                return;
            }

            joueurActuel =
                (joueurActuel == JOUEUR) ? ORDINATEUR : JOUEUR;
        }
    }

public:
    void lancer() {
        srand(static_cast<unsigned int>(time(nullptr)));

        int choix;

        do {
            cout << "\n";
            cout << "==============================\n";
            cout << "       JEU PUISSANCE 4\n";
            cout << "==============================\n";
            cout << "1. Joueur contre joueur\n";
            cout << "2. Joueur contre ordinateur\n";
            cout << "3. Scores\n";
            cout << "4. Quitter\n";
            cout << "Votre choix : ";

            if (!(cin >> choix)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                choix = 0;
            }

            switch (choix) {
                case 1:
                    partie(false, 0);
                    break;

                case 2: {
                    int niveau;

                    cout << "\n1. Facile\n";
                    cout << "2. Moyen\n";
                    cout << "3. Difficile\n";
                    cout << "Niveau : ";

                    if (!(cin >> niveau) ||
                        niveau < 1 || niveau > 3) {
                        cin.clear();
                        cin.ignore(
                            numeric_limits<streamsize>::max(), '\n');
                        cout << "Niveau invalide.\n";
                        break;
                    }

                    partie(true, niveau);
                    break;
                }

                case 3:
                    afficherScores();
                    break;

                case 4:
                    cout << "Fin du jeu. Merci !\n";
                    break;

                default:
                    cout << "Choix invalide.\n";
            }

        } while (choix != 4);
    }
};

int main() {
    Jeu puissance4;
    puissance4.lancer();

    return 0;
}
