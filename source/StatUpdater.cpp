#include "../headers/StatUpdater.h"

StatUpdater::StatUpdater(DList<PCB> *rq, DList<PCB> *fq, Clock *cl, int alg, std::string fn, int tq){
ready_queue = rq;
finished_queue = fq;
clock = cl;
algorithm = alg;
timeq = tq;
filename = fn;
last_update = 0;
}

//main function that gets called every clock cycle to update times of pcbs
void StatUpdater::execute() {
    //increment handles situations where a context switch happens in middle of cycle
    //allows updater to increment times
    float increment = clock->gettime() - last_update;
    last_update = clock->gettime();
    for(int index = 0; index < ready_queue->size(); ++index){
        //get pointer to each pcb in queue and update their waiting times
        PCB* temp = ready_queue->getindex(index);
        temp->wait_time += increment;
    }
}


//straightforward print function that prints to file using iomanip and column for a table format
//uses finished queue to tally up final stats
void StatUpdater::print() {
    num_tasks = finished_queue->size();
    std::string alg;
    int colwidth = 11;
    float tot_burst, tot_turn, tot_wait, tot_resp;
    int contexts;
    tot_burst = tot_turn = tot_wait = tot_resp = contexts = 0;

    std::ofstream outfile(filename);


    switch(algorithm){
        case 0:
            alg = "FCFS";
            break;
        case 1:
            alg = "SRTF";
            break;
        case 2:
            alg = "Round Robin";
            break;
        case 3:
            alg = "Preemptive Priority";
            break;
    }

    outfile << "*******************************************************************" << std::endl;
    outfile << "Scheduling Algorithm: " << alg << std::endl;
    if(timeq != -1) outfile << "(No. Of Tasks = " << finished_queue->size() << " Quantum = " << timeq << ")" << std::endl;
    outfile << "*******************************************************************" << std::endl;

    outfile << "----------------------------------------------------------------------------------------------------------------------" << std::endl;
    outfile << "| " << std::left << std::setw(colwidth) << "PID" << "| " << std::left << std::setw(colwidth) << "Arrival"
            << "| " << std::left << std::setw(colwidth) << "CPU-Burst" << "| " << std::left << std::setw(colwidth) << "Priority"
            << "| " << std::left << std::setw(colwidth) << "Finish" << "| " << std::left << std::setw(colwidth) << "Waiting"
            << "| " << std::left << std::setw(colwidth) << "Turnaround" << "| " << std::left << std::setw(colwidth) << "Response"
            << "| " << std::left << std::setw(colwidth) << "C. Switches" << "| " << std::endl
            << "----------------------------------------------------------------------------------------------------------------------" << std::endl;

    for(int id = 1; id < num_tasks+1; ++id){
        for(int index = 0; index < finished_queue->size(); ++index){
            if(finished_queue->getindex(index)->pid == id){
                PCB temp = finished_queue->removeindex(index);
                float turnaround = temp.finish_time - temp.arrival;
                tot_burst += temp.burst;
                tot_turn += turnaround;
                tot_wait += temp.wait_time;
                tot_resp += temp.resp_time;
                contexts += temp.num_context;

                outfile << "| " << std::left << std::setw(colwidth) << temp.pid << "| " << std::left << std::setw(colwidth)
                        << temp.arrival << "| " << std::left << std::setw(colwidth) << temp.burst << "| " << std::left
                        << std::setw(colwidth) << temp.priority << "| " << std::left << std::setw(colwidth) << temp.finish_time
                        << "| " << std::left << std::setw(colwidth) << temp.wait_time << "| " << std::left << std::setw(colwidth)
                        << turnaround << "| " << std::left << std::setw(colwidth) << temp.resp_time << "| " << std::left << std::setw(colwidth)
                        << temp.num_context << "|" << std::endl;
                outfile << "----------------------------------------------------------------------------------------------------------------------" << std::endl;
            }
        }
    }
    outfile << std::endl;
    outfile << "Average CPU Burst Time: " << tot_burst/num_tasks << " ms\t\tAverage Waiting Time: " << tot_wait/num_tasks << " ms" << std::endl
            << "Average Turnaround Time: " << tot_turn/num_tasks << " ms\t\tAverage Response Time: " << tot_resp/num_tasks << " ms" << std::endl
            << "Total No. of Context Switching Performed: " << contexts << std::endl;
}