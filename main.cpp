#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "tabr.hpp"

using namespace std;


bool is_file_exist(string file){
    std::ifstream infile(file.c_str());
    return infile.good();
}

int main(){
	Tabr tabr("anticonstitutionnellement_pas.txt");
	string nom, c, v;
	string folderName;
	int val,p,q;
	int choix=1;
	// Pour générer un arbre // 
	int max,nbInter,nbNoeud;

	while (choix != 0){
		cout << " ----------------------- MENU --------------------------"  << endl;
		cout << "|1  - Afficher TABR en mode simple (parcours suffixe)   |" << endl;
		cout << "|2  - Charger un TABR depuis un fichier                 |" << endl;
		cout << "|3  - Afficher TABR en mode graphique (parcours suffixe)|" << endl;
		cout << "|4  - Exporter TABR dans un fichier                     |" << endl;
		cout << "|5  - Générer TABR                                      |" << endl;
		cout << "|6  - Ajouter une valeur au TABR                        |" << endl;
		cout << "|7  - Supprimer une valeur au TABR                      |" << endl;
		cout << "|8  - Vérifier si TABR est bien rempli                  |" << endl; 
		cout << "|9  - Fusion de deux cases du TABR                      |" << endl;
		cout << "|10 - Equilibre en profondeur d'un ABR                  |" << endl; 
		cout << "|11 - ABR vers TABR                                     |" << endl;
		cout << "|12 - TABR vers ABR                                     |" << endl;
		cout << "|  ---------------------                                |" << endl;
		cout << "|0  - Quitter                                           |" << endl;
		cout << " -------------------------------------------------------"  << endl;


		cin >> choix;
		switch (choix) {
		case 0: 
			cout << "Merci et à bientôt !" << endl;
			break; 

		case 1:
			tabr.afficher_tabr();
			break;
		case 2:
			cout << "Entrez le nom du fichier d'import: " << endl;
			cin >> nom; 
			nom +=  ".txt";
			if(is_file_exist(nom)){
				Tabr tabgenerate(nom);
				tabr = tabgenerate;
			}else{
				cout << "Ce fichier n'existe pas" << endl;
			}
			break;
		case 3:
			tabr.afficher_tabr_graphique();
			break;
		case 4:
			cout << "Entrez le nom du fichier d'export: " << endl;
			cin >> nom;
			nom += ".txt";
			if(is_file_exist(nom)){
				cout << "Attention ce fichier existe, voulez vous l'écraser? (o pour oui, n pour non) " << endl;
				cin >> c;
				if(c == "o"){
					tabr.export_tabr(nom);
				}else{
					cout << "Abandon sauvegarde" << endl;
					break;
				}
			}else{
				tabr.export_tabr(nom);
			}
			cout << "Création du fichier : " << nom  << endl;
			break;
		case 5:
			{ 
				cout << "Saisir la valeur maximum de l'intervalle max du TABR"<< endl;	 
				cin >> max; 

				cout << "Saisir le nombre d'intervalle"<< endl;	 
				cin >> nbInter; 

				cout << "Saisir le nombre de noeud à générer par arbre"<< endl;	 
				cin >> nbNoeud; 

				Tabr tabgenerate(max,nbInter,nbNoeud);
				tabr = tabgenerate;

				cout << "Tabr généré avec succés, félicitation"<< endl;
			}	
			break;
		case 6:
			{
				cout << "Saisir la valeur à ajouter"<< endl;	 
				cin >> val; 
				if (cin.fail()) {
				    cout << "Saisir un entier"<< endl;
				}else{
					if(tabr.addToTabr(val)){
						cout << "Valeur ajoutée avec succés, félicitation."<< endl;
					}
				}
				break;
			}
		case 7:
			{
				cout << "Saisir la valeur à supprimer"<< endl;	 
				cin >> val; 
				if (cin.fail()) {
				    cout << "Saisir un entier"<< endl;
				}else{
					if(tabr.delToTabr(val)){
						cout << "Valeur supprimée avec succés."<< endl;
					} else {
						cout << "Valeur non trouvée dans le TABR "<< endl;
					}
				}
				break;
			}	
		case 8:	
			{
				bool verif = false;
				cout << "Vérification "<< endl;	 		

				verif = tabr.tabrBienRempli();

				if(verif){
					cout << "TABR est conforme" << endl;
				} else {
					cout << "Le TABR est mal rempli";
				}	
			}
			break;	
		case 9:	
			{
				int indice1; 
				bool verif = false;
				cout << "Fusion cases TABR "<< endl;	 		

				tabr.afficher_tabr();
				cout << "Saisir le numero de la première case du TABR à fusioner "<< endl;	 		
				cin >> indice1; 
				if (cin.fail()) {
				    cout << "Saisir un entier"<< endl;
				}else if(indice1 < 1 || (indice1+1) > tabr.tabr.size()){
					cout << "Le numero de la case doit être supérieur à 0 et strictement inférieur au nombre de case du TABR" << endl;
				} else {
					tabr.fusion(indice1-1);
				}
					
				
			}
			break;
		case 10:	
			{
				int indice;
				tabr.afficher_tabr();
				cout << "Saisir le numero de la case du TABR correspondant à l'ABR à tester"<< endl;	
					cin >> indice;  	
				if (cin.fail()) {
				    cout << "Saisir un entier"<< endl;
				}else{ 
					if(indice < 1 || indice > tabr.tabr.size()){
						cout << "Merci de saisir un entier entre 1 et "<< tabr.tabr.size() << endl;
					} else {
						indice--;
						if(tabr.isEquilibreAbr(indice)){
							cout << "Abr à la case :"<< indice+1 <<" est équilibré" << endl;
						} else {
							cout << "Abr à la case :"<< indice+1 <<"n'est pas équilibré" << endl;
						}
					}
				}
			}
			break;
		case 11:	
			{
				int saisie = 1; 
				
				cout << "Transformation d'un Abr en TABR" << endl;
				cout << "Merci de saisir votre Abr valeur par valeur en respectant son parcours suffixe entrer 0 quand vous aurez terminé " << endl;

				vector<int> values;

				int max = numeric_limits<int>::min(); // min val
				int min = numeric_limits<int>::max(); // max val 

				while (saisie !=0){
					cout << "Merci de saisir une valeur strictement positive ou bien entrer 0 si vous avez terminé" << endl;
					cin >> saisie; 

					if (cin.fail()||saisie < 0) {
				    	cout << "Erreur "<< endl;
				    	saisie = -1;
				    	cin.clear();
				    	cin.ignore(10000,'\n');
					} 
					
					if(saisie > 0){
						// mise à jour de la valeur minimale //
						if(saisie > max){
							max = saisie;
						}  
						if (saisie < min){
							min = saisie;
						}
						values.push_back(saisie);
					}
					
				}
				// on construit l'ABR // 
				Abr abr(values); 
				cout << "Voici l'ABR que vous avez saisi (parcours suffixe) : ";
				abr.afficher(abr.racine); 
				cout << "" << endl;
				cout << "Contenant "<< abr.nbElements <<" élément(s) distinct(s)" << endl;
				cout << "valeur min" << min << endl; 
				cout << "valeur max" << max << endl;

				// On le convertit en TABR 
				Tabr convert(Tabr(values, min, max));

				tabr = convert;

				cout << "Afficher graphiquement"<< endl;
				tabr.afficher_tabr();

			}
			break;					
		case 12:	
			{
				cout << "transformation du TABR actuel en Abr" << endl;
				
				Tabr copy = tabr;

				copy.afficher_tabr();

				Abr abr = copy.tabrToAbr();

				abr.afficher(abr.racine);
			}
			break;					


		default:
			cout << "Merci de re-saisir choix incorrect" << endl;
			break;
		}
	}
	return 0;
}
