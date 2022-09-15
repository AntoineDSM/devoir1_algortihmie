#pragma once
#include <iostream>
#include <math.h>
#include <random>

#ifndef UTILSDM

#define UTILSDM

namespace utilsDM {

	//methode permettant la génération d'un entier entre min et max.
	inline int randomInt(int min, int max)
	{
		std::random_device rd;//genere une nouvelle "seed" pour la generator, permet de faire varier le resultat de retour
		std::default_random_engine generator(rd());
		std::uniform_int_distribution<int> distribution(min, max);//distribution uniform entre min et max
		int random = distribution(generator);
		return random;
	}

}//utilsDM

#endif // UTILSDM


