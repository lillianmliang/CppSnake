#ifndef FOOD_H
#define FOOD_H

#include "SDL.h"

enum FoodType
{
    Normal,
    Speedy,
    Slow,
    Poison,
    Filling
};

class Food : public SDL_Point {
    public:
    Food(FoodType type, int xval, int yval);
    FoodType _type;
    double _speedDiff; // will be added to snake's current speed when Food is consumed
    int _points; // will be added to score when Food is consumed 
    int _Rvalue; // R value
    int _Gvalue; // G value
    int _Bvalue; // B value
    private:
};

#endif