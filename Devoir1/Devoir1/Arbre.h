#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include "NoeudArbreGenealogique.h"

template <typename T>
class Arbre
{
public:

	//Compteur �l�ments de l'arbre
	int cpt = 0;

	//correspond au premier element de l'arbre
	NoeudArbreGenealogique<T>* racine = (NoeudArbreGenealogique<T>*) malloc(sizeof(NoeudArbreGenealogique<T>));

	//liste d'�l�ments sans parents.
	std::vector<NoeudArbreGenealogique<T>*> elemSansParent;



	//---------------------------------------------------------------------------CONSTRUCTEUR----------------------------------------------------------------------------------------------------------------------------------

			//Constructeur par d�faut
	Arbre()
	{
		cpt = 0;
	}


	//---------------------------------------------------------------------------METHODES PUBLIQUES---------------------------------------------------------------------------------------------------------------------------------

	NoeudArbreGenealogique<T>* CreerNoeud(const T& data)
	{
		return new NoeudArbreGenealogique<T>(data);
	}


	NoeudArbreGenealogique<T>* AjouterNoeud(const T& data, std::vector<NoeudArbreGenealogique<T>*> _parent = std::vector<NoeudArbreGenealogique<T>*>())
	{
		NoeudArbreGenealogique<T>* noeud = new NoeudArbreGenealogique<T>(data, _parent);

		//Si nous n'avons pas encore de racine et que nous voulons ajouter un �l�ment avec des parents ce n'est pas possible, le commencement de notre arbre est un point sans parents.
		if (cpt == 0 && !_parent.empty())
		{
			std::cout << "le premier element ne peux pas avoir de parents\n";
			return 0;
		}
		else if (cpt == 0)//Si nous n'avons pas encore de racine
		{
			racine = noeud;
			elemSansParent.push_back(racine);//Nous avons une liste rescensant les �l�ments qui ne poss�de pas d'attache parentale, important pour ne pas perdre les r�f�rences de nos noeuds vu qu'ils ne sont pour l'instant li�s � personne d'autre.
			cpt++;
			return racine;
		}

		if (_parent.empty())//Nous avons une liste rescensant les �l�ments qui ne poss�de pas d'attache parentale, important pour ne pas perdre les r�f�rences de nos noeuds vu qu'ils ne sont pour l'instant li�s � personne d'autre.
		{
			elemSansParent.push_back(noeud);
		}
		else//Nous avons des parents, nous incr�mentons de 1 la g�n�ration car nous sommes un fils, on affecte aux parents l'enfant suppl�mentaire.
		{
			_parent[0]->hauteur > _parent[1]->hauteur ? noeud->hauteur = _parent[0]->hauteur+1 : noeud->hauteur = _parent[1]->hauteur+1;
			_parent[0]->enfants.push_back(noeud);
			_parent[1]->enfants.push_back(noeud);
		}

		cpt++;
		return noeud;
	}

	//Permet de r�pertorier l'ensemble des �l�ments de notre arbre dans un vecteur.
	std::vector<NoeudArbreGenealogique<T>*> listeElementArbre(NoeudArbreGenealogique<T>* noeud, std::vector<NoeudArbreGenealogique<T>*> listeElem = std::vector<NoeudArbreGenealogique<T>*>(), std::vector< NoeudArbreGenealogique<T>*> listElementsNonParcourus = std::vector< NoeudArbreGenealogique<T>*>(), std::vector< NoeudArbreGenealogique<T>*> listeElementsParcourus = std::vector<NoeudArbreGenealogique<T>*>())
	{
		std::vector<NoeudArbreGenealogique<T>*> newListeElem = listeElem;
		std::vector<NoeudArbreGenealogique<T>*> newListeElemParcourus = listeElementsParcourus;
		std::vector<NoeudArbreGenealogique<T>*> newListeElemNonParcourus = listElementsNonParcourus;

		if (newListeElemNonParcourus == std::vector<NoeudArbreGenealogique<T>*>())//Nous sommes a la premi�re it�ration, on ajoute directement dans la liste des noeuds non parcourus nos �l�ments sans parents.
		{
			for (auto elem : elemSansParent)//Reflechir si nous avons besoin de parcourir la liste des elements sans parents
			{
				if (elem != noeud)
				{
					newListeElemNonParcourus.push_back(elem);
				}
			}
		}

		if (cpt != 0)//Si notre arbre n'est pas vide
		{
			if (!std::count(newListeElem.begin(), newListeElem.end(), noeud))//Si l'�l�ment courant n'est pas d�j� dans notre liste de retour, eviter les doublons.
			{
				newListeElem.push_back(noeud);
			}

			for (NoeudArbreGenealogique<T>* enfant : noeud->enfants)//on balaye les enfants de notre noeud courant et s'ils ne sont pas dans la liste des �l�ments non parcourus on les ajoute afin de les parcourir plus tard
			{
				if (!std::count(listeElementsParcourus.begin(), listeElementsParcourus.end(), enfant))
				{
					newListeElemNonParcourus.push_back(enfant);
				}
			}
			for (NoeudArbreGenealogique<T>* parent : noeud->parents)//de m�me pour nos parents
			{
				if (!std::count(listeElementsParcourus.begin(), listeElementsParcourus.end(), parent))
				{
					newListeElemNonParcourus.push_back(parent);
				}
			}

			newListeElemParcourus.push_back(noeud);//On ajoute l'�l�ment courant a la liste des parcourus car nous l'avons balay�.

			int size = static_cast<int>(newListeElemNonParcourus.size());
			if (noeud != racine)//Nous n'avons pas rentr� la racine dans les �l�ments des non parcourus, donc on v�rifie que nous ne sommes pas a la premiere it�ration pour �viter l'exception. SInon on enl�ve l'�l�ment courant de la liste.
			{
				newListeElemNonParcourus.erase(std::find(newListeElemNonParcourus.begin(), newListeElemNonParcourus.end(), noeud));
				size--;
			}
			if (size > 0)//Tant que nous avons des �l�ments dans la liste des non parcourus. On effectue notre recursion avec le dernier element de la liste.
			{
				newListeElem = listeElementArbre(newListeElemNonParcourus.back(), newListeElem, newListeElemNonParcourus, newListeElemParcourus);
			}
		}
		return newListeElem;
	}

