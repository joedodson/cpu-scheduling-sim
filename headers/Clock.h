#ifndef LAB2_CLOCK_H
#define LAB2_CLOCK_H

//class that is shared with most other objects that need to be synced to a clock to manage timers and stat collection
class Clock{
private:
    float time;
public:
    Clock(){time=0;}
    void reset();
    float gettime();
    void step();
};

#endif //LAB2_CLOCK_H
