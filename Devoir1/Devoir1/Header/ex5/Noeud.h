#pragma once
#ifndef NOEUD
#define NOEUD

namespace noeud {

	template <typename T>
	class Noeud
	{
	public:
		Noeud(const T&);
		~Noeud();

		void setPrecedent(Noeud<T>* nPrecedent);
		void setSuivant(Noeud<T>* nSuivant);
		void setId(int nId);
		void setIdPrecedent(int nId);
		void setIdSuivant(int nId);

		Noeud<T>* getPrecedent() const;
		Noeud<T>* getSuivant() const;
		int getId() const;
		T* getData();

		int somme();
		int sommePrecedent(int somme);
		int sommeSuivant(int somme);

	private:
		Noeud* precedent;
		Noeud* suivant;
		T data;
		int id;
	};

	template<typename T>
	Noeud<T>::Noeud(const T& e)
	{
		data = e;
		precedent = nullptr;
		suivant = nullptr;
		id = 0;
	}
	template<typename T>
	Noeud<T>::~Noeud()
	{
		precedent = nullptr;
		suivant = nullptr;
	}
	template<typename T>
	void Noeud<T>::setPrecedent(Noeud<T>* nPrecedent)
	{
		if (nPrecedent == NULL)
			precedent = nullptr;
		else
			precedent = nPrecedent;
	}
	template<typename T>
	void Noeud<T>::setSuivant(Noeud<T>* nSuivant)
	{
		if (nSuivant == NULL)
			suivant = nullptr;
		else
			suivant = nSuivant;
	}
	template<typename T>
	void Noeud<T>::setId(int nId)
	{
		id = nId;
		setIdPrecedent(nId);
		setIdSuivant(nId);
	}

	template<typename T>
	void Noeud<T>::setIdPrecedent(int nId)
	{
		if (getPrecedent() != nullptr)
		{
			id = nId;
			Noeud* temp = getPrecedent();
			nId -= 1;
			temp->setIdPrecedent(nId);
		}
		if (getPrecedent() == nullptr)
		{
			id = nId;
		}
	}

	template<typename T>
	void Noeud<T>::setIdSuivant(int nId)
	{
		if ((getSuivant() != nullptr))
		{
			id = nId;
			Noeud* temp = getSuivant();
			nId += 1;
			temp->setIdSuivant(nId);
		}
		if (getSuivant() == nullptr)
		{
			nId += 1;
			id = nId;
		}
	}

	template<typename T>
	Noeud<T>* Noeud<T>::getPrecedent() const
	{
		return precedent;
	}
	template<typename T>
	Noeud<T>* Noeud<T>::getSuivant() const
	{
		return suivant;
	}

	template<typename T>
	int Noeud<T>::getId() const
	{
		return id;
	}

	template<typename T>
	inline T* Noeud<T>::getData()
	{
		return &data;
	}

	template<typename T>
	int Noeud<T>::somme()
	{
		int somme = getId();
		int somme1 = sommePrecedent(0);
		int somme2 = sommeSuivant(0);
		return somme1 + somme2 - somme;
	}

	template<typename T>
	int Noeud<T>::sommePrecedent(int somme)
	{
		if (this->getPrecedent() != nullptr)
		{
			somme = this->getPrecedent()->sommePrecedent(somme);
		}
		somme += this->getId();
		return somme;
	}

	template<typename T>
	int Noeud<T>::sommeSuivant(int somme)
	{
		if (this->getSuivant() != nullptr)
		{
			somme = this->getSuivant()->sommeSuivant(somme);
		}
		somme += this->getId();
		return somme;
	}
}

#endif // !NOEUD

