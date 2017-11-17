# Process Scheduling Simulator
A software implementation of how an OS might schedule processes on a CPU given a file of "processes" designed for a class project. The simulator is programmed to simulate any one of four scheduling algorithms (FCFS, SRTF, RR, and PP), and output the results to a specified file.

## Getting Started

The program will obviously need to be compiled and ran using some sort 
When running the program, execute it with the arguments in the following general form:
```
./a.out inputFileName outputFileName AlgorithmNumber timeQuantum(if applicable)
```

An example on Linux using the provided input/output files:
```
./a.out sample_input.txt sample_outputSRTF.txt 1
```
or
```
./a.out sample_input.txt sample_outputRR4.txt 2 4
```

#### Input/Output File
Each line in the input file must be of the form:
```
ProcessID ArrivalTime BurstTime Priority
```
Any valid filename will suffice for outputFileName. Numbers in output are considered to be ms and context switches account for 0.5ms

An example input and output file is provided

#### Algorithm Numbers
0 - FCFS, First Come First Serve
1 - SRTF, Shortest Remaining Time First (preemptive)
2 - RR, Round Robin (must enter time quantum to execute)
3 - PP, Preemptive Priority (uses provided priorities in input file)

#### Time Quantum
How long each process runs on the CPU (minimum = .5)

### Prerequisites

Program can be compile and ran with specified arguments using most IDEs that support C++. Implementation will depend on platform.

## Built With

* [CLion](https://www.jetbrains.com/clion/) - IDE Used

## Authors

* **Joseph Dodson** - *Sole contributor* - [joedodson](https://github.com/joedodson)

