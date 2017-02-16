//
// Created by doudou on 16/01/17.
//

#include "InsertFluxApache.h"
#include "IndexString.h"
#include "StatistiquesApache.h"
#include <iostream>
#include <regex>



using namespace std;


InsertFluxApache::InsertFluxApache(string nomFichier, string fichierLocalURL)
        :ifstream(nomFichier.c_str())
{
#ifdef MAP
    cout<<"Appel du constructeur de <InserFluxApache>"<<endl;
#endif
    /**
     * Test de l'ifstream : détermination de la cause de l'erreur
     */
    if(!(*this))
        /**
         * Echec à l'ouverture : 2 possibilites
         *      le fichier n'existe pas
         *      pas de droits en lecture sur le fichier
         */
    {
        if(fopen(nomFichier.c_str(),"a+")!=NULL)//vrai si le fichier n'existait pas, le fichier est alors créé
        {

            remove(nomFichier.c_str());
            cerr<<"Fichier log inexistant : arrêt du programme"<<endl;


        }
        else//le fichier existe -> il manque des droits en lecture
        {
            cerr<<"Droits insuffisants en lecture sur le fichier log : arrêt du programme"<<endl;

        }
        setstate(ios_base::iostate::_S_failbit);//le flux n'est pas utilisable
    }
    else
    {

        ifstream logStream(fichierLocalURL.c_str());
        if(!(logStream))
        {
            /**
             * idem avec la lecture du fichierLocalURL
             * voir plus haut pour plus de détail
             */
            if(fopen(fichierLocalURL.c_str(),"a+")!=NULL)
            {
                remove(fichierLocalURL.c_str());
                cerr<<"Fichier URL locales inexistant : arrêt du programme"<<endl;

            }
            else
            {
                cerr<<"Droits insuffisants en lecture sur le fichier URL locales : arrêt du programme"<<endl;

            }
            setstate(ios_base::iostate::_S_failbit);

        }
        else
        {
            /**
             * Si le stream est bon
             * On lit chaque ligne et on l'ajoute au conteneur si elle n'est pas vide
             */
            string buf;
            do
            {

                std::getline(logStream, buf);

                if(buf!="")//si la ligne est non vide
                {
                    localURL.push_back(buf);
                }
            }while(logStream.good());
        }


    }


}


InsertFluxApache::~InsertFluxApache()
{
#ifdef MAP
    cout<<"Appel du destructeur de <InserFluxApache>"<<endl;
#endif

    this->close();


}

LigneRequete InsertFluxApache::getLigneApache()
{
    /**
     * Déclaration de variables pour parser une ligne
     */
    string codeIP;
    string user;
    string pseudo;
    tm date;
    string methodeHTTP;
    string pageCible;
    string extensionCible;
    string argumentsCible;
    string versionHTTP;
    int codeErreur;
    int tailleReponse;
    string pageReferer;
    string argumentsReferer;
    string browser;
    string timeString;


    (*this) >> codeIP >> user >> pseudo >> timeString;
    strptime(timeString.c_str(), "[%d/%b/%Y:%T", &date);//conversion de timeString au format tm

    (*this).ignore(10, '"');
    (*this) >> methodeHTTP >> pageCible;
    std::getline(*this, versionHTTP, '"');

    /**
     * Partie argumentsCible
     * but : extraire les arguments de l'URL
     */
    unsigned long index = pageCible.find("?");
    if (index != string::npos)
    {
        argumentsCible = pageCible.substr(index+1);
        pageCible=pageCible.substr(0,index);
    }

    index =pageCible.find(";jsessionid");
    if (index != string::npos)
    {
        argumentsCible += pageCible.substr((index+1));
        pageCible=pageCible.substr(0,index-1);
    }
    //extraction de l'extension
    if((index=pageCible.find("."))!=string::npos)
    {
        extensionCible=pageCible.substr(index);

    }


    (*this)>>codeErreur>>tailleReponse;

    //si la lecture échoue : ex avec "-"
    if(this->fail())
    {
        tailleReponse=0;
        this->clear();
    }

    (*this).ignore(10,'"');

    std::getline((*this), pageReferer,'"');

    /**
     * extraction des arguments pour pageReferer
     */
    index = pageReferer.find("?");
    if (index != string::npos)
    {
        argumentsReferer = pageReferer.substr(index+1);
        pageReferer=pageReferer.substr(0,index);
    }

    index =pageReferer.find(";jsessionid");
    if (index != string::npos)
    {
        argumentsReferer += pageReferer.substr((index+1));
        pageReferer=pageReferer.substr(0,index-1);
    }



    //traitement pour retirer les URL locales
    for(vector<string>::iterator i = localURL.begin(); i!=localURL.end(); i++)
    {
        if((pageReferer.find(*i))==0)
        {
            pageReferer=pageReferer.substr(i->length());
            break;
        }
    }


    (*this).ignore(10,'"');

    std::getline((*this), browser,'"');

    this->ignore(10,'\n');//retour début de ligne suivante
    return LigneRequete(codeIP,user,pseudo,date,methodeHTTP,pageCible, extensionCible, argumentsCible, versionHTTP, codeErreur, tailleReponse, pageReferer, argumentsReferer, browser);
}
