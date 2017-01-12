

#include "tabr.hpp"
#include <string>
#include <sstream>
#include <vector>
#include <time.h>  
#include "tabr.hpp"
#include "abrprinter.hpp"
using namespace std;
//créer un abr vide


Tabr::Tabr(string file){
	ifstream fichier(file.c_str(), ios::in);
	vector<string> vligne;
	vector<string> vinterval;
	vector<string> vvalues;
	if(fichier)
	{
		string ligne;
		while(getline(fichier, ligne))  
		{
			vligne = splitVector(ligne, ';');
			vinterval = splitVector(vligne[0], ':');
			vvalues = splitVector(vligne[1], ':');
			remplirCaseString(vinterval, vvalues);
		    vligne.clear();
		    vinterval.clear();
		    vvalues.clear();
		}
		fichier.close();
		cout << "Tabr généré avec succés, félicitation." << endl;
	}
	else{
		cerr << "Impossible d'ouvrir le fichier !" << endl;
	}
}


Tabr::Tabr(int m,int n,int nbNoeud){
	vector<Interval> intervalles = generateInter(1,m,n);
	afficher_vector_intervalles(intervalles);
	for(int i=0;i<intervalles.size();i++)
	{
		vector<int> values;
		Case c;
		c.interval = intervalles.at(i);	
		c.abr = multiple_random(c.interval.valmin,c.interval.valmax,nbNoeud);
		tabr.push_back(c);
	}
}


Tabr::Tabr(vector<int> values, int min, int max){

	// Déterminer k, le nombre d'intervales // 

	int nbElements = values.size();
	int k = 0;

	k = nbElements / 10 + 1;

	vector<Interval> intervalles = generateInter(min,max,k);
	afficher_vector_intervalles(intervalles);

	for(int i=0;i<intervalles.size();i++)
	{
		Case c;
		c.interval = intervalles.at(i);	
		Abr abr;
		c.abr = abr;
		tabr.push_back(c);
	}




	for(int i=0;i<values.size();i++){
		bool trouve = false;
		int val = values.at(i);

		addToTabr(val);
	}



}


bool Tabr::appartientInterval(Interval inter, int val){

	return (val>=inter.valmin && inter.valmax >= val);

}


bool Tabr::isEquilibreAbr(int indice){

	Abr abrAtester = tabr.at(indice).abr;

	return(abrAtester.isEquilibre(abrAtester.racine));

}


Abr Tabr::tabrToAbr(){

	while(tabr.size()>1){
		fusion(0);
	}

	Abr abr = tabr.at(0).abr; 

	return abr;
}


void Tabr::fusion(int indice){

	Case cMin = tabr.at(indice); 
	Case cMax = tabr.at(indice+1); 

	if(cMin.abr.nbElements>cMax.abr.nbElements){
		// On ajoute l'arbre min dans l'arbre max //
		cMax.abr.ajouterNoeud(cMax.abr.racine,cMin.abr.racine);
		tabr.at(indice+1).interval.valmax = cMax.interval.valmax;

		// Arbres fusionnés il ne reste plus qu'a décaler //
		for(int i=indice+1;i<tabr.size();i++){
			tabr.at(i-1) = tabr.at(i);
		}
	} else {
		// On ajoute l'arbre max dans l'arbre min //
		cMin.abr.ajouterNoeud(cMin.abr.racine,cMax.abr.racine);
		tabr.at(indice).interval.valmax = cMax.interval.valmax;

		// Arbres fusionnés il ne reste plus qu'a décaler //
		for(int i=indice+1;i<tabr.size()-1;i++){
			tabr.at(i) = tabr.at(i+1);
		}
	}

	// On supprime le dernier élément //
	tabr.pop_back();

}


void Tabr::remplirCase(vector<Interval> intervals,vector<int> values){




}


bool Tabr::tabrBienRempli(){

	bool res = true; 
	// vérifications des intervalles // 
	int nbIntervalles = tabr.size();
	int i=0;
/*
(a) Ilssontbiendéfinis:pourtouti,T[i].debut≤T[i].fin;
(b) Ils sont tous disjoints : deux intervalles différents n’ont aucun élément en commun ;
(c) Ils sont ordonnés par ordre croissant : pour tout i (sauf le dernier), T [i].f in < T [i + 1].debut.
*/
	while(i<nbIntervalles&&res){

		int valmin = tabr.at(i).interval.valmin;
		int valmax = tabr.at(i).interval.valmax;

		if(valmin > valmax){
			res = false; 
		}

		if(i!=nbIntervalles-1){
			res = tabr.at(i).interval.valmax <= tabr.at(i+1).interval.valmin;
			
			if(!res){
				cout << "Problème avec : ";
				afficher_inter(tabr.at(i).interval);
				cout << "et : ";
				afficher_inter(tabr.at(i+1).interval);
				cout << "elles se chevauchent ! " << endl;
			}
			
		}

		vector<int> values;
		Abr abr = tabr.at(i).abr;
		res = abr.abrBienRempli(abr.racine,values,res,valmin,valmax);
		i++;
	}


	return res; 
}


