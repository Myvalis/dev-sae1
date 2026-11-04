#include <iostream>
#include <cstdlib>
/*
bool arret=false;
	if(ipion+1!=symbole){
		//verifie toute la ligne à droite du pion, s'arrete à case vide ou à multiple de nb
		for(int i=ipion;(i%nb!=0)and(tab[i]!='.')and(arret==false);i++){
			if(tab[i]==symbole){
				std::cout<<"uk";
				retourneLigne(tab,ipion,i,symbole);
				arret=true;
			}
		}
	}
	arret=false;
	if(ipion-1!=symbole){
		//verifie toute la ligne à gauche du pion, s'arrete à case vide ou à multiple de nb-1
		for(int i=ipion;((i-1)%nb!=0)and(tab[i]!='.')and(arret==false);i--){
			if(tab[i]==symbole){
				std::cout<<"uk";
				retourneLigne(tab,i,ipion,symbole);
				arret=true;
			}
		}
	}
	arret=false;
	if(ipion+8!=symbole){
		for(int i=ipion;(i<=nb*nb)and(tab[i]!='.')and(arret==false);i+=8){
			if(tab[i]==symbole){
				retourneColonne(tab,ipion,i,symbole);
				arret=true;
			}
		}
	}
	arret=false;
	if(ipion-8!=symbole){
		for(int i=ipion;(i<=nb*nb)and(tab[i]!='.')and(arret==false);i-=8){
			if(tab[i]==symbole){
				retourneColonne(tab,i,ipion,symbole);
				arret=true;
			}
		}
	}
	arret=false;
	if(ipion+9!=symbole){
		for(int i=ipion;(i<=nb*nb)and(tab[i]!='.')and(arret==false);i+=9){
			if(tab[i]==symbole){
				retourneDiagonaleGD(tab,ipion,i,symbole);
				arret=true;
			}
		}
	}
	arret=false;
	if(ipion-9!=symbole){
		for(int i=ipion;(i<=nb*nb)and(tab[i]!='.')and(arret==false);i-=9){
			if(tab[i]==symbole){
				retourneDiagonaleGD(tab,i,ipion,symbole);
				arret=true;
			}
		}
	}
	arret=false;
	if(ipion+7!=symbole){
		for(int i=ipion;(i<=nb*nb)and(tab[i]!='.')and(arret==false);i+=7){
			if(tab[i]==symbole){
				std::cout<<"uk";
				retourneDiagonaleDG(tab,ipion,i,symbole);
				arret=true;
			}
		}
	}
	arret=false;
	if(ipion-7!=symbole){
		for(int i=ipion;(i<=nb*nb)and(tab[i]!='.')and(arret==false);i-=7){
			if(tab[i]==symbole){
				retourneDiagonaleDG(tab,i,ipion,symbole);
				arret=true;
			}
		}
	}	*/
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
	if(ipion+1!=symbole){
		//verifie toute la ligne à droite du pion, s'arrete à case vide ou à multiple de nb
		for(int i=ipion;(i%nb!=0)and(tab[i]!='.');i++){
			if(tab[i]==symbole){
				retourneLigne(tab,ipion,i,symbole);
			}
		}
	}
	if(ipion-1!=symbole){
		//verifie toute la ligne à gauche du pion, s'arrete à case vide ou à multiple de nb-1
		for(int i=ipion;((i-1)%nb!=0)and(tab[i]!='.');i--){
			if(tab[i]==symbole){
				retourneLigne(tab,i,ipion,symbole);
			}
		}
	}
	if(ipion+8!=symbole){
		for(int i=ipion;(i<=nb*nb)and(tab[i]!='.');i+=8){
			if(tab[i]==symbole){
				retourneColonne(tab,ipion,i,symbole);
			}
		}
	}
	if(ipion-8!=symbole){
		for(int i=ipion;(i<=nb*nb)and(tab[i]!='.');i-=8){
			if(tab[i]==symbole){
				retourneColonne(tab,i,ipion,symbole);
			}
		}
	}
	if(ipion+9!=symbole){
		for(int i=ipion;(i<=nb*nb)and(tab[i]!='.');i+=9){
			if(tab[i]==symbole){
				retourneDiagonaleGD(tab,ipion,i,symbole);
			}
		}
	}
	if(ipion-9!=symbole){
		for(int i=ipion;(i<=nb*nb)and(tab[i]!='.');i-=9){
			if(tab[i]==symbole){
				retourneDiagonaleGD(tab,i,ipion,symbole);
			}
		}
	}
	if(ipion+7!=symbole){
		for(int i=ipion;(i<=nb*nb)and(tab[i]!='.');i+=7){
			if(tab[i]==symbole){
				retourneDiagonaleDG(tab,ipion,i,symbole);
			}
		}
	}
	if(ipion-7!=symbole){
		for(int i=ipion;(i<=nb*nb)and(tab[i]!='.');i-=7){
			if(tab[i]==symbole){
				retourneDiagonaleDG(tab,i,ipion,symbole);
			}
		}
	}	
}

bool adjacence(char tab[],int nb,int ipion,char symbole){
	//prend en parametre le tableau,sa taille,l'indice du pion et sa couleur
	//retourne si le pion est adjacent à un pion d'une autre couleur
	//verifie toute la ligne à droite du pion, s'arrete à case vide ou à multiple de nb
	for(int i=ipion+1;(i%nb!=0)and(tab[i]!='.');i++){
		if(tab[i]==symbole){
			return true;
		}
	}
	//verifie toute la ligne à gauche du pion, s'arrete à case vide ou à multiple de nb-1
	for(int i=ipion-1;((i-1)%nb!=0)and(tab[i]!='.');i--){
		if(tab[i]==symbole){
			return true;
		}
	}
	for(int i=ipion+8;(i<=nb*nb)and(tab[i]!='.');i+=8){
		if(tab[i]==symbole){
			return true;
		}
	}
	for(int i=ipion-8;(i<=nb*nb)and(tab[i]!='.');i-=8){
		if(tab[i]==symbole){
			return true;
		}
	}
	for(int i=ipion+9;(i<=nb*nb)and(tab[i]!='.');i+=9){
		if(tab[i]==symbole){
			return true;
		}
	}
	for(int i=ipion-9;(i<=nb*nb)and(tab[i]!='.');i-=9){
		if(tab[i]==symbole){
			return true;
		}
	}	
	for(int i=ipion+7;(i<=nb*nb)and(tab[i]!='.');i+=7){
		if(tab[i]==symbole){
			return true;
		}
	}
	for(int i=ipion-7;(i<=nb*nb)and(tab[i]!='.');i-=7){
		if(tab[i]==symbole){
			return true;
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
	for(int i=0;i<=nb*nb;i++){
		if(tab[i]=='.'){
			return false;
		}
	}
	return true;
}

void victoire(char tab[],int nb){
	int X=0,O=0;
	for(int i=0;i<=nb*nb;i++){
		if(tab[i]=='X'){
			X++;
		}else{
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
	for(int i=0;(i<=nb)and(possible==false);i++){
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
		fin=veriFin(tab,nb);
		//clear la console
		//std::system("cls");
		affichageTab(tab,nb);
		std::cout<<std::endl;
		std::cout<<"Les "<<currentchar<<" jouent, entrez les coordonnees:"<<std::endl;
		std::cin>>x;
		std::cin>>y;
		//pour arreter le programe sans finir la partie
		if((x==67)and(y=69)){
			fin=true;
		}
		ipion=(y-1)*nb+(x-1);
		if(jeuPossible){
			if((x<nb)and(y<nb)){
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
		}
	}
	victoire(tab,nb);
}

