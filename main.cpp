#include "Sommet.h"
#include "Graphe.h"
#include "Trajet.h"
#include "Type.h"
#include "Compte.h"


int main()
{
    int a=0;
    int b=0;
    int d=0;
    int y=0;

    int choix=0;

    std :: vector <std :: string> nomClient;

    Graphe g{"data_arcs.txt"};

    g.TUTO();

    do
    {
        switch (choix)
        {
        case 0 :
        {
            choix=g.Accueil();
        }
        break;

        case 1 :
        {
            a=g.afficher();
            if (a==2)
            {
                choix=0;
            }

        }
        break;

        case 2 :
        {
            b=g.afficherTrajets();
            if(b==0)
            {
                choix=0;
            }

        }
        break;

        case 3 :
        {
            g.AccueilTrajet();
            choix=0;
        }
        break;

        case 4 :
        {
            d=g.Connexion(&y);
            if(d==3)
            {
                choix =0;
            }
            else if (d==4)
            {
                choix=4;
            }
        }
        break;
        case 5 :
        {
            choix=5;
        }
        break;
        }
    }
    while (choix!=5);

    return 0;
}
