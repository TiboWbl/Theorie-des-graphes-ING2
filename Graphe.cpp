#include "Sommet.h"
#include "Graphe.h"
#include "Trajet.h"
#include "Type.h"
#include "Compte.h"


Graphe :: Graphe ()
{

}

/// Chargement du fichier data_arcs.txt
Graphe :: Graphe(std::string nomFichier)
{
    std::ifstream ifs{nomFichier};
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );

    int ordre;
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");

    int num=1;

    std :: string nom = " ";
    int altitude=0;

    ifs >> num;

    for(int i = num ; i < ordre+1 ; i++)
    {
        if (i!=num)
        {
            ifs >> num;
        }
        ifs >> nom >> altitude;
        m_sommets.push_back( new Sommet(num,nom,altitude));
    }

    int taille2;
    ifs >> taille2;


    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille 2 du graphe");

    std::string type = " ";
    int temps;
    int attente;
    for (int i=0 ; i< taille2 ; ++i)
    {
        ifs >> nom >> type >> temps >> attente;
        m_type.push_back( new Type(nom,type,temps,attente));
    }

    int taille;
    ifs >> taille;

    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");

    int num2;
    int depart;
    int arrivee;
    int tempp;

    for (int i=0 ; i< taille ; ++i)
    {
        ifs >> num2 >> nom >> type >> depart >> arrivee;
        for (int i=0; i< (int) m_type.size() ; i++)
        {
            if(type == m_type[i]->getType())
            {
                tempp=i;
            }
        }
        m_trajets.push_back( new Trajet(num2,nom,m_type[tempp],m_sommets[depart-1],m_sommets[arrivee-1],0,0));
        m_sommets[depart-1]->setSortant(m_trajets[i]);
        m_sommets[arrivee-1]->setEntrant(m_trajets[i]);
        m_trajets[m_trajets.size()-1]->CalculTrajet();
        m_sommets[depart-1]->ajouterSucc(m_sommets[arrivee-1]);
        m_sommets[arrivee-1]->ajouterSucc(m_sommets[depart-1]);
    }

    int ordre2=0;
    ifs >> ordre2;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");

    int num3=1;

    std :: string pseudo = " ";
    std :: string mdp = " ";
    bool v;
    bool b;
    bool r;
    bool n;
    bool kl;
    bool surf;
    bool tph;
    bool tc;
    bool tsd;
    bool ts;
    bool tk;
    bool bus;
    std::vector <bool> preference;


    if (ordre2!=0)
    {
        for(int i = 0 ; i < ordre2 ; i++)
        {
            ifs >> num3 >> pseudo >> mdp;
            ifs >> v;
            ifs >> b;
            ifs >> r;
            ifs >> n;
            ifs >> kl;
            ifs >> surf;
            ifs >> tph;
            ifs >> tc;
            ifs >> tsd ;
            ifs >> ts;
            ifs >> tk,
                ifs >> bus;

            preference.push_back(v);
            preference.push_back(b);
            preference.push_back(r);
            preference.push_back(n);
            preference.push_back(kl);
            preference.push_back(surf);
            preference.push_back(tph);
            preference.push_back(tc);
            preference.push_back(tsd);
            preference.push_back(ts);
            preference.push_back(tk);
            preference.push_back(bus);

            m_compte.push_back(new Compte(num3,pseudo,mdp,preference));
            preference.erase(preference.begin(),preference.end());
        }
    }
    initialisationBool();
}

/// Initialisation des trajets
void Graphe :: initialisationBool ()
{
    for (int i=0; i< (int) m_trajets.size(); i++)
    {
        m_trajets[i]->setActif(true); // On met les trajets à true pour que lorsque l'on est pas connecté à notre compte on puisse faire dijkstra et le bfs sans probleme
    }
}

std :: vector <Compte*> Graphe :: getCompte()
{
    return m_compte;
}

// Destructeur
Graphe :: ~Graphe()
{
    for (auto s : m_sommets)
        delete s;
}


std :: vector<Sommet*> Graphe :: getSommet()
{
    return m_sommets;
}

/////////////////////////////////////////////////////////////////////////////////////  AFFICHAGE  //////////////////////////////////////////////////////////////////////////////////////////////////

// Affichage pour Dijkstra d'un sommet A vers un sommet B
void Graphe :: afficher2()
{
    char trait1;
    char trait2;
    char numero;

    trait1=0xC4;
    trait2=0xB3;
    numero=0xF8;

    system("cls");

    for (int i=69; i<115; i++)
    {
        Color(3,0);
        gotoligcol(3,i);
        std :: cout << trait1;
    }

    for (int i=6; i<41; i++)
    {
        Color(11,0);
        gotoligcol(i,80);
        std :: cout << trait2;
    }

    Color(15,0);
    gotoligcol(2,74);
    std::cout<<"TRAJET LE PLUS COURT A --> B (DJIKSTRA)"<<std::endl<<std::endl<<std::endl;
    for (auto s : m_sommets)
    {
        std::cout << "La Borne n" << numero;
        Color(14,0);
        std :: cout << s->getNum();
        Color(15,0);
        std :: cout << " qui se nomme ";
        Color(14,0);
        std :: cout << s->getNom();
        Color(15,0);
        std :: cout << " se situe a une altitude de ";
        Color(14,0);
        std :: cout << s->getAltitude() << "m";
        Color(15,0);
        std::cout<<std::endl;
    }
}

// Affichage des types
void Graphe :: afficher3()
{
    std::cout<<"Nombre de types = " << m_type.size()<<std::endl;
    std::cout<<"Liste des types : "<<std::endl;
    for (auto s : m_type)
    {
        std::cout << s->getNom() << "  " << s->getType() << "  " << s->getTemps() << "  " << s->getAttente();
        std::cout<<std::endl;
    }
}

// Affichage des bornes
void Graphe :: afficher4()
{
    char trait1;
    char trait2;
    char numero;

    trait1=0xC4;
    trait2=0xB3;
    numero=0xF8;

    system("cls");

    for (int i=69; i<125; i++)
    {
        Color(3,0);
        gotoligcol(3,i);
        std :: cout << trait1;
    }

    for (int i=10; i<46; i++)
    {
        Color(11,0);
        gotoligcol(i,95);
        std :: cout << trait2;
    }

    for (auto s : m_sommets)
    {
        Color(15,0);
        gotoligcol(s->getNum()+8,105);
        std::cout << "La Borne n" << numero;
        Color(14,0);
        std :: cout << s->getNum();
        Color(15,0);
        std :: cout << " qui se nomme ";
        Color(14,0);
        std :: cout << s->getNom();
        Color(15,0);
        std :: cout << " se situe a une altitude de ";
        Color(14,0);
        std :: cout << s->getAltitude() << "m";
        Color(15,0);
    }
}

// Demande d'informations complémentaires sur les bornes
int Graphe :: afficher()
{
    char trait1;
    char numero;

    trait1=0xC4;
    numero=0xF8;
    int choixxxx;

    do
    {
        system("cls");
        choixxxx=0;

        for (int i=74; i<127; i++)
        {
            Color(3,0);
            gotoligcol(3,i);
            std :: cout << trait1;
        }

        Color(15,0);
        gotoligcol(2,75);
        std::cout<<"Voici la liste des differentes bornes de la station"<<std::endl<<std::endl<<std::endl;
        for (auto s : m_sommets)
        {
            std::cout << "La Borne n" << numero;
            Color(14,0);
            std :: cout << s->getNum();
            Color(15,0);
            std :: cout << " qui se nomme ";
            Color(14,0);
            std :: cout << s->getNom();
            Color(15,0);
            std :: cout << " se situe a une altitude de ";
            Color(14,0);
            std :: cout << s->getAltitude() << "m";
            Color(15,0);
            std::cout<<std::endl<<std::endl;
        }

        std::cout << std::endl;

        int sommet1=0;
        std::cout << "Quelle borne voulez vous selectionner ?  Je souhaite etudier la borne n"<< numero;
        Color(11,0);
        std::cin>> sommet1;
        Color(15,0);
        while ((sommet1<1) || (sommet1>37))
        {
            Color(12,15);
            gotoligcol(80,91);
            std :: cout << "  Cette borne n existe pas encore !!";
            gotoligcol(80,1);
            Color(15,0);
            std::cout << "Quelle borne voulez vous selectionner ?  Je souhaite etudier la borne n"<< numero << "       ";
            Sleep(2000);
            gotoligcol(80,91);
            Color(0,0);
            std :: cout << "                                    ";
            Color(15,0);
            gotoligcol(80,1);
            std::cout << "Quelle borne voulez vous selectionner ?  Je souhaite etudier la borne n"<< numero;
            Color(11,0);
            std::cin>> sommet1;
            Color(15,0);
        }

        std::cout << std::endl;

        for (auto t : m_sommets)
        {
            if(sommet1 == t->getNum())
            {
                std::cout << "Voici les differents trajets partant de la borne n"<< numero;
                Color(11,0);
                std :: cout << sommet1;
                Color(15,0);
                std :: cout << " : " << std::endl << std::endl;
                for (int i=0; i<54; i++)
                {
                    Color(3,0);
                    gotoligcol(83,i);
                    std :: cout << trait1;
                }
                std :: cout << std :: endl << std :: endl;
                for (auto u : m_trajets)
                {
                    if (sommet1 == u->getDepart()->getNum())
                    {
                        Color(15,0);
                        std :: cout << "- ";
                        Color(14,0);
                        std::cout << u->getNom();
                        Color(15,0);
                        std :: cout << " est un(e) ";
                        Color(14,0);
                        if (u->getType()->getType()== "BUS")
                        {
                            std :: cout << u->getType()->getType();
                        }
                        else
                        {
                            std :: cout << u->getType()->getNom();
                        }
                        Color(15,0);
                        std :: cout << " reliant la borne ";
                        Color(11,0);
                        std :: cout << u->getDepart()->getNum();
                        Color(15,0);
                        std :: cout << " a la borne ";
                        Color(11,0);
                        std :: cout << u->getArrivee()->getNum();
                        Color(15,0);
                        std::cout << std::endl;
                    }
                }
                std::cout << std::endl;
                std::cout << "Voici les differents trajets arrivant de la borne n " << numero;
                Color(11,0);
                std :: cout << sommet1;
                Color(15,0);
                std :: cout << " : " << std::endl;
                for (int i=0; i<112; i++)
                {
                    Color(3,0);
                    std :: cout << trait1;
                    i++;
                }
                Color(15,0);
                std :: cout << std :: endl << std :: endl;

                for (auto v : m_trajets)
                {
                    if (sommet1 == v->getArrivee()->getNum())
                    {
                        Color(15,0);
                        std :: cout << "- ";
                        Color(14,0);
                        std::cout << v->getNom();
                        Color(15,0);
                        std :: cout << " est un(e) ";
                        Color(14,0);
                        if (v->getType()->getType()== "BUS")
                        {
                            std :: cout << v->getType()->getType();
                        }
                        else
                        {
                            std :: cout << v->getType()->getNom();
                        }
                        Color(15,0);
                        std :: cout << " reliant la borne ";
                        Color(11,0);
                        std :: cout << v->getDepart()->getNum();
                        Color(15,0);
                        std :: cout << " a la borne ";
                        Color(11,0);
                        std :: cout << v->getArrivee()->getNum();
                        Color(15,0);
                        std::cout << std::endl;
                    }
                }

            }
        }
        std :: cout << std :: endl;
        std :: cout << "Desirez vous avoir une information sur une autre borne ?   1.OUI  2.NON " << std :: endl;
        std :: cout << "Votre choix ...  ";
        Color(11,0);
        std :: cin >> choixxxx;
        std :: cout << std :: endl;
        Color(15,0);
        while ((choixxxx<1) || (choixxxx>2))
        {
            std :: cout << "Votre choix ...  ";
            Color(11,0);
            std :: cin >> choixxxx;
            Color(15,0);
        }

        if(choixxxx==2)
            return choixxxx;

    }
    while ((choixxxx=1));
    return choixxxx;
}

void Graphe :: texte()
{
    Color(15,0);
    gotoligcol(2,74);
    std::cout<<"                                        "<<std::endl<<std::endl<<std::endl;
    gotoligcol(2,74);
    std::cout<<"        REJOINDRE LE RESTAURANT        "<<std::endl<<std::endl<<std::endl;
    gotoligcol(8,86);
    std :: cout << " Ici, vous pouvez trouver le trajet le plus courts pour pouvoir rejoindre le restaurant";
    Color(1,0);
    std :: cout << " FOOD SNOW";
    Color(15,0);
    gotoligcol(10,86);
    std :: cout << "               (ouvert de 10h a 21h 7/7j) se situant a la borne 9 de la station.        ";
}


void Graphe :: Calcul()
{
    gotoligcol(21,136);
    Color(12,0);
    std :: cout << "Calcul de l heure d arrivee .";
    Sleep(500);
    gotoligcol(21,136);
    std :: cout << "Calcul de l heure d arrivee ..";
    Sleep(500);
    gotoligcol(21,136);
    std :: cout << "Calcul de l heure d arrivee ...";
    Sleep(500);
    gotoligcol(21,136);
    std :: cout << "Calcul de l heure d arrivee .  ";
    Sleep(500);
    gotoligcol(21,136);
    std :: cout << "Calcul de l heure d arrivee ..";
    Sleep(500);
    gotoligcol(21,136);
    std :: cout << "Calcul de l heure d arrivee ...";
    Sleep(500);
    gotoligcol(21,136);
    std :: cout << "Calcul de l heure d arrivee .  ";
    Sleep(500);
    gotoligcol(21,136);
    std :: cout << "Calcul de l heure d arrivee ..";
    Sleep(500);
    gotoligcol(21,136);
    std :: cout << "Calcul de l heure d arrivee ...";
    Sleep(500);
    gotoligcol(21,136);
    std :: cout << "Calcul de l heure d arrivee .  ";
    Sleep(500);
    gotoligcol(21,136);
    std :: cout << "Calcul de l heure d arrivee ..";
    Sleep(500);
    gotoligcol(21,136);
    std :: cout << "                                ";
    Color(15,0);
}


void Graphe :: Calcul2()
{
    gotoligcol(12,116);
    Color(12,0);
    std :: cout << "Chargement .";
    Sleep(500);
    gotoligcol(12,116);
    std :: cout << "Chargement ..";
    Sleep(500);
    gotoligcol(12,116);
    std :: cout << "Chargement ...";
    Sleep(500);
    gotoligcol(12,116);
    std :: cout << "Chargement .  ";
    Sleep(500);
    gotoligcol(12,116);
    std :: cout << "Chargement ..";
    Sleep(500);
    gotoligcol(12,116);
    std :: cout << "Chargement ...";
    Sleep(500);
    gotoligcol(12,116);
    std :: cout << "Chargement .  ";
    Sleep(500);
    gotoligcol(12,116);
    std :: cout << "Chargement ..";
    Sleep(500);
    gotoligcol(12,116);
    std :: cout << "Chargement ...";
    Sleep(500);
    gotoligcol(12,116);
    std :: cout << "Chargement .  ";
    Sleep(500);
    gotoligcol(12,116);
    std :: cout << "Chargement ..";
    Sleep(500);
    gotoligcol(12,116);
    std :: cout << "                                ";
    Color(15,0);
    gotoligcol(12,116);
    std :: cout << "Vos preferences ont ete enregistrees avec succes !!";
    Sleep(3000);
}


void Graphe :: trait()
{
    char trait1;

    trait1=0xC4;

    for (int i=120; i<150; i++)
    {
        Color(1,0);
        gotoligcol(12,i);
        std :: cout << trait1;
    }
    Color(15,0);
}


void Graphe :: trait2()
{
    char trait1;

    trait1=0xC4;

    for (int i=120; i<150; i++)
    {
        Color(1,0);
        gotoligcol(19,i);
        std :: cout << trait1;
    }
    Color(15,0);
}


