#pragma once

#include <vector>

//Type correspondant aux noeuds de notre arbre et repertoriant les informations nécessaires à son utilisation et à son balayage.
template <typename T>
class NoeudArbreGenealogique {

public:

	T data;//donnée portée par notre noeud
	std::vector<NoeudArbreGenealogique<T>*> enfants;//pointe vers le/les enfants
	std::vector < NoeudArbreGenealogique<T>*> parents;//pointe vers le/les parents, avec deux parents maximum
	int hauteur;//hauteur du noeud dans l'arbre


	//Constructeur par default
	NoeudArbreGenealogique()
	{
		data = T{};
		enfants = std::vector<NoeudArbreGenealogique<T>*>();
		parents = std::vector<NoeudArbreGenealogique<T>*>();
		hauteur = 1;
	}


	//Constructeur
	NoeudArbreGenealogique(const T& d, std::vector<NoeudArbreGenealogique<T>*> _parent = std::vector<NoeudArbreGenealogique<T>*>(), int hauteur = 1) : hauteur(hauteur), enfants(0), data(d)
	{
		if (!_parent.empty())
		{
			parents.push_back(_parent[0]);
			parents.push_back(_parent[1]);
		}
	}


	//Permet de faire de la comparaison sur notre type.
	template <typename T>
	friend bool operator==(const NoeudArbreGenealogique<T>& x, const NoeudArbreGenealogique<T>& y)
	{
		{
			if (x.data == y.data)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

};