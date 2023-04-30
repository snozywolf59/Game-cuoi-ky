#include "HighScore.h"

HighScoreMenu::HighScoreMenu(SDL_Renderer* _renderer, TTF_Font* _font, Button* _backButton)
{
    renderer = _renderer;
    font = _font;
    backButton = _backButton;

    for (int i = 0; i < TOP_SCORE; i++)
        topScore[i] = new Word(0,0,renderer,font,NULL);
}

HighScoreMenu::~HighScoreMenu()
{}

void HighScoreMenu::read()
{
    ifstream readfile(file_score);
    unsigned int n;
    while (!readfile.eof())
    {
        readfile >> n;
    }
    readfile.close();
}

void HighScoreMenu::write()
{
    ofstream writefile(file_score);
    for (int i = 0; i < TOP_SCORE; i++)
        writefile << top[i] << '\n';
}


void HighScoreMenu::update(const unsigned int& newScore)
{
    updateScore(newScore);
}

void HighScoreMenu::updateScore(const unsigned int& newScore)
{
    for (int i = TOP_SCORE - 1; i >= 0; i--)
    {
        if (top[i] < newScore) continue;
        if (i < TOP_SCORE) top[i] = newScore;
    }
}

void HighScoreMenu::render()
{
    SDL_RenderClear(renderer);
    for (int i = 0; i < TOP_SCORE; i++)
    {
        SDL_DestroyTexture(topScore->texture);
    }
}