// Affichage des pistes
int Graphe :: afficherPistes()
{
    int i;
    int compteur=0;
    int compteurr=0;
    int nm=0;
    char trait1;
    char trait2;
    char coin1;
    char coin2;

    coin1=0xD9;
    coin2=0xDA;
    trait1=0xC4;
    trait2=0xB3;

    do
    {

        for (int i=80; i<104; i++)
        {
            Color(3,0);
            gotoligcol(3,i);
            std :: cout << trait1;
        }

        Color(15,0);
        gotoligcol(2,80);
        std::cout << "VOICI LE PLAN DES PISTES " << std::endl << std::endl;


        for (i=12; i<36; i++)
        {
            Color(10,0);
            gotoligcol(7,i);
            std :: cout << trait1;
        }

        for(i=12; i<36; i++)
        {

            gotoligcol(12,i);
            std :: cout << trait1;
        }

        for (i=8; i<12; i++)
        {
            Color(10,0);
            gotoligcol(i,11);
            std :: cout << trait2;
            Color(10,0);
            gotoligcol(i,36);
            std :: cout << trait2;
        }

        gotoligcol(9,17);
        std :: cout << "PISTES VERTES";
        gotoligcol(10,23);
        for (i=0; i<(int)m_trajets.size(); i++)
        {
            if (m_trajets[i]->getType()->getType()=="V")
            {
                compteurr ++;
            }
        }
        std :: cout << compteurr;
        compteurr=0;

        gotoligcol(13,22);
        Color(11,0);
        std :: cout << " 1";

        /// PISTES VERTES

        for (i=40; i<64; i++)
        {
            Color(9,0);
            gotoligcol(7,i);
            std :: cout << trait1;
        }

        for(i=40; i<64; i++)
        {

            gotoligcol(12,i);
            std :: cout << trait1;
        }

        for (i=8; i<12; i++)
        {
            Color(9,0);
            gotoligcol(i,39);
            std :: cout << trait2;
            Color(9,0);
            gotoligcol(i,64);
            std :: cout << trait2;
        }

        gotoligcol(9,45);
        std :: cout << "PISTES BLEUES";
        gotoligcol(10,50);
        for (i=0; i<(int)m_trajets.size(); i++)
        {
            if (m_trajets[i]->getType()->getType()=="B")
            {
                compteur ++;
            }
        }
        std :: cout << compteur;
        compteur=0;

        gotoligcol(13,50);
        Color(11,0);
        std :: cout << "2";

        /// PISTES BLEUES

        for (i=68; i<92; i++)
        {
            Color(12,0);
            gotoligcol(7,i);
            std :: cout << trait1;
        }

        for(i=68; i<92; i++)
        {

            gotoligcol(12,i);
            std :: cout << trait1;
        }

        for (i=8; i<12; i++)
        {
            Color(12,0);
            gotoligcol(i,67);
            std :: cout << trait2;
            Color(12,0);
            gotoligcol(i,92);
            std :: cout << trait2;
        }

        gotoligcol(9,73);
        std :: cout << "PISTES ROUGES";
        gotoligcol(10,78);
        for (i=0; i<(int)m_trajets.size(); i++)
        {
            if (m_trajets[i]->getType()->getType()=="R")
            {
                compteur ++;
            }
        }
        std :: cout << compteur;
        compteur=0;

        gotoligcol(13,78);
        Color(11,0);
        std :: cout << "3";

/// PISTES ROUGES

        for (i=96; i<120; i++)
        {
            Color(8,0);
            gotoligcol(7,i);
            std :: cout << trait1;
        }

        for(i=96; i<120; i++)
        {

            gotoligcol(12,i);
            std :: cout << trait1;
        }

        for (i=8; i<12; i++)
        {
            Color(8,0);
            gotoligcol(i,95);
            std :: cout << trait2;
            Color(8,0);
            gotoligcol(i,120);
            std :: cout << trait2;
        }

        gotoligcol(9,101);
        std :: cout << "PISTES NOIRES";
        gotoligcol(10,106);
        for (i=0; i<(int)m_trajets.size(); i++)
        {
            if (m_trajets[i]->getType()->getType()=="N")
            {
                compteur ++;
            }
        }
        std :: cout << compteur;
        compteur=0;

        gotoligcol(13,106);
        Color(11,0);
        std :: cout << "4";

        /// PISTES KL

        for (i=124; i<148; i++)
        {
            Color(13,0);
            gotoligcol(7,i);
            std :: cout << trait1;
        }

        for(i=124; i<148; i++)
        {

            gotoligcol(12,i);
            std :: cout << trait1;
        }

        for (i=8; i<12; i++)
        {
            Color(13,0);
            gotoligcol(i,123);
            std :: cout << trait2;
            Color(13,0);
            gotoligcol(i,148);
            std :: cout << trait2;
        }

        gotoligcol(9,125);
        std :: cout << "PISTE KILOMETRE LANCE";
        gotoligcol(10,136);
        for (i=0; i<(int)m_trajets.size(); i++)
        {
            if (m_trajets[i]->getType()->getType()=="KL")
            {
                compteur ++;
            }
        }
        std :: cout << compteur;
        compteur=0;

        gotoligcol(13,136);
        Color(11,0);
        std :: cout << "5";

        /// PISTES SNOWPARK

        for (i=152; i<176; i++)
        {
            Color(11,0);
            gotoligcol(7,i);
            std :: cout << trait1;
        }

        for(i=152; i<176; i++)
        {

            gotoligcol(12,i);
            std :: cout << trait1;
        }

        for (i=8; i<12; i++)
        {
            Color(11,0);
            gotoligcol(i,151);
            std :: cout << trait2;
            Color(11,0);
            gotoligcol(i,176);
            std :: cout << trait2;
        }

        gotoligcol(9,160);
        std :: cout << "SNOWPARK";
        gotoligcol(10,164);
        for (i=0; i<(int)m_trajets.size(); i++)
        {
            if (m_trajets[i]->getType()->getType()=="SURF")
            {
                compteur ++;
            }
        }
        std :: cout << compteur;
        compteur=0;

        gotoligcol(13,164);
        Color(11,0);
        std :: cout << "6";


        gotoligcol(17,75);
        Color(11,0);
        std :: cout << coin2;
        gotoligcol(18,75);
        std :: cout << trait2;
        gotoligcol(17,76);
        std :: cout << trait1;
        gotoligcol(17,77);
        std :: cout << trait1;
        gotoligcol(18,77);
        Color(15,0);
        std :: cout << " Veuillez faire un choix ...   ";
        Color(11,0);
        gotoligcol(20,108);
        std :: cout << coin1;
        gotoligcol(19,108);
        std :: cout << trait2;
        gotoligcol(20,107);
        std :: cout << trait1;
        gotoligcol(20,106);
        std :: cout << trait1;

        Color(4,0);
        gotoligcol(21,98);
        std :: cout << "0 : RETOUR";

        Color(14,0);
        gotoligcol(19,90);
        std :: cin >> nm;
        while ((nm<0) || (nm>6))
        {
            gotoligcol(19,90);
            std :: cout << "        ";
            gotoligcol(19,90);
            std :: cin >> nm;
        }
        system("cls");

        switch (nm)
        {
        case 0:
        {
            return nm;
        }
        case 1:
        {
            system("cls");
            if (compteurr==0)
            {
                std :: cout << "Il n existe pas de pistes vertes dans cette station";
                std :: cout << std :: endl << std :: endl;
                Color(15,0);
                system("Pause");
            }
            else
                afficherPistes_Vert();
        }
        break;
        case 2:
        {
            system("cls");
            afficherPistes_Bleu();
        }
        break;
        case 3:
        {
            system("cls");
            afficherPistes_Rouge();
        }
        break;
        case 4:
        {
            system("cls");
            afficherPistes_Noire();
        }
        break;
        case 5:
        {
            system("cls");
            afficherPistes_KL();
        }
        break;
        case 6:
        {
            system("cls");
            afficherPistes_Snowpark();
        }
        break;
        }
        system("cls");

    }
    while((nm<0)||(nm>6));

    return nm;
}


void Graphe :: afficherPistes_Vert()
{
    std::cout << "PISTES VERTES" << std::endl<<std::endl;
    int wesh;
    Color(10,0);
    for (int i=0; i<(int)m_trajets.size(); i++)
    {
        if (m_trajets[i]->getType()->getType()=="V")
        {
            Color(15,0);
            std :: cout <<"- ";
            Color(10,0);
            std::cout << "La piste "  << m_trajets[i]->getNum();
            std :: cout << " se nomme " << m_trajets[i]->getNom();
            std::cout << std::endl;
        }

    }
    Color(15,0);
    do
    {
        do
        {
            std::cout << std::endl << std::endl;
            std :: cout << "Desirez-vous avoir des infomations plus precises sur une de ces pistes (entrez ID) ...  ";
            Color(11,0);
            std :: cin >> wesh;
            Color(15,0);
        }
        while((wesh<=0) || (wesh>=96));
    }
    while (m_trajets[wesh-1]->getType()->getType()!="V");

    Color(10,0);
    std :: cout << std :: endl;
    std :: cout << "La piste "  << m_trajets[wesh-1]->getNum();
    std :: cout << " qui se nomme " << m_trajets[wesh-1]->getNom();
    std :: cout << " est une piste VERTES reliant la borne ";
    std :: cout << m_trajets[wesh-1]->getDepart()->getNom();
    std :: cout << " a la borne ";
    std :: cout << m_trajets[wesh-1]->getArrivee()->getNom();
    std :: cout << " en ";
    std :: cout << m_trajets[wesh-1]->getMin() << " min " << m_trajets[wesh-1]->getSec() << " s";
    std :: cout << std :: endl << std :: endl;
    Color(15,0);

    system("Pause");

}


void Graphe :: afficherPistes_Noire()
{
    std::cout << "PISTES NOIRES" << std::endl<<std::endl;
    int wesh;
    Color(8,0);
    for (int i=0; i<(int)m_trajets.size(); i++)
    {
        if (m_trajets[i]->getType()->getType()=="N")
        {
            Color(15,0);
            std :: cout <<"- ";
            Color(8,0);
            std::cout << "La piste "  << m_trajets[i]->getNum();
            std :: cout << " se nomme " << m_trajets[i]->getNom();
            std::cout << std::endl;
        }

    }
    Color(15,0);
    do
    {
        do
        {
            std::cout << std::endl << std::endl;
            std :: cout << "Desirez-vous avoir des infomations plus precises sur une de ces pistes (entrez ID) ...  ";
            Color(11,0);
            std :: cin >> wesh;
            Color(15,0);
        }
        while((wesh<=0) || (wesh>=96));

    }
    while (m_trajets[wesh-1]->getType()->getType()!="N");

    Color(8,0);
    std :: cout << std :: endl;
    std :: cout << "La piste "  << m_trajets[wesh-1]->getNum();
    std :: cout << " qui se nomme " << m_trajets[wesh-1]->getNom();
    std :: cout << " est une piste NOIRE reliant la borne ";
    std :: cout << m_trajets[wesh-1]->getDepart()->getNom();
    std :: cout << " a la borne ";
    std :: cout << m_trajets[wesh-1]->getArrivee()->getNom();
    std :: cout << " en ";
    std :: cout << m_trajets[wesh-1]->getMin() << " min " << m_trajets[wesh-1]->getSec() << " s";
    std :: cout << std :: endl << std :: endl;
    Color(15,0);

    system("Pause");

}


void Graphe :: afficherPistes_Rouge()
{
    std::cout << "PISTES ROUGES" << std::endl<<std::endl;
    int wesh;
    Color(12,0);
    for (int i=0; i<(int)m_trajets.size(); i++)
    {
        if (m_trajets[i]->getType()->getType()=="R")
        {
            Color(15,0);
            std :: cout <<"- ";
            Color(12,0);
            std::cout << "La piste "  << m_trajets[i]->getNum();
            std :: cout << " se nomme " << m_trajets[i]->getNom();
            std::cout << std::endl;
        }

    }
    Color(15,0);
    do
    {
        do
        {
            std::cout << std::endl << std::endl;
            std :: cout << "Desirez-vous avoir des infomations plus precises sur une de ces pistes (entrez ID) ...  ";
            Color(11,0);
            std :: cin >> wesh;
            Color(15,0);
        }
        while((wesh<=0) || (wesh>=96));

    }
    while (m_trajets[wesh-1]->getType()->getType()!="R");

    Color(12,0);
    std :: cout << std :: endl;
    std :: cout << "La piste "  << m_trajets[wesh-1]->getNum();
    std :: cout << " qui se nomme " << m_trajets[wesh-1]->getNom();
    std :: cout << " est une piste ROUGE reliant la borne ";
    std :: cout << m_trajets[wesh-1]->getDepart()->getNom();
    std :: cout << " a la borne ";
    std :: cout << m_trajets[wesh-1]->getArrivee()->getNom();
    std :: cout << " en ";
    std :: cout << m_trajets[wesh-1]->getMin() << " min " << m_trajets[wesh-1]->getSec() << " s";
    std :: cout << std :: endl << std :: endl;
    Color(15,0);

    system("Pause");

}


void Graphe :: afficherPistes_Bleu()
{
    std::cout << "PISTES BLEUES" << std::endl<<std::endl;
    int wesh;
    Color(9,0);
    for (int i=0; i<(int)m_trajets.size(); i++)
    {
        if (m_trajets[i]->getType()->getType()=="B")
        {
            Color(15,0);
            std :: cout <<"- ";
            Color(9,0);
            std::cout << "La piste "  << m_trajets[i]->getNum();
            std :: cout << " se nomme " << m_trajets[i]->getNom();
            std::cout << std::endl;
        }

    }
    Color(15,0);
    do
    {
        do
        {
            std::cout << std::endl << std::endl;
            std :: cout << "Desirez-vous avoir des infomations plus precises sur une de ces pistes (entrez ID) ...  ";
            Color(11,0);
            std :: cin >> wesh;
            Color(15,0);
        }
        while((wesh<=0) || (wesh>=96));


    }
    while (m_trajets[wesh-1]->getType()->getType()!="B");

    Color(9,0);
    std :: cout << std :: endl;
    std :: cout << "La piste "  << m_trajets[wesh-1]->getNum();
    std :: cout << " qui se nomme " << m_trajets[wesh-1]->getNom();
    std :: cout << " est une piste BLEUE reliant la borne ";
    std :: cout << m_trajets[wesh-1]->getDepart()->getNom();
    std :: cout << " a la borne ";
    std :: cout << m_trajets[wesh-1]->getArrivee()->getNom();
    std :: cout << " en ";
    std :: cout << m_trajets[wesh-1]->getMin() << " min " << m_trajets[wesh-1]->getSec() << " s";
    std :: cout << std :: endl << std :: endl;
    Color(15,0);

    system("Pause");

}


void Graphe :: afficherPistes_KL()
{
    std::cout << "PISTES KILOMETRES LANCES" << std::endl<<std::endl;
    int wesh;
    Color(13,0);
    for (int i=0; i<(int)m_trajets.size(); i++)
    {
        if (m_trajets[i]->getType()->getType()=="KL")
        {
            Color(15,0);
            std :: cout <<"- ";
            Color(13,0);
            std::cout << "La piste "  << m_trajets[i]->getNum();
            std :: cout << " se nomme " << m_trajets[i]->getNom();
            std::cout << std::endl;
        }

    }
    Color(15,0);
    do
    {
        do
        {
            std::cout << std::endl << std::endl;
            std :: cout << "Desirez-vous avoir des infomations plus precises sur une de ces pistes (entrez ID) ...  ";
            Color(11,0);
            std :: cin >> wesh;
            Color(15,0);
        }
        while((wesh<=0) || (wesh>=96));

    }
    while (m_trajets[wesh-1]->getType()->getType()!="KL");

    Color(13,0);
    std :: cout << std :: endl;
    std :: cout << "La piste "  << m_trajets[wesh-1]->getNum();
    std :: cout << " qui se nomme " << m_trajets[wesh-1]->getNom();
    std :: cout << " est une une piste KILOMETRE LANCE reliant la borne ";
    std :: cout << m_trajets[wesh-1]->getDepart()->getNom();
    std :: cout << " a la borne ";
    std :: cout << m_trajets[wesh-1]->getArrivee()->getNom();
    std :: cout << " en ";
    std :: cout << m_trajets[wesh-1]->getMin() << " min " << m_trajets[wesh-1]->getSec() << " s";
    std :: cout << std :: endl << std :: endl;
    Color(15,0);
    system("Pause");

}


void Graphe :: afficherPistes_Snowpark()
{
    std::cout << "SNOWPARK" << std::endl<<std::endl;
    int wesh;
    Color(11,0);
    for (int i=0; i<(int)m_trajets.size(); i++)
    {
        if (m_trajets[i]->getType()->getType()=="SURF")
        {
            Color(15,0);
            std :: cout <<"- ";
            Color(11,0);
            std::cout << "La piste "  << m_trajets[i]->getNum();
            std :: cout << " se nomme " << m_trajets[i]->getNom();
            std::cout << std::endl;
        }

    }
    Color(15,0);
    do
    {
        do
        {
            std::cout << std::endl << std::endl;
            std :: cout << "Desirez-vous avoir des infomations plus precises sur une de ces pistes (entrez ID) ...  ";
            Color(11,0);
            std :: cin >> wesh;
            Color(15,0);
        }
        while((wesh<=0) || (wesh>=96));

    }
    while (m_trajets[wesh-1]->getType()->getType()!="SURF");

    Color(11,0);
    std :: cout << std :: endl;
    std :: cout << "La piste "  << m_trajets[wesh-1]->getNum();
    std :: cout << " qui se nomme " << m_trajets[wesh-1]->getNom();
    std :: cout << " est un SnowPark reliant la borne ";
    std :: cout << m_trajets[wesh-1]->getDepart()->getNom();
    std :: cout << " a la borne ";
    std :: cout << m_trajets[wesh-1]->getArrivee()->getNom();
    std :: cout << " en ";
    std :: cout << m_trajets[wesh-1]->getMin() << " min " << m_trajets[wesh-1]->getSec() << " s";
    std :: cout << std :: endl << std :: endl;
    Color(15,0);

    system("Pause");

}


