#ifndef COMPTE_H_INCLUDED
#define COMPTE_H_INCLUDED

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <windows.h>

#include<time.h>

class Compte
{

private :

    int m_num;
    std :: string m_pseudo;
    std::string m_mdp;
    std :: vector <bool> m_preference;

public :

    Compte (int _num, std::string _pseudo, std::string _mdp, std::vector<bool> _preference);
    int getNum();
    std::string getPseudo();
    std::string getMdp();
    std::vector <bool> getPreference();
    void setNum(int _num);
    void setPseudo(std :: string  _pseudo);
    void setMdp(std :: string  _mdp);
    void setPreferences(std::vector<bool> preference);

};
#endif // COMPTE_H_INCLUDED
