#include <iostream>
#include "..\..\Header\ex5\Noeud.h"
#include "..\..\Header\ex5\Liste.h"

using namespace std;
using namespace noeud;
using namespace liste;

int main()
{

	Liste<int> l = Liste<int>();

	l.ajouterTete(5);
	l.ajouterTete(3);
	l.ajouterTete(2);
	l.ajouterTete(9);
	l.ajouterTete(4);
	l.ajouterTete(6);
	l.ajouterTete(1);
	l.ajouterTete(8);
	l.ajouterTete(0);
	l.ajouterTete(7);
	l.ajouterQueue(2);

	Noeud<int>* head = l.getTete();
	Noeud<int>* tail = l.getQueue();
	Noeud<int>* middle = head->getSuivant();

	int total1 = head->somme();
	int total2 = tail->somme();
	int total3 = middle->somme();
	cout << "Somme des ID en partant de la tete de liste: " << total1 << endl;
	cout << "Somme des ID en partant de la queue de liste: " << total2 << endl;
	cout << "Somme des ID en partant d'une element quelconque de la liste: " << total3 << endl;
	return 0;
}