/// PREMIER CHOIX

int Graphe :: afficherTrajets()
{
    int i;
    int compteur2=0;
    int choice=0;
    char trait1;
    char trait2;
    char coin1;
    char coin2;

    coin1=0xD9;
    coin2=0xDA;
    trait1=0xC4;
    trait2=0xB3;

    for (int i=80; i<104; i++)
    {
        Color(3,0);
        gotoligcol(3,i);
        std :: cout << trait1;
    }

    Color(15,0);
    gotoligcol(2,80);
    std::cout << "VOICI LE PLAN DES PISTES " << std::endl << std::endl;

    /// LES PISTES

    for (i=47; i<71; i++)
    {
        Color(14,0);
        gotoligcol(7,i);
        std :: cout << trait1;
    }

    for(i=47; i<71; i++)
    {

        gotoligcol(12,i);
        std :: cout << trait1;
    }

    for (i=8; i<12; i++)
    {
        Color(14,0);
        gotoligcol(i,46);
        std :: cout << trait2;
        Color(14,0);
        gotoligcol(i,71);
        std :: cout << trait2;
    }

    gotoligcol(9,52);
    std :: cout << "  LES PISTES";
    gotoligcol(10,58);
    Color(15,0);
    for (i=0; i<(int)m_trajets.size(); i++)
    {
        if ((m_trajets[i]->getType()->getType()=="SURF") || (m_trajets[i]->getType()->getType()=="KL") || (m_trajets[i]->getType()->getType()=="V") || (m_trajets[i]->getType()->getType()=="B") || (m_trajets[i]->getType()->getType()=="R") || (m_trajets[i]->getType()->getType()=="N"))
        {
            compteur2 ++;
        }
    }
    std :: cout << compteur2;
    compteur2=0;
    gotoligcol(13,52);
    Color(11,0);
    std :: cout << "      1      ";

    /// PISTES REMONTEES

    for (i=80; i<104; i++)
    {
        Color(14,0);
        gotoligcol(7,i);
        std :: cout << trait1;
    }

    for(i=80; i<104; i++)
    {

        gotoligcol(12,i);
        std :: cout << trait1;
    }

    for (i=8; i<12; i++)
    {
        Color(14,0);
        gotoligcol(i,79);
        std :: cout << trait2;
        Color(14,0);
        gotoligcol(i,104);
        std :: cout << trait2;
    }

    gotoligcol(9,85);
    std :: cout << "LES REMONTEES";
    gotoligcol(10,91);
    Color(15,0);
    for (i=0; i<(int)m_trajets.size(); i++)
    {
        if ((m_trajets[i]->getType()->getType()=="TS") || (m_trajets[i]->getType()->getType()=="TPH") || (m_trajets[i]->getType()->getType()=="TK") || (m_trajets[i]->getType()->getType()=="TSD") || (m_trajets[i]->getType()->getType()=="TC"))
        {
            compteur2 ++;
        }
    }
    std :: cout << compteur2;
    compteur2=0;
    gotoligcol(13,85);
    Color(11,0);
    std :: cout << "       2      ";

    /// LES NAVETTES

    for (i=113; i<137; i++)
    {
        Color(14,0);
        gotoligcol(7,i);
        std :: cout << trait1;
    }

    for(i=113; i<137; i++)
    {

        gotoligcol(12,i);
        std :: cout << trait1;
    }

    for (i=8; i<12; i++)
    {
        Color(14,0);
        gotoligcol(i,112);
        std :: cout << trait2;
        Color(14,0);
        gotoligcol(i,137);
        std :: cout << trait2;
    }

    gotoligcol(9,118);
    std :: cout << " LES NAVETTES";
    gotoligcol(10,125);
    Color(15,0);
    for (i=0; i<(int)m_trajets.size(); i++)
    {
        if (m_trajets[i]->getType()->getType()=="BUS")
        {
            compteur2 ++;
        }
    }
    std :: cout << compteur2;
    compteur2=0;
    gotoligcol(13,118);
    Color(11,0);
    std :: cout << "       3      ";


    gotoligcol(17,75);
    Color(11,0);
    std :: cout << coin2;
    gotoligcol(18,75);
    std :: cout << trait2;
    gotoligcol(17,76);
    std :: cout << trait1;
    gotoligcol(17,77);
    std :: cout << trait1;
    gotoligcol(18,77);
    Color(15,0);
    std :: cout << " Veuillez faire un choix ...   ";
    Color(11,0);
    gotoligcol(20,108);
    std :: cout << coin1;
    gotoligcol(19,108);
    std :: cout << trait2;
    gotoligcol(20,107);
    std :: cout << trait1;
    gotoligcol(20,106);
    std :: cout << trait1;

    Color(4,0);
    gotoligcol(21,91);
    std :: cout << "0 : ECRAN ACCUEIL";

    Color(14,0);
    gotoligcol(19,90);
    std :: cin >> choice;
    while ((choice<0) || (choice>3))
    {
        gotoligcol(19,90);
        std :: cout << "        ";
        gotoligcol(19,90);
        std :: cin >> choice;
    }
    system("cls");

    switch (choice)
    {
    case 0:
    {
        return choice;
    }
    case 1:
    {
        system("cls");
        afficherPistes();
    }
    break;
    case 2:
    {
        system("cls");
        afficherRemontees();

    }
    break;
    case 3:
    {
        system("cls");
        afficherBus();
    }
    break;
    system("cls");

    }
    while((choice<0)||(choice>3));

    return choice;
}



/// REMONTEES

int Graphe :: afficherRemontees()
{
    int i;
    int ch=0;
    int compteur3=0;
    char trait1;
    char trait2;
    char coin1;
    char coin2;

    coin1=0xD9;
    coin2=0xDA;
    trait1=0xC4;
    trait2=0xB3;


    do
    {
        for (int i=80; i<104; i++)
        {
            Color(3,0);
            gotoligcol(3,i);
            std :: cout << trait1;
        }

        Color(15,0);
        gotoligcol(2,80);
        std::cout << "VOICI LE PLAN DES REMONTEES " << std::endl << std::endl;

///--------------------------------------------------TPH------------------------------------------

        for (i=14; i<38; i++)
        {
            Color(14,0);
            gotoligcol(7,i);
            std :: cout << trait1;
        }

        for(i=14; i<38; i++)
        {

            gotoligcol(12,i);
            std :: cout << trait1;
        }

        for (i=8; i<12; i++)
        {
            Color(14,0);
            gotoligcol(i,13);
            std :: cout << trait2;
            Color(14,0);
            gotoligcol(i,38);
            std :: cout << trait2;
        }

        gotoligcol(9,18);
        std :: cout << "  TELEPHERIQUES";
        gotoligcol(10,26);
        Color(15,0);
        for (i=0; i<(int)m_trajets.size(); i++)
        {
            if (m_trajets[i]->getType()->getType()=="TPH")
            {
                compteur3 ++;
            }
        }
        std :: cout << compteur3;
        compteur3=0;
        gotoligcol(13,18);
        Color(11,0);
        std :: cout << "        1      ";


///-------------------------------------------------------- TC---------------------------------------------

        for (i=47; i<71; i++)
        {
            Color(14,0);
            gotoligcol(7,i);
            std :: cout << trait1;
        }

        for(i=47; i<71; i++)
        {

            gotoligcol(12,i);
            std :: cout << trait1;
        }

        for (i=8; i<12; i++)
        {
            Color(14,0);
            gotoligcol(i,46);
            std :: cout << trait2;
            Color(14,0);
            gotoligcol(i,71);
            std :: cout << trait2;
        }

        gotoligcol(9,52);
        std :: cout << "  TELECABINES";
        gotoligcol(10,59);
        Color(15,0);
        for (i=0; i<(int)m_trajets.size(); i++)
        {
            if (m_trajets[i]->getType()->getType()=="TC")
            {
                compteur3 ++;
            }
        }
        std :: cout << compteur3;
        compteur3=0;
        gotoligcol(13,52);
        Color(11,0);
        std :: cout << "       2      ";

/// --------------------------------------------------------- TSD -----------------------------------------------

        for (i=80; i<104; i++)
        {
            Color(14,0);
            gotoligcol(7,i);
            std :: cout << trait1;
        }

        for(i=80; i<104; i++)
        {

            gotoligcol(12,i);
            std :: cout << trait1;
        }

        for (i=8; i<12; i++)
        {
            Color(14,0);
            gotoligcol(i,79);
            std :: cout << trait2;
            Color(14,0);
            gotoligcol(i,104);
            std :: cout << trait2;
        }

        gotoligcol(9,82);
        std :: cout << "TELESIEGE-DEBRAYABLE";
        gotoligcol(10,91);
        Color(15,0);
        for (i=0; i<(int)m_trajets.size(); i++)
        {
            if (m_trajets[i]->getType()->getType()=="TSD")
            {
                compteur3 ++;
            }
        }
        std :: cout << compteur3;
        compteur3=0;
        gotoligcol(13,85);
        Color(11,0);
        std :: cout << "      3      ";

/// ---------------------------------------------- TS ------------------------------------------------

        for (i=113; i<137; i++)
        {
            Color(14,0);
            gotoligcol(7,i);
            std :: cout << trait1;
        }

        for(i=113; i<137; i++)
        {

            gotoligcol(12,i);
            std :: cout << trait1;
        }

        for (i=8; i<12; i++)
        {
            Color(14,0);
            gotoligcol(i,112);
            std :: cout << trait2;
            Color(14,0);
            gotoligcol(i,137);
            std :: cout << trait2;
        }

        gotoligcol(9,118);
        std :: cout << "  TELESIEGE";
        gotoligcol(10,124);
        Color(15,0);
        for (i=0; i<(int)m_trajets.size(); i++)
        {
            if (m_trajets[i]->getType()->getType()=="TS")
            {
                compteur3 ++;
            }
        }
        std :: cout << compteur3;
        compteur3=0;
        gotoligcol(13,118);
        Color(11,0);
        std :: cout << "       4      ";

/// --------------------------------- TK ----------------------------------

        for (i=146; i<170; i++)
        {
            Color(14,0);
            gotoligcol(7,i);
            std :: cout << trait1;
        }

        for(i=146; i<170; i++)
        {

            gotoligcol(12,i);
            std :: cout << trait1;
        }

        for (i=8; i<12; i++)
        {
            Color(14,0);
            gotoligcol(i,145);
            std :: cout << trait2;
            Color(14,0);
            gotoligcol(i,170);
            std :: cout << trait2;
        }

        gotoligcol(9,150);
        std :: cout << "    TELESKI";
        gotoligcol(10,157);
        Color(15,0);
        for (i=0; i<(int)m_trajets.size(); i++)
        {
            if (m_trajets[i]->getType()->getType()=="TK")
            {
                compteur3 ++;
            }
        }
        std :: cout << compteur3;
        compteur3=0;
        gotoligcol(13,150);
        Color(11,0);
        std :: cout << "       5      ";

        gotoligcol(17,75);
        Color(11,0);
        std :: cout << coin2;
        gotoligcol(18,75);
        std :: cout << trait2;
        gotoligcol(17,76);
        std :: cout << trait1;
        gotoligcol(17,77);
        std :: cout << trait1;
        gotoligcol(18,77);
        Color(15,0);
        std :: cout << " Veuillez faire un choix ...   ";
        Color(11,0);
        gotoligcol(20,108);
        std :: cout << coin1;
        gotoligcol(19,108);
        std :: cout << trait2;
        gotoligcol(20,107);
        std :: cout << trait1;
        gotoligcol(20,106);
        std :: cout << trait1;

        Color(4,0);
        gotoligcol(21,98);
        std :: cout << "0 : RETOUR";

        Color(14,0);
        gotoligcol(19,90);
        std :: cin >> ch;
        while ((ch<0) || (ch>5))
        {
            gotoligcol(19,90);
            std :: cout << "        ";
            gotoligcol(19,90);
            std :: cin >> ch;
        }
        system("cls");

        switch (ch)
        {
        case 0:
        {
            return ch;
        }
        break;
        case 1:
        {
            system("cls");
            afficherTPH();
        }
        break;
        case 2:
        {
            system("cls");
            afficherTC();
        }
        break;
        case 3:
        {
            system("cls");
            afficherTSD();
        }
        break;
        case 4:
        {
            system("cls");
            afficherTS();
        }
        break;
        case 5:
        {
            system("cls");
            afficherTK();
        }
        break;
        }
        system("cls");
    }
    while((ch<0)||(ch>5));

    return ch;
}

/// ------------------------------------------------TPH--------------------------------------------------


void Graphe :: afficherTPH()
{
    std::cout << "TELEPHERIQUE" << std::endl<<std::endl;

    int select;
    Color(11,0);
    for (int i=0; i<(int)m_trajets.size(); i++)
    {
        if (m_trajets[i]->getType()->getType()=="TPH")
        {
            Color(15,0);
            std :: cout <<"- ";
            Color(11,0);
            std::cout << "La remontee "  << m_trajets[i]->getNum();
            std :: cout << " se nomme " << m_trajets[i]->getNom();
            std::cout << std::endl;
        }

    }
    Color(15,0);
    do
    {
        do
        {
            std::cout << std::endl << std::endl;
            std :: cout << "Desirez-vous avoir des infomations plus precises sur une de ces remontees (entrez ID) ...  ";
            Color(11,0);
            std :: cin >> select;
            Color(15,0);
        }
        while((select<=0) || (select>=96));

    }
    while (m_trajets[select-1]->getType()->getType()!="TPH");

    Color(11,0);
    std :: cout << std :: endl;
    std :: cout << "La remontee "  << m_trajets[select-1]->getNum();
    std :: cout << " qui se nomme " << m_trajets[select-1]->getNom();
    std :: cout << " est un Telepherique reliant la borne ";
    std :: cout << m_trajets[select-1]->getDepart()->getNom();
    std :: cout << " a la borne ";
    std :: cout << m_trajets[select-1]->getArrivee()->getNom();
    std :: cout << " en ";
    std :: cout << m_trajets[select-1]->getMin() << " min " << m_trajets[select-1]->getSec() << " s";
    std :: cout << std :: endl << std :: endl;
    Color(15,0);

    system("Pause");
}

/// ------------------------------------------------TC--------------------------------------------------

void Graphe :: afficherTC()
{
    std::cout << "TELECABINE" << std::endl<<std::endl;

    int select;
    Color(11,0);
    for (int i=0; i<(int)m_trajets.size(); i++)
    {
        if (m_trajets[i]->getType()->getType()=="TC")
        {
            Color(15,0);
            std :: cout <<"- ";
            Color(11,0);
            std::cout << "La remontee "  << m_trajets[i]->getNum();
            std :: cout << " se nomme " << m_trajets[i]->getNom();
            std::cout << std::endl;
        }

    }
    Color(15,0);
    do
    {
        do
        {
            std::cout << std::endl << std::endl;
            std :: cout << "Desirez-vous avoir des infomations plus precises sur une de ces remontees (entrez ID) ...  ";
            Color(11,0);
            std :: cin >> select;
            Color(15,0);
        }
        while((select<=0) || (select>=96));

    }
    while (m_trajets[select-1]->getType()->getType()!="TC");

    Color(11,0);
    std :: cout << std :: endl;
    std :: cout << "La remontee "  << m_trajets[select-1]->getNum();
    std :: cout << " qui se nomme " << m_trajets[select-1]->getNom();
    std :: cout << " est une Telecabine reliant la borne ";
    std :: cout << m_trajets[select-1]->getDepart()->getNom();
    std :: cout << " a la borne ";
    std :: cout << m_trajets[select-1]->getArrivee()->getNom();
    std :: cout << " en ";
    std :: cout << m_trajets[select-1]->getMin() << " min " << m_trajets[select-1]->getSec() << " s";
    std :: cout << std :: endl << std :: endl;
    Color(15,0);

    system("Pause");
}

/// ------------------------------------------------TSD--------------------------------------------------

void Graphe :: afficherTSD()
{
    std::cout << "TELESIEGE-DEBRAYABLE" << std::endl<<std::endl;

    int select;
    Color(11,0);
    for (int i=0; i<(int)m_trajets.size(); i++)
    {
        if (m_trajets[i]->getType()->getType()=="TSD")
        {
            Color(15,0);
            std :: cout <<"- ";
            Color(11,0);
            std::cout << "La remontee "  << m_trajets[i]->getNum();
            std :: cout << " se nomme " << m_trajets[i]->getNom();
            std::cout << std::endl;
        }

    }
    Color(15,0);
    do
    {
        do
        {
            std::cout << std::endl << std::endl;
            std :: cout << "Desirez-vous avoir des infomations plus precises sur une de ces remontees (entrez ID) ...  ";
            Color(11,0);
            std :: cin >> select;
            Color(15,0);
        }
        while((select<=0) || (select>=96));

    }
    while (m_trajets[select-1]->getType()->getType()!="TSD");

    Color(11,0);
    std :: cout << std :: endl;
    std :: cout << "La remontee "  << m_trajets[select-1]->getNum();
    std :: cout << " qui se nomme " << m_trajets[select-1]->getNom();
    std :: cout << " est un Telesiege-Debrayable reliant la borne ";
    std :: cout << m_trajets[select-1]->getDepart()->getNom();
    std :: cout << " a la borne ";
    std :: cout << m_trajets[select-1]->getArrivee()->getNom();
    std :: cout << " en ";
    std :: cout << m_trajets[select-1]->getMin() << " min " << m_trajets[select-1]->getSec() << " s";
    std :: cout << std :: endl << std :: endl;
    Color(15,0);

    system("Pause");
}

