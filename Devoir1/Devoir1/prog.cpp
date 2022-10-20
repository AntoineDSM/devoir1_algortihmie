#include <iostream>
#include <algorithm>
#include <stdexcept>

#define MAIN1

//-------------------------------------------------------------------------------DECOMMENTER LE MAIN CORRESPONDANT A L'EXERCICE SOUHAITE------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------MAIN POUR LE PREMIER EXERCICE---------------------------------------------------------------------------------------------

#ifdef MAIN1

#include "Header/ex1/GameMaster.h"

void demandeRejouer()
{
	std::string autrePartie = GameMaster::demandeAutrePartie();
	if (autrePartie == "oui" || autrePartie == "Oui")
	{
		return;
	}
	if (autrePartie == "non" || autrePartie == "Non")
	{
		std::exit(1);
	}
}

void deroulementPartie()
{
	std::vector<std::string> noms = GameMaster::demandeNomsJoueurs();
	int nombreCarte = GameMaster::demanderNombreCarteTirage();
	GameMaster GM = GameMaster::GameMaster(nombreCarte, noms[0], noms[1]);
	demandeRejouer();
}

int
main()
{
    while (1)
    {
        deroulementPartie();
    }
    return 0;
}

#endif

//-------------------------------------------------------------------------------------------MAIN POUR LE DEUXIEME EXERCICE---------------------------------------------------------------------------------------------

#ifdef MAIN2

#include "Header/ex2/Machine.h"
#include "Header/ex2/File.h"

int NB_PISTON = 100;
int NB_PIECE = 500;

flux s(NB_PIECE);
flux st(NB_PIECE);
flux sj(NB_PIECE);
flux sa(NB_PIECE);
flux tp(NB_PIECE);
flux jp(NB_PIECE);
flux ap(NB_PIECE);
flux p(NB_PIECE);

Machine ms(0.1, 0);
Machine mt(2.0, 1);
Machine mj(3.0, 2);
Machine ma(2.5, 3);
Machine mp(1.0, 4);

double tcs = 0.0;
double tct = 0.0;
double tcj = 0.0;
double tca = 0.0;
double tcp = 0.0;


int main()
{
	for (int i = 0; i < NB_PIECE; i++)
	{
		s.enfiler(0.0);
	}

	while (1)
	{
		// La machine de tri traite une piece
		if (s.taille() != 0)
		{
			tcs += ms.traitement();


			mt19937_64 gen{ random_device()() };
			uniform_real_distribution<float> dis{ 0.0, 3.0 };
			for (int i = 0; i < NB_PIECE; i++)
			{

				s.defiler();
				float nb = dis(gen);
				if (nb < 1)
					st.enfiler(tcs);
				else if (nb >= 2)
					sj.enfiler(tcs);
				else
					sa.enfiler(tcs);
			}
		}

		// La machine d'usinage de tete traite une piece
		if (st.taille() > 0)
		{
			double pi = st.defiler();
			if (pi > tct)
				tct = pi + mp.traitement();
			else
				tct += mp.traitement();
			tp.enfiler(tct);
		}

		// La machine d'usinage de jupe traite une piece
		if (sj.taille() > 0)
		{
			double pi = sj.defiler();
			if (pi > tcj)
				tcj = pi + mp.traitement();
			else
				tcj += mp.traitement();
			jp.enfiler(tcj);
		}

		// La machine d'usinage de d'axe traite une piece
		if (sa.taille() > 0)
		{
			double pi = sa.defiler();
			if (pi > tca)
				tca = pi + mp.traitement();
			else
				tca += mp.traitement();
			ap.enfiler(tca);
		}

		// La machine d'assamblage traite une piece
		if ((tp.taille() > 0) && (jp.taille() > 0) && (ap.taille() > 0))
		{
			double pit = tp.defiler();
			double pij = jp.defiler();
			double pia = ap.defiler();

			double pi;
			if (pit > pij)
				pi = pit;
			else
				pi = pij;
			if (pia > pi)
				pi = pia;

			if (pi > tcp)
				tcp = pi + mp.traitement();
			else
				tcp += mp.traitement();

			p.enfiler(tcp);
		}

		// La machine d'assamblage a traite le nombre de pistons demandes
		if (p.taille() == NB_PISTON)
		{
			std::cout << p.taille() << " ont ete produits! Le temps de production est de " << p.dernier() << " minutes" << std::endl;
			exit(EXIT_SUCCESS);
		}
	}
	return 0;
}

#endif

//-------------------------------------------------------------------------------------------MAIN POUR LE TROISIEME EXERCICE----------------------------------------------------------------------------------------------

#ifdef MAIN3

#include "Header/ex3/Dictionnaire.h"
#include "Header/ex3/ArbreBinaire.h"
int
main()
{
    Dictionnaire* dict = new Dictionnaire();
    std::cout << "\nOn ajoute les mots abas, arbre, arbuste, bas puis afficher le dictionnaire :\n\n";
    dict->AjouterMot("abas");
    dict->AjouterMot("arbre");
    dict->AjouterMot("arbuste");
    dict->AjouterMot("bas");
    dict->AfficherDictionnaire();
    std::cout << "\nOn recherche les mots abas, pol, navire et arbre :\n\n";
    dict->ChercherMot("abas");
    dict->ChercherMot("pol");
    dict->ChercherMot("navire");
    dict->ChercherMot("arbre");
    std::cout << "\nEnlever le mot abas et afficher le dictionnaire :\n\n";
    dict->EnleverMot("abas");
    dict->AfficherDictionnaire();
    std::cout << "\n";
    std::cout << "\nEnlever le mot voiture alors qu'il n'y est pas, l'ajouter et afficher le dictionnaire :\n\n";
    dict->EnleverMot("voiture");
    dict->AjouterMot("voiture");
    dict->AfficherDictionnaire();
    std::cout << "\nEssayer d'enlever le mot a nouveau, afficher le dictionnaire :\n\n";
    dict->EnleverMot("voiture");
    dict->AfficherDictionnaire();
    
    return 0;
}

