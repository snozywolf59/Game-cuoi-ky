#pragma once

#include "Entity.h"
#include "Game.h"

const string file_game_over = "image/GameUI/GameOver/GameOver.png";
const string file_new_game = "image/GameUI/GameOver/NewGame.png";

struct OverMenu
{
    Button* MainMenu;
    Button* NewGame;
    Entity* GameOver;
    Mouse* mouse;
    Mix_Chunk* gameOverSound;
    SDL_Renderer* renderer;

    unsigned int cnt;

    OverMenu(Mouse* _mouse, SDL_Renderer* _renderer);

    int handle();

    void render();
};
