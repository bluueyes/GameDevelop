#include "SceneMain.h"
#include "SDL_image.h"
#include "Game.h"

SceneMain::SceneMain()
    : game(Game::getInstance())
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::init()
{
    player.texture = IMG_LoadTexture(game.getRenderer(), "../../assets/image/SpaceShip.png");
    if(player.texture == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load texture: %s", IMG_GetError());
        return;
    }
    
    SDL_QueryTexture(player.texture, nullptr, nullptr, &player.width, &player.height);
    player.width /= 4;
    player.height /= 4;

    player.position.x = static_cast<float>(game.getWindowWidth()/2) - player.width/2;
    player.position.y = static_cast<float>(game.getWindowHeight()) - player.height;
}

void SceneMain::update()
{
}

void SceneMain::render()
{
    SDL_Rect playerRect = {static_cast<int>(player.position.x), 
                            static_cast<int>(player.position.y), 
                            player.width, player.height};
    SDL_RenderCopy(game.getRenderer(), player.texture, nullptr, &playerRect);
}

void SceneMain::clean()
{
    if(player.texture != nullptr)
    {
        SDL_DestroyTexture(player.texture);
        player.texture = nullptr;
    }
}

void SceneMain::handleEvents(SDL_Event* event)
{
}