	//Permet de parcourir les parents d'un �l�ment.
	std::vector<NoeudArbreGenealogique<T>*> listeElementPrecedentArbre(NoeudArbreGenealogique<T>* noeud, std::vector<NoeudArbreGenealogique<T>*> listeElem = std::vector<NoeudArbreGenealogique<T>*>(), std::vector< NoeudArbreGenealogique<T>*> listElementsNonParcourus = std::vector< NoeudArbreGenealogique<T>*>(), std::vector< NoeudArbreGenealogique<T>*> listeElementsParcourus = std::vector<NoeudArbreGenealogique<T>*>(), NoeudArbreGenealogique<T>* premierNoeud = 0)
	{
		std::vector<NoeudArbreGenealogique<T>*> newListeElem = listeElem;
		std::vector<NoeudArbreGenealogique<T>*> newListeElemParcourus = listeElementsParcourus;
		std::vector<NoeudArbreGenealogique<T>*> newListeElemNonParcourus = listElementsNonParcourus;

		if(premierNoeud == 0)
		{
			premierNoeud = noeud;//Nous gardons notre �l�ment de d�part (pas forc�ment la racine) pour ne pas le supprimer de la liste des non parcourus alors que nous ne l'avons pas ajout�, nous sommes a la premiere it�ration.
		}

		if (cpt != 0)
		{
			newListeElem.push_back(noeud);//On ajoute l'�l�ment courant a notre liste

			for (NoeudArbreGenealogique<T>* parent : noeud->parents)//Nous ne parcourons que les parents car nous cherchons les anc�tres
			{
				if (!std::count(listeElementsParcourus.begin(), listeElementsParcourus.end(), parent))
				{
					newListeElemNonParcourus.push_back(parent);
				}
			}

			newListeElemParcourus.push_back(noeud);//L'�l�ment courant est a pr�sent parcouru

			int size = static_cast<int>(newListeElemNonParcourus.size());
			if (noeud != premierNoeud)
			{
				newListeElemNonParcourus.erase(std::find(newListeElemNonParcourus.begin(), newListeElemNonParcourus.end(), noeud));
				size--;
			}
			if (size > 0)//Tant que nous avons des parents a parcourir, on it�re et on effectue notre r�cursivit�.
			{
				newListeElem = listeElementPrecedentArbre(newListeElemNonParcourus.back(), newListeElem, newListeElemNonParcourus, newListeElemParcourus, premierNoeud);
			}
		}
		return newListeElem;
	}

	//Permet de d�terminer si un noeud comporte notre type g�n�rique.
	NoeudArbreGenealogique<T>* chercherNoeud(T& data)
	{
		NoeudArbreGenealogique<T>* myData = 0;

		std::vector<NoeudArbreGenealogique<T>*> personnes;
		personnes = listeElementArbre(racine);
		for (NoeudArbreGenealogique<T>* elem : personnes)
		{
			if (elem->data == data)
			{
				myData = elem;
			}
		}

		if (myData == 0)
		{
			std::cout << "la personne recherch�e n'existe pas.\n";
		}

		return myData;
	}

