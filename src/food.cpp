#include "food.h"
#include "SDL.h"


Food::Food(FoodType type, int xval, int yval) : _type(type) {
    x = xval;
    y = yval;
    switch (type)
    {
        case Normal:
        _speedDiff = 0.01;
        _points = 1;
        _Rvalue = 0xFF; // yellow
        _Gvalue = 0xFF;
        _Bvalue = 0x00;
        break;
        case Speedy:
        _speedDiff = 0.02;
        _points = 1;
        _Rvalue = 0xFF; // orange
        _Gvalue = 0xA5;
        _Bvalue = 0x00;
        break;
        case Slow:
        _speedDiff = -0.01;
        _points = 1;
        _Rvalue = 0xA0; // purple
        _Gvalue = 0x20;
        _Bvalue = 0xF0;
        break;
        case Poison:
        _speedDiff = 0.01;
        _points = 0;
        _Rvalue = 0xFF; // red
        _Gvalue = 0x00;
        _Bvalue = 0x00;
        break;
        case Filling:
        _speedDiff = 0.01;
        _points = 5;
        _Rvalue = 0x00; // green
        _Gvalue = 0xFF;
        _Bvalue = 0x00;
        break;
        default:
        _speedDiff = 0.02;
        _points = 1;
        _Rvalue = 0xFF; // yellow
        _Gvalue = 0xFF;
        _Bvalue = 0x00;
    }
}
