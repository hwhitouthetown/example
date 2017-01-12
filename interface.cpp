#include <iostream>
#include "aabri.hpp"
#include <vector>
#include <string>

using namespace std;

void aabri_to_abr(Aabri aabri){
	Arbre out_abr =  aabri.aabri_to_abr();
	cout << "Aperçu du résultat:" << endl << out_abr.to_String() << endl;
}

Aabri aabri_fichier(){
	Aabri a("fichier.txt");
	return a;
}

int main(){
	Aabri aabri;
	string nom;
	int val,p,q;
	int choix=1;
	while (choix != 0){
		cout << endl << "Que souhaitez vous faire ?" << endl;
		cout << "1 - Charger le fichier vers un TABR" << endl;
		cout << "0 - Quitter" << endl;
		cin >> choix;
	
		switch (choix) {
		case 1:
			aabri_to_abr(aabri);
			break;
		default:
			// Code
			break;
		}
	}
	return 0;
}

