#pragma once

#include <vector>
#include <iostream>
#include <string>

#include "Noeud.h"


namespace arbreBinaire {

	template <typename T>
	class ArbreBinaire
	{

	public :

		//---------------------------------------------------------------------------CONSTRUCTEUR---------------------------------------------------------------------------------------------------------------------------

		//Constructeur par défaut
		ArbreBinaire(T data)
		{
			const T & _data = data;
			racine = new Noeud<T>(_data,0);
			cpt = 0;
		}

		//Destructeur
		~ArbreBinaire();
		
		//---------------------------------------------------------------------------METHODES PUBLIQUES UTILES---------------------------------------------------------------------------------------------------------------------------

		//Permet de supprimer tous les éléments de l'arbre
		void ViderArbre(Noeud<T> arbre);

		//Retourne true si l'arbre est vide, false sinon
		bool ArbreVide();

		//Retourne la valeur à l'extrême droite de l'arbre
		const T& max() const;

		//Retourne la valeur à l'extrême gauche de l'arbre
		const T& min() const;

		//Retourne le nombre total de noeud de l'arbre
		inline int NombreNoeud() const
		{
			return cpt;
		}

		//Retour le nombre de noeud qui ne possède aucun fils
		int NombreFeuille(Noeud<T>* noeudCourant) const;

		//Retourne la hauteur maximal de l'arbre
		int Hauteur() const;

		inline bool ChercherValeur(const T* data) const
		{
			return _appartient(racine->gauche, data) != 0;
		}

		//Trouver le parent d'un noeud
		const T& TrouverParent(const T&) const;

		//Retourne les fils d'un noeud
		T TrouverSuccesseurs(const  T&) const;

		//Attache au noeud A un fils à sa gauche
		inline void AttacherGauche(Noeud<T>* parent, Noeud<T>* filsGauche)
		{
			parent->gauche = filsGauche;
		}
		
		//Attache au noeud A un fils à sa droite
		inline void AttacherDroit(Noeud<T>* parent, Noeud<T>* filsDroit)
		{
			parent->droite = filsDroit;
		}

		void Supprimer(const T& data);

		void ParcoursPrefixe(const Noeud<T>* noeud, void (*traitement)(T& data)) const;

		void ParcoursInfixe(const Noeud<T>* noeud, void (*traitement)(T& data)) const;

		void ParcoursSufixe(const Noeud<T>* noeud, void (*traitement)(T& data)) const;

		inline T* AfficherArbre(Noeud<T>* noeud, T data[] = NULL, int n = 0)//int nombreElement
		{
			if (noeud == 0)
			{
				return data;
			}
			if (n >= cpt)
			{
				return data;
			}
			bool dataEmpty = false;
			if (data == 0)
			{
				dataEmpty = true;
				data = new char[80];
				for (int m = 0; m < 80; m++)
				{
					data[m] = 0;
				}
			}
			data[n] = noeud->data;
			if (*data && noeud->gauche->data == defaultValue)
			{
				std::cout << data << "\n";
			}
			if (noeud->gauche->data != defaultValue)
			{
				AfficherArbre(noeud->gauche, data, ++n);
			}
			if (noeud->droite->data != defaultValue)
			{
				for (int i = n+1; i < 80; i++)
				{
					data[i] = defaultValue;
				}
				AfficherArbre(noeud->droite, data, --n);
			}
		}

		inline void AjouterListe(Noeud<T>* noeud,const T listeElements[])
		{
			int size = static_cast<int>(std::strlen(listeElements));
			if (noeud->gauche->data == defaultValue)
			{
				Noeud<T>* noeudParent = new Noeud<T>(listeElements[0], 0);
				AttacherGauche(noeud, noeudParent);
				_ajoutBranche(noeudParent, listeElements, size);
				return;
			}
			if (listeElements[0] > noeud->gauche->data)
			{
				Noeud<T>* noeudParent = _ajouterNoeud(noeud->gauche->droite, listeElements, 0);
				*noeudParent = Noeud<T>(listeElements[0], 0);
				_ajoutBranche(noeudParent, listeElements, size);
			}
			else if(listeElements[0] < noeud->gauche->data)
			{
				Noeud<T>* noeudParent = _ajouterNoeud(noeud->gauche->gauche, listeElements, 0);
				*noeudParent = Noeud<T>(listeElements[0], 0);
				_ajoutBranche(noeudParent, listeElements, size);
			}
			else if (listeElements[0] == noeud->gauche->data)
			{
				Noeud<T>* noeudParent = _ajouterNoeud(noeud->gauche->gauche, listeElements, 1);
				int index = cptIndex > 1 ? cptIndex : 1;
				_ajoutBranche(noeudParent, listeElements, size, index);
			}
		}

		inline void _ajoutBranche(Noeud<T>* noeudParent, const T listeElements[], int size, int index = 0)
		{
			*noeudParent = Noeud<T>(listeElements[index], 0);
			cpt++;
			for (unsigned int i = index + 1; i < size + 1; i++)
			{
				Noeud<T>* noeudElementSuivant = new Noeud<T>(listeElements[i], 0);
				AttacherGauche(noeudParent, noeudElementSuivant);
				noeudParent = noeudElementSuivant;
				cpt++;
			}
		}

