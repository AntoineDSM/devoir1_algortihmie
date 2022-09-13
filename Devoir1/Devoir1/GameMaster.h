#pragma once
#include "Joueur.h"
#include "Carte.h"
#include <vector>


class GameMaster
{
	public :
		//total des cartes que nous devons tirer pour chaque joueur
		int nombreCarteTirage;
		//liste contenant les deux joueurs
		std::vector<Joueur> joueurs;
		//vecteur comportant le tirage actuel des 100 cartes
		std::vector<Carte> paquetGlobal;


	public :

		GameMaster(int nombreCarteVoulu) : nombreCarteTirage(nombreCarteVoulu), joueurs(2), paquetGlobal(100)
		{
			//rien de plus a ajouter
		}

		void demanderNombreCarteTirage()
		{

		}

		void creationJoueur(std::string nomJoueur1, std::string nomJoueur2)
		{
			joueurs[0] = Joueur(nomJoueur1, 1, nombreCarteTirage);
			joueurs[1] = Joueur(nomJoueur2, 2, nombreCarteTirage);
		}

		void tirageCartes()
		{
			//joueurs[0].paquet = ....
			//joueurs[1].paquet = ....
		}

		void generationPaquet()
		{
			//generation des 100 cartes dans une liste
		}

};

