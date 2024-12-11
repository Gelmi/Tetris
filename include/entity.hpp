#ifndef ENTITY_HPP
#define ENTITY_HPP

#include<SDL.h>

class Entity {
    protected:
        SDL_Rect dst;
        SDL_Color color;
        char path[30];
        SDL_Texture* texture;
        SDL_Renderer* renderer;
        unsigned int* tiles;
        int w, h;
        
        int atPos(int x, int y);

    public:
        Entity(SDL_Renderer* renderer, char path[30], int w, int h);
        ~Entity();
        void Draw();
        void setPosition(int x, int y);
        void setSize(int w, int h);
};

#endif  
