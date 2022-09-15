//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <iostream>
#include <algorithm>

#include "GameMaster.h"


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


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
