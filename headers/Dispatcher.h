#ifndef LAB2_DISPATCHER_H
#define LAB2_DISPATCHER_H

#include "CPU.h"
#include "Schedulers.h"
#include "DList.h"
#include "Clock.h"
#include "StatUpdater.h"

//class that switches out process for the CPU when scheduler tells it to
class Dispatcher{
private:
    CPU *cpu;
    Scheduler *scheduler;
    DList<PCB> *ready_queue;
    Clock *clock;
    bool _interrupt;
public:
    Dispatcher();
    Dispatcher(CPU *cp, Scheduler *sch, DList<PCB> *rq, Clock *cl);
    PCB* switchcontext(int index);
    void execute();
    void interrupt();
};

#endif //LAB2_DISPATCHER_H
