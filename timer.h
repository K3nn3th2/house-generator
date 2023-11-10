#ifndef TIMER_H
#define TIMER_H

#include <GLFW/glfw3.h>


class Timer{
    
    public:
        float frame_start;
        float frame_current;
        float frame_last;
        float time_delta;
        float time_total;

        Timer(){
        }
        void start(){
            frame_start = static_cast<float>(glfwGetTime());
        }
        void measure();
};

#endif
