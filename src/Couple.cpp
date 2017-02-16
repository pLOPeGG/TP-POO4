//
// Created by doudou on 18/01/17.
//

#include "Couple.h"


unsigned int Couple::getPage()const
{
    return page;

}
unsigned int Couple::getHit()const
{
    return hit;

}


Couple::Couple(unsigned int p, unsigned int h)
    :page (p), hit (h)
{
#ifdef MAP
    cout<<"Appel du constructeur de <Couple>"<<endl;
#endif
}

Couple::~Couple()
{
#ifdef MAP
    cout<<"Appel du destructeur de <Couple>"<<endl;
#endif
}
