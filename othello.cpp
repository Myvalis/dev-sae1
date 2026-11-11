#include <iostream>

void initTab(char tab[],int nb){
	for(int i=0;i<nb*nb;i++){
		if((i==28)or(i==35)){
			tab[i]='X';
		}else if((i==27)or(i==36)){
			tab[i]='O';
		}else{
			tab[i]='.';
		}
	}
}

 
void affichageTab(char tab[],int nb){
	//la marge
	std::cout<<"  ";
	for(int i=0;i<nb;i++){
		std::cout<<(i+1)<<' ';
	}
	for(int i=0;i<nb*nb;i++){
		if((i)%nb==0){
			std::cout<<std::endl;
			//affichage des numéros de collonne
			std::cout<<(i/nb+1)<<' ';
		}
		std::cout<<tab[i]<<' ';
	}
}

void retourneLigne(char tab[],int idep,int ifin,char symbole){
	for(int i=idep;i<=ifin;i++){
		tab[i]=symbole;
	}
}

void retourneColonne(char tab[],int idep,int ifin,char symbole){
	for(int i=idep;i<=ifin;i+=8){
		tab[i]=symbole;
	}
}

void retourneDiagonaleGD(char tab[],int idep,int ifin,char symbole){
	for(int i=idep;i<=ifin;i+=9){
		tab[i]=symbole;
	}
}

void retourneDiagonaleDG(char tab[],int idep,int ifin,char symbole){
	for(int i=idep;i<=ifin;i+=7){
		tab[i]=symbole;
	}
}

void cascade(char tab[],int nb,int ipion,char symbole){
	//prend en parametre le tableau,sa taille et l'indice et le symbole du dernier pion joué
	//et retourne(dans le sens change de sens) les cases à retourner
	//on verifie la case adjacente 
	if((ipion+1<nb*nb)and(tab[ipion+1]!=symbole)){
		//verifie toute la ligne à droite du pion, s'arrete à case vide ou à multiple de nb
		for(int i=ipion+1;(i%nb!=0)and(tab[i]!='.');i++){
			if(tab[i]==symbole){
				retourneLigne(tab,ipion,i,symbole);
				break;
			}
		}
	}
	if((ipion-1>=0)and(tab[ipion-1]!=symbole)){
		//verifie toute la ligne à gauche du pion, s'arrete à case vide ou à multiple de nb-1
		for(int i=ipion-1;((i+1)%nb!=0)and(tab[i]!='.');i--){
			if(tab[i]==symbole){
				retourneLigne(tab,i,ipion,symbole);
				break;
			}
		}
	}
	if((ipion+8<nb*nb)and(tab[ipion+8]!=symbole)){
		for(int i=ipion+8;(i<nb*nb)and(tab[i]!='.');i+=8){
			if(tab[i]==symbole){
				retourneColonne(tab,ipion,i,symbole);
				break;
			}
		}
	}
	if((ipion-8>=0)and(tab[ipion-8]!=symbole)){
		for(int i=ipion-8;(i>=0)and(i<nb*nb)and(tab[i]!='.');i-=8){
			if(tab[i]==symbole){
				retourneColonne(tab,i,ipion,symbole);
				break;
			}
		}
	}
	if((ipion+9<nb*nb)and(ipion%8!=0)and(tab[ipion+9]!=symbole)){
		for(int i=ipion+9;(i<nb*nb)and(tab[i]!='.');i+=9){
			if(tab[i]==symbole){
				retourneDiagonaleGD(tab,ipion,i,symbole);
				break;
			}
		}
	}
	if((ipion-9>=0)and(tab[ipion-9]!=symbole)){
		for(int i=ipion-9;(i>=0)and(i<nb*nb)and(tab[i]!='.');i-=9){
			if(tab[i]==symbole){
				retourneDiagonaleGD(tab,i,ipion,symbole);
				break;
			}
		}
	}
	if((ipion+7<nb*nb)and(tab[ipion+7]!=symbole)){
		for(int i=ipion+7;(i<nb*nb)and(tab[i]!='.');i+=7){
			if(tab[i]==symbole){
				retourneDiagonaleDG(tab,ipion,i,symbole);
				break;
			}
		}
	}
	if((ipion-7>=0)and(tab[ipion-7]!=symbole)){
		for(int i=ipion-7;(i>=0)and(i<nb*nb)and(tab[i]!='.');i-=7){
			if(tab[i]==symbole){
				retourneDiagonaleDG(tab,i,ipion,symbole);
				break;
			}
		}
	}	
}

