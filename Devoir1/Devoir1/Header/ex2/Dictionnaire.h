#pragma once

#include <string>

#include "ArbreBinaire.h"

using namespace arbreBinaire;

class Dictionnaire
{

public :

	//---------------------------------------------------------------------------CONSTRUCTEUR----------------------------------------------------------------------------------------------------------------------------------

	Dictionnaire()
	{
		char c = '0';
		arbre = new arbreBinaire::ArbreBinaire<char>(c);
	}

	//---------------------------------------------------------------------------METHODES PUBLIQUES UTILES----------------------------------------------------------------------------------------------------------------------------------

	void ChercherMot(std::string data);

	void AjouterMot(std::string data);

	void AfficherDictionnaire();

	void EnleverMot(std::string data);

private :

	
	arbreBinaire::ArbreBinaire<char> *arbre;

};