		inline void SupprimerListe(Noeud<T>* noeud, const T listeElements[])
		{
			int size = static_cast<int>(std::strlen(listeElements));//a revoir car la le type n'est pas generique
			Noeud<T>* noeudParent = ChercherNoeud(noeud, listeElements[0], true);
			if (noeudParent->data != listeElements[0])
			{
				noeudParent = ChercherNoeud(noeud, listeElements[0], false);
			}
			std::vector<Noeud<T>*> listeNoeud;
			listeNoeud.push_back(noeudParent);
			for (int i = 1; i < size; i++)
			{
				Noeud<T>* noeud = ChercherNoeud(noeudParent, listeElements[i], true);
				listeNoeud.push_back(noeud);
				noeudParent = noeud;
			}
			for (int i = size - 1; i >= 0; i--)
			{
				_supprimerNoeud(listeNoeud[i]);
			}
		
		}

		inline Noeud<T>* ChercherNoeud(Noeud<T>* noeud, const T data, bool gauche)
		{
			if (noeud->data == data)
			{
				return noeud;
			}
			else
			{
				if (noeud->gauche->data != defaultValue && gauche)
				{
					ChercherNoeud(noeud->gauche, data, gauche);
				}
				else if (noeud->droite->data != defaultValue && !gauche)
				{
					ChercherNoeud(noeud->droite, data, gauche);
				}
			}
		}

		Noeud<T>* racine; //racine de notre arbre 
		int cpt; //nombre de noeud dans notre arbre
		int cptIndex;
		T defaultValue;
		Noeud<T>* parent_;

	private :
	
		inline int _hauteurParcours(Noeud<T>* noeud) const
		{
			if (noeud->data == defaultValue && noeud->hauteur != 0)
			{
				return -1;
			}

			int HauteurGauche = _hauteurParcours(noeud->gauche);
			int HauteurDroite = _hauteurParcours(noeud->droite);
			auto max = std::max(&HauteurGauche, &HauteurDroite);
			return 1 + *max;
		}
	
		inline Noeud<T>* _parent(Noeud<T>* noeud, Noeud<T>* noeudFils, std::vector<Noeud<T>*> listeNoeud)
		{
			if (racine->gauche == noeudFils)
			{
				parent_ = racine;
				return racine;
			}
			if (noeud->droite == noeudFils || noeud->gauche == noeudFils)
			{
				parent_ = noeud;
				return noeud;
			}
			else
			{
				if (noeud->droite->data != defaultValue)
				{
					listeNoeud.push_back(noeud->droite);
				}
				if (noeud->gauche->data != defaultValue)
				{
					_parent(noeud->gauche, noeudFils, listeNoeud);
				}
				else
				{
					Noeud<T>* dernierNoeudAvecFilsDroit = listeNoeud.back();
					listeNoeud.pop_back();
					_parent(dernierNoeudAvecFilsDroit, noeudFils, listeNoeud);
				}
			}
		}

		inline bool _appartient(Noeud<T>* noeud,const T* data) const
		{
			if ((noeud == 0) || (noeud->data > *data))
			{
				return false;
			}
			if (*data == noeud->data)
			{
				if (noeud->gauche->data != defaultValue)
				{
					return _appartient(noeud->gauche, data + 1);
				}
				else
				{
					return true;
				}
			}
			if (noeud->droite->data != defaultValue)
			{
				return _appartient(noeud->droite, data);
			}
			else
			{
				return false;
			}
		}
				 
		//Permet d'ajouter un noeud à l'arbre
		inline Noeud<T>* _ajouterNoeud(Noeud<T>* noeud, const T listeElements[], int index)
		{
			if (noeud->data == defaultValue)
			{
				return noeud;
			}
			else if (noeud->data > listeElements[index])
			{
				_ajouterNoeud(noeud->gauche, listeElements, index);
			}
			else if(noeud->data < listeElements[index])
			{
				_ajouterNoeud(noeud->droite, listeElements, index);
			}
			else// ==
			{
				cptIndex = index + 1;
				_ajouterNoeud(noeud->gauche, listeElements, index + 1);
			}
		}

		//Permet de supprimer le noeud de l'arbre
		inline void _supprimerNoeud(Noeud<T>* noeud)
		{
			std::vector <Noeud<T>*> listeNoeud;
			Noeud<T>* parent = _parent(racine->gauche, noeud, listeNoeud);
			parent = parent_;
			if (noeud->gauche->data == defaultValue && noeud->droite->data == defaultValue)//feuille
			{				
				if (parent->gauche == noeud)
				{
					delete noeud;
					parent->gauche->data = defaultValue;
				}
				else if (parent->droite == noeud)
				{
					delete noeud;
					parent->droite->data = defaultValue;
				}
				return;
			}
			else//un seul enfant
			{
				if (noeud->gauche->data != defaultValue)
				{
					return;
				}
				else
				{
					parent->gauche == noeud ? AttacherGauche(parent, noeud->droite) : AttacherDroit(parent, noeud->droite);
				}
				delete noeud;
			}
		}

		T _successeur(Noeud<T>* noeud, const T& data);

		Noeud<T>* _successeur(Noeud<T>* noeud, Noeud<T>* parent);

		Noeud<T>* _trouverNoeud(const T& valeur, Noeud<T>* ptr, Noeud<T>*& parent) const;

	};
}

