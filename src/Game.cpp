#include "Game.h"
#include "SceneMain.h"
#include "SDL.h"
#include "SDL_image.h"

Game::Game()
{
}

Game::~Game(){
    clean();
}

void Game::init(){

    //SDL初始化
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init Error: %s", SDL_GetError());
        return;
    }

    //创建窗口
    window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    if(window == nullptr){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateWindow Error: %s", SDL_GetError());
        isRunning = false;
    }
    //创建渲染器
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateRenderer Error: %s", SDL_GetError());
        isRunning = false;
    }
    
    //初始化图片加载器
    if(IMG_Init(IMG_INIT_PNG) == 0){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IMG_Init Error: %s", IMG_GetError());
        isRunning = false;
    }

    currentScene = new SceneMain();

    currentScene->init();


}

void Game::clean(){
    if(currentScene != nullptr){
        currentScene->clean();
        delete currentScene;
    }
    //销毁纹理
    IMG_Quit();
    //销毁渲染器
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    isRunning = false;
}

void Game::run(){
    SDL_Event event;
    while(isRunning){

        //处理事件
        handleEvents(&event);
        //更新
        update();
        //渲染
        render();

    }
}

void Game::changeScene(Scene* scene){
    if(currentScene != nullptr){
        currentScene->clean();
        delete currentScene;
    }
    currentScene = scene;
    currentScene->init();
}

void Game::handleEvents(SDL_Event* event){

    while(SDL_PollEvent(event)){
        if(event->type == SDL_QUIT){

            isRunning = false;
        }    
        currentScene->handleEvents(event);
    }

}

void Game::update(){

    //更新场景
    currentScene->update();
}

void Game::render(){
    //清空渲染器
    SDL_RenderClear(renderer);
        
    //渲染当前场景
    currentScene->render();

    //显示更新
    SDL_RenderPresent(renderer);
}