#include "SDL.h"


struct Player
{
    SDL_Texture* texture;
    SDL_FPoint position = {0, 0};

    int width = 0;
    int height = 0;

};