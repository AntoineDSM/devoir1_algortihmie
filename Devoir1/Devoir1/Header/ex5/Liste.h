#pragma once
#ifndef LISTE
#define LISTE

#include <iostream>
#include "Noeud.h"

using namespace std;
using namespace noeud;


namespace liste
{
    template<typename T>
    class Liste {
    public:
        Noeud<T>* tete;
        Noeud<T>* queue;
    public:
        Liste();
        void ajouterTete(const T& e);
        void ajouterQueue(const T& e);
        void ajouterAvant(Noeud<T>* sNoeud, const T& e);
        void ajouterApres(Noeud<T>* pNoeud, const T& e);
        void supprimer(Noeud<T>* pNoeud);
        Noeud<T>* getTete();
        Noeud<T>* getQueue();
        void setTete(Noeud<T>* teteNoeud);
        void setQueue(Noeud<T>* queueNoeud);
        void displayList();

    };

    template<typename T>
    Liste<T>::Liste()
    {
        tete = nullptr;
        queue = nullptr;
    }

    template<typename T>
    void Liste<T>::ajouterTete(const T& e)
    {
        Noeud<T>* nouveauNoeud = new Noeud<T>(e);
        nouveauNoeud->setSuivant(tete);

        if (tete != nullptr)
            tete->setPrecedent(nouveauNoeud);
        else
            setQueue(nouveauNoeud);
        setTete(nouveauNoeud);
        nouveauNoeud->setId(0);
        cout << " Ajout d'un element a la tete: ";
        displayList();
    }

    template<typename T>
    void Liste<T>::ajouterQueue(const T& e)
    {
        Noeud<T>* nouveauNoeud = new Noeud<T>(e);
        nouveauNoeud->setPrecedent(queue);
        nouveauNoeud->setSuivant(nullptr);

        int id;
        if (queue != nullptr)
        {
            queue->setSuivant(nouveauNoeud);
            id = getQueue()->getId();
            nouveauNoeud->setId(id + 1);
        }
        else
            id = 0;
        nouveauNoeud->setId(id);
        setQueue(nouveauNoeud);

        if (tete == nullptr)
            setTete(nouveauNoeud);

        cout << " Ajout d'un element a la queue: ";
        displayList();
    }
    template<typename T>
    void Liste<T>::ajouterAvant(Noeud<T>* sNoeud, const T& e)
    {
        if (sNoeud == nullptr)
        {
            throw "Le noeud ne doit pas etre NULL!";
            return;
        }
        Noeud<T>* nouveauNoeud = new Noeud(e);
        nouveauNoeud->setPrecedent(sNoeud->getPrecedent());
        sNoeud->setPrecedent(nouveauNoeud);
        nouveauNoeud->setSuivant(sNoeud);

        nouveauNoeud->setId(nouveauNoeud->getPrecedent()->getId() + 1);
        if (sNoeud == tete)
            tete = nouveauNoeud;
    }

    template<typename T>
    void Liste<T>::ajouterApres(Noeud<T>* pNoeud, const T& e)
    {
        if (pNoeud == nullptr)
        {
            throw "Le noeud ne doit pas etre NULL!";
            return;
        }

        Noeud<T>* nouveauNoeud = new Noeud(e);
        nouveauNoeud->setSuivant(pNoeud->getSuivant());
        pNoeud->setSuivant(nouveauNoeud);
        nouveauNoeud->setPrecedent(pNoeud);

        nouveauNoeud->setId(nouveauNoeud->getPrecedent()->getId() + 1);
        if (pNoeud == queue)
            queue = nouveauNoeud;
    }

    template<typename T>
    void Liste<T>::supprimer(Noeud<T>* aNoeud)
    {
        if (aNoeud == tete)
            tete = aNoeud->getSuivant();
        if (aNoeud == queue)
            queue = aNoeud->getPrecedent();

        aNoeud.getPrecedent()->setSuivant(aNoeud->getSuivant);
        aNoeud.getSuivant()->setPrecedent(aNoeud->getPrecedent);

        aNoeud->getPrecedent()->setId(aNoeud->getPrecedent()->getId());

        delete aNoeud;
    }
    template<typename T>
    Noeud<T>* Liste<T>::getTete()
    {
        return tete;
    }
    template<typename T>
    Noeud<T>* Liste<T>::getQueue()
    {
        return queue;
    }
    template<typename T>
    void Liste<T>::setTete(Noeud<T>* teteNoeud)
    {
        tete = teteNoeud;
    }
    template<typename T>
    inline void Liste<T>::setQueue(Noeud<T>* queueNoeud)
    {
        queue = queueNoeud;
    }
    template<typename T>
    void Liste<T>::displayList()
    {
        Noeud<T>* temp = tete;
        while (temp->getSuivant() != nullptr)
        {
            cout << *temp->getData() << " <==> ";
            temp = temp->getSuivant();
        }
        cout << *temp->getData() << endl;
    }
}
#endif // !LISTE