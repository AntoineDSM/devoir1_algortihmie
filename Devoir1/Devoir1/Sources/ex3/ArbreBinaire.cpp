
#include "..\..\Header\ex3\ArbreBinaire.h"

using namespace arbreBinaire;

//------------------------------------------------------------------------------DEFINITION CONSTRUCTEURS---------------------------------------------------------------------------------------------------------------

template<typename T>
ArbreBinaire<T>::~ArbreBinaire()
{
	if (cpt > 0)
	{
		ViderArbre(racine->gauche);
		ViderArbre(racine->droite);
		delete racine;
	}
}

//------------------------------------------------------------------------------DEFINITION METHODES PUBLIQUES---------------------------------------------------------------------------------------------------------------

template<typename T>
void ArbreBinaire<T>::ViderArbre(Noeud<T> arbre)
{
	if (arbre != 0)
	{
		ViderArbre(arbre->gauche);
		ViderArbre(arbre->droite);
		delete arbre;
	}
}

template<typename T>
bool ArbreBinaire<T>::ArbreVide()
{
	if (cpt == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Permet de retourner l'extrême droite de l'arbre.
template<typename T>
const T& ArbreBinaire<T>::max() const
{
	if (cpt == 0)
	{
		std::cout << "L'arbre est vide\n";
	}

	if (racine->droite == 0)
	{
		return racine->data;
	}

	Noeud<T>* temp = racine->droite;
	while (temp->droite != 0)
	{
		temp = temp->droite;
	}

	return temp->data;
}


//permet de retourner l'extrême gauche de l'arbre.
template<typename T>
const T& ArbreBinaire<T>::min() const
{
	if (cpt == 0)
	{
		std::cout << "L'arbre est vide\n";
	}

	if (racine->gauche == 0)
	{
		return racine->data;
	}

	Noeud<T>* temp = racine->gauche;
	while (temp->droite != 0)
	{
		temp = temp->gauche;
	}

	return temp->data;
}

template<typename T>
int ArbreBinaire<T>::NombreFeuille(Noeud<T>* noeudCourant) const
{
	int nombreGauche, nombreDroit = 0;

	if (noeudCourant != 0)
	{
		if (noeudCourant->gauche == 0 && noeudCourant->droite == 0)
		{
			std::cout << "L'arbre n'a que sa racine\n";
			return 1;
		}
		else
		{
			if (noeudCourant->gauche != 0)
			{
				nombreGauche = NombreFeuille(noeudCourant->gauche);
			}
			if (noeudCourant->droite != 0)
			{
				nombreDroit = NombreFeuille(noeudCourant->droite);
			}
		}
	}
	return nombreGauche + nombreDroit;
}

template<typename T>
int ArbreBinaire<T>::Hauteur() const
{
	if (cpt == 0)
	{
		std::cout << "L'arbre est vide\n";
	}
	else
	{
		return _hauteurParcours(racine);
	}
}

template<typename T>
const T& ArbreBinaire<T>::TrouverParent(const T& noeudData) const
{
	Noeud* dataNoeud = _appartient(racine, noeudData);
	Noeud* parentNoeud = _parent(racine, dataNoeud);

	return parentNoeud->data;
}

template<typename T>
T ArbreBinaire<T>::TrouverSuccesseurs(const  T& data) const
{
	return _successeur(racine, data);
}

template<typename T>
void ArbreBinaire<T>::ParcoursPrefixe(const Noeud<T>* noeud, void(*traitement)(T& data)) const
{
	if (noeud != 0)
	{
		traitement(noeud->data);
		ParcoursPrefixe(noeud->gauche, traitement);
		ParcoursPrefixe(noeud->droite, traitement);
	}
}

template<typename T>
void ArbreBinaire<T>::ParcoursInfixe(const Noeud<T>* noeud, void(*traitement)(T& data)) const
{
	if (noeud != 0)
	{
		ParcoursInfixe(noeud->gauche, traitement);
		traitement(noeud->data);
		ParcoursInfixe(noeud->droite, traitement);
	}
}

template<typename T>
void ArbreBinaire<T>::ParcoursSufixe(const Noeud<T>* noeud, void(*traitement)(T& data)) const
{
	if (noeud != 0)
	{
		ParcoursSufixe(noeud->gauche, traitement);
		ParcoursSufixe(noeud->droite, traitement);
		traitement(noeud->data);
	}
}

template<typename T>
void ArbreBinaire<T>::Supprimer(const T& data)
{
	Noeud <T>* parent = 0;
	Noeud <T>* noeud = _trouverNoeud(data, racine, parent);
	if (noeud == 0) {
		std::cout << "Le noeud n'appartient pas a l'arbre\n";
	}
	else 
	{
		_supprimerNoeud(noeud, parent);
	}
}

//------------------------------------------------------------------------------DEFINITION METHODES PRIVEES---------------------------------------------------------------------------------------------------------------

template <class T>
Noeud <T>* ArbreBinaire<T>::_trouverNoeud(const T& data, Noeud <T>* noeud, Noeud <T>*& parent) const
{
	if (noeud == 0)
	{
		return 0;
	}
	else if ((noeud->data) == data) {
		return noeud;
	}
	else if (data < (noeud->data)) {
		parent = noeud;
		return _trouverNoeud(data, noeud->gauche, parent);
	}
	else {
		parent = noeud;
		return _tTrouverNoeud(data, noeud->droite, parent);
	}
}

template<typename T>
T ArbreBinaire<T>::_successeur(Noeud<T>* noeud, const T& data)
{
	if (cpt == 0)
	{

	}
	Noeud* noeudFils = _appartient(racine, data);
	if (noeudFils == 0)
	{
		std::cout << "l'élément n'existe pas\n";
	}
	if (data == max())
	{
		std::cout << "l'élément est le max de l'arbre\n";
	}
	if (noeudFils->droite != 0)
	{
		return min();
	}
	else
	{
		Noeud* parent = _parent(noeud, noeudFils);
		while (parent->data < noeudFils->data)
		{
			parent = _parent(noeud, parent);
		}
		return parent->data;
	}
}

template<typename T>
Noeud<T>* ArbreBinaire<T>::_successeur(Noeud<T>* noeud, Noeud<T>* parent)
{
	if (!noeud)
	{
		return 0;
	}
	Noeud <T>* courant = noeud;
	while (courant->gauche != 0) {
		parent = courant;
		courant = courant->gauche;
	}
	return courant;
}
*/