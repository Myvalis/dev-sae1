#include <iostream>
#include <cstdlib>

void initTab(char tab[],int nb){
	for(int i=0;i<=nb*nb;i++){
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
			std::cout<<(i/8+1)<<' ';
		}
		std::cout<<tab[i]<<' ';
	}
}

void retourneLigne(char tab[],int nb,int idep,int ifin,char symbole){
	for(int i=idep;i<=ifin;i++){
		tab[i]=symbole;
	}
}

void retourneColonne(char tab[],int nb,int idep,int ifin,char symbole){
	for(int i=idep;i<=ifin;i+=8){
		tab[i]=symbole;
	}
}

void cascade(char tab[],int nb,int ipion,char symbole){
	//prend en parametre le tableau,sa taille et l'indice et le symbole du dernier pion joué
	//et retourne les cases à retourner
	for(int i=ipion;(i%nb!=0)and(tab[i]!='.');i++){
		if(tab[i]==symbole){
			retourneLigne(tab,nb,ipion,i,symbole);
		}
	}
	for(int i=ipion;((i-1)%nb!=0)and(tab[i]!='.');i--){
		if(tab[i]==symbole){
			retourneLigne(tab,nb,i,ipion,symbole);
		}
	}
	for(int i=ipion;(i<=nb*nb)and(tab[i]!='.');i+=8){
		if(tab[i]==symbole){
			retourneColonne(tab,nb,ipion,i,symbole);
		}
	}
	for(int i=ipion;(i<=nb*nb)and(tab[i]!='.');i-=8){
		if(tab[i]==symbole){
			retourneColonne(tab,nb,i,ipion,symbole);
		}
	}			
}

int adjacence(char tab[],int nb,int ipion,char symbole){
	//prend en parametre le tableau,sa taille,l'indice du pion et sa couleur
	//retourne si le pion est adjacent à un pion d'une autre couleur
	if(symbole=='X'){
		if(tab[ipion+1]=='O'){
			return ipion+1;
		}
		if(tab[ipion-1]=='O'){
			return ipion-1;
		}
		if(tab[ipion-nb]=='O'){
			return ipion-nb;
		}
		if(tab[ipion+nb]=='O'){
			return ipion+nb;
		}
	}
	if(symbole=='O'){
		if(tab[ipion+1]=='X'){
			return ipion+1;
		}
		if(tab[ipion-1]=='X'){
			return ipion-1;
		}
		if(tab[ipion-nb]=='X'){
			return ipion-nb;
		}
		if(tab[ipion+nb]=='X'){
			return ipion+nb;
		}
	}
/*  if(symbole=='O'){
		if((tab[ipion+1]=='X')or(tab[ipion-1]=='X')or(tab[ipion-nb]=='X')or(tab[ipion+nb]=='X')){
			return true;
		}
	}
*/
	return 0;
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

int main(){
	//nb est égal au nombre de colonne et de ligne
	//on le met au carré pour optenir le nombre de case
	char currentchar='X';
	int nb=8;
	char tab[nb*nb];
	bool jeu=true;
	int ipion,x,y;
	initTab(tab,nb);
	while(jeu){
		std::system("cls");
		affichageTab(tab,nb);
		std::cout<<std::endl;
		std::cout<<"Entrez les coordonnees:"<<std::endl;
		std::cin>>x;
		std::cin>>y;
		ipion=(y-1)*nb+(x-1);
		if((x==67)and(y=69)){
			jeu=false;
		}
		if((x<nb)and(y<nb)){
			if((adjacence(tab,nb,ipion,currentchar))){
				ecriture(tab,ipion,currentchar);
				cascade(tab,nb,ipion,currentchar);
				alternance(currentchar);
			}
		}else{
			std::cout<<"coordonnees non comprise dans le tableau"<<std::endl;
		}
	}
}

