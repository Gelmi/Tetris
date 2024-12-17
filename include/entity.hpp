#ifndef ENTITY_HPP
#define ENTITY_HPP

#include<SDL.h>

class Entity {
    protected:
        SDL_Rect rect;
        int x, y, h, w;
        SDL_Color color;
        unsigned int* tiles;
        
    public:
        Entity(int x, int y, int w, int h);
        Entity(int w, int h) : Entity(0, 0, w, h) {};
        SDL_Rect * getRect();
        unsigned int* getTiles();
        int getX();
        int getY();
        int atPos(int x, int y);
};

#endif  
