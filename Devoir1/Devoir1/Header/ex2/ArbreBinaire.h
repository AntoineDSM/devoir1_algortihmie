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

		//Constructeur par d�faut
		ArbreBinaire(T data)
		{
			const T & _data = data;
			racine = new Noeud<T>(_data,0);
			cpt = 0;
		}

		//Destructeur
		~ArbreBinaire();
		
		//---------------------------------------------------------------------------METHODES PUBLIQUES UTILES---------------------------------------------------------------------------------------------------------------------------

		//Permet de supprimer tous les �l�ments de l'arbre
		void ViderArbre(Noeud<T> arbre);

		//Retourne true si l'arbre est vide, false sinon
		bool ArbreVide();

		//Retourne la valeur � l'extr�me droite de l'arbre
		const T& max() const;

		//Retourne la valeur � l'extr�me gauche de l'arbre
		const T& min() const;

		//Retour le nombre de noeud qui ne poss�de aucun fils
		int NombreFeuille(Noeud<T>* noeudCourant) const;

		//Retourne la hauteur maximal de l'arbre
		int Hauteur() const;

		//Trouver le parent d'un noeud
		const T& TrouverParent(const T&) const;

		//Retourne les fils d'un noeud
		T TrouverSuccesseurs(const  T&) const;

		void Supprimer(const T& data);

		void ParcoursPrefixe(const Noeud<T>* noeud, void (*traitement)(T& data)) const;

		void ParcoursInfixe(const Noeud<T>* noeud, void (*traitement)(T& data)) const;

		void ParcoursSufixe(const Noeud<T>* noeud, void (*traitement)(T& data)) const;

		//-------------------METHODES INLINES, erreur d'�diteur de liens non r�solue entre .h et .cpp---------------------------------------

		//Retourne le nombre total de noeud de l'arbre
		inline int NombreNoeud() const
		{
			return cpt;
		}

		inline bool ChercherValeur(const T* data) const
		{
			return _appartient(racine->gauche, data) != 0;
		}

		//Attache au noeud A un fils � sa gauche
		inline void AttacherGauche(Noeud<T>* parent, Noeud<T>* filsGauche)
		{
			parent->gauche = filsGauche;
		}
		
		//Attache au noeud A un fils � sa droite
		inline void AttacherDroit(Noeud<T>* parent, Noeud<T>* filsDroit)
		{
			parent->droite = filsDroit;
		}

		//Permet d'afficher l'ensemble des branches de notre arbre.
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

		//Permet d'ajouter une liste de donn�es � notre arbre.
		inline void AjouterListe(Noeud<T>* noeud,const T listeElements[], int size)
		{
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

		//Permet de supprimer une liste de donn�es de notre arbre.
		inline void SupprimerListe(Noeud<T>* noeud, const T listeElements[], int size)
		{
			Noeud<T>* noeudParent = ChercherNoeud(noeud, listeElements[0], true);
			if (noeudParent->data != listeElements[0])
			{
				noeudParent = ChercherNoeud(noeud, listeElements[0], false);
			}
			std::vector<Noeud<T>*> listeNoeud;
			listeNoeud.push_back(noeudParent);//Nous gardons l'ensemble des noeuds constituant notre cha�ne de donn�es.
			for (int i = 1; i < size; i++)
			{
				Noeud<T>* noeud = ChercherNoeud(noeudParent, listeElements[i], true);
				listeNoeud.push_back(noeud);//On ajoute donc les noeuds correspond un � un.
				noeudParent = noeud;
			}
			for (int i = size - 1; i >= 0; i--)
			{
				_supprimerNoeud(listeNoeud[i]);//On supprime l'ensemble de ces noeuds en partant du bas.
			}
		
		}

		//Permet de rechercher un noeud dans notre arbre en fonction de sa donn�e.
		inline Noeud<T>* ChercherNoeud(Noeud<T>* noeud, const T data, bool gauche)
		{
			if (noeud->data == data)
			{
				return noeud;
			}
			else
			{
				if (noeud->gauche->data != defaultValue && gauche)//Cherche d'abord dans les enfants gauches de notre noeud courant
				{
					ChercherNoeud(noeud->gauche, data, gauche);
				}
				else if (noeud->droite->data != defaultValue && !gauche)//Ensuite dans les droits si nous n'avons pas trouv� de r�sultat.
				{
					ChercherNoeud(noeud->droite, data, gauche);
				}
			}
		}

		Noeud<T>* racine; //racine de notre arbre 
		int cpt; //nombre de noeud dans notre arbre
		T defaultValue;//valeur par defaut de notre type T

		//---------------------VARIABLE POUR CONTRER SOUCIS D'OPTIMISATION, non viable------------------------------
		
		int cptIndex;//permet de savoir a partir de quel element de la liste nous devons continuer � ajouter si une partie est d�j� existante dans l'arbre (ARBRE existant, on ajoute ARBUSTE, CptIndex = 3 pour le U de ARBUSTE).
		Noeud<T>* parent_;//erreur du pointer dans la fonction _parent pour retrouver le pr�d�cesseur d'un noeud, je passe par cette variable pour garder la r�f�rence, non viable.

	private :

		//---------------------------------------------------------------------------METHODES PRIVATES UTILES---------------------------------------------------------------------------------------------------------------------------

		T _successeur(Noeud<T>* noeud, const T& data);

		Noeud<T>* _successeur(Noeud<T>* noeud, Noeud<T>* parent);

		Noeud<T>* _trouverNoeud(const T& valeur, Noeud<T>* ptr, Noeud<T>*& parent) const;
	
		//-------------------METHODES INLINES, erreur d'�diteur de liens non r�solue entre .h et .cpp---------------------------------------

		//Permet de d�terminer la hauteur de notre noeud.
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
	
		//Retourne le pointer vers notre Noeud parent, on rentre le noeud fils puis la m�thode parcourt l'arbre pour retrouver le pr�d�cesseur.
		inline Noeud<T>* _parent(Noeud<T>* noeud, Noeud<T>* noeudFils, std::vector<Noeud<T>*> listeNoeud)
		{
			if (racine->gauche == noeudFils)//le fils est directement sous la racine.
			{
				parent_ = racine;
				return racine;
			}
			if (noeud->droite == noeudFils || noeud->gauche == noeudFils)//un des successeurs du noeud est notre fils, le noeud courant est le parent.
			{
				parent_ = noeud;
				return noeud;
			}
			else//le noeud courant n'est pas le parent.
			{
				if (noeud->droite->data != defaultValue)//si le noeud courant poss�de un fils droit, on le rentre dans une liste, elle sera parcourue d�s que l'�l�ment courant n'a pas de fils gauche.
				{
					listeNoeud.push_back(noeud->droite);
				}
				if (noeud->gauche->data != defaultValue)//le noeud courant a un fils gauche, on it�re sur celui-ci
				{
					_parent(noeud->gauche, noeudFils, listeNoeud);
				}
				else//le noeud courant n'a pas de fils gauche, on retourne au dernier noeud qui poss�dait un fils droit, on part de ce fils droit pour parcourir ses fils gauche si il en a, ainsi de suite.
				{
					Noeud<T>* dernierNoeudAvecFilsDroit = listeNoeud.back();
					listeNoeud.pop_back();
					_parent(dernierNoeudAvecFilsDroit, noeudFils, listeNoeud);
				}
			}
		}

		//permet de d�terminer si une cha�ne de donn�es appartient � notre arbre, si cette cha�ne correspond � une branche de l'arbre.
		inline bool _appartient(Noeud<T>* noeud,const T* data) const
		{
			if ((noeud == 0) || (noeud->data > *data))//si le noeud est un pointeur null (pas de point de d�part) 
			{
				return false;
			}
			if (*data == noeud->data)//si le noeud courant poss�de la donn�e que nous cherchons, on continue vers son fils gauche si il en a un.
			{
				if (noeud->gauche->data != defaultValue)
				{
					return _appartient(noeud->gauche, data + 1);//on continue en avancant dans la cha�ne de donn�es en incr�mentant le pointeur.
				}
				else
				{
					return true;
				}
			}
			if (noeud->droite->data != defaultValue)//si la donn�e n'est pas la m�me, on teste son fils droit
			{
				return _appartient(noeud->droite, data);
			}
			else
			{
				return false;
			}
		}
				 
		//Permet de r�cup�rer le noeud ad�quate pour le placement d'une donn�e.
		inline Noeud<T>* _ajouterNoeud(Noeud<T>* noeud, const T listeElements[], int index)
		{
			if (noeud->data == defaultValue)
			{
				return noeud;
			}
			else if (noeud->data > listeElements[index])//le noeud courant a une donn�e sup�rieure, le noeud sera forc�ment � sa gauche
			{
				_ajouterNoeud(noeud->gauche, listeElements, index);
			}
			else if(noeud->data < listeElements[index])//le noeud courant a une donn�e inf�rieure, le noeud sera forc�ment � sa droite
			{
				_ajouterNoeud(noeud->droite, listeElements, index);
			}
			else//les donn�es sont �gales, on ajoutera la suite de donn�es � partir de l'�l�ment suivant dans la cha�ne car les �l�ments pr�c�dents sont d�j� existant sur une branche.
			{
				cptIndex = index + 1;
				_ajouterNoeud(noeud->gauche, listeElements, index + 1);
			}
		}

		//Permet de supprimer un noeud de l'arbre, dans la methode SupprimerListe(), nous partons du dernier noeud de notre branche, ainsi si nous supprimons de bas en haut, nous n'aurons jamais deux enfants � d�placer car le noeud suivant aura vu son enfant �tre supprim� juste avant.
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

	};
}

