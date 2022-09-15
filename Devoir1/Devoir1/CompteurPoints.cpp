#include "CompteurPoints.h"

float compteurpoints::CompteurPoints::comptagePaquet(pile::PileDM<carte::Carte> paquet)
{
	float gainsPaquet = 0;
	carte::Carte carteActuelle;
	int taille = paquet.get_taille();


	for (int i = 0; i < taille; i++)
	{
		float multiplicateur;
		carteActuelle = paquet.depiler();
		carteActuelle.couleur == true ? multiplicateur = 1.5 : multiplicateur = 1;
		gainsPaquet += carteActuelle.numero * carteActuelle.bonus * multiplicateur;
	}

	return gainsPaquet;
}
