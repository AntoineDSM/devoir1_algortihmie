#pragma once
#include <iostream>
#include <vector>

#include "Joueur.h"
#include "Carte.h"
#include "compteurpoints.h"
#include "PileDM.h"
#include "TourDeJeu.h"
#include "utilsDM.h"

#ifndef GAMEMASTER

#define GAMEMASTER

class GameMaster
{
	public :
		//total des cartes que nous devons tirer pour chaque joueur
		int nombreCarteTirage;
		//liste contenant les deux joueurs
		std::vector<joueur::Joueur> joueurs;
		//vecteur comportant le tirage actuel des 100 cartes
		pile::PileDM<carte::Carte> paquetGlobal;


	public :

		//Constructeur
		GameMaster(int nombreCarteVoulu, std::string nomJoueur1, std::string nomJoueur2) : nombreCarteTirage(nombreCarteVoulu)
		{
			paquetGlobal = pile::PileDM<carte::Carte>(100);
			joueurs = std::vector<joueur::Joueur>(2);
			generationPaquet();
			creationJoueur(nomJoueur1, nomJoueur2);
			tirageCartes(nombreCarteVoulu);
			executionPartie();
			determinerGagnant();
		}

		//destructeur
		~GameMaster()
		{
		}

		//creation de nos deux joueurs en fonction du nom inséré
		void creationJoueur(std::string nomJoueur1, std::string nomJoueur2);
		//attribution des cartes du paquet à chacun de nos joueurs
		void tirageCartes(int nombreCarteVoulu);
		//generation des 100 cartes aléatoires du paquet de jeu
		void generationPaquet();
		//apres execution de la partie, déterminer en fonciton des gains notre gagnant
		void determinerGagnant();
		//déroulement de la partie, autant de TourDeJeu que de carte dans le paquet de nos joueurs
		void executionPartie();
		//generation aléatoire d'une carte
		carte::Carte GenerationCarte();

		//---------------------------------------------------------------------Définient dans le .h -------------------------------------------------------------------------------------------
		
		static std::string demandeAutrePartie()
		{
			std::string autrePartie;

			std::cout << "Voulez vous refaire une partie ? Oui ou Non \n";
			std::cin >> autrePartie;
			while (std::cin.fail() || std::cin.eof() || (std::strcmp(autrePartie.c_str(),"oui") && std::strcmp(autrePartie.c_str(), "Oui") && std::strcmp(autrePartie.c_str(), "non") && std::strcmp(autrePartie.c_str(), "Non")==1)) {
				if (std::cin.fail())
				{
					std::cout << "La selection du choix a echoue, veuillez reessayer." << std::endl;
				}
				else
				{
					std::cout << "Veuillez ecrire correctement votre choix." << std::endl;
				}
				std::cin.clear();
				std::cin.ignore(256, '\n');
				std::cin >> autrePartie;
			}

			return autrePartie;
		}

		static std::vector<std::string> demandeNomsJoueurs()
		{
			std::vector<std::string> noms(2);
			std::string buffer;

			//implémenter la demande
			std::cout << "\nVeuillez inserer le nom du Joueur 1 :\n";
			std::cin >> buffer;
			while (std::cin.fail() || std::cin.eof()) {
				std::cout << "Erreur lors de l'insertion du nom, veuillez reessayer." << std::endl;
				std::cin.clear();
				std::cin.ignore(256, '\n');
				std::cin >> buffer;
			}
			noms[0] = buffer;
			std::cout << "Joueur 1 > " << buffer << "\n" << std::endl;
			
			std::cout << "Veuillez inserer le nom du Joueur 2 :\n";
			std::cin >> buffer;
			while (std::cin.fail() || std::cin.eof()) {
				std::cout << "Erreur lors de l'insertion du nom, veuillez reessayer." << std::endl;
				std::cin.clear();
				std::cin.ignore(256, '\n');
				std::cin >> buffer;
			}
			noms[1] = buffer;
			std::cout << "Joueur 2 > " << buffer << "\n" << std::endl;

			return noms;
		}

		static int demanderNombreCarteTirage()
		{
			int nombreCarte;

			std::cout << "Veuillez donner un nombre de cartes par Joueur (2-50) :\n";
			std::cin >> nombreCarte;
			while (std::cin.fail() || std::cin.eof() || (nombreCarte < 2) || (nombreCarte > 50)) {
				if ((nombreCarte < 2) || (nombreCarte > 50))
				{
					std::cout << "Vous devez rester entre 2 et 50 cartes par joueurs." << std::endl;
				}
				else
				{
					std::cout << "Vous devez rentrer un entier." << std::endl;
				}
				std::cin.clear();
				std::cin.ignore(256, '\n');
				std::cin >> nombreCarte;
			}

			return nombreCarte;
		}
};

#endif //GAMEMASTER