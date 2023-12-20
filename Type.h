#ifndef TYPE_H_INCLUDED
#define TYPE_H_INCLUDED

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

class Type
{
private :

    std::string m_nom;
    std::string m_type;
    float m_temps;
    int m_attente;

public :
    Type (std::string _nom, std::string _type, float _temps, int _attente);

    int getAttente();
    int setAttente();

    float getTemps();
    float setTemps();

    std::string getNom();
    std::string getType();
    std::string setNom();
    std::string setType();

};
#endif // TYPE_H_INCLUDED
