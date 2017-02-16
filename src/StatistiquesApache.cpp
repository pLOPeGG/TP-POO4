//
// Created by doudou on 19/01/17.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "StatistiquesApache.h"



using namespace std;

bool StatistiquesApache::AjouterLigne(const LigneRequete & ligne, bool excludeFileTypes, bool useTime, int hour)
{
    if(ligne.filtre(excludeFileTypes,useTime,hour))//vrai si la ligne de requête passe le filtre
    {
        //on récupère les infos à stocker
        unsigned int from = indexPageName.getIndex(ligne.getReferer());
        unsigned int to = indexPageName.getIndex(ligne.getCible());

        /*
         * MIse à jour du nombre de hit de la page cible (to)
         */
        if(nbHit.find(to) == nbHit.end())//vrai si n'existe pas encore
        {
            nbHit[to]=1;
        }
        else
        {
            ++nbHit[to];
        }

        /*
         * Mise à jour du nombre de lien de Referer (from) vers Cible (to)
         */
        if(nbLink[from].find(to)==nbLink[from].end())//vrai si n'existe pas encore
        {
            nbLink[from][to]=1;
        }
        else
        {
            ++nbLink[from][to];

        }
        return true;
    }
    else
    {
        return false;//rien n'est inséré, les maps n'ont pas changé
    }
}

void StatistiquesApache::Afficher(unsigned int nbLignes)
{
    set<Couple> sortedPages;//set utiliser pour trier les pages par hit décroissant (voir class Couple)


    /*
     * Chaque élément de nbHit est inséré dans sortedPages
     */
    for(MapHit::const_iterator i = nbHit.begin(); i!= nbHit.end(); i++)
    {
        sortedPages.insert(Couple(i->first,i->second));//first correspond au nom de la page, second au nombre de hit
    }

    unsigned int index=0;


    /*
     * Affichage des nbLignes pages les plus vues
     */
    set<Couple>::const_iterator i = sortedPages.begin();
    while(index<nbLignes && i!=sortedPages.end())//s'arrête avant nbLignes si le conteneur contient moins d'éléments
    {
        index++;
        cout<<index<<" | Page : "<<indexPageName.getString(i->getPage())<<" | hit : "<<i->getHit()<<endl;
        i++;
    }

}

StatistiquesApache::StatistiquesApache()
    : indexPageName (), nbHit (), nbLink ()
{
#ifdef MAP
    cout<<"Appel du constructeur de <SatistiquesApache>"<<endl;
#endif
}

StatistiquesApache::~StatistiquesApache()
{
#ifdef MAP
    cout<<"Appel du destructeur de <SatistiquesApache>"<<endl;
#endif
}

bool StatistiquesApache::ExportGraph(const string &nomFichierGraph) const
{

    ofstream outputStreamGraph;
    outputStreamGraph.open(nomFichierGraph.c_str(),ios::app|ios::out);//ouverture en fin de fichier pour détecter l'existence de contenu
    if(outputStreamGraph.good())
    {
        /*
         * Le fichier existe déjà ?
         */
        if(outputStreamGraph.tellp()!=0)
        {
            string reponse;
            cout<<"Le fichier existe déjà, supprimer son contenu (y/n)"<<endl;
            cin>>reponse;
            outputStreamGraph.close();//dans les deux cas, on ferme le stream courant
            if(reponse=="y" || reponse=="Y")
            {
                /*
                 * On supprime le contenu du fichier
                 */
                outputStreamGraph.open(nomFichierGraph,ios::trunc|ios::out);//on supprime le contenu
                if(!outputStreamGraph)
                {
                    cerr<<"Erreur rencontrée à la troncature du fichier\nArrêt du programme"<<endl;
                    return false;
                }
            }
            else//l'utilisateur ne souhaite pas modifier le fichier
            {

                cerr<<"Fichier non modifié\nArrêt du programme"<<endl;
                return false;
            }

        }
        /*
         * Le stream est valide, positionné au début du fichier
         */

        string graphString;
        graphString=getGraph(graphString);//le texte en entier à écrire dans le fichier
        outputStreamGraph<<graphString;
        outputStreamGraph.close();
        cout<<"Dot-File "<<nomFichierGraph<<" généré"<<endl;
        return true;
    }
    else
    {
        outputStreamGraph.close();
        cerr<<"Erreur à l'ouverture du fichier"<<endl;
        return false;
    }
}

string & StatistiquesApache::getGraph(string & stringRetour)const {
    stringstream streamRetour;
    streamRetour<<"digraph Graphe_Apache {"<<endl;

    /*
     * Each page
     */
    const unordered_map<string,unsigned int> mapPage = indexPageName.getMapBase();
    for(unordered_map<string,unsigned int>::const_iterator i = mapPage.begin();i!=mapPage.end();i++)
    {
        streamRetour<<"node"<<i->second<<" [label=\""<<i->first<<"\"];"<<endl;//écriture d'un noeud pour une page
    }

    /*
     * Links
     */

    for(MapLink::const_iterator i=nbLink.begin();i!=nbLink.end();i++)//pour chaque page de départ
    {

        for(MapHit::const_iterator j=i->second.begin();j!=i->second.end();j++)//vers chaque cible possible
        {
            streamRetour<<"node"<<i->first<<" -> "<<"node"<<j->first<<" [label =\""<<j->second<<"\"];"<<endl;//écriture d'un lien entre deux pages
        }
    }

    streamRetour<<"}";
    stringRetour=streamRetour.str();//on remplit la string à retourner
    return stringRetour;
}
