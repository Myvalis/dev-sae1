#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
struct Historique{
    std::string mot="";
    int postion[20];
};

std::string fondRGB(int r, int g, int b) {
    return "\033[48;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
}

std::string genererMot(){
    std::string NouvMot;
    int sizeListMot = 0;

    std::srand(std::time(nullptr));
    std::fstream fichier("./MotsEn5Lettre.txt");
    if(fichier.is_open()){
        while(std::getline(fichier, NouvMot)){
            sizeListMot++;
        }
        std::string ListMot[sizeListMot];

        fichier.clear();
        fichier.seekg(0, std::ios::beg);

        for(int i=0; std::getline(fichier, NouvMot); i++){
            ListMot[i]=NouvMot;
        }
        fichier.close();
        return ListMot[std::rand() % sizeListMot];
    }else{
        std::cout << "le fichier ne s'ouvre pas\n";
        return "furry";
    }
}
void tabNull(int tab[], int size){
    for(int i=0; i<size; i++){
        tab[i] = 0;
    }
}
void affichage(int sizeMot, Historique Historique[], int essaie){
    std::system("cls");
    if (essaie==0){
       std::cout<<"Wordle:\n";
       for(int i=0; i<sizeMot; i++){
        std::cout<<"|";
        std::cout<<fondRGB(128, 128, 128)<<"   \33[0m";
       }
       std::cout<<"|\n";
    }else{
        std::cout<<"Wordle:\n";
        for(int i=0; i<essaie; i++){
            for(int j=0; j<sizeMot; j++){
                std::cout<<"|";
                if(Historique[i].postion[j]==2){
                    std::cout<<"\33[42m "<<Historique[i].mot[j]<<" \33[0m";
                }else if(Historique[i].postion[j]==1){
                    std::cout<<"\33[43m "<<Historique[i].mot[j]<<" \33[0m";
                }else{
                    std::cout<<"\33[41m "<<Historique[i].mot[j]<<" \33[0m";
                }
            }
            std::cout<<"|\n";
        }
       
    }
}
void occurence(std::string MotCacher, int sizeMot, int nombreLettre[]){
    int ASQII=0;
    tabNull(nombreLettre, 26);
    for(int i=0; i<sizeMot; i++){
        ASQII = MotCacher[i];
        for(int j=0; j<26; j++){
            if((ASQII%97) == j){
                nombreLettre[j]++;
            }
        }
           
    }
}
void placeLettre(std::string motCacher, int essaie, int sizeMot, Historique Historique[], int nombreLettre[]){
    int ASCII;
    for(int i=0; i<sizeMot; i++){
        ASCII= Historique[essaie].mot[i];
        if(Historique[essaie].mot[i] == motCacher[i]){
            nombreLettre[(ASCII %97)]-= 1;
            Historique[essaie].postion[i]=2;
        }
    }
    for(int i=0; i<sizeMot; i++){
        ASCII= Historique[essaie].mot[i];
        if(Historique[essaie].postion[i]!=2){
            if(nombreLettre[ASCII % 97]>0){
                std::cout<<"male placer";
                nombreLettre[(ASCII %97)]-= 1;
                Historique[essaie].postion[i]=1;          
            }else{
                std::cout<<"pas/plus dans le mot";
                Historique[essaie].postion[i]=0;
            }
        }
    }
}
bool motValable(std::string mot, int sizeMot){
    int ASCII=0;
    for(int i=0; i<sizeMot; i++){
        ASCII=mot[i];
        if((ASCII < 97)||(ASCII > 122)){
            return false;
        }
    }
    return true;
}
std::string saisie(int sizeMot){
    std::string mot=" ";
    
    std::cout<<"nouveaux mots : ";
    std::cin>>mot;
    
    if(mot.length() == sizeMot && motValable(mot , sizeMot)){
        return mot;
    }else{
        std::cout<<"\33[31mmots non valide\33[0m\n";
        return saisie(sizeMot);
    }
}
bool win(std::string motJoueur, std::string MotCacher, int sizeMot){
    for(int i=0; i<sizeMot; i++){
        if(motJoueur[i] != MotCacher[i]){
            return false;
        }
    }
    return true;
}
int fin2Party(int sizeMot, Historique Historique[], int essaie, bool Win, std::string MotCacher){
    affichage(sizeMot, Historique, essaie);
    int retour =3;
    if(Win){
        std::cout<<"FELICITATION :D Tu a Trouver le mot en "<<essaie<<" essaie\n";
    }else{
        std::cout<<"DOMAGE :C le mot a trouver etais "<<MotCacher<<std::endl;
    }

    std::cout<<"Rejouer ?\n1- oui\n0- non \n";
    std::cin>>retour;
    
    if(retour != 1){
        retour = 0;
    }
    std::system("cls");
    return retour;

}
int main() {
    std::string MotCacher = genererMot();
    int sizeMot = MotCacher.length(),essaie = 0, bienPlacer[sizeMot], nombreLettre[26];
    tabNull(bienPlacer, sizeMot);
    tabNull(nombreLettre, 26);
    bool Win = false;
    Historique Historique[sizeMot+1];
    
    
    

    for(essaie; essaie<=sizeMot && !Win; essaie++){
        affichage(sizeMot, Historique, essaie);
        Historique[essaie].mot = saisie(sizeMot);
        Win= win(Historique[essaie].mot, MotCacher, sizeMot);
        occurence(MotCacher, sizeMot, nombreLettre);
        placeLettre(MotCacher, essaie, sizeMot, Historique, nombreLettre);
    }
    return fin2Party(sizeMot, Historique, essaie, Win, MotCacher);
}