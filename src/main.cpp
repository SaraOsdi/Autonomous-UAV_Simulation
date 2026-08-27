#include <iostream>
#include "Simulation.h"

int main() {
    Simulation sim;

 
    if (!sim.loadParams("D:/AutonomousUAVSimulation/x64/Debug/SimParams.ini")) {
        std::cerr << "Error: Could not load parameters from SimParams.ini" << std::endl;
        return 1;
    }

    if (!sim.loadCommands("D:/AutonomousUAVSimulation/x64/Debug/SimCmds.txt")) {
        std::cerr << "Error: Could not load commands from SimCmds.txt" << std::endl;
        return 1;
    }

    sim.runSimulation();
    return 0;
}
