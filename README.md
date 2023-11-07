## House Generator

## Description


This Program displays a random number of houses in OpenGL.
These houses appear to "grow" out of the ground and disappear again, repeatedly.
The animation cycle does the following:

1. takes one second to let all of the houses appear completely (the highest one will take one second to be fully displayed),
2. displays them for three seconds, and 
3. lets them disappear again within one second.

In between the cycles, all of the houses are assigned new random dimensional attribute values which are displayed in the next cycle.

Developed using 
- G++ 13.2.1
- Glew 2.2.0,
- GLFW 3.3.8
- OpenGL 3.3
- glm 0.9.9.8

## Visuals
![Houses rising](https://i.ibb.co/PjW1dTp/2023-11-07-084501-1920x1080-scrot.png)
![Houses fully displayed](https://i.ibb.co/Kbwn2d4/2023-11-07-084502-1920x1080-scrot.png)

## Installation
- Download the files into a directory.

- `cd` into the directory in a terminal and run `make`

## Usage
simply run the compiled program.
WASD keys can be used for movement.

Esc quits the program.

## Authors and acknowledgment
Kenneth Allan

## License
Free