/// ------------------------------------------------TS--------------------------------------------------

void Graphe :: afficherTS()
{
    std::cout << "TELESIEGE" << std::endl<<std::endl;

    int select;
    Color(11,0);
    for (int i=0; i<(int)m_trajets.size(); i++)
    {
        if (m_trajets[i]->getType()->getType()=="TS")
        {
            Color(15,0);
            std :: cout <<"- ";
            Color(11,0);
            std::cout << "La remontee "  << m_trajets[i]->getNum();
            std :: cout << " se nomme " << m_trajets[i]->getNom();
            std::cout << std::endl;
        }

    }
    Color(15,0);
    do
    {
        do
        {
            std::cout << std::endl << std::endl;
            std :: cout << "Desirez-vous avoir des infomations plus precises sur une de ces remontees (entrez ID) ...  ";
            Color(11,0);
            std :: cin >> select;
            Color(15,0);
        }
        while((select<=0) || (select>=96));

    }
    while (m_trajets[select-1]->getType()->getType()!="TS");

    Color(11,0);
    std :: cout << std :: endl;
    std :: cout << "La remontee "  << m_trajets[select-1]->getNum();
    std :: cout << " qui se nomme " << m_trajets[select-1]->getNom();
    std :: cout << " est un Telesiege reliant la borne ";
    std :: cout << m_trajets[select-1]->getDepart()->getNom();
    std :: cout << " a la borne ";
    std :: cout << m_trajets[select-1]->getArrivee()->getNom();
    std :: cout << " en ";
    std :: cout << m_trajets[select-1]->getMin() << " min " << m_trajets[select-1]->getSec() << " s";
    std :: cout << std :: endl << std :: endl;
    Color(15,0);

    system("Pause");
}

/// ------------------------------------------------TK--------------------------------------------------

void Graphe :: afficherTK()
{
    std::cout << "TELESKI" << std::endl<<std::endl;

    int select;
    Color(11,0);
    for (int i=0; i<(int)m_trajets.size(); i++)
    {
        if (m_trajets[i]->getType()->getType()=="TK")
        {
            Color(15,0);
            std :: cout <<"- ";
            Color(11,0);
            std::cout << "La remontee "  << m_trajets[i]->getNum();
            std :: cout << " se nomme " << m_trajets[i]->getNom();
            std::cout << std::endl;
        }

    }
    Color(15,0);
    do
    {
        do
        {
            std::cout << std::endl << std::endl;
            std :: cout << "Desirez-vous avoir des infomations plus precises sur une de ces remontees (entrez ID) ...  ";
            Color(11,0);
            std :: cin >> select;
            Color(15,0);
        }
        while((select<=0) || (select>=96));

    }
    while (m_trajets[select-1]->getType()->getType()!="TK");

    Color(11,0);
    std :: cout << std :: endl;
    std :: cout << "La remontee "  << m_trajets[select-1]->getNum();
    std :: cout << " qui se nomme " << m_trajets[select-1]->getNom();
    std :: cout << " est un Teleski reliant la borne ";
    std :: cout << m_trajets[select-1]->getDepart()->getNom();
    std :: cout << " a la borne ";
    std :: cout << m_trajets[select-1]->getArrivee()->getNom();
    std :: cout << " en ";
    std :: cout << m_trajets[select-1]->getMin() << " min " << m_trajets[select-1]->getSec() << " s";
    std :: cout << std :: endl << std :: endl;
    Color(15,0);

    system("Pause");
}


///------------------------------------------------ NAVETTE------------------------------------------------

void Graphe :: afficherBus()
{
    std::cout << "LES NAVETTES" << std::endl << std::endl;

    int select;
    Color(11,0);
    for (int i=0; i<(int)m_trajets.size(); i++)
    {
        if (m_trajets[i]->getType()->getType()=="BUS")
        {
            Color(15,0);
            std :: cout <<"- ";
            Color(11,0);
            std::cout << "La navette "  << m_trajets[i]->getNum();
            std :: cout << " se nomme " << m_trajets[i]->getNom();
            std::cout << std::endl;
        }

    }
    Color(15,0);
    do
    {
        do
        {
            std::cout << std::endl << std::endl;
            std :: cout << "Desirez-vous avoir des infomations plus precises sur une de ces navettes (entrez ID) ...  ";
            Color(11,0);
            std :: cin >> select;
            Color(15,0);
        }
        while((select<=0) || (select>=96));

    }
    while (m_trajets[select-1]->getType()->getType()!="BUS");

    Color(11,0);
    std :: cout << std :: endl;
    std :: cout << "La navette "  << m_trajets[select-1]->getNum();
    std :: cout << " qui se nomme " << m_trajets[select-1]->getNom();
    std :: cout << " est une NAVETTE reliant la borne ";
    std :: cout << m_trajets[select-1]->getDepart()->getNom();
    std :: cout << " a la borne ";
    std :: cout << m_trajets[select-1]->getArrivee()->getNom();
    std :: cout << " en ";
    if((m_trajets[select-1]->getMin()>=60)&&(m_trajets[select-1]->getMin()<=120))
    {
        std :: cout << "1 h " << m_trajets[select-1]->getMin()-60 << " min " << m_trajets[select-1]->getSec() << " s";
    }
    if(m_trajets[select-1]->getMin()>=120)
    {
        std :: cout << "2 h " << m_trajets[select-1]->getMin()-120 << " min " << m_trajets[select-1]->getSec() << " s";
    }
    if (m_trajets[select-1]->getMin()<=60)
    {
        std :: cout << m_trajets[select-1]->getMin() << " min " << m_trajets[select-1]->getSec() << " s";
    }
    std :: cout << std :: endl << std :: endl;
    Color(15,0);

    system("Pause");
    system("cls");
}


///--------------------------------------------------------------------Affichage des trajets------------------------------------------------------

void Graphe :: trajet()
{
    std::cout<<"Nombre de trajets = " << m_trajets.size()<<std::endl;
    std::cout<<"Liste des trajets : "<<std::endl;
    for (auto s : m_trajets)
    {
        std::cout << "Nom : " << s->getNom() << "  Type : " << s->getType()->getType() << "  Numero Depart : " << s->getDepart()->getNum() << "  Numero Arrivee : " << s->getArrivee()->getNum() << "  Temps : " << s->getMin() << " min " << s->getSec() << " s";
        std::cout<<std::endl;
    }
    int trajet=0;
    std::string type = " ";
    std::cout << "Quel trajet souhaitez vous regarder ? " << std::endl;
    std::cin >> trajet;
    for (auto y : m_trajets)
    {
        if(trajet == y->getNum())
        {
            std::cout << "Nom du trajet : " << y->getNom() << std::endl;
            if (y->getType()->getType()=="N")
            {
                type = "Piste Noire";
            }
            if (y->getType()->getType()=="R")
            {
                type = "Piste Rouge";
            }
            if (y->getType()->getType()=="B")
            {
                type = "Piste Bleu";
            }
            if (y->getType()->getType()=="KL")
            {
                type = "Piste Kilometre Lance";
            }
            if (y->getType()->getType()=="SURF")
            {
                type = "Snowpark";
            }
            if (y->getType()->getType()=="TPH")
            {
                type = "Telepherique";
            }
            if (y->getType()->getType()=="TC")
            {
                type = "Telecabine";
            }
            if (y->getType()->getType()=="TSD")
            {
                type = "Telesiege debrayable";
            }
            if (y->getType()->getType()=="TS")
            {
                type = "Telesiege";
            }
            if (y->getType()->getType()=="TK")
            {
                type = "Teleski";
            }
            if (y->getType()->getType()=="BUS")
            {
                type = "BUS";
            }
            std::cout << "Type du trajet : " << type << std::endl;
            std::cout << "Point de depart du trajet : " << y->getDepart()->getNom() << std::endl;
            std::cout << "Point d arrivee du trajet : " << y->getArrivee()->getNom() << std::endl;
            std::cout << "Temps de trajet : " << y->getMin() << " min " << y->getSec() << " s";
        }
    }
}


//////////////////////////////////////////////////////////////////////////////////// SOUS-PROGRAMMES DES INTERFACES /////////////////////////////////////////////////////////////////////////

/// Accueil principal

int Graphe :: Accueil()
{
    unsigned choix=0;
    int i,j;
    char rectangle;
    char triangle;
    char fleche;
    char soleil;
    char rayon;
    char trait;
    char trait1;
    char trait2;
    char trait3;
    char coin1;
    char coin2;
    char coin3;
    char coin4;

    system("cls");

    rayon=0xFE;
    soleil=0xDB;
    fleche=0x1A;
    triangle=0x10;
    rectangle=0xDC;
    trait=0xDD;
    trait1=0xDE;
    trait2=0xB3;
    trait3=0xC4;
    coin1=0xBF;
    coin2=0xD9;
    coin3=0xDA;
    coin4=0xC0;

    do
    {
        for (i=53; i<135; i++)
        {
            for (j=7; j<28; j++)
            {
                Color(0,15);
                gotoligcol(j,i);
                std :: cout << " ";
                gotoligcol(j,i);
                std :: cout << " ";
            }
        }

        for (i=80; i<135; i++)
        {
            Color(0,3);
            gotoligcol(7,i);
            std :: cout << " ";
        }

        for (i=85; i<135; i++)
        {
            Color(0,3);
            gotoligcol(8,i);
            std :: cout << " ";
        }

        for (i=90; i<135; i++)
        {
            Color(0,3);
            gotoligcol(9,i);
            std :: cout << " ";
        }

        for (i=95; i<135; i++)
        {
            Color(0,3);
            gotoligcol(10,i);
            std :: cout << " ";
        }

        for (i=100; i<135; i++)
        {
            Color(0,3);
            gotoligcol(11,i);
            std :: cout << " ";
        }

        for (i=105; i<135; i++)
        {
            Color(0,3);
            gotoligcol(12,i);
            std :: cout << " ";
        }

        for (i=110; i<135; i++)
        {
            Color(0,3);
            gotoligcol(13,i);
            std :: cout << " ";
        }

        for (i=115; i<135; i++)
        {
            Color(0,3);
            gotoligcol(14,i);
            std :: cout << " ";
        }

        for (i=120; i<135; i++)
        {
            Color(0,3);
            gotoligcol(15,i);
            std :: cout << " ";
        }

        for (i=125; i<135; i++)
        {
            Color(0,3);
            gotoligcol(16,i);
            std :: cout << " ";
        }

        for (i=130; i<135; i++)
        {
            Color(0,3);
            gotoligcol(17,i);
            std :: cout << " ";
        }

        for (i=135; i<135; i++)
        {
            Color(0,3);
            gotoligcol(18,i);
            std :: cout << " ";
        }

        gotoligcol(9,125);
        Color(14,3);
        std :: cout << soleil;
        gotoligcol(9,126);
        Color(14,3);
        std :: cout << soleil;
        gotoligcol(9,127);
        Color(14,3);
        std :: cout << soleil;
        gotoligcol(9,128);
        Color(14,3);
        std :: cout << soleil;
        gotoligcol(10,125);
        Color(14,3);
        std :: cout << soleil;
        gotoligcol(10,126);
        Color(14,3);
        std :: cout << soleil;
        gotoligcol(10,127);
        Color(14,3);
        std :: cout << soleil;
        gotoligcol(10,128);
        Color(14,3);
        std :: cout << soleil;

        gotoligcol(8,124);
        Color(14,3);
        std :: cout << rayon;
        gotoligcol(8,129);
        Color(14,3);
        std :: cout << rayon;
        gotoligcol(11,124);
        Color(14,3);
        std :: cout << rayon;
        gotoligcol(11,129);
        Color(14,3);
        std :: cout << rayon;

        gotoligcol(9,123);
        Color(14,3);
        std :: cout << rectangle;
        gotoligcol(9,130);
        Color(14,3);
        std :: cout << rectangle;

        for (i=12; i<24; i++)
        {
            Color(0,15);
            gotoligcol(i,65);
            std :: cout << trait;

        }

        for (i=65; i<76; i++)
        {
            Color(0,15);
            gotoligcol(11,i);
            std :: cout << rectangle;
        }

        for (i=55; i<65; i++)
        {
            Color(0,15);
            gotoligcol(11,i);
            std :: cout << rectangle;
        }

        for (i=12; i<16; i++)
        {
            Color(0,15);
            gotoligcol(i,55);
            std :: cout << trait;

        }

        for (i=12; i<16; i++)
        {
            Color(0,15);
            gotoligcol(i,75);
            std :: cout << trait1;
        }

        /// Cabine

        for (i=70; i<81; i++)
        {
            Color(0,15);
            gotoligcol(16,i);
            std :: cout << trait3;
        }

        for (i=70; i<81; i++)
        {
            Color(0,15);
            gotoligcol(19,i);
            std :: cout << trait3;
        }

        for (i=70; i<81; i++)
        {
            Color(0,15);
            gotoligcol(18,i);
            std :: cout << trait3;
        }


        for (i=53; i<61; i++)
        {
            Color(0,15);
            gotoligcol(16,i);
            std :: cout << trait3;
        }

        for (i=53; i<61; i++)
        {
            Color(0,15);
            gotoligcol(19,i);
            std :: cout << trait3;
        }

        for (i=53; i<61; i++)
        {
            Color(0,15);
            gotoligcol(18,i);
            std :: cout << trait3;
        }

        gotoligcol(16,61);
        std :: cout << coin1;
        gotoligcol(19,61);
        std :: cout << coin2;

        for (i=17; i<19; i++)
        {
            Color(0,15);
            gotoligcol(i,61);
            std :: cout << trait2;
        }

        for (i=17; i<19; i++)
        {
            Color(0,15);
            gotoligcol(i,69);
            std :: cout << trait2;
        }

        for (i=17; i<19; i++)
        {
            Color(0,15);
            gotoligcol(i,81);
            std :: cout << trait2;
        }

        gotoligcol(16,81);
        std :: cout << coin1;
        gotoligcol(16,69);
        std :: cout << coin3;
        gotoligcol(19,81);
        std :: cout << coin2;
        gotoligcol(19,69);
        std :: cout << coin4;

        Color(0,15);

        /// Plan station

        gotoligcol(8,54);
        Color(4,15);
        std :: cout << "BORNE D INFORMATION DE LA";
        gotoligcol(9,54);
        std :: cout << "STATION DES ARCS";
        Color(0,15);





        gotoligcol(15,87);
        std :: cout << triangle;
        std :: cout <<"   LES STATIONS ";
        gotoligcol(15,106);
        std :: cout << fleche << " 1";


        gotoligcol(17,87);
        std :: cout << triangle;
        std :: cout <<"  PLAN DES PISTES";
        gotoligcol(17,106);
        std :: cout << fleche << " 2";

        gotoligcol(19,87);
        std :: cout << triangle;
        std :: cout <<"    LES TRAJETS ";
        gotoligcol(19,106);
        std :: cout << fleche << " 3";

        gotoligcol(21,87);
        std :: cout << triangle;
        std :: cout <<"      COMPTE    ";
        gotoligcol(21,106);
        std :: cout << fleche << " 4";

        gotoligcol(23,87);
        std :: cout << triangle;
        std :: cout <<"      QUITTER    ";
        gotoligcol(23,106);
        std :: cout << fleche << " 5";

        gotoligcol(23,87);
        gotoligcol(26,55);
        std :: cout << "Veuillez entrer un chiffre ... ";

        do
        {
            std::cin>>choix;
            gotoligcol(26,94);
            if ((choix!=1)&&(choix!=2)&&(choix!=3)&&(choix!=4)&&(choix!=5))
            {
                Color(4,15);
                std :: cout << "Choix non valide !! ... ";
                Sleep(2000);
                Color(0,15);
                gotoligcol(26,94);
                std::cout<<"                          ";
                gotoligcol(26,55);

                std :: cout << "Veuillez entrer un chiffre ...       ";
                gotoligcol(26,86);
            }
        }
        while((choix!=1)&&(choix!=2)&&(choix!=3)&&(choix!=4)&&(choix!=5));
        Color(15,0);
        system("cls");
    }
    while (choix>6);
    system("cls");
    return choix;
}


/// Donné sur campus pour les couleurs
void Graphe :: Color(int couleurDuTexte,int couleurDeFond)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,couleurDeFond*16+couleurDuTexte);

    /*  (0 : NOIR) (1 : BLEU FONCE)  (2 : VERT FONCE) (3 : TURQUOISE) (4 : Rouge FONCE) (5 : VIOLET)
        (6 : VERT CACA D OIE) (7 : GRIS CLAIR) (8 : GRIS FONCE) (9 : BLEU FLUO) (10 : VERT FLUO) (11 : TURQUOISE)
        (12 : ROUGE FLUO ) (13 : VIOLET 2) (14 : JAUNE) (15 : BLANC) */

}

