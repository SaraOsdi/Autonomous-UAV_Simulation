#pragma once
#ifndef COMMAND_H
#define COMMAND_H

struct Command {
    double time;   
    int uavId;     
    double x, y;   

    Command(double t = 0, int id = 0, double tx = 0, double ty = 0)
        : time(t), uavId(id), x(tx), y(ty) {}
};

#endif 
