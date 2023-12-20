#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <time.h>

#include "Trajet.h"

class Sommet
{
private :

    int m_num;
    std::string m_nom;
    float m_altitude;
    std::vector <Trajet*> m_entrant;
    std::vector <Trajet*> m_sortant;
    std::vector <Sommet*> m_successeurs;

    Sommet * m_antecedent = NULL;
    int m_couleur = 0;        //Le sommet quand il n'a pas encore été découvert
    int m_distance = 1000000; //Grand nombre représentant l'infini au debut de l'algorithme

public :

    Sommet (int _num, std::string _nom, float _altitude);

    std::string getNom();

    int getNum();
    int getCouleur ();
    int setCouleur ();
    int setCouleur2();
    int getDistance ();
    int setDistance (int _distance);

    float getAltitude();

    std::vector <Trajet*>  getSortant();
    std::vector <Sommet*> getSuccesseurs();

    void setEntrant(Trajet* _entrant);
    void setSortant(Trajet* _sortant);
    void ajouterSucc(Sommet* s);
    void afficher();
    void ajouterAntecedent(Sommet* antecedent);

    Sommet* setAntecedent (Sommet * _antecedent);
    Sommet(int num):m_num{num} {};
    Sommet* getAntecedent ();

    bool getCouleur2(int f);

};

#endif // SOMMET_H_INCLUDED
