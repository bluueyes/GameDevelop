#include "Game.h"

Game::Game()
{
}

Game::~Game(){

}

void Game::init(){

}

void Game::clean(){

}

void Game::run(){
    while(isRunning){
        SDL_Event event;
        currentScene->handleEvents(&event);
        currentScene->update();
        currentScene->render();
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