//
// Created by doudou on 16/01/17.
//

/**
 * Classe InsertFluxApache : spécification de ifstream pour les fichiers logs Apache
 * Permet de lire ligne par ligne un fichier log, et de parser les données contenu dans un objet
 * de type LigneRequete.
 */
#ifndef TP4_INSERTFLUXAPACHE_H
#define TP4_INSERTFLUXAPACHE_H
#include <fstream>
#include "LigneRequete.h"
#include <string>
#include <vector>



using namespace std;



class InsertFluxApache : public ifstream {

public :

    InsertFluxApache(string nomFichier, string fichierLocalURL);
    /*
     * Constructeur
     * param :  nomFichier = chemin d'accès au fichier lgo
     *          fichierLocalURL = chemain d'accès au fichier qui contient les URL locales à supprimer
     *
     * contrat : si un des deux chemins d'accès est inaccessible (fichier inexistant ou droits insuffisants)
     * alors le failBit est positionné
     */

    virtual ~InsertFluxApache();
    /*
     *Destructeur
     */

    LigneRequete getLigneApache();
    /*
     * Lis la ligne courante du log et se positionne sur la suivante
     *
     * retour : instance de LigneRequete contenant les informations de la ligne lue
     */


private :
    vector<string> localURL;//conteneur des URL locales


};


#endif //TP4_INSERTFLUXAPACHE_H
