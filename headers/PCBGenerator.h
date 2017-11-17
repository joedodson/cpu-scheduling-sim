#ifndef LAB2_PCBGENERATOR_H
#define LAB2_PCBGENERATOR_H

#include <fstream>
#include <sstream>
#include <iostream>
#include "DList.h"
#include "Clock.h"
#include "PCB.h"

class PCBGenerator{
private:
    std::ifstream infile;
    DList<PCB> *ready_queue;
    Clock *clock;
    PCB nextPCB;
    bool _finished;
    int last_arr;
    bool *arrivals;
    bool *pids;
    int arr_size;
public:
    PCBGenerator(std::string filename, DList<PCB> *lst, Clock *c);
    ~PCBGenerator();

    //checks the current time to see if its time to add next process to ready queue
    void generate();

    //if there's still something in the file to read, set it as the next process to be added when its time
    void readnext();

    //simple routine to let others know if more processes are coming
    bool finished();
    void doublearrays();
};

#endif //LAB2_PCBGENERATOR_H
