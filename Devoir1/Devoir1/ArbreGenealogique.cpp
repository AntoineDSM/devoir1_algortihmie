#include "ArbreGenealogique.h"

//permet de savoir lorsqu'un �l�ment est initialis� ou non.
std::string ArbreGenealogique::defaultValue = std::string();

//permet �galement de pouvoir compar� entre argument par defaut ou non pour certaines m�thodes.
Personne ArbreGenealogique::personneParDefaut = Personne();

//Permet d'ajouter un membre � notre arbre, un ou deux parents peuvent �tre renseign�s. 
Personne ArbreGenealogique::ajouterMembre(std::string prenom, std::string nom, std::string couleurYeux, int anneeNaissance, Personne& parent1, Personne& parent2)//std::string nomParent1, std::string prenomParent1, std::string nomParent2, std::string prenomParent2)
{
	std::vector<NoeudArbreGenealogique<Personne>*> personnes;
	std::vector<NoeudArbreGenealogique<Personne>*> parents;
	parents = creerDefaultParents();//Pour eviter des elements non allou�s ensuite, on cr�� des parents vides.
	if (arbre->cpt == 0)
	{
		Personne premierePersonne = Personne(prenom, nom, couleurYeux, anneeNaissance);
		arbre->AjouterNoeud(premierePersonne);
		return premierePersonne;
	}
	else
	{
		if (parent1 != personneParDefaut || parent2 != personneParDefaut)//Nous recherchons les noeuds des parents voulu pour les affecter � notre nouveau noeud si les parents existent dans l'arbre.
		{
			personnes = arbre->listeElementArbre(arbre->racine);
			if (personnes.size() != 0)
			{
				for (NoeudArbreGenealogique<Personne>* p : personnes)
				{
					if (p->data.nom == parent1.nom && p->data.prenom == parent1.prenom)
					{
						parents[0] = p;
					}
					if (p->data.nom == parent2.nom && p->data.prenom == parent2.prenom)
					{
						parents[1] = p;
					}
				}
			}
		}

		if (parents[0]->data.nom == defaultValue && parents[1]->data.nom == defaultValue)
		{
			parents = std::vector<NoeudArbreGenealogique<Personne>*>();
		}

		Personne nouvellePersonne = Personne(prenom, nom, couleurYeux, anneeNaissance);
		arbre->AjouterNoeud(nouvellePersonne, parents);

		return nouvellePersonne;
	}
}

//Permet de r�cup�rer les personnes ayant la couleur d'yeux voulu dans la liste des �l�ments du vecteur personnes.
void ArbreGenealogique::listerPersonnesCouleurYeux(std::string couleur, std::vector<NoeudArbreGenealogique<Personne>*> personnes, bool afficher)
{
	if (personnes.empty())//Si le vecteur personnes est vide, nous voulons l'ensemble des personnes ayant la couleur demand�e. SInon nous ne parcourons que la liste fournie en param�tre (pour parcourir les anc�tres par exemple).
	{
		personnes = arbre->listeElementArbre(arbre->racine);
	}

	std::vector<NoeudArbreGenealogique<Personne>*> personnesAvecCouleur;

	for (NoeudArbreGenealogique<Personne>* elem : personnes)
	{
		if (elem->data.couleurYeux == couleur)//SI l'�l�ment de la liste poss�de la couleur demand�e, on l'ajoute a la liste de retour.
		{
			personnesAvecCouleur.push_back(elem);
		}
	}

	if (afficher)
	{
		std::cout << "Les personnes ayant les yeux " << couleur << " sont : \n" << std::endl;
	}

	for (NoeudArbreGenealogique<Personne>* elem : personnesAvecCouleur)
	{
		std::cout << elem->data << "\n";//ON affiche chacune des personnes.
	}
}

