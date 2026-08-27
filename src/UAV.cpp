#include "UAV.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <fstream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

UAV::UAV(double x, double y, double z, double speed, double azimuth, double radius)
    : x(x), y(y), z(z), speed(speed), azimuth(azimuth), radius(radius), isHovering(false), isIdle(true), hoverAngle(0.0) {

    targetX = x; 
    targetY = y;
    std::cout << "Initialized UAV at position (" << x << ", " << y << ", " << z
        << "), Speed: " << speed << ", Azimuth: " << azimuth << std::endl;
}

void UAV::setInitialTarget(double targetX, double targetY) {
    this->targetX = targetX;
    this->targetY = targetY;
    std::cout << "Initial target for UAV set to (" << targetX << ", " << targetY << ")\n";
}


void UAV::setTarget(double x, double y) {
    targetX = x;
    targetY = y;
    isIdle = false; // Mark UAV as active
    isHovering = false;
    std::cout << "Target set to (" << x << ", " << y << ")\n";
}


void UAV::update(double dt) {
    if (isIdle) {
        std::cout << "UAV is idle at position (" << x << ", " << y << "). Waiting for commands.\n";
        return;
    }

    double dx = targetX - x;
    double dy = targetY - y;
    double distance = std::sqrt(dx * dx + dy * dy);

    double desiredAzimuth = std::atan2(dy, dx); // Target direction
    double azimuthDifference = desiredAzimuth - azimuth;

    // Normalize azimuth difference to [-π, π]
    if (azimuthDifference > M_PI) azimuthDifference -= 2 * M_PI;
    if (azimuthDifference < -M_PI) azimuthDifference += 2 * M_PI;

    // If azimuth is not aligned with the target, turn first
    if (std::abs(azimuthDifference) > 0.01) {  // Significant azimuth adjustment needed
        double turnDirection = (azimuthDifference > 0) ? 1 : -1; // Clockwise or Counter-clockwise
        double maxTurnAngle = (speed / radius) * dt;  // Maximum turn angle in this step
        double turnAngle = turnDirection * std::min(maxTurnAngle, std::abs(azimuthDifference));

        // Update azimuth
        azimuth += turnAngle;

        // Calculate turning center
        double centerX = x - radius * std::sin(azimuth - turnAngle * turnDirection);
        double centerY = y + radius * std::cos(azimuth - turnAngle * turnDirection);

        // Update position along the arc
        x = centerX + radius * std::sin(azimuth);
        y = centerY - radius * std::cos(azimuth);

        std::cout << "Turning: Updated position (" << x << ", " << y
            << "), Azimuth: " << azimuth * 180 / M_PI << " degrees\n";
    }
    else {
        // Azimuth aligned, move straight toward the target
        double step = speed * dt;  // Movement step
        if (step > distance) {
            // Prevent overshooting the target
            x = targetX;
            y = targetY;
            isHovering = true;  // Enter hover mode once the target is reached
            hoverAngle = 0.0;   // Reset hover angle
            std::cout << "Movement clamped. UAV reached target.\n";
        }
        else {
            // Continue straight-line movement
            x += step * std::cos(azimuth);
            y += step * std::sin(azimuth);
            std::cout << "Straight-line movement: Updated position (" << x << ", " << y
                << "), Azimuth: " << azimuth * 180 / M_PI << " degrees\n";
        }
    }
}










void UAV::printStatus(double time, std::ofstream& outFile, bool writeHeader) {
    // Write header only once at the start of the file
    if (writeHeader) {
        outFile << "time,x,y,azimuth" << std::endl;
    }
    
    outFile << std::fixed << std::setprecision(2)
        << time << ","  
        << x << ","     
        << y << ","     
        << ((azimuth < 0) ? (360 + (azimuth * 180 / M_PI)) : (azimuth * 180 / M_PI))     // azimuth in degrees
        << std::endl;
}