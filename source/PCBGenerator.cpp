#include "../headers/PCBGenerator.h"

PCBGenerator::PCBGenerator(std::string filename, DList<PCB> *lst, Clock *c) {
    clock = c;
    ready_queue = lst;
    _finished = false;
    last_arr = 0;
    arr_size = 25;
    arrivals = new bool[arr_size];
    pids = new bool[arr_size];
    for(int i = 0; i < arr_size; ++i) {
        arrivals[i] = false;
        pids[i] = false;
    }
    infile.open(filename);
    readnext();
}

PCBGenerator::~PCBGenerator(){
    delete arrivals;
    delete pids;
}

void PCBGenerator::generate(){
    if(!_finished && clock->gettime() >= nextPCB.arrival){
        ready_queue->add_end(nextPCB);
        readnext();
    }
}

void PCBGenerator::readnext(){
    bool error = false;
    if(!infile.eof()){
        std::stringstream ss;
        std::string line;
        float vals[5];

        while(!infile.fail()){
            getline(infile, line);
            if(line.length() <= 2) continue;
            break;
        }
        if(infile.eof()){
            _finished = true;
            return;
        }

        ss << line;
        int count = 0;
        while(count < 4 && ss >> vals[count]){
            count++;
        };
        while(vals[0] >= arr_size || vals[1] >= arr_size) doublearrays();

        //series of error checking and data validation, the if(error = true) just compacts code
        if(ss.fail() && !error) if(error = true) std::cout << "Missing data for process in file. Exiting Now." << std::endl;
        if(ss >> vals[5] && !error) if(error = true) std::cout << "Too many values for a process in file. Exiting now." << std::endl;
        if(vals[1] < 0 && !error) if(error = true) std::cout << "Arrival time can't be less than zero. Exiting now." << std::endl;
        if(vals[2] <= 0 && !error) if(error = true) std::cout << "CPU Burst time must be greater than 0. Exiting now." << std::endl;
        if(vals[1] < last_arr && !error) if(error = true) std::cout << "File needs to be sorted by arrival time. Exiting now." << std::endl;
        if(pids[int(vals[0])]) if(error = true) std::cout << "Can't have duplicate PIDs. Exiting now." << std::endl;
        if(arrivals[int(vals[1])]) if(error = true) std::cout << "Can't have duplicate arrival times. Exiting now." << std::endl;

        if(error) return(throw 1);

        //no error with data, continue
        arrivals[int(vals[1])] = true;
        pids[int(vals[0])] = true;
        nextPCB = PCB(vals[0], vals[1], vals[2], vals[3]);
    }
    else _finished = true;
}

bool PCBGenerator::finished(){
    return _finished;
}

void PCBGenerator::doublearrays(){
    arr_size *= 2;
    auto temp_arrs = new bool[arr_size];
    auto temp_pids = new bool[arr_size];
    for(int i = 0; i < arr_size; ++i) {
        if(i < arr_size/2){
            temp_arrs[i] = arrivals[i];
            temp_pids[i] = pids[i];
        }
        else {
            temp_arrs[i] = false;
            temp_pids[i] = false;
        }
    }
    delete arrivals;
    delete pids;
    arrivals = temp_arrs;
    pids = temp_pids;
}