/// Donné sur campus pour la position
void Graphe :: gotoligcol( int lig, int col )
{
    COORD mycoord;
    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
}

/// Tuto pour que l'affichage se fasse bien sur votre ordinateur
void Graphe :: TUTO()
{
    gotoligcol(0,0);
    std :: cout << "IMPORTANT" << std::endl << std::endl;
    std::cout << "Faire clique droit sur la barre d'outil de cette fenetre -> PROPRIETES -> POLICE" << std::endl << std ::endl;
    std :: cout <<"Mettre la police : POLICES RASTER, Taille : 10x20"<< std :: endl <<std::endl;
    std::cout << "Allez dans CONFIGURATION -> TAILLE DE LA FENETRE 187x47" << std::endl << std::endl << std:: endl;
    system("Pause");
}

/// Interface d'accueil du compte d'une personne

int Graphe :: AccueilTrajetCompte(int *y)
{
    int i;
    int c=0;
    char trait1;
    char trait2;
    char coin1;
    char coin2;

    coin1=0xD9;
    coin2=0xDA;
    trait1=0xC4;
    trait2=0xB3;

    do
    {

        for (int i=80; i<105; i++)
        {
            Color(3,0);
            gotoligcol(3,i);
            std :: cout << trait1;
        }

        Color(15,0);
        gotoligcol(2,85);
        std::cout << "VOTRE COMPTE" << std::endl << std::endl;

        /// LES PISTES

        for (i=31; i<55; i++)
        {
            Color(14,0);
            gotoligcol(7,i);
            std :: cout << trait1;
        }

        for(i=31; i<55; i++)
        {

            gotoligcol(12,i);
            std :: cout << trait1;
        }

        for (i=8; i<12; i++)
        {
            Color(14,0);
            gotoligcol(i,30);
            std :: cout << trait2;
            Color(14,0);
            gotoligcol(i,55);
            std :: cout << trait2;
        }

        gotoligcol(9,36);
        std :: cout << "PERSONNALISER";
        gotoligcol(10,36);
        std :: cout << "     VOS     ";
        gotoligcol(11,36);
        std :: cout << " PREFERENCES ";
        gotoligcol(13,36);
        Color(11,0);
        std :: cout << "      1      ";

        /// PISTES REMONTEES

        for (i=64; i<88; i++)
        {
            Color(14,0);
            gotoligcol(7,i);
            std :: cout << trait1;
        }

        for(i=64; i<88; i++)
        {

            gotoligcol(12,i);
            std :: cout << trait1;
        }

        for (i=8; i<12; i++)
        {
            Color(14,0);
            gotoligcol(i,63);
            std :: cout << trait2;
            Color(14,0);
            gotoligcol(i,88);
            std :: cout << trait2;
        }

        gotoligcol(9,69);
        std :: cout << "TRAJETS SELON";
        gotoligcol(10,69);
        std :: cout << "     VOS     ";
        gotoligcol(11,69);
        std :: cout << " PREFERENCES ";
        gotoligcol(13,67);
        Color(11,0);
        std :: cout << "        2      ";

        /// LES NAVETTES

        for (i=97; i<121; i++)
        {
            Color(14,0);
            gotoligcol(7,i);
            std :: cout << trait1;
        }

        for(i=97; i<121; i++)
        {

            gotoligcol(12,i);
            std :: cout << trait1;
        }

        for (i=8; i<12; i++)
        {
            Color(14,0);
            gotoligcol(i,96);
            std :: cout << trait2;
            Color(14,0);
            gotoligcol(i,121);
            std :: cout << trait2;
        }

        gotoligcol(9,102);
        std :: cout << "     ALLER ";
        gotoligcol(10,102);
        std :: cout << "      AU   ";
        gotoligcol(11,102);
        std :: cout << "  RESTAURANT";
        gotoligcol(13,102);
        Color(11,0);
        std :: cout << "       3      ";


        /// LES NAVETTES

        for (i=130; i<154; i++)
        {
            Color(14,0);
            gotoligcol(7,i);
            std :: cout << trait1;
        }

        for(i=130; i<154; i++)
        {

            gotoligcol(12,i);
            std :: cout << trait1;
        }

        for (i=8; i<12; i++)
        {
            Color(14,0);
            gotoligcol(i,129);
            std :: cout << trait2;
            Color(14,0);
            gotoligcol(i,154);
            std :: cout << trait2;
        }

        gotoligcol(9,135);
        std :: cout << "      SE ";
        gotoligcol(10,135);
        std :: cout << "  DECONNECTER";
        gotoligcol(13,135);
        Color(11,0);
        std :: cout << "       4      ";

        gotoligcol(17,75);
        Color(11,0);
        std :: cout << coin2;
        gotoligcol(18,75);
        std :: cout << trait2;
        gotoligcol(17,76);
        std :: cout << trait1;
        gotoligcol(17,77);
        std :: cout << trait1;
        gotoligcol(18,77);
        Color(15,0);
        std :: cout << " Veuillez faire un choix ...   ";
        Color(11,0);
        gotoligcol(20,108);
        std :: cout << coin1;
        gotoligcol(19,108);
        std :: cout << trait2;
        gotoligcol(20,107);
        std :: cout << trait1;
        gotoligcol(20,106);
        std :: cout << trait1;

        Color(14,0);
        gotoligcol(19,90);
        std :: cin >> c;
        while ((c<0) || (c>4))
        {
            gotoligcol(19,90);
            std :: cout << "        ";
            gotoligcol(19,90);
            std :: cin >> c;
        }
        system("cls");
        switch (c)
        {
        case 1:
        {
            SaisirPreferences(y);
            Sauvegarde2();
            system("cls");
            c=5;
        }
        break;
        case 2:
        {
            DijkstraPref(y);
            system("cls");
            c=5;
        }
        break;
        case 3:
        {
            int debut=0;

            afficher2();
            texte();
            trait();
            debut=saisieSommetDepart3();
            Dijkstra3(debut,9);

            gotoligcol(27,86);
            system ("Pause");
            system("cls");
            c=5;
        }
        break;
        case 4:
        {
            c=3;
            initialisationBool();
        }
        break;

        }
    }
    while((c<1)||(c>4));

    return c;
}


/// Accueil pour consulter tous les trajets

int Graphe :: AccueilTrajet()
{
    int i;
    int cx=0;
    char trait1;
    char trait2;
    char coin1;
    char coin2;

    coin1=0xD9;
    coin2=0xDA;
    trait1=0xC4;
    trait2=0xB3;

    do
    {

        for (int i=80; i<105; i++)
        {
            Color(3,0);
            gotoligcol(3,i);
            std :: cout << trait1;
        }

        Color(15,0);
        gotoligcol(2,80);
        std::cout << "VOICI LE PLAN DES TRAJETS " << std::endl << std::endl;

        /// LES PISTES

        for (i=31; i<55; i++)
        {
            Color(14,0);
            gotoligcol(7,i);
            std :: cout << trait1;
        }

        for(i=31; i<55; i++)
        {

            gotoligcol(12,i);
            std :: cout << trait1;
        }

        for (i=8; i<12; i++)
        {
            Color(14,0);
            gotoligcol(i,30);
            std :: cout << trait2;
            Color(14,0);
            gotoligcol(i,55);
            std :: cout << trait2;
        }

        gotoligcol(9,33);
        std :: cout << "TRAJET LE PLUS COURT";
        gotoligcol(10,36);
        Color(15,0);
        std :: cout << "   A ";
        Color(14,0);
        std :: cout << "--> ";
        Color(15,0);
        std :: cout << "B";
        gotoligcol(11,36);
        Color(14,0);
        std :: cout << "  (DJIKSTRA)";
        gotoligcol(13,36);
        Color(11,0);
        std :: cout << "      1      ";

        /// PISTES REMONTEES

        for (i=64; i<88; i++)
        {
            Color(14,0);
            gotoligcol(7,i);
            std :: cout << trait1;
        }

        for(i=64; i<88; i++)
        {

            gotoligcol(12,i);
            std :: cout << trait1;
        }

        for (i=8; i<12; i++)
        {
            Color(14,0);
            gotoligcol(i,63);
            std :: cout << trait2;
            Color(14,0);
            gotoligcol(i,88);
            std :: cout << trait2;
        }

        gotoligcol(8,67);
        std :: cout << "   LES TRAJETS ";
        gotoligcol(9,67);
        std :: cout << "  LES PLUS COURTS ";
        gotoligcol(10,65);
        std :: cout << "  PARTANT D UN POINT";
        gotoligcol(11,67);
        Color(15,0);
        std :: cout << "   A";
        Color(14,0);
        std :: cout << "  (DJIKSTRA)";
        gotoligcol(13,67);
        Color(11,0);
        std :: cout << "        2      ";

        /// LES NAVETTES

        for (i=97; i<121; i++)
        {
            Color(14,0);
            gotoligcol(7,i);
            std :: cout << trait1;
        }

        for(i=97; i<121; i++)
        {

            gotoligcol(12,i);
            std :: cout << trait1;
        }

        for (i=8; i<12; i++)
        {
            Color(14,0);
            gotoligcol(i,96);
            std :: cout << trait2;
            Color(14,0);
            gotoligcol(i,121);
            std :: cout << trait2;
        }

        gotoligcol(8,102);
        std :: cout << "  LES TRAJETS";
        gotoligcol(9,102);
        std :: cout << "LES PLUS COURTS ";
        gotoligcol(10,100);
        std :: cout << "PARTANT D UN POINT";
        gotoligcol(11,102);
        Color(15,0);
        std :: cout << "     A ";
        Color(14,0);
        std :: cout << "(BFS)";
        gotoligcol(13,102);
        Color(11,0);
        std :: cout << "       3      ";


        /// LES NAVETTES

        for (i=130; i<154; i++)
        {
            Color(14,0);
            gotoligcol(7,i);
            std :: cout << trait1;
        }

        for(i=130; i<154; i++)
        {

            gotoligcol(12,i);
            std :: cout << trait1;
        }

        for (i=8; i<12; i++)
        {
            Color(14,0);
            gotoligcol(i,129);
            std :: cout << trait2;
            Color(14,0);
            gotoligcol(i,154);
            std :: cout << trait2;
        }

        gotoligcol(9,132);
        std :: cout << "TRAJET LE PLUS COURT";
        gotoligcol(10,135);
        Color(15,0);
        std :: cout << "    A ";
        Color(14,0);
        std :: cout << "--> ";
        Color(15,0);
        std :: cout << "B";
        gotoligcol(11,135);
        Color(14,0);
        std :: cout << "     (BFS)";
        gotoligcol(13,135);
        Color(11,0);
        std :: cout << "       4      ";

        gotoligcol(17,75);
        Color(11,0);
        std :: cout << coin2;
        gotoligcol(18,75);
        std :: cout << trait2;
        gotoligcol(17,76);
        std :: cout << trait1;
        gotoligcol(17,77);
        std :: cout << trait1;
        gotoligcol(18,77);
        Color(15,0);
        std :: cout << " Veuillez faire un choix ...   ";
        Color(11,0);
        gotoligcol(20,108);
        std :: cout << coin1;
        gotoligcol(19,108);
        std :: cout << trait2;
        gotoligcol(20,107);
        std :: cout << trait1;
        gotoligcol(20,106);
        std :: cout << trait1;

        Color(4,0);
        gotoligcol(21,91);
        std :: cout << "0 : ECRAN ACCUEIL";

        Color(14,0);
        gotoligcol(19,90);
        std :: cin >> cx;
        while ((cx<0) || (cx>4))
        {
            gotoligcol(19,90);
            std :: cout << "        ";
            gotoligcol(19,90);
            std :: cin >> cx;
        }
        system("cls");
        int debut=0;
        int fin=0;
        Graphe g{"data_arcs.txt"};
        switch (cx)
        {
        case 0:
        {
            return cx;
        }
        case 1:
        {
            system("cls");
            g.afficher2();
            debut=g.saisieSommetDepart();
            fin=g.saisieSommetArrivee();
            g.Dijkstra(debut,fin);
            gotoligcol(29,95);
            system("Pause");
        }
        break;
        case 2:
        {
            system("cls");
            debut=0;
            g.afficher4();
            Color(15,0);
            gotoligcol(2,69);
            std::cout<<"TOUS LES TRAJETS LES PLUS COURTS PARTANT D UN POINT A"<<std::endl<<std::endl<<std::endl;
            debut=g.saisieSommetDepart2();
            for (int i=0; i<(int)g.getSommet().size(); i++)
            {
                g.Dijkstra2(debut,i+1);
            }
            std :: cout << std :: endl << std :: endl;
            system("Pause");


        }
        break;
        case 3:
        {
            debut=0;
            g.afficher4();
            Color(15,0);
            gotoligcol(2,69);
            std::cout<<"LES TRAJETS LES PLUS COURTS PARTANT D UN POINT A (BFS)"<<std::endl<<std::endl<<std::endl;
            debut=g.saisieSommetDepart2();
            g.BFS(debut);
            std :: cout << std :: endl << std :: endl;
            system("Pause");
        }
        break;
        case 4:
        {
            debut=0;
            g.afficher4();
            Color(15,0);
            gotoligcol(2,80);
            std::cout<<"TRAJET LE PLUS COURT A --> B (BFS)"<<std::endl<<std::endl<<std::endl;
            debut=g.saisieSommetDepart2();
            fin=g.saisieSommetArrivee2();
            g.BFS2 (debut,fin);
            std :: cout << std :: endl << std :: endl;
            system("Pause");
        }
        system("cls");

        }
    }
    while((cx<0)||(cx>4));

    return cx;
}



/////////////////////////////////////////////////////////////////////////////////////  DIJKSTRA  /////////////////////////////////////////////////////////////////////////////////////////

typedef std::pair <int, Sommet*> pi;   /// recuperé sur internet

/// Dijkstra d'un sommet de départ vers un sommet d'arrivée

void Graphe :: Dijkstra (int depart, int arrivee)
{

    std::priority_queue <pi, std::vector<pi>, std::greater <pi> > file;    /// recuperé sur internet, pour classer les sommets en fonction de leurs pondérations
    Sommet * som = m_sommets[depart-1];
    bool finDijkstra=false; //Variable permettant de sortir de l'algorithme

    for (int i=0; i<(int)m_sommets.size(); i++)
    {
        m_sommets[i]->setCouleur2();
        som->setDistance(0);
        m_sommets[i]->setDistance(100000);
        m_sommets[i]->setAntecedent(NULL);
    }
    som->setDistance(0);

    if (som->getSortant().empty())
    {
        gotoligcol(25,95);
        std::cout<< "Le sommet ";
        Color(12,0);
        std :: cout << depart;
        Color(15,0);
        std :: cout << " est un puit !";
    }
    else
    {

        while (finDijkstra==false)
        {
            som->setCouleur(); //Decouverte du sommet
            for(auto f : som->getSortant())
            {

                if (f->getArrivee()->getCouleur()==0) //Si le sommet n'a pas encore été coloré/validé
                {
                    if (f->getActif()==true)
                    {
                        int distance=0;

                        distance=som->getDistance()+f->getMin()*60+f->getSec(); //Distance totale par rapport au sommet de départ

                        if(distance < f->getArrivee()->getDistance())
                        {
                            f->getArrivee()->setDistance(distance);
                            f->getArrivee()->setAntecedent(som);                       //Traitement et coloration du sommet
                            file.push(std::make_pair(distance,f->getArrivee()));
                        }
                    }
                }
            }

            // On retire le sommet validé de la priority queue
            finDijkstra=true;

            for (int i=0; i<(int)m_sommets.size(); i++)
            {
                if(m_sommets[i]->getCouleur()==0) //Si un sommet n'a pas encore été coloré alors l'algorithme continu
                {
                    finDijkstra=false;
                }

            }
            if (file.size()!=0)
            {
                som=file.top().second;
                file.pop();
            }
            else if (finDijkstra==false)
            {
                finDijkstra=true;
            }

        }

        if (m_sommets[arrivee-1]->getCouleur()==true)
        {

            //Affiche du chemin parcouru
            Sommet* smaj=m_sommets[arrivee-1];

            gotoligcol(24,95);
            Color(14,0);
            std::cout<< "Le chemin le plus court entre ces deux bornes est le suivant : ";
            Color(14,0);
            gotoligcol(25,95);
            Color(15,0);
            while(smaj!=m_sommets[depart-1])
            {
                std::cout<<smaj->getNom();
                smaj=smaj->getAntecedent();
                Color(12,0);
                std::cout<<" <- ";
                Color(15,0);
            }

            //Affichage du poids
            std::cout<<depart;
            gotoligcol(27,95);
            Color(14,0);

            //Affichage des temps de trajets

            std::cout<< "Le temps de ce trajet est de : ";
            Color(15,0);
            if(((m_sommets[arrivee-1]->getDistance()-m_sommets[arrivee-1]->getDistance()%60)/60 >=60)  && ((m_sommets[arrivee-1]->getDistance()-m_sommets[arrivee-1]->getDistance()%60)/60 < 120))
            {
                std::cout<< "1 h " << (m_sommets[arrivee-1]->getDistance()-m_sommets[arrivee-1]->getDistance()%60)/60 -60<<" min " << m_sommets[arrivee-1]->getDistance()%60 << " s";
            }
            else if (((m_sommets[arrivee-1]->getDistance()-m_sommets[arrivee-1]->getDistance()%60)/60 >=120) && ((m_sommets[arrivee-1]->getDistance()-m_sommets[arrivee-1]->getDistance()%60)/60 <180))
            {
                std::cout<< "2 h " << ((m_sommets[arrivee-1]->getDistance()-m_sommets[arrivee-1]->getDistance()%60)/60) -120<< " min " << m_sommets[arrivee-1]->getDistance()%60 << " s";
            }
            else if ((m_sommets[arrivee-1]->getDistance()-m_sommets[arrivee-1]->getDistance()%60)/60 >=180)
            {
                std::cout<< "3 h " << ((m_sommets[arrivee-1]->getDistance()-m_sommets[arrivee-1]->getDistance()%60)/60) -180<< " min " << m_sommets[arrivee-1]->getDistance()%60 << " s";
            }
            else if ((m_sommets[arrivee-1]->getDistance()-m_sommets[arrivee-1]->getDistance()%60)/60 < 60)
            {
                std::cout<<(m_sommets[arrivee-1]->getDistance()-m_sommets[arrivee-1]->getDistance()%60)/60<<" min " << m_sommets[arrivee-1]->getDistance()%60 << " s";
            }
        }
        else
        {
            gotoligcol(24,95);
            Color(12,0);
            std :: cout << "Il n existe aucun itineraire allant du sommet " << depart << " au sommet " << arrivee ;
            Color(15,0);
        }
    }
}

