#include "..\..\Header\ex2\Dictionnaire.h"
#include "..\..\Header\ex2\ArbreBinaire.h"
#include <string>

using namespace arbreBinaire;

void Dictionnaire::ChercherMot(std::string data)
{
    auto _data = data.std::string::c_str();
    bool motExiste = arbre->ChercherValeur(_data);
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
    auto _data = data.std::string::c_str();
    arbre->AjouterListe(arbre->racine, _data);
}

void Dictionnaire::AfficherDictionnaire()
{
    arbre->AfficherArbre(arbre->racine->gauche);//, arbre->NombreNoeud());
}

void Dictionnaire::EnleverMot(std::string data)
{
    auto _data = data.std::string::c_str();
    if (arbre->ChercherValeur(_data))
    {
        arbre->SupprimerListe(arbre->racine->gauche, _data);
    }
    else
    {
        std::cout << "le mot n'est pas dans le dictionnaire\n";
    }
}

