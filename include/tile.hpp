#ifndef TILE_HPP
#define TILE_HPP

#include<SDL.h>
#include<color.hpp>

class Tile {
    private:
        SDL_Rect rect;
        Color color;

    public:
        Tile(int x, int y, int w, int h, Color color);
        SDL_Rect getRect();
        Color getColor();
};

#endif
