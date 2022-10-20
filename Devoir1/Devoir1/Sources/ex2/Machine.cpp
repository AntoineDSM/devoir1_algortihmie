#include "..\..\Header\ex2\Machine.h"

Machine::Machine(double tempsTraitement, int ID)
{
    m_ID = ID;
    m_tempsTraitement = tempsTraitement;
}

double Machine::panne()
{
    // initialisation
    std::string nom = "";
    double tempsPanne = 0.0;

    // Creation d'une valeur aleatoire afin de tester la panne
    std::mt19937_64 gen{ std::random_device()() };
    std::uniform_real_distribution<double> dis{ 0.0, 1.0 };
    double enPanne = dis(gen);

    if (enPanne < 0.25)
    {
        // Nom de la machine en panne a indique a l'utilisateur
        if (m_ID == 0)
            nom = "machine de tri";
        else if (m_ID == 1)
            nom = "machine pour les tetes";
        else if (m_ID == 2)
            nom = "machine pour les jupes";
        else if (m_ID == 3)
            nom = "machine pour les axes";
        else if (m_ID == 4)
            nom = "machine d'assemblage";
        else
            throw std::invalid_argument("argument should be in the following list [0, 1, 2, 3]");

        // Creation d'une valeur aleatoire pour determiner le temps de panne (entre 5 et 10 min)
        std::mt19937_64 gen{ std::random_device()() };
        std::uniform_real_distribution<double> dis{ 5.0, 10.0 };
        tempsPanne += dis(gen);

        // Avertissement de panne
        std::cout << "La " << nom << " est tombe en panne.\nLe temps de reparation est estime a " << tempsPanne << " minutes." << std::endl;

    }

    return tempsPanne;
}

double Machine::traitement()
{
    return m_tempsTraitement + panne();
}