/// Dijkstra d'un sommet vers tous les autres sommets (codé dans un sous programme d'affichage avec une boucle for allant du sommet demandé à chacun des autres sommets

void Graphe :: Dijkstra2 (int depart, int arrivee)
{
    std::priority_queue <pi, std::vector<pi>, std::greater <pi> > file;    /// recuperé sur internet, pour classer les sommets en fonction de leurs pondérations
    Sommet * som = m_sommets[depart-1];
    bool finDijkstra=false; //Variable permettant de sortir de l'algorithme

    for (int i=0; i<(int)m_sommets.size(); i++)
    {
        m_sommets[i]->setCouleur2();
        som->setDistance(0);
        m_sommets[i]->setDistance(100000);
        m_sommets[i]->setAntecedent(NULL);
    }
    som->setDistance(0);


    if (som->getSortant().empty())
    {
        gotoligcol(11,0);
        Color(12,0);
        std::cout<< "Il n y a pas de trajet possible possible car c est un puit ";
        Color(15,0);
    }

    else
    {
        while (finDijkstra==false)
        {
            som->setCouleur(); //Decouverte du sommet
            for(auto f : som->getSortant())
            {


                if (f->getArrivee()->getCouleur()==0) //Si le sommet n'a pas encore été coloré/validé
                {
                    int distance=0;

                    distance=som->getDistance()+f->getMin()*60+f->getSec(); //Distance totale par rapport au sommet de départ

                    if(distance < f->getArrivee()->getDistance())
                    {
                        f->getArrivee()->setDistance(distance);
                        f->getArrivee()->setAntecedent(som);                       //Traitement et coloration du sommet
                        file.push(std::make_pair(distance,f->getArrivee()));
                    }
                }

            }

            som=file.top().second;
            file.pop(); // On retire le sommet validé de la priority queue
            finDijkstra=true;

            for (int i=0; i<(int)m_sommets.size(); i++)
            {
                if(m_sommets[i]->getCouleur()==0) //Si un sommet n'a pas encore été coloré alors l'algorithme continu
                {
                    finDijkstra=false;
                }
            }
        }


        //Affiche du chemin parcouru
        Sommet* smaj=m_sommets[arrivee-1];
        Color(14,0);
        std :: cout << std :: endl ;
        std :: cout << "Trajet : ";
        Color(15,0);
        while(smaj!=m_sommets[depart-1])
        {
            std::cout<<smaj->getNom();
            smaj=smaj->getAntecedent();
            Color(12,0);
            std::cout<<" <- ";
            Color(15,0);
        }

        //Affichage du poids
        std::cout<<depart;
        std::cout<<std::endl;
        Color(14,0);
        std::cout<< "Le temps de trajet est de : ";
        Color(15,0);
        if(((m_sommets[arrivee-1]->getDistance()-m_sommets[arrivee-1]->getDistance()%60)/60 >=60)  && ((m_sommets[arrivee-1]->getDistance()-m_sommets[arrivee-1]->getDistance()%60)/60 < 120))
        {
            std::cout<< "1 h " << (m_sommets[arrivee-1]->getDistance()-m_sommets[arrivee-1]->getDistance()%60)/60 -60<<" min " << m_sommets[arrivee-1]->getDistance()%60 << " s" << std :: endl;
        }
        else if (((m_sommets[arrivee-1]->getDistance()-m_sommets[arrivee-1]->getDistance()%60)/60 >=120) && ((m_sommets[arrivee-1]->getDistance()-m_sommets[arrivee-1]->getDistance()%60)/60 <180))
        {
            std::cout<< "2 h " << ((m_sommets[arrivee-1]->getDistance()-m_sommets[arrivee-1]->getDistance()%60)/60) -120<< " min " << m_sommets[arrivee-1]->getDistance()%60 << " s" << std :: endl;
        }
        else if ((m_sommets[arrivee-1]->getDistance()-m_sommets[arrivee-1]->getDistance()%60)/60 >=180)
        {
            std::cout<< "3 h " << ((m_sommets[arrivee-1]->getDistance()-m_sommets[arrivee-1]->getDistance()%60)/60) -180<< " min " << m_sommets[arrivee-1]->getDistance()%60 << " s" << std :: endl;
        }
        else if ((m_sommets[arrivee-1]->getDistance()-m_sommets[arrivee-1]->getDistance()%60)/60 < 60)
        {
            std::cout<<(m_sommets[arrivee-1]->getDistance()-m_sommets[arrivee-1]->getDistance()%60)/60<<" min " << m_sommets[arrivee-1]->getDistance()%60 << " s" << std :: endl;
        }
    }
}

/// Dijkstra pour aller au restaurant se trouvant au sommet 9

void Graphe :: Dijkstra3 (int depart, int arrivee)
{

    std::priority_queue <pi, std::vector<pi>, std::greater <pi> > file;    /// recuperé sur internet, pour classer les sommets en fonction de leurs pondérations
    Sommet * som = m_sommets[depart-1];
    bool finDijkstra=false; //Variable permettant de sortir de l'algorithme

    for (int i=0; i<(int)m_sommets.size(); i++)
    {
        m_sommets[i]->setCouleur2();
        som->setDistance(0);
        m_sommets[i]->setDistance(100000);
        m_sommets[i]->setAntecedent(NULL);
    }
    som->setDistance(0);

    if (som->getSortant().empty())
    {
        gotoligcol(19,86);
        std::cout<< "Il n y a aucun trajet possible partant du sommet ";
        Color(12,0);
        std :: cout << depart;
        Color(15,0);
        std :: cout << " pour arriver au restaurant!";
    }
    else
    {

        while (finDijkstra==false)
        {
            som->setCouleur(); //Decouverte du sommet
            for(auto f : som->getSortant())
            {


                if (f->getArrivee()->getCouleur()==0) //Si le sommet n'a pas encore été coloré/validé
                {
                    int distance=0;

                    distance=som->getDistance()+f->getMin()*60+f->getSec(); //Distance totale par rapport au sommet de départ

                    if(distance < f->getArrivee()->getDistance())
                    {
                        f->getArrivee()->setDistance(distance);
                        f->getArrivee()->setAntecedent(som);                       //Traitement et coloration du sommet
                        file.push(std::make_pair(distance,f->getArrivee()));
                    }
                }

            }

            som=file.top().second;
            file.pop(); // On retire le sommet validé de la priority queue
            finDijkstra=true;

            for (int i=0; i<(int)m_sommets.size(); i++)
            {
                if(m_sommets[i]->getCouleur()==0) //Si un sommet n'a pas encore été coloré alors l'algorithme continu
                {
                    finDijkstra=false;
                }
            }
        }

        //Affiche du chemin parcouru
        Sommet* smaj=m_sommets[arrivee-1];

        gotoligcol(16,86);
        Color(14,0);
        std::cout<< "Le trajet le plus court entre le sommet ";
        std :: cout << depart;
        std :: cout << " et le FOOD SNOW est le suivant : ";
        Color(14,0);
        gotoligcol(17,86);
        Color(15,0);
        while(smaj!=m_sommets[depart-1])
        {
            std::cout<<smaj->getNom();
            smaj=smaj->getAntecedent();
            Color(12,0);
            std::cout<<" <- ";
            Color(15,0);
        }

        //Affichage du poids
        std::cout<<depart;
        gotoligcol(22,90);
        int heure=0;
        int minute=0;
        trait2();


        do
        {
            gotoligcol(21,86);
            std :: cout << "Entrez l'heure actuelle : ?? h ?? min ";
            gotoligcol(21,86);
            std :: cout << "Entrez l'heure actuelle : ";
            Color(11,0);
            std :: cin >> heure;
            Color(15,0);
        }
        while ((heure<10)||(heure>21));

        gotoligcol(21,114);
        std :: cout << " h ";

        do
        {
            gotoligcol(21,117);
            std :: cout << "?? min      ";
            gotoligcol(21,117);
            Color(11,0);
            std :: cin >> minute;
            Color(15,0);
        }
        while ((minute<0)||(minute>=60));

        gotoligcol(21,119);
        std :: cout << " min";

        gotoligcol(21,86);
        std :: cout << "Entrez l'heure actuelle : ";
        Color(11,0);
        std :: cout << heure;
        Color(15,0);
        std :: cout << " h ";
        Color(11,0);
        std :: cout << minute;
        Color(15,0);
        std :: cout << " min  ";

        gotoligcol(24,89);
        Calcul();
        gotoligcol(23,86);

        if (((minute+(m_sommets[8]->getDistance()- m_sommets[8]->getDistance()%60)/60)>=60))
        {
            std :: cout << "En empruntant le trajet ci-dessus vous arriverez au restaurant";
            Color(1,0);
            std :: cout << " FOOD SNOW ";
            Color(15,0);
            std :: cout << "a ";
            Color(11,0);
            std :: cout << heure+(((m_sommets[8]->getDistance()- m_sommets[8]->getDistance()%60)/60)/60)+1;
            Color(15,0);
            std :: cout << " h ";
            Color(11,0);
            std :: cout << minute+((m_sommets[8]->getDistance()- m_sommets[8]->getDistance()%60)/60)-60;
            Color(15,0);
            std :: cout << " min ";
        }
        else
        {
            std :: cout << "En empruntant le trajet ci-dessus vous arriverez au restaurant";
            Color(1,0);
            std :: cout << " FOOD SNOW ";
            Color(15,0);
            std :: cout << "a ";
            Color(11,0);
            std :: cout << heure+(((m_sommets[8]->getDistance()- m_sommets[8]->getDistance()%60)/60)/60);
            Color(15,0);
            std :: cout << " h ";
            Color(11,0);
            std :: cout << minute+((m_sommets[8]->getDistance()- m_sommets[8]->getDistance()%60)/60);
            Color(15,0);
            std :: cout << " min ";
        }

    }
}

/// Dijkstra en fonction des preferences de l'utilisateur, en prenant ou non les pistes qu'il a selectionné précedemment

void Graphe :: DijkstraPref (int *y)
{
    Graphe g;
    std::vector<Trajet*> trajets;
    int debut=0;
    int fin=0;

    for(int i=0; i<(int)m_compte[*y]->getPreference().size(); i++)
    {
        if(m_compte[*y]->getPreference()[i]==false)
        {
            if(i==0)
            {
                for(int j=0; j<(int)m_trajets.size(); j++)
                {
                    if(m_trajets[j]->getType()->getType()=="V")
                    {
                        m_trajets[j]->setActif(false);
                    }
                }
            }
            if(i==1)
            {
                for(int j=0; j<(int)m_trajets.size(); j++)
                {
                    if(m_trajets[j]->getType()->getType()=="B")
                    {
                        m_trajets[j]->setActif(false);
                    }
                }
            }
            if(i==2)
            {
                for(int j=0; j<(int)m_trajets.size(); j++)
                {
                    if(m_trajets[j]->getType()->getType()=="R")
                    {
                        m_trajets[j]->setActif(false);
                    }
                }
            }
            if(i==3)
            {
                for(int j=0; j<(int)m_trajets.size(); j++)
                {
                    if(m_trajets[j]->getType()->getType()=="N")
                    {
                        m_trajets[j]->setActif(false);
                    }
                }
            }
            if(i==4)
            {
                for(int j=0; j<(int)m_trajets.size(); j++)
                {
                    if(m_trajets[j]->getType()->getType()=="KL")
                    {
                        m_trajets[j]->setActif(false);
                    }
                }
            }
            if(i==5)
            {
                for(int j=0; j<(int)m_trajets.size(); j++)
                {
                    if(m_trajets[j]->getType()->getType()=="SURF")
                    {
                        m_trajets[j]->setActif(false);
                    }
                }
            }
            if(i==6)
            {
                for(int j=0; j<(int)m_trajets.size(); j++)
                {
                    if(m_trajets[j]->getType()->getType()=="TPH")
                    {
                        m_trajets[j]->setActif(false);
                    }
                }
            }
            if(i==7)
            {
                for(int j=0; j<(int)m_trajets.size(); j++)
                {
                    if(m_trajets[j]->getType()->getType()=="TC")
                    {
                        m_trajets[j]->setActif(false);
                    }
                }
            }
            if(i==8)
            {
                for(int j=0; j<(int)m_trajets.size(); j++)
                {
                    if(m_trajets[j]->getType()->getType()=="TSD")
                    {
                        m_trajets[j]->setActif(false);
                    }
                }
            }
            if(i==9)
            {
                for(int j=0; j<(int)m_trajets.size(); j++)
                {
                    if(m_trajets[j]->getType()->getType()=="TS")
                    {
                        m_trajets[j]->setActif(false);
                    }
                }
            }
            if(i==10)
            {
                for(int j=0; j<(int)m_trajets.size(); j++)
                {
                    if(m_trajets[j]->getType()->getType()=="TK")
                    {
                        m_trajets[j]->setActif(false);
                    }
                }
            }
            if(i==11)
            {
                for(int j=0; j<(int)m_trajets.size(); j++)
                {
                    if(m_trajets[j]->getType()->getType()=="BUS")
                    {
                        m_trajets[j]->setActif(false);
                    }
                }
            }
        }
    }
    afficher2();
    Color(15,0);
    gotoligcol(2,67);
    std::cout<<"                                                                 ";
    gotoligcol(2,67);
    std::cout<<"TRAJET LE PLUS COURT A --> B SELON MES PREFERENCES"<<std::endl<<std::endl<<std::endl;
    debut=saisieSommetDepart();
    fin=saisieSommetArrivee();
    Dijkstra(debut,fin);
    std :: cout << std :: endl << std :: endl;
    gotoligcol(29,95);
    system("Pause");
}


//////////////////////////////////////////////////////////////////  SAISIES DES SOMMETS DE DEPARTS ET D ARRIVEES ///////////////////////////////////////////////////////////////////////////

int Graphe :: saisieSommetDepart()
{
    int sommetDepart=0;
    gotoligcol(20,119);
    std::cout<<"Veuillez entrer le numero du sommet initial : ";
    Color(11,0);
    std::cin>>sommetDepart;
    while((sommetDepart<0) || (sommetDepart> (int)m_sommets.size()))
    {
        Color(15,0);
        gotoligcol(20,119);
        ///saisie du numéro du sommet initial pour lancer l'algo de Dijkstra
        std::cout<<"Veuillez entrer le numero du sommet initial :              ";
        gotoligcol(20,119);
        std::cout<<"Veuillez entrer le numero du sommet initial : ";
        Color(11,0);
        std::cin>>sommetDepart;
        Color(15,0);
    }
    Color(15,0);

    return sommetDepart;
}


int Graphe :: saisieSommetDepart2()
{
    int sommetDepart2=0;
    gotoligcol(5,20);
    std::cout<<"Veuillez entrer le numero du sommet initial : ";
    Color(11,0);
    std::cin>>sommetDepart2;
    while((sommetDepart2<0) || (sommetDepart2> (int)m_sommets.size()))
    {
        Color(15,0);
        gotoligcol(5,20);
        ///saisie du numéro du sommet initial pour lancer l'algo de Dijkstra
        std::cout<<"Veuillez entrer le numero du sommet initial :              ";
        gotoligcol(5,20);
        std::cout<<"Veuillez entrer le numero du sommet initial : ";
        Color(11,0);
        std::cin>>sommetDepart2;
        Color(15,0);
    }
    Color(15,0);

    return sommetDepart2;
}


