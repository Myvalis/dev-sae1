#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

struct Case{
    bool bombe = false ,show = false, flag = false;
    int nBombe = 0;
};

std::string texteRGB(int r, int g, int b) {
    return "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
}
std::string fondRGB(int r, int g, int b) {
    return "\033[48;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
}

void clearGrille(Case** &Grille, int coll, int lign){
    for(int i=coll-1; i>=0; i-- ){
        for(int j=lign-1; j>=0; j-- )delete & Grille[i][j];
        delete[] Grille[i];
    }
}
void initGrille(Case** &Grille, int &coll, int &lign){
    std::cout<<"nombre de collone: ";
    std::cin>>coll;Grille=new Case*[coll];
    std::cout<<"nombre de ligne: ";std::cin>>lign;
    for(int i=0; i<coll; i++){
        Grille[i] = new Case[lign];
    }
    if((coll<9)||(lign<9)){ 
        std::cout<<"Grille non valable <9\n";
        clearGrille(Grille, coll, lign);
        initGrille(Grille, coll, lign);
    }else{
        std::cout<<"Grille a bien ete creer\n";
    }
}
void initMine(int &nbMine, int coll, int lign){
    std::cout<<"nombre de mine: ";
    std::cin>>nbMine;
    if(nbMine<10 ||nbMine == (coll*lign)){
        std::cout<<"nombre de mine non valable <10\n";
        initMine(nbMine,coll,lign);
    }
    else std::cout<<"Mine a bien ete generer\n";
}
void afficheGrille(Case** &Grille, int coll, int lign){
    std::string color[8]{
        texteRGB(0,0,255),
        texteRGB(0,255,0),
        texteRGB(255,0,0),
        texteRGB(128,0,128),
        texteRGB(128,0,0),
        texteRGB(0,128,128),
        texteRGB(0,0,0),
        texteRGB(64,64,64)
    };
    //std::system("cls");
    std::cout<<" ";
    for(int i=0; i<lign; i++){
        if(i < 10)std::cout<<"   "<<i;
        else std::cout<<"  "<<i;
    }std::cout<<std::endl;
    for(int x=0; x<coll; x++){
        if(x > 9)std::cout<<x;
        else std::cout<<x<<" ";
        for(int y=0; y<lign; y++){
            if(!Grille[x][y].show && !Grille[x][y].flag){
                std::cout<<"\033[0m|"<<fondRGB(128,128,128)<<"   ";
            }else if(Grille[x][y].flag){
                std::cout<<"\033[0m|"<<fondRGB(128,128,128)<<texteRGB(139,0,0)<<" ? ";
            }else if(Grille[x][y].nBombe>0){
                std::cout<<"\033[0m|"<<fondRGB(200,200,200)<<color[Grille[x][y].nBombe-1]<<" "<<Grille[x][y].nBombe<<" ";
            }else if(Grille[x][y].bombe){
                std::cout<<"\033[0m|"<<fondRGB(255,0,0)<<texteRGB(0,0,0)<<" @ ";
            }else{
                std::cout<<"\033[0m|"<<fondRGB(200,200,200)<<"   ";
            }
        }
        std::cout<<"\033[0m| "<<std::endl;
    }
}
void voisineMine(Case** &Grille,int coll, int lign){
    for(int x=0; x<coll; x++){
        for(int y=0; y<lign; y++){
            if(!Grille[x][y].bombe){
                for(int dx=-1; dx<=1; dx++){
                    for(int dy=-1; dy<=1; dy++){
                        int vx = x+dx, vy = y+dy;
                        if(vx>=0 && vx<coll && vy>=0 && vy<lign){
                            if(Grille[vx][vy].bombe)Grille[x][y].nBombe++;
                        }
                    }
                }
            }
        }
    }
}
void genMine(Case** &Grille, int nbMine,int coll, int lign, int xP, int yP){
    int x; int y;
    std::srand(std::time(nullptr));
    for(int i=0; i<nbMine; i++){
        x= std::rand() % (coll-1);
        y= std::rand() % (lign-1);

        while(Grille[x][y].bombe ||((x==xP) && (y==yP))||((x==xP+1) && (y==yP+1))||((x==xP-1) && (y==yP-1))||((x==xP-1) && (y==yP+1))||((x==xP+1) && (y==yP-1))||((x==xP) && (y==yP-1))||((x==xP+1) && (y==yP))||((x==xP) && (y==yP+1))||((x==xP-1) && (y==yP))){
            x= std::rand() % (coll-1);
            y= std::rand() % (lign-1);
        }
        
        Grille[x][y].bombe= true;
        
    }
    voisineMine(Grille, coll, lign);
}
void coPlay(Case** Grille,int coll, int lign, char & action, int &x, int &y){
    std::cout<<"action possible:\n -s devoiler la case\n -f poser un drapeau\n -c enlever le drapeaux\n";
    std::cout<<"(action) (position x) (position y) : ";
    std::cin>>action;
    std::cin>>y;
    std::cin>>x;
    
    if((x>coll || x<0 || y>lign || y<0)||(Grille[x][y].show)){
        std::cout<<"action non jouable\n";
        coPlay(Grille,coll,lign,action,x,y);
    }
}
void cascade(Case** &Grille, int coll, int lign, int x, int y){
    if(Grille[x][y].show && (Grille[x][y].nBombe == 0)){
        for(int dx=-1; dx<=1; dx++){
            for(int dy=-1; dy<=1; dy++){
                int vx = x+dx, vy = y+dy;
                if(dx !=0 || dy !=0){
                    if(vx>=0 && vx<coll && vy>=0 && vy<lign && !Grille[vx][vy].show){
                        Grille[vx][vy].show=true;
                        cascade(Grille, coll, lign, vx, vy);
                    }
                }
            }
        }
    }else return;
}
void showCase(Case** &Grille, int coll, int lign, int nbMine, bool &start){
    int x, y;
    char action;
    
    coPlay(Grille,coll,lign,action,x,y);
    
    if(action == 's'){
        if(!start){
            genMine(Grille, nbMine ,coll, lign, x, y);
            start =true;
        }
        Grille[x][y].show=true;
        cascade(Grille, coll, lign, x, y);
    }else if(action == 'f'){
        Grille[x][y].flag=true;
    }else if(action == 'c'){
        Grille[x][y].flag=false;
    }else{
        std::cout<<"Action non possible\n ";
    }
    
}
void showAll(Case** &Grille, int coll, int lign){
    for(int x=0; x<coll; x++){
        for(int y=0; y<lign; y++){
            Grille[x][y].show=true;
            Grille[x][y].flag= false;
        }
    }
    afficheGrille(Grille, coll, lign);
}
bool fin2partie(Case** Grille, int coll, int lign, int nbMine){
    int NbCase=0;
    for (int x=0; x< coll; x++){
        for (int y = 0; y < lign; y++){
            if(Grille[x][y].show && Grille[x][y].bombe){
                showAll(Grille, coll, lign);
                std::cout<<"KABOUMMMM vous avez perdu :(\n";
                return true;
            }else if(Grille[x][y].show && !Grille[x][y].bombe){
                NbCase++;
            }
        }
    }
    if(NbCase == ((coll*lign)-nbMine)){
        std::cout<<"YEEEEPEEEE tu as deminer la zone :3\n";
        return true;
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
int main(){
    int coll=9 ,lign=9, nbMine=10;
    bool start=false;
    Case **Grille= NULL;
    
    initGrille(Grille, coll, lign);
    initMine(nbMine, coll, lign);
    afficheGrille(Grille, coll, lign);
    while(!fin2partie(Grille, coll, lign, nbMine)){
        showCase(Grille, coll, lign, nbMine, start);
        afficheGrille(Grille, coll, lign);
    }

    clearGrille(Grille, coll, lign);
    if(replay()){
        return main();
    }
}