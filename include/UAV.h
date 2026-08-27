#ifndef UAV_H
#define UAV_H

#include <iostream>
#include <fstream>

class UAV {
public:
    UAV(double x, double y, double z, double speed, double azimuth, double radius);

    void setInitialTarget(double targetX, double targetY);
    void setTarget(double x, double y);
    void update(double dt);
    void printStatus(double time, std::ofstream& outFile, bool writeHeader);

private:
    double x, y, z;         // Current position
    double speed;           // Speed of the UAV
    double azimuth;         // Current direction in radians
    double radius;          // Hovering radius
    double targetX, targetY;// Target position
    bool isHovering;        // Hovering state
    bool isIdle;            // Indicates whether the UAV is idle (waiting for first command)
    double hoverAngle;
};

#endif
