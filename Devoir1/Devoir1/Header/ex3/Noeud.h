#pragma once

template <typename T>
class Noeud {

public:

	T data;//donn�e port�e par notre noeud
	Noeud* gauche;//pointe vers le fils de gauche
	Noeud* droite;//pointe vers le fils de droite
	int card;// ?
	int hauteur;//hauteur du noeud dans l'arbre

	//Constructeur
	Noeud(const T& d, int hauteur) : gauche(0), droite(0), data(d), hauteur(hauteur)
	{
		
		T defaultValue{};//met la valeur par defaut du type renseign�
		
		//alloue l'espace m�moire n�cessaire pour nos noeuds
		gauche = (Noeud<T>*) malloc(sizeof(Noeud<T>)); 
		droite = (Noeud<T>*) malloc(sizeof(Noeud<T>));
		gauche->data = defaultValue;
		droite->data = defaultValue;
	}
};
