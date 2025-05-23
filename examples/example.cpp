#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

int main(int , char**) {
    //初始化SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    //创建窗口
    SDL_Window *win = SDL_CreateWindow("Hello World", 100, 100, 800, 600, SDL_WINDOW_SHOWN);

    //创建渲染器
    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

    //SDL_Image初始化;
    if(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG ) != (IMG_INIT_PNG | IMG_INIT_JPG)) {
        std::cerr << "SDL_Image_Init Error: " << IMG_GetError() << std::endl;
        return 1;
    }
    
    //加载图片
    SDL_Texture *texture = IMG_LoadTexture(renderer,"../../assets/image/bg.png");
    if (texture == NULL) {
        std::cerr << "IMG_LoadTexture Error: " << IMG_GetError() << std::endl;
        return 1;
    }

    //SDL_Mixer初始化
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
        std::cerr << "Mix_OpenAudio Error: " << Mix_GetError() << std::endl;
        return 1;
    }

    //加载音频
    Mix_Chunk *sound = Mix_LoadWAV("../../assets/music/03_Racing_Through_Asteroids_Loop.ogg");
    if (sound == NULL) {
        std::cerr << "Mix_LoadWAV Error: " << Mix_GetError() << std::endl;
        return 1;
    }

    //加载TTF
    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        return 1;
    }

    //创建TTF字体
    TTF_Font *font = TTF_OpenFont("../../assets/font/VonwaonBitmap-12px.ttf", 24);
    if (font == NULL) {
        std::cerr << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        return 1;
    }

    //创建TTF文本
    SDL_Color color = {255, 0, 0, 255};
    SDL_Surface *surface = TTF_RenderUTF8_Solid(font, "Hello World 中文", color);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, surface);

    while(true) {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                break;
            }

        }
        //清屏
        SDL_RenderClear(renderer);

        //绘制红色矩形
        SDL_Rect rect = {100, 100, 200, 200};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        //绘制图片
        SDL_Rect dstrect = {200, 200, 300, 200};
        SDL_RenderCopy(renderer, texture, NULL, &dstrect);

        //播放音频
        Mix_PlayChannel(-1, sound, 0);

        //绘制TTF文本
        SDL_Rect textRect = {300, 300, surface->w, surface->h};
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        //更新屏幕
        SDL_RenderPresent(renderer);

    }
    //释放资源
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    TTF_Quit();
    Mix_FreeChunk(sound);
    Mix_CloseAudio();
    SDL_DestroyTexture(texture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);  
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}