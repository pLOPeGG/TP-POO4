//
// Created by doudou on 19/01/17.
//

#include <iostream>
#include "InsertFluxApache.h"
#include "StatistiquesApache.h"

using namespace std;

void run(string fichierLog, string fichierGraph, string localURL,bool local,  bool graph, int time, bool boolTime, bool excludeExtension);

int main(int length, char * args[])//TODO : rédaction man
{
    if(length<2)
    {
        cerr<<"Argument manquant : nom de fichier\nArrêt du programme"<<endl;
        return 0;
    }
    else
    {
        /**
         * variables pour stocker les arguments
         */
        string fichierLog;
        string fichierGraph;
        string localURL;
        bool local=false;
        bool timer=false;
        bool excludeExtension=false;
        bool graph=false;
        int time=0;


        for(int i=1;i<length;i++)//lecture de chaque arguments fournis en paramètre du main
        {
            if(string(args[i])=="-e")
            {
                excludeExtension=true;
            }
            else if(string(args[i])=="-t" && !timer)
            {
                timer=true;
                if(i+1<length)
                {
                    try{
                        time=stoi(string(args[++i]));//conversion de char* en int, incrémentation de i car lecture de 2 arguments
                    }catch (invalid_argument exception)
                    {
                        cerr<<"Argument "<<args[i-1]<<" invalide : type int attendu\nArrêt du programme"<<endl;
                        return 0;
                    }
                }
                else{
                    cerr<<"Argument attendu après -t : type int\nArrêt du programme"<<endl;
                    return 0;
                }


            }
            else if(string(args[i])=="-g" && !graph) {
                if(i+1<length)
                {
                    graph = true;
                    fichierGraph = string(args[++i]);//incrémentation de i car elcture de 2 arguments
                }
                else{
                    cerr<<"Argument attendu après -g : path vers un fichier\nArrêt du programme"<<endl;
                    return 0;
                }
            }
            else if (string(args[i])=="-l" && !local)
            {
                if(i+1<length)
                {
                    local=true;
                    localURL=string(args[++i]);//incrémentation de i car elcture de 2 arguments
                }
                else
                {
                    cerr<<"Argument attendu après -l : path vers un fichier\nArrêt du programme"<<endl;
                    return 0;
                }

            }
            else{
                fichierLog=string(args[i]);
                run(fichierLog,fichierGraph,localURL, local, graph,time,timer,excludeExtension);
            }
        }
        if(fichierLog=="")
        {
            cerr<<"Argument attendu : nom de fichier log Apache\nArrêt du programme"<<endl;

        }
        return 0;
    }

}

void run(string fichierLog, string fichierGraph, string localURL,bool local,bool graph, int time, bool boolTime, bool excludeExtension)
{
    if(!local)
    {
        localURL="../data/local";
    }
    InsertFluxApache flux (fichierLog, localURL);

    StatistiquesApache stats;

    int cmp=0;//compteur de nombre de lignes lues et enregistrées


    /*
     *
     */
    if(flux.good())
    {
        while(flux.good()) {
            LigneRequete l = flux.getLigneApache();
            if (stats.AjouterLigne(l, excludeExtension, boolTime, time)) {
                cmp++;
            }

        }


        /*
         * Résultats
         */


        stats.Afficher(100);

        if(graph)
        {
            stats.ExportGraph(fichierGraph);
        }
    }


}
