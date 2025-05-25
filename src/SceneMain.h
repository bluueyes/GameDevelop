#ifndef SCENEMAIN_H
#define SCENEMAIN_H

#include "Scene.h"
#include "Object.h"

class Game;

class SceneMain : public Scene
{
public:
    SceneMain();
    ~SceneMain();
    void init() override;
    void update() override;
    void render() override;
    void clean() override;
    void handleEvents(SDL_Event* event) override;

private:
    Player player;
    Game& game;
};

#endif // SCENEMAIN_H