#include "Sommet.h"
#include "Graphe.h"
#include "Trajet.h"
#include "Type.h"
#include "Compte.h"

Trajet :: Trajet (int _num, std::string _nom, Type* _type, Sommet* _depart, Sommet* _arrivee, int _min, int _sec)
    : m_num(_num),m_nom(_nom), m_type(_type), m_depart(_depart), m_arrivee(_arrivee), m_min(_min), m_sec(_sec)
{

}

int Trajet :: getNum()
{
    return m_num;
}

std::string Trajet :: getNom()
{
    return m_nom;
}

Type* Trajet :: getType()
{
    return m_type;
}

Sommet* Trajet :: getDepart()
{
    return m_depart;
}

Sommet* Trajet :: getArrivee()
{
    return m_arrivee;
}

int Trajet :: getHeure()
{
    return m_heure;
}

int Trajet :: getMin()
{
    return m_min;
}

int Trajet :: getSec()
{
    return m_sec;
}

bool Trajet :: getActif()
{
    return m_actif;
}

void Trajet :: setActif(bool a)
{
    m_actif=a;
}

/// Calcul des temps de trajets

void Trajet :: CalculTrajet()
{
    int poids=0.0;
    int heure=0;
    int minute=0;
    int seconde=0;

    poids = m_type->getAttente() + fabs (((m_depart->getAltitude()-m_arrivee->getAltitude())/100.0)* m_type->getTemps() ); // Temps en seconde

    while (minute>=60)  // Calcul des heures
    {
        heure++;
        minute-=60;
    }
    minute=(poids-poids%60)/60; // Calcul des minutes
    seconde=poids%60; // Calcul des secondes

    m_heure=heure; // Récupération des heures
    m_min=minute;  // Recupération des minutes
    m_sec=seconde; // Recupération des secondes
}

