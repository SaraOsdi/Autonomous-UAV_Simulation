#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include <vector>
#include "UAV.h"
#include "Command.h"

class Simulation {
public:
    bool loadParams(const std::string& paramsFile);
    bool loadCommands(const std::string& commandsFile);
    void runSimulation();

private:
    double dt;
    double timeLimit;
    std::vector<UAV> uavs;
    std::vector<Command> commands;
};

#endif
