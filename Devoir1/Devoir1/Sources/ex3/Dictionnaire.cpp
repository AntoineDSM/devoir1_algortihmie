#include "..\..\Header\ex3\Dictionnaire.h"
#include "..\..\Header\ex3\ArbreBinaire.h"
#include <string>

using namespace arbreBinaire;

void Dictionnaire::ChercherMot(std::string data)
{
    if (data.empty())
    {
        std::cout << "Impossible de rechercher un mot vide.\n";
        return;
    }
    auto _data = data.std::string::c_str();//On convertie notre string en const char*
    bool motExiste = arbre->ChercherValeur(_data);//on regarde si le mot est dans notre dictionnaire.
    if (motExiste)
    {
        std::cout << "le mot est dans le dictionnaire\n";
    }
    else
    {
        std::cout << "le mot n'est pas dans le dictionnaire\n";
    }
}

void Dictionnaire::AjouterMot(std::string data)
{
    if (data.empty())
    {
        std::cout << "Impossible d'ajouter un mot vide.\n";
        return;
    }
    auto _data = data.std::string::c_str();//On convertie notre string en const char*
    int size = static_cast<int>(std::strlen(_data));
    if (arbre->cpt == 0)
    {
        arbre->AjouterListe(arbre->racine, _data, size);
    }
    else
    {
        if (!arbre->ChercherValeur(_data))//on regarde si le mot est dans notre dictionnaire, si oui, on n'ajoute pas le mot une seconde fois.
        {
            arbre->AjouterListe(arbre->racine, _data, size);
        }
        else
        {
            std::cout << "le mot est deja dans le dictionnaire\n";
        }
    }
}

void Dictionnaire::AfficherDictionnaire()
{
    arbre->AfficherArbre(arbre->racine->gauche);
}

void Dictionnaire::EnleverMot(std::string data)
{
    if (data.empty())
    {
        std::cout << "Impossible d'enlever un mot vide.\n";
        return;
    }
    auto _data = data.std::string::c_str();//On convertie notre string en const char*
    int size = static_cast<int>(std::strlen(_data));
    if (arbre->ChercherValeur(_data))//on regarde si le mot est dans notre dictionnaire, si oui on le supprime.
    {
        arbre->SupprimerListe(arbre->racine->gauche, _data, size);
    }
    else
    {
        std::cout << "le mot n'est pas dans le dictionnaire\n";
    }
}

