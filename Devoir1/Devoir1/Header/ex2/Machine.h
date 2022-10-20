#pragma once
#ifndef MACHINE
#define MACHINE

#include <string>
#include <map>
#include <iostream>
#include <random>
#include <tuple>
#include "Machine.h"
#include "File.h"

using namespace file;
using namespace std;

typedef File<double> flux;

class Machine
{
public:
    Machine(double tempsTraitement, int ID);
    double panne();
    double traitement();

protected:
    int m_ID;
    double m_tempsTraitement;
};

#endif // !MACHINE