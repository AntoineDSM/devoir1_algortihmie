#pragma once
#include <string>
#include "Carte.h"
#include <list>
#include <vector>

class Joueur
{
	public : 

		//nom du joueur
		std::string nomJoueur;
		//index du joueur, 1 ou 2
		int index;
		//total de cartes dans la main
		int total;
		//paquet de carte
		std::vector<Carte> paquet;
		//pile de gain
		std::vector<Carte> gains;


	public :

		//construteur par d�faut
		Joueur() : nomJoueur(""), index(0), total(0)
		{
			//rien de plus � ajouter ici
		}


		Joueur(const std::string nomJoueur, const int index, const int total) : nomJoueur(nomJoueur), index(index), total(total), paquet(total)
		{
			//rien de plus � ajouter ici
		}
};

