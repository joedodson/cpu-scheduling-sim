#include "../headers/Clock.h"

void Clock::reset(){
    time = 0;
}

float Clock::gettime(){
    return time;
}

void Clock::step(){
    time += .5;
}
