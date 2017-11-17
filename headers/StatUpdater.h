#ifndef LAB2_STATUPDATER_H
#define LAB2_STATUPDATER_H

#include "DList.h"
#include "PCB.h"
#include "Clock.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using std::cout;

//class that handles updating waiting times, response times, etc.
//and prints them in a specific format to a provided file name
class StatUpdater{
private:
    DList<PCB> *ready_queue;
    DList<PCB> *finished_queue;
    Clock *clock;
    int algorithm, num_tasks, timeq;
    float last_update;
    std::string filename;
public:
    StatUpdater(DList<PCB> *rq, DList<PCB> *fq, Clock *cl, int alg, std::string fn, int tq);
    void execute();
    void print();
};
#endif //LAB2_STATUPDATER_H
