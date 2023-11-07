// This file contains functions that generate random integers and floats within a given range
#ifndef RANDOM_FUNCS_H
#define RANDOM_FUNCS_H

#include <random>

std::random_device rd;
std::mt19937 gen(rd());

int random_int(int min, int max){
    std::uniform_int_distribution<int> dist(min, max);
    float generated = dist(gen);
    return generated;
}

float random_float(float min, float max){
    std::uniform_real_distribution<float> dist(min, max);
    float generated = dist(gen);
    return generated;
}

#endif
