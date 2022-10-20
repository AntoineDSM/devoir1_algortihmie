#pragma once

#include <string>

#include "ArbreBinaire.h"

using namespace arbreBinaire;

//Utilise le type générique Arbre pour générer un dictionnaire.
class Dictionnaire
{

public :

	//---------------------------------------------------------------------------CONSTRUCTEUR----------------------------------------------------------------------------------------------------------------------------------

	Dictionnaire()
	{
		//Notre racine possède le caractère "0"
		char c = '0';
		arbre = new arbreBinaire::ArbreBinaire<char>(c);
	}

	//---------------------------------------------------------------------------METHODES PUBLIQUES UTILES----------------------------------------------------------------------------------------------------------------------------------

	//Permet de rechercher un mot dans notre dictionnaire, retourne le résultat de la recherche en console.
	void ChercherMot(std::string data);

	//Permet d'ajouter un mot à notre dictionnaire s'il n'y est pas déjà.
	void AjouterMot(std::string data);

	//Permet d'afficher l'ensemble des mots de notre dictionnaire.
	void AfficherDictionnaire();

	//Permet de supprimer un mot de notre dictionnaire, s'il existe dans celui-ci.
	void EnleverMot(std::string data);

private :
	
	arbreBinaire::ArbreBinaire<char> *arbre;

};