int Graphe :: saisieSommetDepart3()
{
    int sommetDepart3=0;
    gotoligcol(14,86);
    std::cout<<"Veuillez entrer le numero du sommet ou vous vous trouvez : ";
    Color(11,0);
    std::cin>>sommetDepart3;
    while((sommetDepart3<0) || (sommetDepart3> (int)m_sommets.size()))
    {
        Color(15,0);
        gotoligcol(14,86);
        ///saisie du numéro du sommet initial pour lancer l'algo de Dijkstra
        std::cout<<"Veuillez entrer le numero du sommet ou vous vous trouvez :              ";
        gotoligcol(14,86);
        std::cout<<"Veuillez entrer le numero du sommet ou vous vous trouvez : ";
        Color(11,0);
        std::cin>>sommetDepart3;
        Color(15,0);
    }
    Color(15,0);

    return sommetDepart3;
}


int Graphe :: saisieSommetArrivee()
{
    int sommetFinal=0;
    gotoligcol(21,119);
    std::cout<<"Veuillez entrer le numero du sommet final   : ";
    Color(11,0);
    std::cin>>sommetFinal;
    while((sommetFinal<0) || (sommetFinal> (int)m_sommets.size()))
    {
        Color(15,0);
        gotoligcol(21,119);
        ///saisie du numéro du sommet final pour finir l'algo de Dijkstra
        std::cout <<"Veuillez entrer le numero du sommet final :         ";
        gotoligcol(21,119);
        std::cout<<"Veuillez entrer le numero du sommet final   : ";
        Color(11,0);
        std::cin>>sommetFinal;
        Color(15,0);
    }
    Color(15,0);
    std::cout<<std::endl;
    return sommetFinal;
}


int Graphe :: saisieSommetArrivee2()
{
    int sommetFinal=0;
    gotoligcol(6,20);
    std::cout<<"Veuillez entrer le numero du sommet final   : ";
    Color(11,0);
    std::cin>>sommetFinal;
    while((sommetFinal<0) || (sommetFinal> (int)m_sommets.size()))
    {
        Color(15,0);
        gotoligcol(6,20);
        ///saisie du numéro du sommet final pour finir l'algo de Dijkstra
        std::cout <<"Veuillez entrer le numero du sommet final :         ";
        gotoligcol(6,20);
        std::cout<<"Veuillez entrer le numero du sommet final   : ";
        Color(11,0);
        std::cin>>sommetFinal;
        Color(15,0);
    }
    Color(15,0);
    std::cout<<std::endl;
    return sommetFinal;
}

/////////////////////////////////////////////////////////////////////////////////////////  BFS /////////////////////////////////////////////////////////////////////////////////////////////////

void Graphe :: BFS(int depart)
{
    for (unsigned int f=0; f<m_sommets.size(); f++)
    {
        m_sommets[f]->setCouleur2();
    }
    ///Affichage et initialisation BFS
    std::cout<<std::endl;
    std::queue <Sommet*> file;

    ///Changement de la couleur du premier sommet pour qu'il n'apparaisse pas une deuxième fois
    m_sommets[depart-1]->setCouleur();
    file.push(m_sommets[depart-1]);

    std::cout << "Parcours BFS a partir du sommet : ";
    Color(11,0);
    std :: cout << depart << std::endl;
    Color(15,0);

    if (m_sommets[depart-1]->getSortant().empty())
    {
        gotoligcol(11,0);
        Color(12,0);
        std :: cout << "Il n y a pas de trajet possible car c est un puit ";
        Color(15,0);
    }

    else
    {
        while (file.empty()==false)
        {
            for (unsigned int i=0; i<file.front()->getSortant().size(); i++)
            {
                if (file.front()->getCouleur2(i)==false)
                {
                    file.push(file.front()->getSortant()[i]->getArrivee());
                    file.front()->getSortant()[i]->getArrivee()->ajouterAntecedent(file.front());
                    file.front()->getSortant()[i]->getArrivee()->setCouleur();
                }
            }
            file.pop();
        }

        for(unsigned int j =0 ; j < m_sommets.size() ; j++)
        {
            Sommet* dernier;
            dernier = m_sommets[j];

            std::cout << std::endl << m_sommets[j]->getNum();
            while (dernier->getAntecedent() != NULL)
            {
                Color(12,0);
                std::cout <<  " <- ";
                Color(15,0);
                std :: cout << dernier->getAntecedent()->getNom();
                dernier = dernier->getAntecedent();
            }
        }
    }
}


void Graphe :: BFS2 (int depart, int arrivee)
{
    for (unsigned int f=0; f<m_sommets.size(); f++)
    {
        m_sommets[f]->setCouleur2();
    }
    ///Affichage et initialisation BFS
    std::cout<<std::endl;
    std::queue <Sommet*> file;

    ///Changement de la couleur du premier sommet pour qu'il n'apparaisse pas une deuxième fois
    m_sommets[depart-1]->setCouleur();
    file.push(m_sommets[depart-1]);

    gotoligcol(9,0);
    std::cout << "Parcours BFS a partir du sommet : ";
    Color(11,0);
    std :: cout << depart;
    Color(15,0);
    std :: cout << " jusqu au sommet d arrivee ";
    Color(11,0);
    std :: cout << arrivee <<std::endl << std::endl;
    Color(15,0);

    if (m_sommets[depart-1]->getSortant().empty())
    {
        gotoligcol(11,0);
        Color(12,0);
        std :: cout << "Il n'existe pas de trajet possible car c est un puit !";
        Color(15,0);
    }

    else
    {
        while (file.empty()==false)
        {
            for (unsigned int i=0; i<file.front()->getSortant().size(); i++)
            {
                if (file.front()->getCouleur2(i)==false)
                {
                    file.push(file.front()->getSortant()[i]->getArrivee());
                    file.front()->getSortant()[i]->getArrivee()->ajouterAntecedent(file.front());
                    file.front()->getSortant()[i]->getArrivee()->setCouleur();
                }
            }
            file.pop();
        }

        Sommet* dernier;
        dernier = m_sommets[arrivee-1];

        std::cout << std::endl << m_sommets[arrivee-1]->getNum();

        while (dernier->getAntecedent() != NULL)
        {
            Color(12,0);
            std::cout <<  " <- ";
            Color(15,0);
            std :: cout << dernier->getAntecedent()->getNom();
            dernier = dernier->getAntecedent();
        }
        std::cout << std::endl << std::endl;
    }
}

/////////////////////////////////////////////////////////////////////////////////// CREATION D UN COMPTE ///////////////////////////////////////////////////////////////////////////////

std :: vector <Compte*> Graphe :: ficheIdentity()
{
    int retour;
    char trait1;
    char trait2;
    char trait8;
    int i;

    std :: string nom;
    std :: string prenom;
    std :: string pseudo;
    std :: string mdp;
    std :: string cmdp;

    std::vector <bool> preference;
    preference.push_back(true);
    preference.push_back(true);
    preference.push_back(true);
    preference.push_back(true);
    preference.push_back(true);
    preference.push_back(true);
    preference.push_back(true);
    preference.push_back(true);
    preference.push_back(true);
    preference.push_back(true);
    preference.push_back(true);
    preference.push_back(true);

    trait1=0xC4;
    trait2=0xBA;
    trait8=0xCD;

    do
    {
        Color(14,0);
        for (i=72; i<115; i++)
        {
            gotoligcol(6,i);
            std :: cout << trait8;
            gotoligcol(27,i);
            std :: cout << trait8;
            gotoligcol(11,i);
            std :: cout << trait1;
        }

        for (i=7; i<27; i++)
        {
            gotoligcol(i,71);
            std :: cout << trait2;
            gotoligcol(i,115);
            std :: cout << trait2;

        }

        gotoligcol(12,73);
        std :: cout << "NOM : ";
        gotoligcol(14,73);
        std :: cout << "PRENOM : ";
        gotoligcol(16,73);
        std :: cout << trait1;
        gotoligcol(18,73);
        std :: cout << "PSEUDO : ";
        gotoligcol(20,73);
        std :: cout << "MOT DE PASSE : ";
        gotoligcol(22,73);
        std :: cout << "CONFIRMATION MDP : ";
        gotoligcol(24,73);
        std :: cout << trait1;
        gotoligcol(26,73);
        std :: cout << "Annuler -> 0 / Confirmer -> 1 : ";
        gotoligcol(8,86);
        std :: cout << "STATION DES ARCS";
        gotoligcol(9,87);
        std :: cout << "  ( COMPTE )";
        Color(15,0);
        gotoligcol(12,79);
        std :: cin >> nom;
        gotoligcol(14,82);
        std :: cin >> prenom;
        gotoligcol(18,82);
        std :: cin >> pseudo;
        gotoligcol(20,88);
        std :: cin >> mdp;
        gotoligcol(22,92);
        std :: cin >> cmdp;
        if (mdp!=cmdp)
        {
            Color(14,0);
            gotoligcol(22,73);
            std :: cout << "CONFIRMATION MDP :                       ";
            gotoligcol(22,92);
            Color(15,4);
            std :: cout << "Plus qu une chance !";
            Sleep(3000);
            Color(14,0);
            gotoligcol(22,73);
            std :: cout << "CONFIRMATION MDP :                       ";
            gotoligcol(22,92);
            Color(15,0);
            std :: cin >> cmdp;

            if (mdp!=cmdp)
            {

            }
        }
        m_compte.push_back(new Compte(m_compte.size()+1, pseudo, mdp, preference));
        Color(15,0);
        gotoligcol(26,105);
        std :: cin >> retour;

        if(retour==1)
        {
            Sauvegarde2();
        }

        if(retour==0)
        {

        }
    }
    while ((retour!=0)&&(retour!=1));
    return m_compte;
}

//////////////////////////////////////////////////////////////////////////////// CONNEXION A UN COMPTE SAUVEGARDE ///////////////////////////////////////////////////////////////////////////

int Graphe :: SeConnecter(int *y)
{
    char trait1;
    char trait2;
    char trait3;
    char trait4;
    char trait5;
    char trait6;
    char traiit1;
    char traiit2;
    std :: string pseudo;
    std :: string mdp;
    int i;

    trait1=0xBA;
    trait2=0xBB;
    trait3=0xBC;
    trait4=0xC8;
    trait5=0xC9;
    trait6=0xCD;
    traiit1=0xB3;
    traiit2=0xC4;

    int temp=0;
    int temp2=0;
    int fin=0;

    do
    {
        temp=0;
        temp2=0;
        system("cls");
        Color(14,0);
        for (i=15; i<19; i++)
        {
            gotoligcol(i,74);
            std :: cout << trait1;
            gotoligcol(i,111);
            std :: cout << trait1;
        }

        for (i=75; i<111; i++)
        {
            gotoligcol(14,i);
            std :: cout << trait6;
            gotoligcol(19,i);
            std :: cout << trait6;
        }

        gotoligcol(14,74);
        std :: cout << trait5;
        gotoligcol(14,111);
        std :: cout << trait2;
        gotoligcol(19,74);
        std :: cout << trait4;
        gotoligcol(19,111);
        std :: cout << trait3;

        gotoligcol(16,76);
        std :: cout << "Pseudo : ";
        gotoligcol(17,76);
        std :: cout << "MDP : ";
        Color(15,0);
        gotoligcol(16,85);
        std :: cin >> pseudo;

        if(m_compte.size()==0)
        {
            std::cout<<"Aucun client n est enregistre dans la base de donnee"<<std::endl;
        }
        else
        {
            for(int i=0; i<(int)m_compte.size(); i++)
            {

                if(pseudo==m_compte[i]->getPseudo())
                {
                    gotoligcol(17,82);
                    std::cin>> mdp;

                    if( mdp == m_compte[i]->getMdp())
                    {
                        *y=i;
                        temp=1;
                        fin=1;
                    }
                    else
                    {
                        fin=4;
                        temp=1;
                    }
                    temp2=1;
                }

                else if (pseudo=="NONE")
                {
                    fin=4;
                    temp=1;
                }
            }
            if(temp2==0)
            {
                Color(15,0);
                for (i=0; i<44; i++)
                {
                    gotoligcol(5,i);
                    std :: cout << traiit2;
                }

                for (i=0; i<5; i++)
                {
                    gotoligcol(i,44);
                    std :: cout << traiit1;
                }

                Color(12,0);
                gotoligcol(0,0);
                std::cout<<"Ce pseudo n'est pas dans la base de donnee"<<std::endl;
                std::cout<<"Saisissez : ";
                Color(11,0);
                std :: cout << "NONE";
                Color(12,0);
                std :: cout <<" pour annuler"<<std::endl<<std::endl;
                Color(15,0);
                system("Pause");
            }
        }
    }
    while(temp!=1);
    return fin;
}

////////////////////////////////////////////////////////////////////////  ECRAN D ACCUEIL CONNEXION OU CREATION COMPTE /////////////////////////////////////////////////////////////////

int Graphe :: Connexion(int *y)
{
    char trait1;
    char trait2;
    char trait3;
    char trait4;
    char trait5;
    char trait6;
    char fleche;
    char triangle;
    int i;
    int chx;

    trait1=0xBA;
    trait2=0xBB;
    trait3=0xBC;
    trait4=0xC8;
    trait5=0xC9;
    trait6=0xCD;
    fleche=0x1A;
    triangle=0x10;

    system("cls");

    Color(14,0);
    for (i=14; i<23; i++)
    {
        gotoligcol(i,77);
        std :: cout << trait1;
        gotoligcol(i,108);
        std :: cout << trait1;
    }

    for (i=78; i<108; i++)
    {
        gotoligcol(13,i);
        std :: cout << trait6;
        gotoligcol(23,i);
        std :: cout << trait6;
    }

    gotoligcol(13,77);
    std :: cout << trait5;
    gotoligcol(13,108);
    std :: cout << trait2;
    gotoligcol(23,77);
    std :: cout << trait4;
    gotoligcol(23,108);
    std :: cout << trait3;
    Color(15,0);

    gotoligcol(15,82);
    std :: cout << triangle;
    std :: cout <<"   CREER COMPTE ";
    gotoligcol(15,101);
    std :: cout << fleche << " 1";


    gotoligcol(17,82);
    std :: cout << triangle;
    std :: cout <<"   SE CONNECTER";
    gotoligcol(17,101);
    std :: cout << fleche << " 2";

    gotoligcol(19,82);
    std :: cout << triangle;
    std :: cout <<"      QUITTER ";
    gotoligcol(19,101);
    std :: cout << fleche << " 3";

    gotoligcol(21,92);
    Color(11,0);
    std :: cin >> chx;
    while ((chx<1) || (chx>3))
    {
        gotoligcol(21,92);
        std :: cout << "       ";
        gotoligcol(21,92);
        Color(11,0);
        std :: cin >> chx;
        Color(15,0);
    }
    system("cls");

    switch (chx)
    {
    case 1:
    {
        ficheIdentity();
        system("cls");
    }
    break;
    case 2:
    {
        chx=SeConnecter(y);
        system("cls");
        if(chx==1)
        {
            chx=AccueilTrajetCompte(y);
        }
        system("cls");
    }
    break;
    system("cls");

    }
    return chx;
}

///////////////////////////////////////////////////////////////////////  SAUVEGARDE DU PROFIL DU COMPTE AVEC SES PREFERENCES ////////////////////////////////////////////////////////////
void Graphe :: Sauvegarde2()
{
    std::ofstream ifs("data_arcs.txt", std::ios::out);
    if (ifs)
    {
        ifs << m_sommets.size() << std::endl;
        for(int i = 0 ; i<(int)m_sommets.size() ; i++)
            ifs <<m_sommets[i]->getNum() << "  " << m_sommets[i]->getNom() << "  " << m_sommets[i]->getAltitude()<< std::endl;

        ifs << m_type.size() << std::endl;
        for(int i = 0 ; i<(int)m_type.size() ; i++)
            ifs << m_type[i]->getNom() << " " << m_type[i]->getType() << " " << m_type[i]->getTemps() << " " << m_type[i]->getAttente() <<std::endl;

        ifs << m_trajets.size() << std::endl;
        for(int i = 0 ; i<(int)m_trajets.size() ; i++)
            ifs << m_trajets[i]->getNum() << "  " << m_trajets[i]->getNom() << "  " << m_trajets[i]->getType()->getType() <<"  " << m_trajets[i]->getDepart()->getNum() <<"  " << m_trajets[i]->getArrivee()->getNum() << std::endl;

        ifs << m_compte.size() << std::endl;
        if (m_compte.size()!=0)
        {
            for(int i = 0 ; i<(int)m_compte.size() ; i++)
            {
                ifs << m_compte[i]->getNum() << " " << m_compte[i]->getPseudo() << " " << m_compte[i]->getMdp() << " " <<  std::endl;
                for (int j=0; j<(int)m_compte[i]->getPreference().size(); j++)
                {
                    ifs << m_compte[i]->getPreference()[j] << std::endl;
                }
            }
        }
        ifs.close();
    }
}

