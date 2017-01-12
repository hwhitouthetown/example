
#ifndef abr_HPP
#define abr_HPP
#include <string>
// I/O de fichier
#include <deque>
#include "math.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cstddef>



using namespace std;

struct Noeud{
	int val;
	Noeud* sag;//plus grand
	Noeud* sad;//plus petit
};

class Abr{

	public:

		int nbElements;
		Abr();
		Abr(vector<string> values);
		Abr(vector<int> values);
		Noeud* racine; //noeud_arbre vide
		int nb_noeuds; //nb de noeud dans l'arbre

		int profondeur (Noeud* & node);
		bool ajouter(Noeud*& node, int val);
		bool ajouterNoeud(Noeud*& node, Noeud*& nodeToAdd);
		bool supprimer(Noeud*& node, int val);
		void suppriMax(Noeud* &node,int * y);
		void afficher(Noeud* p);
		bool isEquilibre(Noeud* & node);
		bool isRoot(Noeud* c);
		string to_String(Noeud* c);
		bool abrBienRempli(Noeud* c,vector<int> values,bool res,int min,int max);
};

#include "abr.tpp"
#endif // abr_HPP
