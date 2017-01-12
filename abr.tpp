#include "abr.hpp"
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>
#include <deque>
#include <iomanip>
#include <algorithm>

using namespace std;
//créer un abr vide
Abr::Abr(){
	racine = NULL;
	nbElements = 0;
}

Abr::Abr(vector<string> v){
	racine = NULL;
	nbElements = 0;
  	for (int i = v.size() - 1; i >= 0 ;i--){
    	ajouter(racine, stoi(v[i]));
  	}
}

Abr::Abr(vector<int> v){
	racine = NULL;

  	for (int i = v.size() - 1; i >= 0 ;i--){
    	ajouter(racine, v[i]);
  	}
}

//Permet d'ajouter x dans l'arbre
bool Abr::ajouter(Noeud* &node, int val){
	bool res = true;
	if(node == NULL){
		nbElements ++;
		node = new Noeud;
		node->val = val;
		node->sad = NULL;
		node->sag = NULL;
	}
	else{
		//si la valeur à inserer est inférieur à celle du noeud acutel
		if(val < node->val){
			res = ajouter(node->sag, val);
		}
		else if(val > node->val){
			res = ajouter(node->sad, val);
		}else{
			res = false;
			cout << "La valeur : " << val << " existe déjà, skipping.." << endl;
		}
	}
	return res;
}


bool Abr::ajouterNoeud(Noeud*& node, Noeud*& nodeToAdd){
		bool res = true;
		int val = nodeToAdd->val;

	if(node == NULL){
		nbElements ++;
		node = nodeToAdd;
	}
	else{
		//si la valeur à inserer est inférieur à celle du noeud acutel
		if(val < node->val){
			res = ajouterNoeud(node->sag, nodeToAdd);
		}
		else if(val > node->val){
			res = ajouterNoeud(node->sad, nodeToAdd);
		}else{
			res = false;
			cout << "La valeur : " << val << " existe déjà, skipping.." << endl;
		}
	}
	return res;




}


bool Abr::isEquilibre(Noeud* & node){

	// On va calculer pour chaque noeud son équilibre soit la différence de profondeur de son fils droit //
	// et de son fils gauche // 
	bool res = true;

	if(node !=NULL){

		int profondeurgauche = profondeur(node->sag); 
		int profondeurdroite = profondeur(node->sad);
		int deseq = profondeurgauche - profondeurdroite;
		if(deseq< -1 || deseq > 1){
			res = false; 
			cout << "Abr non équilibré pour le noeud ayant comme valeur :" << node->val << endl;
			cout << "profondeur fils de droite = " << profondeurdroite << endl;
			cout << "profondeur fils de gauche = " << profondeurgauche << endl;
			cout << "Déséquilibre = " << deseq << endl; 

		} else {
			res = isEquilibre(node->sad); 
			res = isEquilibre(node->sag);
		}
	}
	return res;
}

int Abr::profondeur (Noeud* & node){


	if (node != NULL){
		return 1 + max( profondeur(node->sag), profondeur(node->sad));
	}
	else {
		return 0;
	}
		
}

void Abr::suppriMax(Noeud* &	node,int * y){

	if(node->sad==NULL){
		 *y = node->val;
		 node = node->sag;
	} else {
		suppriMax(node->sad,y); 
	}
}

//Permet d'ajouter x dans l'arbre
bool Abr::supprimer(Noeud* &node,int val){
	bool res = false;

	if(node!=NULL){
		//si la valeur à inserer est inférieur à celle du noeud acutel
		if(val < node->val){
			res = supprimer(node->sag, val);
		}
		else if(val > node->val){
			res = supprimer(node->sad, val);
		}else{

			if(node->sag == NULL){
				node = node->sad;
				res = true;
				cout << "La valeur : " << val << " a été supprimée" << endl;	
				nbElements --;			
			} else if(node->sad == NULL){
				node = node->sag;
				res = true;
				cout << "La valeur : " << val << " a été supprimée" << endl;
				nbElements --;
			} else {
				int y;
				suppriMax(node->sag,&y);
				cout << "Fin suppriMax" << endl;
				node->val = y;
				cout << "La valeur : " << val << " a été supprimée" << endl;
				res = true;
				nbElements --;
			}
		}
	}	
	return res;
}


void Abr::afficher(Noeud* c)
{
    if (c != NULL)
    {
        cout << to_String(c);
    } 
}

bool Abr::isRoot(Noeud* c){
	bool res = false;
	if(c->val == racine->val){
		res = true;
	}
	return res;
}

bool Abr::abrBienRempli(Noeud* c,vector<int> values,bool res,int min,int max){


	if(res && c!=NULL){

		int val = c->val;

		if(find(values.begin(), values.end(), val) != values.end()){
			cout << "Element déjà présent dans l'ABR";
			res = false; 
		} else {

			if(val>= min && val<= max){

				values.push_back(val);

				return abrBienRempli(c->sad,values,res,min,max);
				return abrBienRempli(c->sag,values,res,min,max);
			} else {
				cout << "Element " << val <<" sort des bornes [" << min <<";"<< max <<"]";

				res =false; 
			}
		}

		return res; 
	} else {
		return res; 
	}
}


string Abr::to_String(Noeud* c){
	string res = "";
    if (c != NULL)
    { 
        res = to_String(c->sag);
        res += to_String(c->sad);
        res += to_string(c->val) +( isRoot(c) == false ? ":" : "" );
    }
    return res;
}

