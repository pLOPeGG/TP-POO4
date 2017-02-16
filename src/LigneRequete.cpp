//
// Created by doudou on 09/01/17.
//

#include "LigneRequete.h"
#include <regex>


string LigneRequete::getCible() const {
    return pageCible;

}

string LigneRequete::getReferer() const {
    return pageReferer;
}

LigneRequete::LigneRequete(string IP, string user, string pseudo, tm date, string methodeHTTP,
                           string PageCible, string extension, string argumentsCible ,string versionHTTP, int codeErreur, int tailleReponse,
                           string PageReferer, string argumentsReferer,  string browser)
    :codeIP (IP),user (user), pseudo (pseudo), date (date), methodeHTTP (methodeHTTP), pageCible (PageCible), extensionCible(extension), argumentsCible (argumentsCible), versionHTTP (versionHTTP), codeErreur (codeErreur), tailleReponse (tailleReponse), pageReferer (PageReferer),argumentsReferer(argumentsReferer), browser (browser)
{
#ifdef MAP
    cout<< "Appel du constructeur de <LigneRequete>"<<endl;
#endif

}

bool LigneRequete::filtre(const bool excludeFileTypes, const bool useTime, const int hour) const {

    /*
     * Obligatoire pour éviter une page vide;
     */
    if(pageCible=="")
    {
        return false;
    }

    if(useTime)
    {

        if(date.tm_hour>=hour+1 || date.tm_hour<hour) //pas dans le créneau time <= t < time +1
        {
            return false;
        }
    }
    if(excludeFileTypes)
    {

        /**
         * extension : 0.30s
         */

        if(extensionCible==".ico" || extensionCible==".jpg" || extensionCible==".css" || extensionCible==".js" || extensionCible==".png" || extensionCible==".jpeg" || extensionCible==".gif" )
        {
            return false;
        }


    }
    return true;
}
