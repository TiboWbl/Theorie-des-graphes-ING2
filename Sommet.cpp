#include "Sommet.h"
#include "Graphe.h"
#include "Trajet.h"
#include "Type.h"
#include "Compte.h"

/// Constructeur
Sommet :: Sommet (int _num, std::string _nom, float _altitude)
    : m_num(_num),m_nom(_nom), m_altitude(_altitude)
{

}

/// Accesseurs
int Sommet :: getNum()
{
    return m_num;
}

std::string Sommet :: getNom()
{
    return m_nom;
}

float Sommet :: getAltitude()
{
    return m_altitude;
}

int Sommet ::  getCouleur ()
{
    return m_couleur;
}

bool Sommet :: getCouleur2(int f)
{
    return m_sortant[f]->getArrivee()->getCouleur();
}

int  Sommet :: getDistance ()
{
    return m_distance;
}

std::vector <Trajet*>  Sommet :: getSortant()
{
    return m_sortant;
}

Sommet* Sommet :: getAntecedent ()
{
    return m_antecedent;
}

std::vector <Sommet*> Sommet :: getSuccesseurs()
{
    return m_successeurs;
}

int Sommet :: setDistance (int _distance)
{
    return m_distance = _distance;
}

Sommet *  Sommet :: setAntecedent (Sommet * _antecedent)
{
    return m_antecedent = _antecedent;
}

int Sommet :: setCouleur ()
{
    return m_couleur = 1;
}

int Sommet :: setCouleur2 ()
{
    return m_couleur = 0;
}

void Sommet :: setEntrant(Trajet* _entrant)
{
    m_entrant.push_back(_entrant);
}

void Sommet :: setSortant(Trajet* _sortant)
{
    m_sortant.push_back(_sortant);
}

void Sommet :: ajouterAntecedent(Sommet* antecedent)
{
    m_antecedent=antecedent;
}

/// Ajout d'un successeur pour un sommet (pour les algos)
void Sommet :: ajouterSucc(Sommet* s)
{
    m_successeurs.push_back(s);
}


