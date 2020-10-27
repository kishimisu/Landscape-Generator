# The project

In 2018 I made a project for my engineering school that was a landscape generator. 
The goal of this project was to become more familiar with C++, object-oriented programming and random number generators.

I've chosen to create a space-themed generator with a lot of properties you can tweak in order to change the generated landscape.

The program generates a `.svg` file that can be opened in a browser to see the result.
This extension stands for _Scalable Vector Graphics_ and means that it can be zoomed in and out without any loss of detail, as opposite to an image file.

# Run instructions

You will need a c++ compiler and `make`.


From a terminal, run `make` from the root of the project, then execute the application with `./landscape-generator`.

If you're on Windows you can open the project with an IDE containing an integrated C++ compiler like `Command Blocks`.

To generate a landscape, run `5) Draw Scene` and open in a web browser the generated `output.svg` image.

# The generation parameters

The scene is subdivided in 4 layers :
- **The planet's surface** contains trees and mountains
- **The atmosphere** is populated by spaceships and satellites
- **The _foreground_ space** contains all the different types of planets
- **The _background_ space** contains all the stars, blackholes and what I call supernovaes (that are juste brighter and bigger stars)

## Layers properties

For each layer, you can modify a set of parameters specific to the elements present on the layer.

For each parameter, you can set a minimum and a maximum value that will be used during the random generation.

### Surface

- **Trees density**
- **Trees segments count** 

### Flying objects

- **Spaceships density** 
- **Satellites density** 

### Planets 

- **Planets density** 
- **Planets size** 

### Stars 

- **Stars density and size** 
- **Supernovaes density** 
- **Blackholes density** 

## Random seeds and number generator

For each layer, you also have an option to reset the seed used for the number generator for this specific layer, thus you can regenerate a layer independently from the other ones.

You can also enter a manual seed (represented by a number) or change the whole's scene seed and regenerate the 4 layers to have a completely new landscape

## UML Diagram

![UML Diagram]("UML Diagram.png")