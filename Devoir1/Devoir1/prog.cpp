
#include <iostream>
#include <algorithm>

#include "Header/ex2/Dictionnaire.h"
#include "Header/ex2/ArbreBinaire.h"

#include "Header/ex1/GameMaster.h"

#include "ArbreGenealogique.h"
#include "Arbre.h"
#include "Personne.h"

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

//-------------------------------------------------------------------------------DECOMMENTER LE MAIN CORRESPONDANT A L'EXERCICE SOUHAITE------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------MAIN POUR LE PREMIER EXERCICE---------------------------------------------------------------------------------------------
/*
int
main()
{
    while (1)
    {
        deroulementPartie();
    }
    return 0;
}
*/


//-------------------------------------------------------------------------------------------MAIN POUR LE TROISIEME EXERCICE----------------------------------------------------------------------------------------------
/*
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
*/


//--------------------------------------------------------------------------------------MAIN POUR LE QUATRIEME EXERCICE---------------------------------------------------------------------------
/*
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
}*/

