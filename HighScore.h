#pragma once

#include "Entity.h"
#include "Button.h"
#include "Word.h"
#include "Mouse.h"

const int TOP_SCORE = 5;

const string file_score = "text/HighScore.txt";

class HighScoreMenu
{
public:
    HighScoreMenu(SDL_Renderer* _renderer);
    HighScoreMenu(SDL_Renderer* _renderer, TTF_Font* _font, Button* _backButton);
    ~HighScoreMenu();

    void read();
    void write();

    void update(const unsigned int& newScore);
    void updateScore(const unsigned int& newScore);
    void render();

private:
    SDL_Renderer* renderer;
    unsigned int top[TOP_SCORE];
    Word* topScore[TOP_SCORE];
    Button* backButton;
    TTF_Font* font;
};
