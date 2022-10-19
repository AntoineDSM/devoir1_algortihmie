#include "ArbreGenealogique.h"

//permet de savoir lorsqu'un élément est initialisé ou non.
std::string ArbreGenealogique::defaultValue = std::string();

//permet également de pouvoir comparé entre argument par defaut ou non pour certaines méthodes.
Personne ArbreGenealogique::personneParDefaut = Personne();

//Permet d'ajouter un membre à notre arbre, un ou deux parents peuvent être renseignés. 
Personne ArbreGenealogique::ajouterMembre(std::string prenom, std::string nom, std::string couleurYeux, int anneeNaissance, Personne& parent1, Personne& parent2)//std::string nomParent1, std::string prenomParent1, std::string nomParent2, std::string prenomParent2)
{
	std::vector<NoeudArbreGenealogique<Personne>*> personnes;
	std::vector<NoeudArbreGenealogique<Personne>*> parents;
	parents = creerDefaultParents();//Pour eviter des elements non alloués ensuite, on créé des parents vides.
	if (arbre->cpt == 0)
	{
		Personne premierePersonne = Personne(prenom, nom, couleurYeux, anneeNaissance);
		arbre->AjouterNoeud(premierePersonne);
		return premierePersonne;
	}
	else
	{
		if (parent1 != personneParDefaut || parent2 != personneParDefaut)//Nous recherchons les noeuds des parents voulu pour les affecter à notre nouveau noeud si les parents existent dans l'arbre.
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

//Permet de récupérer les personnes ayant la couleur d'yeux voulu dans la liste des éléments du vecteur personnes.
void ArbreGenealogique::listerPersonnesCouleurYeux(std::string couleur, std::vector<NoeudArbreGenealogique<Personne>*> personnes, bool afficher)
{
	if (personnes.empty())//Si le vecteur personnes est vide, nous voulons l'ensemble des personnes ayant la couleur demandée. SInon nous ne parcourons que la liste fournie en paramètre (pour parcourir les ancêtres par exemple).
	{
		personnes = arbre->listeElementArbre(arbre->racine);
	}

	std::vector<NoeudArbreGenealogique<Personne>*> personnesAvecCouleur;

	for (NoeudArbreGenealogique<Personne>* elem : personnes)
	{
		if (elem->data.couleurYeux == couleur)//SI l'élément de la liste possède la couleur demandée, on l'ajoute a la liste de retour.
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
	int personneAvecAgeInconnu = 0;//Quand nous ajoutons un élément avec un seul parent, le second est par défaut et son age est à 0, il ne faut pas le prendre en compte et donc diviser le total par le nombre de personne - les personnes par défaut.

	personnes = arbre->listeElementArbre(arbre->racine);
	for (NoeudArbreGenealogique<Personne>* elem : personnes)
	{
		if (elem->data.anneeNaissance != 0)//Si la personne a un age cohérent
		{
			listeAges.push_back(anneeCourante - elem->data.anneeNaissance);
		}
		else
		{
			personneAvecAgeInconnu++;//Nous avons une personne avec un age biaisé supplémentaire.
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

//Permet de chercher parmis les ancêtres d'une personne veux ayant la couleur d'yeux renseignée.
void ArbreGenealogique::listerPersonnesCouleurYeuxAvant(Personne& personne, std::string couleur)
{

	std::vector<NoeudArbreGenealogique<Personne>*> personnes;

	NoeudArbreGenealogique<Personne>* noeud = arbre->chercherNoeud(personne);
	
	if(noeud == 0)
	{
		return;
	}

	personnes = arbre->listeElementPrecedentArbre(noeud);//On récupère les ancêtres
	
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

//Nous retournons seulement la valeur du noeud ayant la hauteur la plus haute, car c'est celui ayant le plus de parents donc le nombre de générations de l'arbre.
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