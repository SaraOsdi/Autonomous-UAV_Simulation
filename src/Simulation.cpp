#include "Simulation.h"
#include <fstream>
#include <iostream>
#include <algorithm>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


bool Simulation::loadParams(const std::string& paramsFile) {
    std::ifstream file(paramsFile);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << paramsFile << std::endl;
        return false;
    }
    std::cout << "Successfully opened " << paramsFile << std::endl;

    double x0, y0, z0, speed, azimuth, radius;
    int numUAVs;
   

    file >> dt >> numUAVs >> radius >> x0 >> y0 >> z0 >> speed >> azimuth >> timeLimit;

    std::cout << "Simulation parameters loaded:\n"
        << "dt = " << dt << ", numUAVs = " << numUAVs << ", radius = " << radius << "\n"
        << "Initial position = (" << x0 << ", " << y0 << ", " << z0 << ")\n"
        << "Speed = " << speed << ", azimuth = " << azimuth  << ", timeLimit = " << timeLimit << std::endl;

    for (int i = 0; i < numUAVs; ++i) {
        uavs.emplace_back(x0, y0, z0, speed, azimuth * M_PI / 180, radius);
        uavs[i].setInitialTarget(x0, y0); // Set the initial target without calling setTarget
        std::cout << "UAV " << i << " initialized at position (" << x0 << ", " << y0 << ", " << z0 << ")\n";
    }



    return true;
}

bool Simulation::loadCommands(const std::string& commandsFile) {
    std::ifstream file(commandsFile);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << commandsFile << std::endl;
        return false;
    }

    std::cout << "Successfully opened " << commandsFile << std::endl;

    Command cmd;
    while (file >> cmd.time >> cmd.uavId >> cmd.x >> cmd.y) {
        if (cmd.uavId >= uavs.size()) {
            std::cerr << "Invalid UAV ID in command: " << cmd.uavId << std::endl;
            continue;
        }
        commands.push_back(cmd);
        std::cout << "Loaded command: time = " << cmd.time
            << ", UAV ID = " << cmd.uavId
            << ", target = (" << cmd.x << ", " << cmd.y << ")\n";
    }

    // Sort commands by time (ascending order)
    std::sort(commands.begin(), commands.end(), [](const Command& a, const Command& b) {
        return a.time < b.time;
        });

    return true;
}

void Simulation::runSimulation() {
    std::ofstream* outputFiles = new std::ofstream[uavs.size()];
    for (size_t i = 0; i < uavs.size(); ++i) {
        outputFiles[i].open("UAV" + std::to_string(i) + ".txt");
        if (!outputFiles[i].is_open()) {
            std::cerr << "Failed to create output file for UAV " << i << std::endl;
        }
        else {
            std::cout << "Created output file for UAV " << i << std::endl;
            // Write the header row to the file
            uavs[i].printStatus(0, outputFiles[i], true); // Pass `true` to write the header
        }
    }

    double time = 0;
    size_t commandIndex = 0;

    // Run the simulation loop
    while (time <= timeLimit) {
        // Execute commands exactly at their specified time
        while (commandIndex < commands.size() && commands[commandIndex].time <= time) {
            const Command& cmd = commands[commandIndex++];
            std::cout << "Executing command for UAV " << cmd.uavId << ": target = ("
                << cmd.x << ", " << cmd.y << ")\n";
            uavs[cmd.uavId].setTarget(cmd.x, cmd.y);
        }


        // Update and log the status of each UAV
        for (size_t i = 0; i < uavs.size(); ++i) {
            uavs[i].update(dt);
            uavs[i].printStatus(time, outputFiles[i], false); // Pass `false` to skip the header
        }
        time += dt;
    }

    // Close all output files
    for (size_t i = 0; i < uavs.size(); ++i) {
        outputFiles[i].close();
        std::cout << "Closed output file for UAV " << i << std::endl;
    }
    delete[] outputFiles;
}
