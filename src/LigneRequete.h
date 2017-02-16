//
// Created by doudou on 09/01/17.
//
/**
 * Classe LigneRequete : permet de stocker les informations contenues dans une ligne d'un fichier
 * de logs Apache
 */
#ifndef TP4_LIGNEREQUETE_H
#define TP4_LIGNEREQUETE_H


#include <ctime>
#include <cstring>
#include <string>


using namespace std;

class LigneRequete {
public:

    LigneRequete(string codeIP="", string user="", string pseudo="",  tm date=tm(), string methodeHTTP="", string PageCible="", string extension="", string argumentsCible = "", string versionHTTP="", int codeErreur=0, int tailleReponse=0, string PageReferer="", string argumentsReferer="", string browser="");
    /*
     * Constructeur avec pour paramètres tous les attributs de la classe
     */

    string getCible()const;
    /*
     * retour : attribut pageCible
     */

    string getReferer()const;
    /*
     * retour : attribut pageReferer
     */

    bool filtre(const bool excludeFileTypes=false, const bool useTime=false, const int hour = 0)const;
    /*
     * param :  excludeFileTypes = true si l'on refuse les type d'images et de javascript
     *          useTime = true si on souhaite filtrer en fonction d'un créneau horaire
     *          hour = l'heure de départ du créneau horaire
     *
     * retour : true si l'objet passe tous les tests avec succès
     *          false sinon
     *
     * contrat : la méthode ne prend pas en compte l'attribut codeErreur et peut renvoyer true à un objet
     * ayant codeErreur=404 par exemple.
     */




private:
    string codeIP;//IP de l'utilisateur
    string user;//nom de l'utilisateur
    string pseudo;//pseudo de l'utilisateur
    tm date;//date de la requète
    string methodeHTTP;//nom de la méthode HTTP : GET, POST etc.
    string pageCible;//ressource ciblée par la requète
    string extensionCible;//extension de la ressource ciblée
    string argumentsCible;//arguments contenus dans la ressource ciblée
    string versionHTTP;//version HTTP du client
    int codeErreur;//code d'erreur HTTP renvoyé par le serveur
    int tailleReponse;//taille de la réponse du serveur en octets
    string pageReferer;//page d'origine du client
    string argumentsReferer;//arguments de la page d'origine du client
    string browser;//browser web utilisé par le client

};


#endif //TP4_LIGNEREQUETE_H
