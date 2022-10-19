#pragma once

#include "Personne.h"
#include "Arbre.h"
#include "NoeudArbreGenealogique.h"
#include <string>
#include <vector>

class ArbreGenealogique
{

public : 


	ArbreGenealogique(int anneeCourante) : anneeCourante(anneeCourante)
	{
		arbre = new Arbre<Personne>();
	}

	//Ajouter membre
	Personne ajouterMembre(std::string nom, std::string prenom, std::string couleurYeux, int anneeNaissancen, Personne& parent1 = personneParDefaut, Personne& parent2 = personneParDefaut);//std::string nomParent1 = defaultValue, std::string prenomParent1 = defaultValue, std::string nomParent2 = defaultValue, std::string prenomParent2 = defaultValue);

	//Lire descendance d'une personne
	void lireDescendancePersonne(Personne& personne, int order = 0);//0 : in order, 1 : pre order, 2 : post order

	//lister personne avec tel couleur d'yeux
	void listerPersonnesCouleurYeux(std::string couleur, std::vector<NoeudArbreGenealogique<Personne>*> personnes = std::vector<NoeudArbreGenealogique<Personne>*>(), bool afficher = true);

	//calculer moyenne d'age
	double calculerMoyenneAge();

	//calculer taille de l'arbre genealogique
	void nombreDeGeneration();

	//liste tous les ancêtres avec une couleur d'yeux donnée pour une personne (elle meme si oui), les ancêtres sont uniquements les parents précédents
	void listerPersonnesCouleurYeuxAvant(Personne& personne, std::string couleur);

	std::vector<NoeudArbreGenealogique<Personne>*> creerDefaultParents();

	private:
	
		Arbre<Personne>* arbre;

		static std::string defaultValue;

		static Personne personneParDefaut;

		int anneeCourante;

};

