#pragma once
#include "Carte.h"

#ifndef TOURDEJEU

#define TOURDEJEU

namespace tourdejeu {

	class TourDeJeu
	{
	public :
		//carte courante du joueur 1
		carte::Carte carteJoueur1;
		//carte courante du joueur 2
		carte::Carte carteJoueur2;
		//si gagnantTour = 1, J1 sinon J2. Si 0 égalité, les joueurs récupère leur carte. Si nous avons un gagnant, il met sa carte dans la pile des gains.
		int gagnantTour;

	public :

		TourDeJeu(carte::Carte carteJ1, carte::Carte carteJ2) : carteJoueur1(carteJ1), carteJoueur2(carteJ2)
		{
			gagnantTour = determinerGagnant();
		}

		//permet de comparer les cartes courantes des deux joueurs et de les comparer
		int determinerGagnant();
	};

}

#endif //TOURDEJEU
