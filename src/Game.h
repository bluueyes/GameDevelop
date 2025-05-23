#ifndef GAME_H
#define GAME_H
#include "Scene.h"

class Game
{
public:
    Game();
    ~Game();
    void init();
    void clean();
    void run();
    void changeScene(Scene* scene);
private:
    bool isRunning = true;
    Scene* currentScene = nullptr;
};


#endif // GAME_H


