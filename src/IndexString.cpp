#include <unordered_map>
#include <utility>
#include <string>
#include <iostream>

using namespace std;

#include "IndexString.h"

unsigned int IndexString::getIndex(const string str)
{
    //recherche de la string
    unordered_map<string,unsigned int>::const_iterator got = mapBase.find (str);

    if ( got == mapBase.end() )//la string n'est pas encore dans la structure
    {
        compteur++;
        /**
         * On insère dans les deux map
         */
        mapBase.insert(std::make_pair(str,compteur));
        mapReavers.insert(std::make_pair(compteur,str));

        return compteur;
    }
    else
    {//la string est trouvée
        return got->second;
    }
}

string IndexString::getString(const unsigned int index)const
{
    try{
        return mapReavers.at(index);//retour d'une copie de la chaine stockée

    }
    catch(out_of_range exception)//si l'index n'a jamais été attribué
    {
        cerr<<"Nom de page introuvable"<<endl;
        return string();//conformément au contrat
    }
}

IndexString::IndexString(): mapBase(), mapReavers() , compteur(0)
{
#ifdef MAP
    cout<<"Appel du construteur de <IndexString>"<<endl;
#endif
}

IndexString::~IndexString()
{
#ifdef MAP
    cout<<"Appel du destructeur de <IndexString>"<<endl;
#endif
}

const unordered_map<string, unsigned int> &IndexString::getMapBase()const
{
    return mapBase;//copie de l'attribut
}


