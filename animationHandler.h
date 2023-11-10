#ifndef ANIMATION_HANDLER_H
#define ANIMATION_HANDLER_H

#include <vector>

#include "renderer.h"
#include "house.h"
#include "timer.h"

const int MIN_RANDOM_HOUSES = 3;
const int MAX_RANDOM_HOUSES = 7;

/*
 * Class handling the input, animation cycle and calls to the renderer.
 * Params:
 *     houses: house data to be drawn
 *     house_highest: highest generated house
 *     timer: timer object handling animation time
 *     renderer: for drawing the houses
 *
 *  Methods:
        AnimationHandler(float x, float y, float z, float fov): the constructor takes a position in space looking towards the origin as well as the field of view angle. 
 *      handle_input_kb: handles user keyboard input
 *      generate_houses: generates houses to be drawn
 *      calculate_clip_height: computes current clip height according to animation time
 *      loop: animation loop
 *
 */
class AnimationHandler{

    std::vector<House> houses;
    float house_highest = 0.0;
    Timer timer;
    Renderer renderer;

    // process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
    void handle_input_kb();
    
    public:
        // the constructor takes a position in space looking towards the origin as well as the field of view angle. 
        AnimationHandler(float x, float y, float z, float fov);

        // generates house data
        void generate_houses();
        // calculates the clipping plane height according to the current time and highest building
        void calculate_clip_height();

        // animation loop
        void loop();

};

#endif
