#pragma once
#include <iostream>
#include <vector>

#include "Carte.h"
#include "PileDM.h"

#ifndef  COMPTEURPOINTS

#define COMPTEURPOINTS

namespace compteurpoints {

	class CompteurPoints
	{

		public : 
			//gains du joueur 1.
			float gainsJ1;
			//gains du j�oueur 2
			float gainsJ2;

		public :

			//Constructeur
			CompteurPoints(pile::PileDM<carte::Carte> paquet1, pile::PileDM<carte::Carte> paquet2)
			{
				gainsJ1 = comptagePaquet(paquet1);
				gainsJ2 = comptagePaquet(paquet2);
			}

			//Methode permettant le d�compte des points pour nos joueurs, appel�e dans GameMaster
			float comptagePaquet(pile::PileDM<carte::Carte> paquet);

	};

}

#endif //COMPTEURPOINTS
