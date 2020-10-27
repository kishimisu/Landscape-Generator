#include <iostream>
#include "time.h"
#include "others/styledessin.h"
#include "others/scene.h"
#include "geometry/gradient.h"
//#include "windows.h"

#include "math.h"
#include "others/util.h"
#include "others/settings.h"

void mainMenu();
void backgroundMenu(Settings& settings);
void spaceMenu(Settings& settings);
void skyMenu(Settings& settings);
void surfaceMenu(Settings& settings);
void reinitMenu(Settings& settings);
void saveMenu(Settings settings);
void loadMenu(Settings& settings);
void drawMenu(Settings settings);

void printMenuTitle(std::string title);
void printQuit();
void printChoice(int number, std::string text, double param[2]);
void printChoice(int number, std::string text, int param[2]);
void modifyParameter(double param[2]);
void modifyParameter(int param[2]);
void modifySeed(Settings& settings, int seed);

int main()
{
    srand(time(NULL));

    mainMenu();

    return 0;
}

void printMenuTitle(std::string title)
{
    std::cout << "----- " << title << " -----" << std::endl << std::endl;
}

void mainMenu()
{
    Settings settings;
    int s;

    reinitMenu(settings);

    do
    {
        printMenuTitle("Menu Principal");
        std::cout << "1) Modifier les etoiles\n2) Modifier les planetes\n3) Modifier les objets volants\n4) Modifier la surface\n\n5) Dessiner scene\n6) Reinitialiser graines\n\n7) Sauvegarder dessin\n8) Charger dessin\n\n0) Quitter\n\n";

        do
        {
            std::cout << "Selection: ";
            std::cin >> s;

            if(s == 1) backgroundMenu(settings);
            else if(s == 2) spaceMenu(settings);
            else if(s == 3) skyMenu(settings);
            else if(s == 4) surfaceMenu(settings);
            else if (s == 5) drawMenu(settings);
            else if (s == 6) reinitMenu(settings);
            else if(s == 7) saveMenu(settings);
            else if (s == 8) loadMenu(settings);
            else std::cout << "Selection invalide" << std::endl;
        }while(s < 0 || s > 8);

    }while(s != 0);
}

void printQuit()
{
    std::cout << std::endl << "0) Quitter" << std::endl << std::endl;
}
void printChoice(int number, std::string text, double param[2])
{
    std::cout << number << ") " << text << " (" << param[0] << "-" << param[1] << ")" << std::endl;
}

void printChoice(int number, std::string text, int param[2])
{
    std::cout << number << ") " << text << " (" << param[0] << "-" << param[1] << ")" << std::endl;
}

void modifyParameter(int param[2])
{
    std::cout << "Valeurs actuelles (min-max) : " << param[0] << "-" << param[1] << std::endl;
    std::cout << "Nouveau min: ";
    std::cin >> param[0];

    do
    {
        std::cout << "Nouveau max: ";
        std::cin >> param[1];

        if(param[1] < param[0]) std::cout << "La valeur max ne peut pas etre plus petite que la valeur min." << std::endl;
    }while(param[1] < param[0]);
}

void modifyParameter(double param[2])
{
    std::cout << "Valeurs actuelles (min-max) : " << param[0] << "-" << param[1] << std::endl;
    std::cout << "Nouveau min: ";
    std::cin >> param[0];

    do
    {
        std::cout << "Nouveau max: ";
        std::cin >> param[1];

        if(param[1] < param[0]) std::cout << "Erreur. La valeur max ne peut pas etre plus petite que la valeur min." << std::endl;
    }while(param[1] < param[0]);
}

void backgroundMenu(Settings& settings)
{
    int s;

    util::clearScreen();

    do
    {
        printMenuTitle("Modifier etoiles");
        printChoice(1, "Densite des etoiles", settings.star_density);
        printChoice(2, "Taille des etoiles", settings.star_size);
        printChoice(3, "Densite des supernovas", settings.supernovae_density);
        printChoice(4, "Densite des trous noirs", settings.blackhole_density);
        std::cout << std::endl << "5) Reinitialiser graine";
        printQuit();

        do
        {
            std::cout << "Selection: ";
            std::cin >> s;

            if(s == 1) modifyParameter(settings.star_density);
            else if(s == 2) modifyParameter(settings.star_size);
            else if(s == 3) modifyParameter(settings.supernovae_density);
            else if(s == 4) modifyParameter(settings.blackhole_density);
            else if (s == 5) modifySeed(settings, BackgroundSeed);
            else if(s != 0) std::cout << "Selection invalide." << std::endl;
        }while(s < 0 || s > 5);

     util::clearScreen();

    }while(s != 0);
}

