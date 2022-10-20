#pragma once
#ifndef FILE
#define FILE

#include <stdexcept>

using namespace std;

namespace file
{

	template<typename T>
	class File
	{
	public:
		//constructeurs et destructeurs
		File();
		File(int max);
		~File();

		// modificateurs
		void enfiler(const T&);
		T defiler();

		// selecteurs
		int taille() const;
		bool estVide() const;
		bool estPleine() const;
		T& premier() const; // tête de la file
		T& dernier() const; // queue de la file

	private:
		T* tab;
		int tete;
		int queue;
		int tailleMax;
		int cpt;
	};


	// Les methodes utilisant template doivent etre definis dans le header
	// Sources: https://stackoverflow.com/questions/456713/why-do-i-get-unresolved-external-symbol-errors-when-using-templates

	template<typename T>
	File<T>::File()
	{
		tab = new T[100];
		tete = 0;
		queue = 0;
		cpt = 0;
		tailleMax = 100;
	}

	template<typename T>
	File<T>::File(int max)
	{
		tab = new T[max];
		tete = 0;
		queue = -1;
		cpt = 0;
		tailleMax = max;
	}

	template<typename T>
	File<T>::~File()
	{
		delete[] tab;
	}

	template<typename T>
	void File<T>::enfiler(const T& e)
	{
		if (cpt < tailleMax)
		{
			tab[queue + 1] = e;
			queue = (queue + 1) % tailleMax;
			cpt++;
			cpt = cpt;
		}
		else
			throw length_error("Enfiler : la file est pleine!");
	}

	template<typename T>
	T File<T>::defiler()
	{
		if (cpt != 0)
		{
			T elementaDefiler = tab[tete];
			tete = (tete + 1) % tailleMax; //permet de « boucler » si on dépasse
			cpt--;
			return elementaDefiler;
		}
		else
			throw logic_error("Defiler: la file est vide!");
	}

	template<typename T>
	inline int File<T>::taille() const
	{
		return cpt;
	}

	template<typename T>
	inline bool File<T>::estVide() const
	{
		if (cpt == 0)
			return true;
		else
			return false;
	}

	template<typename T>
	inline bool File<T>::estPleine() const
	{
		if (cpt == tailleMax)
			return true;
		else
			return false;
	}

	template<typename T>
	T& File<T>::premier() const
	{
		return tab[tete];
	}

	template<typename T>
	T& File<T>::dernier() const
	{
		return tab[queue];
	}

}

#endif // !FILE