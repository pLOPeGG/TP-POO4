//
// Created by doudou on 16/01/17.
//

/**
 * Classe IndexString : implémente la structure de donnée qui permet d'éviter la duplication en mémoire
 * des noms de pages.
 * But : établir une bijection entre les noms rencontrés et les entiers naturels afin d'utiliser
 * un entie en mémoire au lieu d'un string partout où on en a besoin
 */
#ifndef TP4_INDEXSTRING_H
#define TP4_INDEXSTRING_H

#include <unordered_map>
#include <string>
using namespace std;

class IndexString{
public:

    IndexString();
    /*
     * Constructeur
     */

    virtual ~IndexString();
    /*
     * Destructeur
     */

    unsigned int getIndex(const string obj);
    /*
     * param :  obj = nom de la page dont on souhaite connaitre l'entier correspondant
     * retour : entier correspondant à la page passée en paramètre
     *
     * contrat : si la page passée en paramètre n'est pas encore dans la structure de donnée, elle sera ajoutée
     * automatiquement par la méthode. L'entier renvoyé est toujours l'entier correspondant.
     */

    string getString(const unsigned int index)const;
    /*
     * param :  index = entier dont on souhaite connaitre le nom de page correspondant
     * retour : nom de la page
     *
     * contrat : l'entier doit correspondre à une page stockée dans la structure.
     * renvoie la string vide si rien n'est trouvé
     */

    const unordered_map<string, unsigned int> & getMapBase()const;
    /*
     * retour : une référence constante sur l'attribut mapBase
     */

private:
    unordered_map<string,unsigned int> mapBase;//map sens direct : nom de page -> entier
    unordered_map<unsigned int,string> mapReavers;//map sens indirect : entier -> nom de page
    unsigned int compteur;//compte le nombre d'éléments afin d'attribuer un entier ad hoc aux nouveaux éléments
};

#endif //TP4_INDEXSTRING_H