///////////////////////////////////////////////////////////////////////////////////// SAISIE DES PREFERENCES DU CLIENT ////////////////////////////////////////////////////////////////////////

void Graphe :: SaisirPreferences(int *pseudo)
{
    int choix=0;

    bool b;
    std::vector <bool> preference;

    gotoligcol(1,1);
    std :: cout << "Voulez vous emprunter des pistes vertes ..";
    Color(15,0);
    std :: cout << " 1. OUI - 2. NON";
    std :: cout << "    | Votre choix : ";
    Color(11,0);
    std :: cin >> choix;
    while ((choix<1) || (choix>2))
    {
        Color(14,0);
        gotoligcol(1,1);
        std :: cout << "Voulez vous emprunter des pistes vertes ..";
        Color(15,0);
        std :: cout << " 1. OUI - 2. NON";
        std :: cout << "    | Votre choix :              ";
        Color(14,0);
        gotoligcol(1,1);
        std :: cout << "Voulez vous emprunter des pistes vertes ..";
        Color(15,0);
        std :: cout << " 1. OUI - 2. NON";
        std :: cout << "    | Votre choix : ";
        Color(11,0);
        std :: cin >> choix;
    }
    if (choix == 1)
    {
        b=true;
        gotoligcol(1,44);
        Color(2,0);
        std :: cout << "1. OUI";
        gotoligcol(1,53);
        Color(4,0);
        std :: cout << "2. NON";
    }
    else
    {
        b=false;
        gotoligcol(1,44);
        Color(4,0);
        std :: cout << "1. OUI";
        gotoligcol(1,53);
        Color(2,0);
        std :: cout << "2. NON";

    }
    preference.push_back(b);

    Color(14,0);
    gotoligcol(3,1);
    std :: cout << "Voulez vous emprunter des pistes bleues ..";
    Color(15,0);
    std :: cout << " 1. OUI - 2. NON";
    std :: cout << "    | Votre choix : ";
    Color(11,0);
    std :: cin >> choix;
    while ((choix<1) || (choix>2))
    {
        Color(14,0);
        gotoligcol(3,1);
        std :: cout << "Voulez vous emprunter des pistes bleues ..";
        Color(15,0);
        std :: cout << " 1. OUI - 2. NON";
        std :: cout << "    | Votre choix :               ";
        Color(14,0);
        gotoligcol(3,1);
        std :: cout << "Voulez vous emprunter des pistes bleues ..";
        Color(15,0);
        std :: cout << " 1. OUI - 2. NON";
        std :: cout << "    | Votre choix : ";
        Color(11,0);
        std :: cin >> choix;
    }
    if (choix == 1)
    {
        b=true;
        gotoligcol(3,44);
        Color(2,0);
        std :: cout << "1. OUI";
        gotoligcol(3,53);
        Color(4,0);
        std :: cout << "2. NON";
    }
    else
    {
        b=false;
        gotoligcol(3,44);
        Color(4,0);
        std :: cout << "1. OUI";
        gotoligcol(3,53);
        Color(2,0);
        std :: cout << "2. NON";

    }
    preference.push_back(b);

    Color(14,0);
    gotoligcol(5,1);
    std :: cout << "Voulez vous emprunter des pistes rouges ..";
    Color(15,0);
    std :: cout << " 1. OUI - 2. NON";
    std :: cout << "    | Votre choix : ";
    Color(11,0);
    std :: cin >> choix;
    while ((choix<1) || (choix>2))
    {
        Color(14,0);
        gotoligcol(5,1);
        std :: cout << "Voulez vous emprunter des pistes rouges ..";
        Color(15,0);
        std :: cout << " 1. OUI - 2. NON";
        std :: cout << "    | Votre choix :               ";
        Color(14,0);
        gotoligcol(5,1);
        std :: cout << "Voulez vous emprunter des pistes rouges ..";
        Color(15,0);
        std :: cout << " 1. OUI - 2. NON";
        std :: cout << "    | Votre choix : ";
        Color(11,0);
        std :: cin >> choix;
    }

    if (choix == 1)
    {
        b=true;
        gotoligcol(5,44);
        Color(2,0);
        std :: cout << "1. OUI";
        gotoligcol(5,53);
        Color(4,0);
        std :: cout << "2. NON";
    }
    else
    {
        b=false;
        gotoligcol(5,44);
        Color(4,0);
        std :: cout << "1. OUI";
        gotoligcol(5,53);
        Color(2,0);
        std :: cout << "2. NON";

    }
    preference.push_back(b);


    Color(14,0);
    gotoligcol(7,1);
    std :: cout << "Voulez vous emprunter des pistes noires ..";
    Color(15,0);
    std :: cout << " 1. OUI - 2. NON";
    std :: cout << "    | Votre choix : ";
    Color(11,0);
    std :: cin >> choix;
    while ((choix<1) || (choix>2))
    {
        Color(14,0);
        gotoligcol(7,1);
        std :: cout << "Voulez vous emprunter des pistes noires ..";
        Color(15,0);
        std :: cout << " 1. OUI - 2. NON";
        std :: cout << "    | Votre choix :               ";
        Color(14,0);
        gotoligcol(7,1);
        std :: cout << "Voulez vous emprunter des pistes noires ..";
        Color(15,0);
        std :: cout << " 1. OUI - 2. NON";
        std :: cout << "    | Votre choix : ";
        Color(11,0);
        std :: cin >> choix;
    }

    if (choix == 1)
    {
        b=true;
        gotoligcol(7,44);
        Color(2,0);
        std :: cout << "1. OUI";
        gotoligcol(7,53);
        Color(4,0);
        std :: cout << "2. NON";
    }
    else
    {
        b=false;
        gotoligcol(7,44);
        Color(4,0);
        std :: cout << "1. OUI";
        gotoligcol(7,53);
        Color(2,0);
        std :: cout << "2. NON";

    }
    preference.push_back(b);

    Color(14,0);
    gotoligcol(9,1);
    std :: cout << "Voulez vous emprunter des pistes kilometres lancees ..";
    Color(15,0);
    std :: cout << " 1. OUI - 2. NON";
    std :: cout << "    | Votre choix : ";
    Color(11,0);
    std :: cin >> choix;
    while ((choix<1) || (choix>2))
    {
        Color(14,0);
        gotoligcol(9,1);
        std :: cout << "Voulez vous emprunter des pistes kilometres lancees ..";
        Color(15,0);
        std :: cout << " 1. OUI - 2. NON";
        std :: cout << "    | Votre choix :               ";
        Color(14,0);
        gotoligcol(9,1);
        std :: cout << "Voulez vous emprunter des pistes kilometres lancees ..";
        Color(15,0);
        std :: cout << " 1. OUI - 2. NON";
        std :: cout << "    | Votre choix : ";
        Color(11,0);
        std :: cin >> choix;
    }
    if (choix == 1)
    {
        b=true;
        gotoligcol(9,56);
        Color(2,0);
        std :: cout << "1. OUI";
        gotoligcol(9,65);
        Color(4,0);
        std :: cout << "2. NON";
    }
    else
    {
        b=false;
        gotoligcol(9,56);
        Color(4,0);
        std :: cout << "1. OUI";
        gotoligcol(9,65);
        Color(2,0);
        std :: cout << "2. NON";

    }
    preference.push_back(b);

    Color(14,0);
    gotoligcol(11,1);
    std :: cout << "Voulez vous emprunter des pistes snowboard ..";
    Color(15,0);
    std :: cout << " 1. OUI - 2. NON";
    std :: cout << "    | Votre choix : ";
    Color(11,0);
    std :: cin >> choix;
    while ((choix<1) || (choix>2))
    {
        Color(14,0);
        gotoligcol(11,1);
        std :: cout << "Voulez vous emprunter des pistes snowboard ..";
        Color(15,0);
        std :: cout << " 1. OUI - 2. NON";
        std :: cout << "    | Votre choix :              ";
        Color(14,0);
        gotoligcol(11,1);
        std :: cout << "Voulez vous emprunter des pistes snowboard ..";
        Color(15,0);
        std :: cout << " 1. OUI - 2. NON";
        std :: cout << "    | Votre choix : ";
        Color(11,0);
        std :: cin >> choix;
    }
    if (choix == 1)
    {
        b=true;
        gotoligcol(11,47);
        Color(2,0);
        std :: cout << "1. OUI";
        gotoligcol(11,56);
        Color(4,0);
        std :: cout << "2. NON";
    }
    else
    {
        b=false;
        gotoligcol(11,47);
        Color(4,0);
        std :: cout << "1. OUI";
        gotoligcol(11,56);
        Color(2,0);
        std :: cout << "2. NON";

    }
    preference.push_back(b);

    Color(14,0);
    gotoligcol(13,1);
    std :: cout << "Voulez vous emprunter des telepheriques ..";
    Color(15,0);
    std :: cout << " 1. OUI - 2. NON";
    std :: cout << "    | Votre choix : ";
    Color(11,0);
    std :: cin >> choix;
    while ((choix<1) || (choix>2))
    {
        Color(14,0);
        gotoligcol(13,1);
        std :: cout << "Voulez vous emprunter des telepheriques ..";
        Color(15,0);
        std :: cout << " 1. OUI - 2. NON";
        std :: cout << "    | Votre choix :             ";
        Color(14,0);
        gotoligcol(13,1);
        std :: cout << "Voulez vous emprunter des telepheriques ..";
        Color(15,0);
        std :: cout << " 1. OUI - 2. NON";
        std :: cout << "    | Votre choix : ";
        Color(11,0);
        std :: cin >> choix;
    }
    if (choix == 1)
    {
        b=true;
        gotoligcol(13,44);
        Color(2,0);
        std :: cout << "1. OUI";
        gotoligcol(13,53);
        Color(4,0);
        std :: cout << "2. NON";
    }
    else
    {
        b=false;
        gotoligcol(13,44);
        Color(4,0);
        std :: cout << "1. OUI";
        gotoligcol(13,53);
        Color(2,0);
        std :: cout << "2. NON";

    }
    preference.push_back(b);

    Color(14,0);
    gotoligcol(15,1);
    std :: cout << "Voulez vous emprunter des telecabines ..";
    Color(15,0);
    std :: cout << " 1. OUI - 2. NON";
    std :: cout << "    | Votre choix : ";
    Color(11,0);
    std :: cin >> choix;
    while ((choix<1) || (choix>2))
    {
        Color(14,0);
        gotoligcol(15,1);
        std :: cout << "Voulez vous emprunter des telecabines ..";
        Color(15,0);
        std :: cout << " 1. OUI - 2. NON";
        std :: cout << "    | Votre choix :             ";
        Color(14,0);
        gotoligcol(15,1);
        std :: cout << "Voulez vous emprunter des telecabines ..";
        Color(15,0);
        std :: cout << " 1. OUI - 2. NON";
        std :: cout << "    | Votre choix : ";
        Color(11,0);
        std :: cin >> choix;
    }

    if (choix == 1)
    {
        b=true;
        gotoligcol(15,42);
        Color(2,0);
        std :: cout << "1. OUI";
        gotoligcol(15,51);
        Color(4,0);
        std :: cout << "2. NON";
    }
    else
    {
        b=false;
        gotoligcol(15,42);
        Color(4,0);
        std :: cout << "1. OUI";
        gotoligcol(15,51);
        Color(2,0);
        std :: cout << "2. NON";

    }
    preference.push_back(b);

    Color(14,0);
    gotoligcol(17,1);
    std :: cout << "Voulez vous emprunter des telesieges debrayables ..";
    Color(15,0);
    std :: cout << " 1. OUI - 2. NON";
    std :: cout << "    | Votre choix : ";
    Color(11,0);
    std :: cin >> choix;
    while ((choix<1) || (choix>2))
    {
        Color(14,0);
        gotoligcol(17,1);
        std :: cout << "Voulez vous emprunter des telesieges debrayables ..";
        Color(15,0);
        std :: cout << " 1. OUI - 2. NON";
        std :: cout << "    | Votre choix :              ";
        Color(14,0);
        gotoligcol(17,1);
        std :: cout << "Voulez vous emprunter des telesieges debrayables ..";
        Color(15,0);
        std :: cout << " 1. OUI - 2. NON";
        std :: cout << "    | Votre choix : ";
        Color(11,0);
        std :: cin >> choix;
    }

    if (choix == 1)
    {
        b=true;
        gotoligcol(17,52);
        Color(2,0);
        std :: cout << "1. OUI";
        gotoligcol(17,61);
        Color(4,0);
        std :: cout << "2. NON";
    }
    else
    {
        b=false;
        gotoligcol(17,52);
        Color(4,0);
        std :: cout << "1. OUI";
        gotoligcol(17,61);
        Color(2,0);
        std :: cout << "2. NON";

    }
    preference.push_back(b);

    Color(14,0);
    gotoligcol(19,1);
    std :: cout << "Voulez vous emprunter des telesieges ..";
    Color(15,0);
    std :: cout << " 1. OUI - 2. NON";
    std :: cout << "    | Votre choix : ";
    Color(11,0);
    std :: cin >> choix;
    while ((choix<1) || (choix>2))
    {
        Color(14,0);
        gotoligcol(19,1);
        std :: cout << "Voulez vous emprunter des telesieges ..";
        Color(15,0);
        std :: cout << " 1. OUI - 2. NON";
        std :: cout << "    | Votre choix :              ";
        Color(14,0);
        gotoligcol(19,1);
        std :: cout << "Voulez vous emprunter des telesieges ..";
        Color(15,0);
        std :: cout << " 1. OUI - 2. NON";
        std :: cout << "    | Votre choix : ";
        Color(11,0);
        std :: cin >> choix;
    }

    if (choix == 1)
    {
        b=true;
        gotoligcol(19,41);
        Color(2,0);
        std :: cout << "1. OUI";
        gotoligcol(19,50);
        Color(4,0);
        std :: cout << "2. NON";
    }
    else
    {
        b=false;
        gotoligcol(19,41);
        Color(4,0);
        std :: cout << "1. OUI";
        gotoligcol(19,50);
        Color(2,0);
        std :: cout << "2. NON";

    }
    preference.push_back(b);

    Color(14,0);
    gotoligcol(21,1);
    std :: cout << "Voulez vous emprunter des teleskis ..";
    Color(15,0);
    std :: cout << " 1. OUI - 2. NON";
    std :: cout << "    | Votre choix : ";
    Color(11,0);
    std :: cin >> choix;
    while ((choix<1) || (choix>2))
    {
        Color(14,0);
        gotoligcol(21,1);
        std :: cout << "Voulez vous emprunter des teleskis ..";
        Color(15,0);
        std :: cout << " 1. OUI - 2. NON";
        std :: cout << "    | Votre choix :            ";
        Color(14,0);
        gotoligcol(21,1);
        std :: cout << "Voulez vous emprunter des teleskis ..";
        Color(15,0);
        std :: cout << " 1. OUI - 2. NON";
        std :: cout << "    | Votre choix : ";
        Color(11,0);
        std :: cin >> choix;
    }

    if (choix == 1)
    {
        b=true;
        gotoligcol(21,39);
        Color(2,0);
        std :: cout << "1. OUI";
        gotoligcol(21,48);
        Color(4,0);
        std :: cout << "2. NON";
    }
    else
    {
        b=false;
        gotoligcol(21,39);
        Color(4,0);
        std :: cout << "1. OUI";
        gotoligcol(21,48);
        Color(2,0);
        std :: cout << "2. NON";

    }
    preference.push_back(b);

    Color(14,0);
    gotoligcol(23,1);
    std :: cout << "Voulez vous emprunter des navettes ..";
    Color(15,0);
    std :: cout << " 1. OUI - 2. NON";
    std :: cout << "    | Votre choix : ";
    Color(11,0);
    std :: cin >> choix;
    while ((choix<1) || (choix>2))
    {
        Color(14,0);
        gotoligcol(23,1);
        std :: cout << "Voulez vous emprunter des navettes ..";
        Color(15,0);
        std :: cout << " 1. OUI - 2. NON";
        std :: cout << "    | Votre choix :              ";
        Color(14,0);
        gotoligcol(23,1);
        std :: cout << "Voulez vous emprunter des navettes ..";
        Color(15,0);
        std :: cout << " 1. OUI - 2. NON";
        std :: cout << "    | Votre choix : ";
        Color(11,0);
        std :: cin >> choix;
    }

    if (choix == 1)
    {
        b=true;
        gotoligcol(23,39);
        Color(2,0);
        std :: cout << "1. OUI";
        gotoligcol(23,48);
        Color(4,0);
        std :: cout << "2. NON";
    }
    else
    {
        b=false;
        gotoligcol(23,39);
        Color(4,0);
        std :: cout << "1. OUI";
        gotoligcol(23,48);
        Color(2,0);
        std :: cout << "2. NON";

    }
    preference.push_back(b);
    Calcul2();
    m_compte[*pseudo]->setPreferences(preference);

}
