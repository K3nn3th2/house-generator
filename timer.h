#ifndef TIMER_H
#define TIMER_H

#include <GLFW/glfw3.h>

/*
 *  The Timer class provides functions to measure the time between frames as well as the total passed time of animation
 */ 
class Timer{
    
    public:
        // startin frame
        float frame_start;

        // current frame
        float frame_current;

        // last frame
        float frame_last;

        // time between last frame and current
        float time_delta;

        // time between last frame and start of animation
        float time_total;

        // default constructor
        Timer(){
        }

        // mark start of timer
        void start(){
            frame_start = static_cast<float>(glfwGetTime());
        }
        // measure time between frames as well as total time passed
        void measure();
};

#endif