void Tabr::remplirCaseString(vector<string> intervals,vector<string> values){

	Case c ;
	Interval i;

	i.valmin = stoi(intervals[0]);
	i.valmax = stoi(intervals[1]);
	Abr abr(values);

	c.interval = i; 
	c.abr = abr;

	tabr.push_back(c);
}

void Tabr::afficher_tabr(){
	for (int i=0; i<tabr.size();i++){
		cout << "Interval : " << tabr[i].interval.valmin << ";" << tabr[i].interval.valmax << ":";
		tabr[i].abr.afficher(tabr[i].abr.racine);
		cout << endl;
	}
}

bool Tabr::addToTabr(int my_val){
	bool res = false;
	bool foundInter = false;
	for (int i=0; i<tabr.size();i++){
		
		if(tabr[i].interval.valmin <= my_val &&  my_val <= tabr[i].interval.valmax){
			foundInter = true;
			res = tabr[i].abr.ajouter(tabr[i].abr.racine, my_val);
			cout << "La valeur " << my_val << " a bien été ajouté dans le TABR" << endl;
		}
	}
	if(!foundInter){
		cout << "La valeur" << my_val << " ne correspond à aucun interval" << endl;
	}
	return res;
}


bool Tabr::delToTabr(int my_val){
	bool res = false;
	bool foundInter = false;
	for (int i=0; i<tabr.size();i++){
		if(tabr[i].interval.valmin <= my_val &&  my_val <= tabr[i].interval.valmax){
			foundInter = true;
			res = tabr[i].abr.supprimer(tabr[i].abr.racine, my_val);
		}
	}
	if(!foundInter){
		cout << "La valeur" << my_val << " ne correspond à aucun interval" << endl;
	}
	return res;
}	

string Tabr::to_String(){
	string res = "";
	for (int i=0; i<tabr.size();i++){
		res += to_string(tabr[i].interval.valmin) + ":" + to_string(tabr[i].interval.valmax) + ";" + tabr[i].abr.to_String(tabr[i].abr.racine) + "\n";
	}
	return res;
}

void Tabr::afficher_tabr_graphique(){
	AbrPrinter ap;
	for (int i=0; i<tabr.size();i++){
		cout << "Interval : " << to_string(tabr[i].interval.valmin) << ";" << to_string(tabr[i].interval.valmax) << endl;
		ap.printPretty(tabr[i].abr.racine, 1, 0, cout);
	}
}

//Exporte un Tabr dans un fichier texte dont le chemin est passé en paramètre
void Tabr::export_tabr(string path){
  	ofstream myfile;
  	myfile.open (path.c_str());
  	myfile << to_String();
  	myfile.close();	
}

void Tabr::split(const string &s, char delim, vector<string> &elems) {
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

vector<string> Tabr::splitVector(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;

}
// m valeur interval max 
vector<Interval> Tabr::generateInter(int min,int max,int n){

	vector<Interval> intervalles; 

	Interval inter; 
	int borne_min=min;
	int borne_max=max;
	int i = 0;

	srand(time(NULL)); // initialisation de rand

	for(int i=0;i<n-1;i++){

	borne_max = random(borne_min,(borne_max/n)*(1+i) + n);

	inter.valmin = borne_min; 
	inter.valmax = borne_max;

	if(borne_max < max-6){
		int a = borne_max + random(1,5);
		cout << "Sorti Random" << endl;
		borne_max = a;
	}

	borne_min = borne_max + 1;
	borne_max = max;
	
	intervalles.push_back(inter);// ajout intervalle dans le vector //

	}

	// POur le dernier intervalle // 

	inter.valmin = inter.valmax + 1; 

	inter.valmax = max;

	intervalles.push_back(inter);

	return intervalles;
}

void Tabr::afficher_vector_string (const vector<string>& v){
  for (int i=0; i<v.size();i++){
    cout << v[i] << endl;
  }
}

void Tabr::afficher_vector_int(const vector<int>& v){
  for (int i=0; i<v.size();i++){
    cout << v[i] << endl;
  }
}


void Tabr::afficher_vector_intervalles(vector<Interval> inter){


for(int i=0;i<inter.size();i++)
{
	afficher_inter(inter.at(i));
}

}


void Tabr::afficher_inter(Interval inter){
	cout << "Interval : " << inter.valmin << ";" << inter.valmax << endl;
}


int Tabr::random(int min,int max){
	cout << "Dans Random" << endl;
	cout << "Max random :" << max << endl;
	cout << "Min random :" << min << endl;

	int random_variable = rand();
	return random_variable %(max-min) + min;
}

Abr Tabr::multiple_random(int min,int max,int nb){

	Abr abr;

	int diff = max - min;
	if(nb > diff){
		nb = diff;
	}

	for(int i=0;i<nb;i++){

		int val = random(min,max+1);
		if(!abr.ajouter(abr.racine,val)){
			i--;
		}
	}

	// Dans le cas ou on l'on a un max = min //
	if(nb == 0){
		abr.ajouter(abr.racine,min);
	}

	return abr;
}