	//La taille de l'arbre correspond au nombre de "niveaux", nous gardons la valeur du niveau d'un noeud dans son type, la variable hauteur. Ainsi il nous suffit de retourner la valeur hauteur la plus haute parmis l'ensemble de nos noeuds.
	int calculerTailleArbre()
	{
		std::vector<NoeudArbreGenealogique<T>*> personnes;
		personnes = listeElementArbre(racine);

		int hauteurMax = 0;
		for (NoeudArbreGenealogique<T>* elem : personnes)
		{
			if (elem->hauteur > hauteurMax)
			{
				hauteurMax = elem->hauteur;
			}
		}
		return hauteurMax;
	}
	
	//Permet de parcourir notre arbre et de r�cup�rer les descendants d'un noeud dans l'ordre pr� order.  Consiste � afficher notre parent puis ses enfants, � chaque enfants contenant des enfants, ils sont directement affich�s et ainsi de suite.
	std::vector<NoeudArbreGenealogique<T>*> ParcoursPrefixe(NoeudArbreGenealogique<T>* noeud, std::vector<NoeudArbreGenealogique<T>*> listeElem = std::vector<NoeudArbreGenealogique<T>*>(), std::vector< NoeudArbreGenealogique<T>*> listElementsNonParcourus = std::vector< NoeudArbreGenealogique<T>*>(), std::vector< NoeudArbreGenealogique<T>*> listeElementsParcourus = std::vector<NoeudArbreGenealogique<T>*>(), NoeudArbreGenealogique<T>* premierNoeud = 0) const
	{
		std::vector<NoeudArbreGenealogique<T>*> newListeElem = listeElem;
		std::vector<NoeudArbreGenealogique<T>*> newListeElemParcourus = listeElementsParcourus;
		std::vector<NoeudArbreGenealogique<T>*> newListeElemNonParcourus = listElementsNonParcourus;

		if (premierNoeud == 0)
		{
			premierNoeud = noeud;
		}

		if (cpt != 0)
		{
			if (!std::count(newListeElem.begin(), newListeElem.end(), noeud))//Si notre noeud nest pas d�j� dans la listed de retour, on l'ajoute
			{
				newListeElem.push_back(noeud);
			}

			for (NoeudArbreGenealogique<T>* enfant : noeud->enfants)//On ajoute chacun de ses enfants dans la liste des non parcourus � la fin de la liste, ils seront les premiers parcourus ensuite avec la recursivit� et donc les premiers affich�s.
			{
				if (!std::count(listeElementsParcourus.begin(), listeElementsParcourus.end(), enfant))
				{
					newListeElemNonParcourus.push_back(enfant);
				}
			}

			int sizeElementNonParcourus = static_cast<int>(newListeElemNonParcourus.size());
			if (noeud != premierNoeud)
			{
				newListeElemNonParcourus.erase(std::find(newListeElemNonParcourus.begin(), newListeElemNonParcourus.end(), noeud));
				sizeElementNonParcourus--;
			}

			int size = static_cast<int>(noeud->enfants.size());
			for (int i = 0; i < size; i++)//Pour l'ensemble des enfants de notre noeud courant, on effectue une recursivit� sur eux.
			{
				newListeElem = ParcoursPrefixe(newListeElemNonParcourus.back(), newListeElem, newListeElemNonParcourus, newListeElemParcourus, premierNoeud);
			}

			if (sizeElementNonParcourus > 0)//Tant que la liste des �l�ments non parcourus n'est pas vide.
			{
				newListeElem = ParcoursPrefixe(newListeElemNonParcourus.back(), newListeElem, newListeElemNonParcourus, newListeElemParcourus, premierNoeud);
			}
			return newListeElem;
		}

	}

