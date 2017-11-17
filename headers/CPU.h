#ifndef LAB2_CPU_H
#define LAB2_CPU_H

#include "PCB.h"
#include "DList.h"
#include "Clock.h"
#include "Schedulers.h"

//forward declaration so that CPU can declare dispatcher as friend
class Dispatcher;

class CPU{
private:
    PCB *pcb;
    bool idle;
    Clock *clock;
    DList<PCB> *finished_queue; //for terminated process, used later by statupdater
    friend Dispatcher; //allows dispatcher to switch out processes
public:
    CPU(DList<PCB> *fq, Clock *cl);
    PCB* getpcb();
    bool isidle();
    void execute();
    void terminate();
};

#endif