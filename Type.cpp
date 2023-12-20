#include "Sommet.h"
#include "Graphe.h"
#include "Trajet.h"
#include "Type.h"
#include "Compte.h"

/// Constructeur de Type

Type :: Type (std::string _nom, std::string _type, float _temps, int _attente)
    : m_nom(_nom), m_type(_type), m_temps(_temps), m_attente(_attente)
{

}

std::string Type :: getNom()
{
    return m_nom;
}

std::string Type :: getType()
{
    return m_type;
}

float Type :: getTemps ()
{
    return m_temps;
}

int Type :: getAttente()
{
    return m_attente;
}