	//Permet de parcourir notre arbre et de r�cup�rer les descendants d'un noeud dans l'ordre in order.
	std::vector<NoeudArbreGenealogique<T>*> ParcoursInfixe(NoeudArbreGenealogique<T>* noeud, std::vector<NoeudArbreGenealogique<T>*> listeElem = std::vector<NoeudArbreGenealogique<T>*>(), std::vector< NoeudArbreGenealogique<T>*> listElementsNonParcourus = std::vector< NoeudArbreGenealogique<T>*>(), std::vector< NoeudArbreGenealogique<T>*> listeElementsParcourus = std::vector<NoeudArbreGenealogique<T>*>(), NoeudArbreGenealogique<T>* premierNoeud = 0, NoeudArbreGenealogique<T>* parent = 0) const
	{
		std::vector<NoeudArbreGenealogique<T>*> newListeElem = listeElem;
		std::vector<NoeudArbreGenealogique<T>*> newListeElemParcourus = listeElementsParcourus;
		std::vector<NoeudArbreGenealogique<T>*> newListeElemNonParcourus = listElementsNonParcourus;

		if (premierNoeud == 0)
		{
			premierNoeud = noeud;
		}

		if (cpt != 0)
		{
			int sizeListeEnfants = static_cast<int>(noeud->enfants.size());
			if (sizeListeEnfants == 0)
			{
				if (!std::count(newListeElem.begin(), newListeElem.end(), noeud))
				{
					newListeElem.push_back(noeud);
				}
				if (!std::count(newListeElem.begin(), newListeElem.end(), parent))
				{
					newListeElem.push_back(parent);
				}

			}

			for (NoeudArbreGenealogique<T>* enfant : noeud->enfants)
			{
				if (!std::count(listeElementsParcourus.begin(), listeElementsParcourus.end(), enfant))
				{
					newListeElemNonParcourus.push_back(enfant);
				}
			}

			int sizeElementNonParcourus = static_cast<int>(newListeElemNonParcourus.size());
			if (noeud != premierNoeud)
			{
				newListeElemNonParcourus.erase(std::find(newListeElemNonParcourus.begin(), newListeElemNonParcourus.end(), noeud));
				sizeElementNonParcourus--;
			}

			for (int i = 0; i < sizeListeEnfants; i++)
			{
				newListeElem = ParcoursInfixe(newListeElemNonParcourus.back(), newListeElem, newListeElemNonParcourus, newListeElemParcourus, premierNoeud, noeud);
			}

			if (sizeElementNonParcourus > 0)
			{
				newListeElem = ParcoursInfixe(newListeElemNonParcourus.back(), newListeElem, newListeElemNonParcourus, newListeElemParcourus, premierNoeud, noeud);
			}
			else
			{
				if (!std::count(newListeElem.begin(), newListeElem.end(), premierNoeud))
				{
					newListeElem.push_back(premierNoeud);
				}
			}
			return newListeElem;
		}
	}

	//Permet de parcourir notre arbre et de r�cup�rer les descendants d'un noeud dans l'ordre post order.
	std::vector<NoeudArbreGenealogique<T>*> ParcoursSufixe(NoeudArbreGenealogique<T>* noeud, std::vector<NoeudArbreGenealogique<T>*> listeElem = std::vector<NoeudArbreGenealogique<T>*>(), std::vector< NoeudArbreGenealogique<T>*> listElementsNonParcourus = std::vector< NoeudArbreGenealogique<T>*>(), std::vector< NoeudArbreGenealogique<T>*> listeElementsParcourus = std::vector<NoeudArbreGenealogique<T>*>(), NoeudArbreGenealogique<T>* premierNoeud = 0, NoeudArbreGenealogique<T>* parent = 0) const
	{
		std::vector<NoeudArbreGenealogique<T>*> newListeElem = listeElem;
		std::vector<NoeudArbreGenealogique<T>*> newListeElemParcourus = listeElementsParcourus;
		std::vector<NoeudArbreGenealogique<T>*> newListeElemNonParcourus = listElementsNonParcourus;

		if (premierNoeud == 0)
		{
			premierNoeud = noeud;
		}

		if (cpt != 0)
		{
			int sizeListeEnfants = static_cast<int>(noeud->enfants.size());
			if (sizeListeEnfants == 0)
			{
				for (auto elem : parent->enfants)
				{
					if (!std::count(newListeElem.begin(), newListeElem.end(), noeud))
					{
						newListeElem.push_back(elem);
					}
				}
				if (!std::count(newListeElem.begin(), newListeElem.end(), parent))
				{
					newListeElem.push_back(parent);
				}
			}
			for (NoeudArbreGenealogique<T>* enfant : noeud->enfants)
			{
				if (!std::count(listeElementsParcourus.begin(), listeElementsParcourus.end(), enfant))
				{
					newListeElemNonParcourus.push_back(enfant);
				}
			}

			int sizeElementNonParcourus = static_cast<int>(newListeElemNonParcourus.size());
			if (noeud != premierNoeud)
			{
				newListeElemNonParcourus.erase(std::find(newListeElemNonParcourus.begin(), newListeElemNonParcourus.end(), noeud));
				sizeElementNonParcourus--;
			}

			for (int i = 0; i < sizeListeEnfants; i++)
			{
				newListeElem = ParcoursSufixe(newListeElemNonParcourus.back(), newListeElem, newListeElemNonParcourus, newListeElemParcourus, premierNoeud, noeud);
			}

			if (sizeElementNonParcourus > 0)
			{
				newListeElem = ParcoursSufixe(newListeElemNonParcourus.back(), newListeElem, newListeElemNonParcourus, newListeElemParcourus, premierNoeud, noeud);
			}
			else
			{
				if (!std::count(newListeElem.begin(), newListeElem.end(), premierNoeud))
				{
					newListeElem.push_back(premierNoeud);
				}
			}
			return newListeElem;
			}
		}
	//---------------------------------------------------------------------------METHODES PRIVATES---------------------------------------------------------------------------------------------------------------------------------

private:

};
