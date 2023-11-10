#include "timer.h"

void Timer::measure(){
    frame_current = static_cast<float>(glfwGetTime());
    time_delta = frame_current - frame_last;
    time_total = frame_current - frame_start;
    frame_last = frame_current;
}
