#ifndef STYLEDESSIN_H_INCLUDED
#define STYLEDESSIN_H_INCLUDED

#include "../geometry/couleur.h"

struct StyleDessin
{
    /// Aretes
    bool dessinerAretes = true;
    double epaisseurArete = 2;
    Color colorArete = {0, 0, 0};

    /// Sommets
    bool dessinerSommets = true;
    double rayonSommet = 5;
    Color colorSommet = {0, 0, 0};

    /// Sommets sélectionnés
    double rayonSommetSelect = 10;
    double epaisseurSommetSelect = 3;
    Color colorSommetSelect = {0, 0, 0};
};


#endif // STYLEDESSIN_H_INCLUDED
