
#ifndef abrprinter_HPP
#define abrprinter_HPP
#include <string>
// I/O de fichier
#include <deque>
#include "math.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class AbrPrinter{

	public:
		AbrPrinter();
		void printPretty(Noeud *root, int level, int indentSpace, ostream& out);
		void printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<Noeud*>& nodesQueue, ostream& out);
		void printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<Noeud*>& nodesQueue, ostream& out);
		void printLeaves(int indentSpace, int level, int nodesInThisLevel, const deque<Noeud*>& nodesQueue, ostream& out);
		int maxHeight(Noeud *p);
		string intToString(int val);
};

#include "abrprinter.tpp"
#endif // abrprinter_HPP
