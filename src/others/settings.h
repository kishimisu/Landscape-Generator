#ifndef SETTINGS_H
#define SETTINGS_H

#include <random>

enum Seeds
{
    BackgroundSeed, SpaceSeed, SkySeed, SurfaceSeed
};

struct Settings
{
    std::mt19937 seeds[4];

    int star_density[2] = {2000, 4000};
    double star_size[2] = {0.01, 0.5};
    int blackhole_density[2] = {0, 3};
    int supernovae_density[2] = {20, 60};

    int planet_density[2] = {5, 25};
    double planet_size[2] = {20, 80};

    int spaceship_density[2] = {1, 10};
    int satellite_density[2] = {2, 7};

    int tree_density[2] = {350, 450};
    int tree_segments[2] = {3, 5};
};

#endif // SETTINGS_H
