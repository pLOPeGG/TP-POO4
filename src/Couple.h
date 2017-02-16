//
// Created by doudou on 18/01/17.
//
/**
 * Classe Couple : réunit deux unsigned int et offre un operateur de comparaison pour
 * trier en fonction du second élément
 */
#ifndef TP4_COUPLE_H
#define TP4_COUPLE_H


class Couple {
public:

    Couple(unsigned int p, unsigned int h);
    /*
     * Constructeur, deux unsigned in en paramètre
     */

    virtual ~Couple();
    /*
     * Destructeur
     */

    unsigned int getPage()const;
    /*
     * retour : attribut page
     */

    unsigned int getHit()const;
    /*
     * retour : attribut hit
     */

    friend bool operator<(const Couple & c1, const Couple & c2);
    /*
     * surcharge de l'opérateur
     * fonction amie
     */



private:
    unsigned int page;//unsigned int référence vers un nom de page
    unsigned int hit;//nombre de hit sur la page
};
/**
 * Opérateur < afin d'utiliser le tri automatique d'un set.
 * Ici, les objets d'un set seront triés par ordre décroissant de hit
 */
inline bool operator<(const Couple & c1, const Couple & c2)
{

    if(c1.hit!=c2.hit)
    {
        return c1.hit>c2.hit;
    }
    else
    {
        return c1.page<c2.page;
    }

}
#endif //TP4_COUPLE_H
