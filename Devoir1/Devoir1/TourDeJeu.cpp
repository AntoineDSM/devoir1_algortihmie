#include "TourDeJeu.h"

int tourdejeu::TourDeJeu::determinerGagnant()
{
	if (carteJoueur1.numero > carteJoueur2.numero)//joueur 1 gagne
	{
		return 1;
	}
	else if (carteJoueur1.numero == carteJoueur2.numero)
	{
		if (carteJoueur1.couleur == carteJoueur2.couleur)
		{
			//egalite
			return 0;
		}
		else if (carteJoueur1.couleur == true)//joueur 1 gagne
		{
			//rouge
			return 1;
		}
		else if (carteJoueur2.couleur == true)//joueur 2 gagne
		{
			//rouge
			return 2;
		}
	}
	else//joueur 2 gagne
	{
		return 2;
	}
}
