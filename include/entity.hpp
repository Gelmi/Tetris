#ifndef ENTITY_HPP
#define ENTITY_HPP

#include<SDL.h>

class Entity {
    private:
        SDL_Rect dst;
        SDL_Surface* image;
        SDL_Texture* texture;
        SDL_Renderer* renderer;

    public:
        Entity(SDL_Renderer* renderer, char path[30]);
        ~Entity();
        void Draw();
        void setPosition(int x, int y);
        void setSize(int w, int h);
};

#endif  
