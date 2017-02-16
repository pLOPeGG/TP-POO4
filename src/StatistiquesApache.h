//
// Created by doudou on 19/01/17.
//
/**
 * Classe StatistiquesApache : Permet d'effectuer des opérations statistiques de base
 * comme afficher les classement des pages les plus visitées et écrire le graphe reflétant
 * le fichier log lu
 */
#ifndef TP4_STATSTIQUESAPACHE_H
#define TP4_STATSTIQUESAPACHE_H
#include <unordered_map>
#include <set>
#include "IndexString.h"
#include "LigneRequete.h"
#include "Couple.h"

typedef unordered_map<unsigned int,unsigned int> MapHit;
typedef unordered_map<unsigned int,unordered_map<unsigned int,unsigned int>> MapLink;



class StatistiquesApache {
public:

    StatistiquesApache();
    /*
     * Constructeur
     */

    virtual ~StatistiquesApache();
    /*
     * Destructeur
     */

    bool AjouterLigne(const LigneRequete & ligne, bool excludeFileTypes=false, bool useTime=false, int hour = 0);
    /*
     * param :  ligne = référence constante sur un objet LigneRequete que l'on souhaite ajouter aux données
     *          excludeFileTypes = true si on n'ajoute pas les fichier images et javascript, false sinon
     *          useTime = true si on filtre sur un période d'une heure seulement
     *          hour = heure de début du filtre de temps
     * retour : true si la ligne a été ajoutée aux données, false sinon
     *
     * Ajoute ligne aux données si elle passe les différents filtres positionnés en paramètre
     *
     * constrat : ligne doit être instanciée correctement, les champs extension, date pageCible et pageReferer sont utilisés pas la méthode
     */

    void Afficher(unsigned int nbLignes);
    /*
     * param :  nbLignes = nombre de lignes à afficher
     *
     * Affiche le classement des pages par odre décroissant de hit
     *
     * contrat : si nbLignes>nbHit.size(), affiche nbHit.size(à nombre de lignes à la place.
     */

    bool ExportGraph(const string & nomFichierGraph)const;
    /*
     * param :  nomFichierGraph = chemin d'accès au fichier que l'on souhaite créer
     *
     * Créer un fichier contenant le code nécessaire à la visualisation des données sous forme de graphe via GraphViz
     *
     * contrat : si le fichier existe déjà, il sera demandé à l'utilisateur de confirmer la suppression de son contenu.
     */




private:

    string & getGraph(string & stringRetour)const;
    /*
     * param :  stringRetour = référence sur une string qui sera remplie par la méthode
     * retour : la string passée en paramètre est passée par référance à l'appeleant afin d'éviter la copie.
     *
     * Rédige une string contenant le texte à écrire dans le fichier graphe
     */

    IndexString indexPageName;//permet l'utilisation d'entier à la place de strings
    MapHit nbHit;//clef : un entier référencant une page, valeur : nombre de fois que cette page a été accédée
    MapLink nbLink;//clef : entier référencant la page source, valeur : ( clef : entier référencant la page cible, valeur : nombre de fois que le lien a été emprunté)



};


#endif //TP4_STATSTIQUESAPACHE_H
