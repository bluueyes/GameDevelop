#include <iostream>
#include <SDL.h>

int main(int , char**) {
    std::cout << "Hello, World!" << std::endl;
    //初始化SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    //创建窗口
    SDL_Window *win = SDL_CreateWindow("Hello World", 100, 100, 800, 600, SDL_WINDOW_SHOWN);

    //创建渲染器
    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);


    while(true) {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                break;
            }

            //清屏
            SDL_RenderClear(renderer);
            //绘制红色矩形
            SDL_Rect rect = {100, 100, 600, 400};
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderFillRect(renderer, &rect);
        }

        //清屏
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //绘制红色矩形
        SDL_Rect rect = {100, 100, 600, 400};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);

        //更新屏幕
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);  
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}