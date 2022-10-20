#pragma once
#include <string>
#include <ostream>


class Personne {

	public :
	
		std::string nom;

		std::string prenom;

		int anneeNaissance;

		std::string couleurYeux;

		Personne() : nom(""), prenom(""), couleurYeux(""), anneeNaissance(0)
		{
			//rien de plus a ajouter
		}

		Personne(std::string valeurString, int valeurInt) : nom(valeurString), prenom(valeurString), couleurYeux(valeurString), anneeNaissance(valeurInt)
		{
			//rien de plus a ajouter
		}

		//Constructeur par passage de paramètrez
		Personne(std::string prenom, std::string nom, std::string couleurYeux, int anneeNaissance) : nom(nom), prenom(prenom), couleurYeux(couleurYeux), anneeNaissance(anneeNaissance)
		{
			//rien de plus à ajouter
		}

		//Permet d'afficher dans la console notre type personne.
		friend std::ostream& operator<<(std::ostream& out, const Personne& p) {
			out << "Prenom : " << p.prenom << ", nom : " << p.nom << ", annee de naissance : " << p.anneeNaissance << ", couleur des yeux : " << p.couleurYeux << "\n";
			return out;
		}
		
		//Permet d'effectuer des opérations de comparaison sur notre type
		friend bool operator==(const Personne& x, const Personne& y)
		{
			{
				if (x.prenom == y.prenom && x.nom == y.nom && x.couleurYeux == y.couleurYeux && x.anneeNaissance == y.anneeNaissance)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}

		//Permet d'effectuer des opérations de comparaison sur notre type
		friend bool operator!=(const Personne& x, const Personne& y)
		{
			{
				if (x.prenom != y.prenom || x.nom != y.nom || x.couleurYeux != y.couleurYeux || x.anneeNaissance != y.anneeNaissance)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
};

