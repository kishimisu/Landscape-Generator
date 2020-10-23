#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include <string>
#include <sstream>
#include "../geometry/coords.h"
#include "svgfile.h"
#include <random>

namespace util
{

/// L'appel de cette fonction redirige les
/// donn�es du fichier dont le nom est pass�
/// en param�tre vers std::cin
/// On "simule" les frappes clavier ce qui
/// permet de tester sans avoir � retaper
/// � chaque fois les m�me donn�es
/// temporisation : nombre de milliseconde entre chaque frappe clavier
/// color : colorisation (WINDOWS seulement https://ss64.com/nt/color.html
///                         pr�fixer par 0x, exemple 0x1a vert sur fond bleu)
void startAutoCin(std::string fileName, size_t temporisation=0, short color=0);

/// Cette fonction doit �tre appel�e pour
/// terminer la saisie automatique et retrouver
/// un comportement normal (saisir au clavier)
void stopAutoCin();

/// Vide tampon clavier
void videCin();

/// Cette fonction retourne un entier al�atoire dans [min...max]

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef INT_MIN
#define INT_MIN -2147483647-1
#endif

#ifndef INT_MAX
#define INT_MAX 2147483647
#endif

int random(int min, int max);
double random(double min, double max);
int max(int a, int b, int c);
int min(int a, int b, int c);
double degToRad(double deg);
double radToDeg(double rad);
std::string doubleToString(double d);
double distanceBetween(Coords c1, Coords c2);
Color hexToColor(std::string hex);
double random(double min, double max, std::mt19937& seed);
int random(int min, int max, std::mt19937& seed);
int randomBetween(int param[2], std::mt19937& seed);
double randomBetween(double param[2], std::mt19937& seed);

/// Le code qui suit est sp�cifique aux plateformes Windows
/// et ne concerne ni macOS ni les Linux
#ifdef _WIN32
void accentsPourWindows();
#endif // _WIN32

}


#endif // UTIL_H_INCLUDED
