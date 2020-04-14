#ifndef FOOD_H
#define FOOD_H

#include <random>
#include "SDL.h"

enum FoodType
{
    Normal,
    Speedy,
    Slow,
    Poison,
    Filling
};

// TODO: define class Food inheriting from SDL_Point
class Food : public SDL_Point {
    public:
    Food(FoodType type);
    FoodType _type;
    double _speedDiff; // will be added to snake's current speed when Food is consumed
    int _points; // will be added to score when Food is consumed 
    int _Rvalue; // R value
    int _Gvalue; // G value
    int _Bvalue; // B value
    private:
};

Food::Food(FoodType type) : _type(type) {
    switch (type)
    {
        case Normal:
        _speedDiff = 0.02;
        _points = 1;
        _Rvalue = 0xFF; // yellow
        _Gvalue = 0xFF;
        _Bvalue = 0x00;

        break;
        case Speedy:
        _speedDiff = 0.04;
        _points = 1;
        _Rvalue = 0xFF; // orange
        _Gvalue = 0xA5;
        _Bvalue = 0x00;

        break;
        case Slow:
        _speedDiff = -0.02;
        _points = 1;
        _Rvalue = 0xA0; // purple
        _Gvalue = 0x20;
        _Bvalue = 0xF0;

        break;
        case Poison:
        _speedDiff = 0.02;
        _points = 0;
        _Rvalue = 0xFF; // red
        _Gvalue = 0x00;
        _Bvalue = 0x00;
        
        break;
        case Filling:
        _speedDiff = 0.02;
        _points = 5;
        _Rvalue = 0x00; // green
        _Gvalue = 0xFF;
        _Bvalue = 0x00;

        break;
        case default:
        _speedDiff = 0.02;
        _points = 1;
        _Rvalue = 0xFF; // yellow
        _Gvalue = 0xFF;
        _Bvalue = 0x00;

    }
}

#endif