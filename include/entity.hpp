#ifndef ENTITY_HPP
#define ENTITY_HPP

#include<SDL.h>

class Entity {
    private:
        SDL_Rect dst;
        char path[30];
        SDL_Texture* texture;
        SDL_Renderer* renderer;
        unsigned int* tiles;
        unsigned int w, h;
        
        int atPos(unsigned int x, unsigned int y);

    public:
        Entity(SDL_Renderer* renderer, char path[30], unsigned int w, unsigned int h);
        ~Entity();
        void Draw();
        void setPosition(int x, int y);
        void setSize(int w, int h);
};

#endif  