#endif

//--------------------------------------------------------------------------------------MAIN POUR LE QUATRIEME EXERCICE---------------------------------------------------------------------------

#ifdef MAIN4

#include "ArbreGenealogique.h"
#include "Arbre.h"
#include "Personne.h"

int
main()
{
    ArbreGenealogique* arbreG = new ArbreGenealogique(2022);

    //On ajoute une liste de perzonnes à notre arbre en créant des liens de parenté.
    Personne GP1 = arbreG->ajouterMembre("GP1", "Inconnu", "Noir", 1948);
    Personne GP2 = arbreG->ajouterMembre("GP2", "Inconnu", "Marron", 1944);
    Personne Gabriel = arbreG->ajouterMembre("Gabriel", "DSM", "Vert", 1965, GP1, GP2);
    Personne Marianne = arbreG->ajouterMembre("Marianne", "DSM", "Marron", 1965, GP1, GP2);
    Personne Andre = arbreG->ajouterMembre("Andre", "DSM", "Vert", 1965, GP1, GP2);
    Personne Rita = arbreG->ajouterMembre("Rita", "DSM", "Bleu", 1965, GP1, GP2);
    Personne Damien = arbreG->ajouterMembre("Damien", "DSM", "Noir", 1965, GP1, GP2);
    Personne Benoit = arbreG->ajouterMembre("Benoit", "DSM", "Bleu", 1965, GP1, GP2);
    Personne GP3 = arbreG->ajouterMembre("GP3", "Inconnu", "Bleu", 1941);
    Personne GP4 = arbreG->ajouterMembre("GP4", "Inconnu", "Bleu", 1942);
    Personne Claudine = arbreG->ajouterMembre("Claudine", "Fayard", "Vert", 1959,GP3,GP4);
    Personne Christine = arbreG->ajouterMembre("Christine", "Fayard", "Noir", 1962, GP3, GP4);
    Personne Antoine = arbreG->ajouterMembre("Antoine", "DSM", "Bleu", 2001,Benoit, Claudine);
    Personne Alexis = arbreG->ajouterMembre("Alexis", "DSM", "Vert", 2003, Benoit, Claudine);
    Personne Marine = arbreG->ajouterMembre("Marine", "Veillon", "Vert", 2000);
    Personne Laura = arbreG->ajouterMembre("Laura", "Saque", "Vert", 1996, Christine);
    Personne Loic = arbreG->ajouterMembre("Loic", "Saque", "Marron", 1990, Christine);
    Personne Paul = arbreG->ajouterMembre("Paul", "Saque", "Bleu", 2018, Loic);

    //Test des différentes méthodes implémentées.
    arbreG->calculerMoyenneAge();
    arbreG->listerPersonnesCouleurYeux("Vert");
    arbreG->listerPersonnesCouleurYeux("Marron");
    arbreG->listerPersonnesCouleurYeux("Bleu");
    arbreG->listerPersonnesCouleurYeuxAvant(Antoine, "Marron");
    arbreG->listerPersonnesCouleurYeuxAvant(Rita, "Noir");
    arbreG->nombreDeGeneration();
    //Parcours dans l'arbre, par défaut In Order si aucun paramètre n'est rentrée.
    arbreG->lireDescendancePersonne(GP1,0);//In order
    arbreG->lireDescendancePersonne(GP1,2);//Pré order
    arbreG->lireDescendancePersonne(Benoit,0);//In order
    arbreG->lireDescendancePersonne(GP1, 1);//Post order
    return 0;
}

#endif

//--------------------------------------------------------------------------------------MAIN POUR LE CINQUIEME EXERCICE---------------------------------------------------------------------------

#ifdef MAIN4

#include "Header/ex5/Liste.h"
#include "Header/ex5/Noeud.h"

using namespace std;
using namespace noeud;
using namespace liste;

int main()
{

	Liste<int> l = Liste<int>();

	l.ajouterTete(5);
	l.ajouterTete(3);
	l.ajouterTete(2);
	l.ajouterTete(9);
	l.ajouterTete(4);
	l.ajouterTete(6);
	l.ajouterTete(1);
	l.ajouterTete(8);
	l.ajouterTete(0);
	l.ajouterTete(7);
	l.ajouterQueue(2);

	Noeud<int>* head = l.getTete();
	Noeud<int>* tail = l.getQueue();
	Noeud<int>* middle = head->getSuivant();

	int total1 = head->somme();
	int total2 = tail->somme();
	int total3 = middle->somme();
	cout << "Somme des ID en partant de la tete de liste: " << total1 << endl;
	cout << "Somme des ID en partant de la queue de liste: " << total2 << endl;
	cout << "Somme des ID en partant d'une element quelconque de la liste: " << total3 << endl;
	return 0;
}

#endif