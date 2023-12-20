#ifndef TRAJET_H_INCLUDED
#define TRAJET_H_INCLUDED

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include<time.h>

#include "Type.h"

class Sommet;
class Trajet
{
private :

    int m_num;
    std::string m_nom;
    Type* m_type;
    Sommet* m_depart;
    Sommet* m_arrivee;
    bool m_actif;
    int m_heure;
    int m_min;
    int m_sec;


public :

    Trajet (int _num, std::string _nom, Type* _type, Sommet* _depart, Sommet* _arrivee, int _min, int _sec);

    std::string getNom();

    int getHeure();
    int getNum();
    int getMin();
    int getSec();
    bool getActif();
    void setActif(bool a);

    Sommet* getDepart();
    Sommet* getArrivee();

    Type* getType();

    void CalculTrajet();
};


#endif // TRAJET_H_INCLUDED
