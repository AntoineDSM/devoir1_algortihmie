#pragma once

//Type correspondant aux noeuds de notre arbre et repertoriant les informations nécessaires à son utilisation et à son balayage.
template <typename T>
class Noeud {

public:

	T data;//donnée portée par notre noeud
	Noeud* gauche;//pointe vers le fils de gauche
	Noeud* droite;//pointe vers le fils de droite
	int hauteur;//hauteur du noeud dans l'arbre

	//Constructeur
	Noeud(const T& d, int hauteur) : gauche(0), droite(0), data(d), hauteur(hauteur)
	{
		
		T defaultValue{};//met la valeur par defaut du type renseigné
		
		//alloue l'espace mémoire nécessaire pour nos noeuds et assigne la valeur de leurs données à la valeur par defaut de notre type.
		gauche = (Noeud<T>*) malloc(sizeof(Noeud<T>)); 
		droite = (Noeud<T>*) malloc(sizeof(Noeud<T>));
		gauche->data = defaultValue;
		droite->data = defaultValue;
	}
};