//Permet de calculer la moyenne d'age par rapport a l'ensemble des personnes de notre arbre
double ArbreGenealogique::calculerMoyenneAge()
{
	std::vector<NoeudArbreGenealogique<Personne>*> personnes;
	std::vector<int> listeAges;
	int personneAvecAgeInconnu = 0;//Quand nous ajoutons un �l�ment avec un seul parent, le second est par d�faut et son age est � 0, il ne faut pas le prendre en compte et donc diviser le total par le nombre de personne - les personnes par d�faut.

	personnes = arbre->listeElementArbre(arbre->racine);
	for (NoeudArbreGenealogique<Personne>* elem : personnes)
	{
		if (elem->data.anneeNaissance != 0)//Si la personne a un age coh�rent
		{
			listeAges.push_back(anneeCourante - elem->data.anneeNaissance);
		}
		else
		{
			personneAvecAgeInconnu++;//Nous avons une personne avec un age biais� suppl�mentaire.
		}
	}

	int total = 0;
	for (int i : listeAges)
	{
		total += i;
	}

	int size = static_cast<int>(personnes.size());
	std::cout << "La moyenne d'age est de : " << (double)total / (size-personneAvecAgeInconnu) << "ans.\n" << std::endl;
	return (double)total/size;
}

//Permet de chercher parmis les anc�tres d'une personne veux ayant la couleur d'yeux renseign�e.
void ArbreGenealogique::listerPersonnesCouleurYeuxAvant(Personne& personne, std::string couleur)
{

	std::vector<NoeudArbreGenealogique<Personne>*> personnes;

	NoeudArbreGenealogique<Personne>* noeud = arbre->chercherNoeud(personne);
	
	if(noeud == 0)
	{
		return;
	}

	personnes = arbre->listeElementPrecedentArbre(noeud);//On r�cup�re les anc�tres
	
	std::cout << "Les ancetres de " << personne.prenom << " " << personne.nom << " ayant les yeux " << couleur << " sont : \n" << std::endl;
	listerPersonnesCouleurYeux(couleur, personnes, false);
}

std::vector<NoeudArbreGenealogique<Personne>*> ArbreGenealogique::creerDefaultParents()
{
	Personne p1 = Personne();
	Personne p2 = Personne();
	NoeudArbreGenealogique<Personne>* n1 = arbre->CreerNoeud(p1);
	NoeudArbreGenealogique<Personne>* n2 = arbre->CreerNoeud(p2);
	std::vector<NoeudArbreGenealogique<Personne>*> parents;
	parents.push_back(n1);
	parents.push_back(n2);
	return parents;
}

//Nous retournons seulement la valeur du noeud ayant la hauteur la plus haute, car c'est celui ayant le plus de parents donc le nombre de g�n�rations de l'arbre.
void ArbreGenealogique::nombreDeGeneration()
{
	std::cout << "Le nombre de generations de l'arbre est de  : " << arbre->calculerTailleArbre() << ".\n" << std::endl;
}

void ArbreGenealogique::lireDescendancePersonne(Personne& personne, int order)//in order, post order et preorder
{
	std::vector<NoeudArbreGenealogique<Personne>*> descendance;
	NoeudArbreGenealogique<Personne>* noeud = arbre->chercherNoeud(personne);
	if (noeud == 0)
	{
		return;
	}

	if (order < 0 || order > 2)
	{
		order = 0;
	}
	//in order
	if (order == 0)
	{
		std::cout << "In order : \n" << std::endl;
		descendance = arbre->ParcoursInfixe(noeud);
	}
	//post order
	else if (order == 1)
	{
		std::cout << "Post order : \n" << std::endl;
		descendance = arbre->ParcoursSufixe(noeud);
	}
	//preorder
	else if (order == 2)
	{
		std::cout << "Pre order : \n" << std::endl;
		descendance = arbre->ParcoursPrefixe(noeud);
	}

	for (NoeudArbreGenealogique<Personne>* elem : descendance)
	{
		std::cout << elem->data << "\n";
	}
}