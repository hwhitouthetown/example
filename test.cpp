#include <iostream>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>

using namespace std;



struct Interval{
	int valmin;
	int valmax;
};


vector<Interval> generateInter(int m,int n);
void afficher_inter(Interval inter);
void afficher_vecteur(vector<Interval> inter);
int rando(int min,int max);

int main ()
{
  
	afficher_vecteur(generateInter(30,10));


return 0;
}

vector<Interval> generateInter(int m,int n){

	vector<Interval> intervalles; 

	Interval inter; 
	int borne_min=1;
	int borne_max=m;
	int i = 0;

	srand(time(NULL)); // initialisation de rand

	for(int i=0;i<n-1;i++){

	borne_max = rando(borne_min,(borne_max/n)*(1+i));

	inter.valmin = borne_min; 
	inter.valmax = borne_max;

	if(borne_max < m-5){
		int a = borne_max + rando(0,5);
		borne_max = a;
	}

	borne_min = borne_max;
	borne_max = m;
	
	intervalles.push_back(inter);// ajout intervalle dans le vector //

	}

	// POur le dernier intervalle // 

	inter.valmin = inter.valmax; 

	inter.valmax = m;

	intervalles.push_back(inter);

	return intervalles;
}

void afficher_vecteur(vector<Interval> inter){


for(int i=0;i<inter.size();i++)
{
	afficher_inter(inter.at(i));
}

}


 void afficher_inter(Interval inter){
	cout << "Interval : " << inter.valmin << ";" << inter.valmax << endl;
}


int rando(int min,int max){

	return rand()%(max-min) + min;
}