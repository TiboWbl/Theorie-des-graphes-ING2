#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

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

#include "Trajet.h"
#include "Type.h"
#include "Compte.h"

class Graphe
{
private :

    /// Liste des sommets (vecteur de pointeurs sur Sommet)
    std::vector<Sommet*> m_sommets;
    std::vector<Trajet*> m_trajets;
    std::vector<Type*> m_type;
    std::vector<Compte*> m_compte;

public :

    Graphe (std::string nomFichier);
    Graphe();
    ~Graphe();
    std :: vector <Compte*> ficheIdentity();
    std :: vector <Sommet*> getSommet();
    std :: vector <Compte*> getCompte();

    int saisieSommetDepart();
    int saisieSommetArrivee();
    int saisieSommetDepart2();
    int saisieSommetArrivee2();
    int saisieSommetDepart3();
    int saisieSommetDepart4();
    int saisieSommetArrivee3();

    int Accueil();
    int AccueilTrajet();
    int AccueilTrajetCompte(int *y);
    int afficherPistes();
    int afficherTrajets();
    int Connexion(int *y);
    int afficher();
    int afficherRemontees();

    float CalculTrajet ();

    void afficher2();
    void afficher4();
    void trajet();
    void afficher3();
    void texte();
    void Calcul();
    void Calcul2();
    void trait();
    void trait2();
    int SeConnecter(int *y);
    void afficherPistes_KL();
    void afficherPistes_Vert();
    void afficherPistes_Noire();
    void afficherPistes_Rouge();
    void afficherPistes_Snowpark();
    void afficherPistes_Bleu();
    void afficherTPH();
    void afficherTSD();
    void afficherTS();
    void afficherTK();
    void afficherTC();
    void afficherBus();
    void Color(int couleurDuTexte,int couleurDeFond);
    void gotoligcol( int lig, int col );
    void TUTO();
    void Sauvegarde2();
    void SaisirPreferences(int *pseudo);
    void initialisationBool ();

    void Dijkstra (int depart, int arrivee);
    void Dijkstra2 (int depart, int arrivee);
    void Dijkstra3 (int depart, int arrivee);
    void DijkstraPref (int *y);

    void BFS(int depart);
    void BFS2 (int depart, int arrivee);

};

#endif // GRAPHE_H_INCLUDED