bool adjacence(char tab[],int nb,int ipion,char symbole){
	//un coup est valide si la case est vide et qu'une direction contient
	//au moins un pion adverse suivi d'un pion à soi
	if(tab[ipion]!='.'){
		return false;
	}
	int pas[8]={1,-1,8,-8,9,-9,7,-7};
	for(int k=0;k<8;k++){
		int i=ipion;
		int compte=0;
		while(true){
			int suivant=i+pas[k];
			//écart de colonne entre deux cases consécutives : plus de 1 = on a changé de bord
			int dcol=suivant%nb-i%nb;
			if(dcol<0){
				dcol=-dcol;
			}
			if((suivant<0)or(suivant>=nb*nb)or(dcol>1)){
				break;
			}
			i=suivant;
			if(tab[i]=='.'){
				break;
			}
			if(tab[i]==symbole){
				if(compte>0){
					return true;
				}
				break;
			}
			compte++;
		}
	}
	return false;
}

void ecriture(char tab[],int ipion,char symbole){
	//Formule pour obtenir l'indice de tableau à partir des coordonnées
	//(y-1)*nb+(x-1)
	tab[ipion]=symbole;
}

void alternance(char &cara){
	if(cara=='X'){
		cara='O';
	}else{
		cara='X';
	}
}

bool veriFin(char tab[],int nb){
	for(int i=0;i<nb*nb;i++){
		if(tab[i]=='.'){
			return false;
		}
	}
	return true;
}

void victoire(char tab[],int nb){
	int X=0,O=0;
	for(int i=0;i<nb*nb;i++){
		if(tab[i]=='X'){
			X++;
		}else if(tab[i]=='O'){
			O++;
		}
	}
	if(X<O){
		std::cout<<"Les X ont gagne";
	}else{
		std::cout<<"Les O ont gagne";
	}
}

bool jeuPossible(char tab[],int nb,char symbole){
	bool possible=false;
	for(int i=0;(i<nb*nb)and(possible==false);i++){
		possible=adjacence(tab,nb,i,symbole);
	}
	return possible;
}

int main(){
	//nb est égal au nombre de colonne et de ligne
	//on le met au carré pour optenir le nombre de case
	char currentchar='X';
	int nb=8;
	char tab[nb*nb];
	bool fin=false;
	int ipion,x,y;
	initTab(tab,nb);
	while(fin==false){
		//clear la console
		std::system("cls");
		affichageTab(tab,nb);
		std::cout<<std::endl;
		std::cout<<"Les "<<currentchar<<" jouent, entrez les coordonnees:"<<std::endl;
		std::cin>>x;
		std::cin>>y;
		//pour arreter le programe sans finir la partie
		ipion=(y-1)*nb+(x-1);
		if(jeuPossible(tab,nb,currentchar)){
			if(x>=1 && x<=nb && y>=1 && y<=nb){
			if((adjacence(tab,nb,ipion,currentchar))and(tab[ipion]=='.')){
				ecriture(tab,ipion,currentchar);
				cascade(tab,nb,ipion,currentchar);
				alternance(currentchar);
			}
			}else{
				std::cout<<"coup non valide"<<std::endl;
			}
		}else{
			std::cout<<"aucun coup possible"<<std::endl;
			alternance(currentchar);
			//verifie que l'autre joueur peut jouer,sinon c'est la fin
			if(jeuPossible(tab,nb,currentchar)!=true){
				fin=true;
			}
		}
		fin=veriFin(tab,nb);
		if((x==67)and(y==69)){
			fin=true;
		}
	}
	victoire(tab,nb);
}

