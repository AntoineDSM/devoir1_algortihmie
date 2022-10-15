#pragma once
#include <string>
#include <list>
#include <vector>

#include "Carte.h"
#include "PileDM.h"

#ifndef JOUEUR

#define JOUEUR

namespace joueur {

	class Joueur
	{
	public:

		//nom du joueur
		std::string nomJoueur;
		//index du joueur, 1 ou 2
		int index;
		//total de cartes dans la main
		int total;
		//paquet de carte
		pile::PileDM<carte::Carte> paquet;
		//pile de gain
		pile::PileDM<carte::Carte> gains;


	public:

		//construteur par défaut
		Joueur() : nomJoueur(""), index(0), total(0), paquet(0), gains(0)
		{
			//rien de plus à ajouter ici
		}
		
		//constructeur avec parametres
		Joueur(std::string nomJoueur, int index, int total) : nomJoueur(nomJoueur), index(index), total(total)
		{
			paquet = pile::PileDM<carte::Carte>();
			gains = pile::PileDM<carte::Carte>();
		}
	};

}//namespace joueur


#endif //JOUEUR