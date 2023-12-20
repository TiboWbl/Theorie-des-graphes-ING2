#include "Sommet.h"
#include "Graphe.h"
#include "Trajet.h"
#include "Type.h"
#include "Compte.h"

/// Constructeur surchargé

Compte :: Compte (int _num, std::string _pseudo, std::string _mdp, std::vector<bool> _preference)
    : m_num(_num), m_pseudo(_pseudo), m_mdp(_mdp), m_preference(_preference)
{

}

int Compte :: getNum()
{
    return m_num;
}

std::string Compte :: getPseudo()
{
    return m_pseudo;
}

std::string Compte :: getMdp()
{
    return m_mdp;
}

std::vector <bool> Compte :: getPreference()
{
    return m_preference;
}

void Compte :: setNum(int _num)
{
    m_num=_num;
}

void Compte :: setPseudo(std :: string  _pseudo)
{
    m_pseudo=_pseudo;
}

void Compte :: setMdp(std :: string  _mdp)
{
    m_mdp=_mdp;
}

void Compte :: setPreferences(std::vector<bool> preference)
{
    m_preference=preference;
}