void spaceMenu(Settings& settings)
{
    int s;
    util::clearScreen();

    do
    {
        printMenuTitle("Modifier espace");
        printChoice(1, "Densite des planetes", settings.planet_density);
        printChoice(2, "Taille des planetes", settings.planet_size);
        std::cout << std::endl << "3) Reinitialiser graine";
        printQuit();

        do
        {
            std::cout << "Selection: ";
            std::cin >> s;

            if(s == 1) modifyParameter(settings.planet_density);
            else if(s == 2) modifyParameter(settings.planet_size);
            else if(s == 3) modifySeed(settings, SpaceSeed);
            else if(s != 0) std::cout << "Selection invalide." << std::endl;
        }while(s < 0 || s > 3);

        util::clearScreen();

    }while(s != 0);
}

void skyMenu(Settings& settings)
{
    int s;
    util::clearScreen();

    do
    {
        printMenuTitle("Modifier objets volants");
        printChoice(1, "Densite des vaisseaux", settings.spaceship_density);
        printChoice(2, "Densite des satellites", settings.satellite_density);
        std::cout << std::endl << "3) Reinitialiser graine";
        printQuit();

        do
        {
            std::cout << "Selection: ";
            std::cin >> s;

            if(s == 1) modifyParameter(settings.spaceship_density);
            else if(s == 2) modifyParameter(settings.satellite_density);
            else if(s == 3) modifySeed(settings, SkySeed);
            else if(s != 0) std::cout << "Selection invalide." << std::endl;
        }while(s < 0 || s > 3);

        util::clearScreen();

    }while(s != 0);
}

void surfaceMenu(Settings& settings)
{
    int s;
    util::clearScreen();

    do
    {
        printMenuTitle("Modifier surface");
        printChoice(1, "Densite des arbres", settings.tree_density);
        printChoice(2, "Nombre de segments constituant un arbre", settings.tree_segments);
        std::cout << std::endl << "3) Reinitialiser graine";
        printQuit();

        do
        {
            std::cout << "Selection: ";
            std::cin >> s;

            if(s == 1) modifyParameter(settings.tree_density);
            else if(s == 2) modifyParameter(settings.tree_segments);
            else if(s == 3) modifySeed(settings, SurfaceSeed);
            else if(s != 0) std::cout << "Selection invalide." << std::endl;
        }while(s < 0 || s > 3);
        util::clearScreen();

    }while(s != 0);
}

void drawMenu(Settings settings)
{
    Svgfile out;
    Scene scene(settings);
    scene.draw(out);
    util::clearScreen();
}

void reinitMenu(Settings& settings)
{
    util::clearScreen();

    for(int i = 0; i < 4; i++)
    {
        int seed = util::random(INT_MIN, INT_MAX);
        std::mt19937 randGen{static_cast<std::mt19937>(seed)};
        settings.seeds[i] = randGen;
    }

    util::clearScreen();
}

void modifySeed(Settings& settings, int seedNumber)
{
    //util::clearScreen();
    int seed;

    do
    {
        std::cout << "Nouvelle graine: ";
        std::cin >> seed;

        if(seed == 42)
            std::cout << "Encore ? Un peu d'originalite M.Short..." << std::endl;
    }while(seed == 42);

    //int seed = util::random(INT_MIN, INT_MAX);
    std::mt19937 randGen{static_cast<std::mt19937>(seed)};
    settings.seeds[seedNumber] = randGen;

    util::clearScreen();
}

void saveMenu(Settings settings)
{
    std::string fileName;

    std::cout << "Nom de la scene : ";
    std::cin >> fileName;

    std::ofstream file(fileName + ".bin", std::ios::out | std::ios::binary);

    if(file)
    {
        file.write((char*)&settings, sizeof(settings));
        file.close();

        std::cout << "Le fichier a bien ete sauvegarde" << std::endl << std::endl;
    }
    else std::cout << "Erreur lors de l'ouverture du fichier." << std::endl << std::endl;
}

void loadMenu(Settings& settings)
{
    std::string fileName;

    std::cout << "Nom de la scene: ";
    std::cin >> fileName;

    std::ifstream file(fileName + ".bin", std::ios::in | std::ios::binary);

    if(file)
    {
        file.read((char*)&settings, sizeof(settings));
        file.close();

        std::cout << "Le fichier " << fileName << " a bien ete charge" << std::endl << std::endl;
    }
    else
    {
        std::cout << "Erreur lors de l'ouverture du fichier." << std::endl << std::endl;
    }
}
