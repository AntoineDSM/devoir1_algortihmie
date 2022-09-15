#include "GameMaster.h"


void GameMaster::creationJoueur(std::string nomJoueur1, std::string nomJoueur2)
{
	joueurs[0] = joueur::Joueur(nomJoueur1, 1, nombreCarteTirage);
	joueurs[1] = joueur::Joueur(nomJoueur2, 2, nombreCarteTirage);
}

void GameMaster::tirageCartes(int nombreCarteVoulu)
{
	int nombreCartesDistribution = 2 * nombreCarteVoulu;

	for (int i = 0; i < nombreCartesDistribution; i++)
	{
		int randNumeroCarteCourante = rand() % (0 - nombreCartesDistribution + 1) + 0;
		if (i % 2 == 0)
		{
			joueurs[0].paquet.empiler(paquetGlobal.depiler());
		}
		else
		{
			joueurs[1].paquet.empiler(paquetGlobal.depiler());
		}
	}
}

void GameMaster::generationPaquet()
{
	//generation des 100 cartes dans une liste
	for (int i = 0; i < 100; i++)
	{
		paquetGlobal.empiler(GenerationCarte());
	}
}

void GameMaster::determinerGagnant()
{
	compteurpoints::CompteurPoints monCompteur(joueurs[0].gains, joueurs[1].gains);

	if (monCompteur.gainsJ1 > monCompteur.gainsJ2)
	{
		//gagnant Joueur1
		std::cout << "\n" << joueurs[0].nomJoueur <<" a gagne la partie avec " << monCompteur.gainsJ1 << " points contre " << monCompteur.gainsJ2 << " points pour " << joueurs[1].nomJoueur << "\n";
	}
	else if (monCompteur.gainsJ1 == monCompteur.gainsJ2)
	{
		//egalité
		std::cout << "\nLes deux joueurs ont fait egalite avec " << monCompteur.gainsJ1 << " points.\n";
	}
	else
	{
		//gagnant Joueur2
		std::cout << "\n" << joueurs[1].nomJoueur << " a gagne la partie avec " << monCompteur.gainsJ2 << " points contre " << monCompteur.gainsJ1 << " points pour " << joueurs[0].nomJoueur << "\n";
	}
}

void GameMaster::executionPartie()
{
	carte::Carte carteTourJ1;
	carte::Carte carteTourJ2;

	for (int i = 0; i < nombreCarteTirage; i++)
	{
		carteTourJ1 = joueurs[0].paquet.depiler();
		carteTourJ2 = joueurs[1].paquet.depiler();

		tourdejeu::TourDeJeu tourCourant = tourdejeu::TourDeJeu(carteTourJ1, carteTourJ2);

		if (tourCourant.gagnantTour == 0)
		{
			//chaque joueur recupère sa carte dans sa pile de gain ? sinon égalité a chaque tour si nous metttons  a derniere position en cas d'égalité
			joueurs[0].gains.empiler(carteTourJ1);
			joueurs[1].gains.empiler(carteTourJ2);
		}
		else if (tourCourant.gagnantTour == 1)
		{
			joueurs[0].gains.empiler(carteTourJ1);
		}
		else if (tourCourant.gagnantTour == 2)
		{
			joueurs[1].gains.empiler(carteTourJ2);
		}
	}
}

carte::Carte GameMaster::GenerationCarte()
{
	int randNumero = utilsDM::randomInt(1, 10);
	int randBonus = utilsDM::randomInt(1, 4);
	int randCouleur = utilsDM::randomInt(0, 1);

	bool couleur;
	randCouleur == 1 ? couleur = true : couleur = false;

	return carte::Carte(randNumero, couleur, randBonus);
}