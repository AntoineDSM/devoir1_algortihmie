#pragma once
#include <random>

#ifndef CARTE

#define CARTE

namespace carte {

	class Carte
	{
	public:

		//le numero allant de 1 à 10
		int numero;
		//la couleur étant rouge ou noire, true = rouge, false = noire
		bool couleur;
		//le bonus est la puissance de la carte, puissance affectee a son numero. Entre 1 et 4
		int bonus;

	public:

		//constructeur par defaut
		Carte() : numero(0), couleur(false), bonus(0)
		{
		}

		//constructeur avec paramètres
		Carte(int numero, bool couleur, int bonus) : numero(numero), couleur(couleur), bonus(bonus)
		{
		}

	};

}//namespace carte


#endif //CARTE
