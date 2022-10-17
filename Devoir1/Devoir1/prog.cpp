
#include <iostream>
#include <algorithm>
#include "Header/ex2/Dictionnaire.h"
#include "Header/ex2/ArbreBinaire.h"

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

//MAIN POUR LE PREMIER EXERCICE
//int
//main()
//{
//    while (1)
//    {
//        deroulementPartie();
//    }
//    return 0;
//}


//MAIN POUR LE SECOND EXERCICE
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
