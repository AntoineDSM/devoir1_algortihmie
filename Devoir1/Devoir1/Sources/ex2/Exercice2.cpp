#include <iostream>
#include <stdexcept>
#include "..\..\Header\ex2\File.h"
#include "..\..\Header\ex2\Machine.h"

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