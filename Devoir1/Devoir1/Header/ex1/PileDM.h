#pragma once
#include <stdexcept>

#ifndef  PILEDM

#define PILEDM

namespace pile {

	template <typename T>
	class PileDM
	{
		public:

			// constructeurs et destructeurs

			//constructeur
			PileDM(int max = MAX_PILE) throw(std::bad_alloc)
			{
				tab = new T[max];
				sommet = -1; //valeur fausse pour montrer que la liste est sans élément initiallement
				tailleMax = max;
				taille = 0;
			}
			
			//constructeur copie
			PileDM(const PileDM<T>& p)
			{
				tab = new T[p.tailleMax];
				tailleMax = p.tailleMax;
				for (int i = 0; i < tailleMax; i++)
				{
					tab[i] = p.tab[i];
				}

				sommet = p.sommet;
			}
			
			//destructeur
			~PileDM()
			{
				delete[] tab;
			}
			 
			// Modificateurs
			void empiler(const T& e) throw(std::length_error)
			{
				if (sommet + 1 < tailleMax)//pile pas encore pleine
				{
					sommet += 1; //incrémentation compteur, si nous commençons à -1 nous sommes à 0 au premier élément ajouté
					tab[sommet] = e;
				}
				else
				{
					throw std::length_error("La liste est pleine, impossible d'ajouter un élément.");
				}
			}

			const T depiler() throw(std::logic_error)
			{
				if (!estVide())
				{
					return tab[sommet--];//it returns tab[sommet] before changing value of sommet.
				}
				else
				{
					throw std::logic_error("La liste est vide, aucun élément à enlever.");
				}
			}

			//Sélecteurs
			bool estVide() const
			{
				return(sommet == -1);//vide si true
			}

			//retourne la taille
			int get_taille() const
			{
				return sommet;
			}

			// consulte l’élément au sommet
			const T& get_sommet() const
			{
				return tab[sommet];
			}

			void resize(const PileDM<T>& p) throw(std::bad_alloc)
			{
				int nouvelleTaille = sommet++ * 2;//
				tab = new T[nouvelleTaille];

				for (int i = 0; i < sommet; i++)
				{
					tab[i] = p.tab[i];
				}
				tailleMax = nouvelleTaille;
			}

			//surcharge d'opérateurs
			const PileDM<T>& operator=(const PileDM<T> &p) throw (std::bad_alloc)
			{
				if (tab != 0) delete[] tab; //on nettoie l'objet qu'on veut ecraser
				tab = new T[p.tailleMax];

				tailleMax = p.tailleMax;
				for (int i = 0; i < tailleMax; i++)
				{
					tab[i] = p.tab[i];
				}
				sommet = p.sommet;

				return (*this);
			}


			//template <typename U> friend std::ostream& operator<<(std::ostream&, const PileDM<U>&)


		private: 

			T* tab;
			int sommet; //indice du dernier élément
			int tailleMax;
			int taille;
			static const int MAX_PILE = 100;

	};

}//namespace pile

#endif //PILEDM


