#include "HighScore.h"

HighScoreMenu::HighScoreMenu(SDL_Renderer* _renderer)
{
    renderer = _renderer;
}


HighScoreMenu::HighScoreMenu(SDL_Renderer* _renderer, TTF_Font* _font, Button* _backButton)
{
    renderer = _renderer;
    font = _font;
    backButton = _backButton;

    for (int i = 0; i < TOP_SCORE; i++)
        topScore[i] = new Word(0,0,renderer,font,NULL);

    backButton = _backButton;
}

HighScoreMenu::~HighScoreMenu()
{}

void HighScoreMenu::read()
{
    cout << 1;
    ifstream readfile(file_score);
    unsigned int n;
    int cnt = 0;
    while (!readfile.eof())
    {
        readfile >> n;

        top[cnt++] = n;

        if (cnt >= 5) break;
    }

    readfile.close();

    sort(top,top + TOP_SCORE,greater <unsigned int>());
    cout << 1;
}

void HighScoreMenu::write()
{
    ofstream writefile(file_score);
    sort(top,top + TOP_SCORE,greater <unsigned int>());
    for (int i = 0; i < TOP_SCORE; i++)
        writefile << top[i] << '\n';
    writefile.close();
}


void HighScoreMenu::update(const unsigned int& newScore)
{
    updateScore(newScore);
}

void HighScoreMenu::updateScore(const unsigned int& newScore)
{
    unsigned int now = TOP_SCORE;
    if (top[--now] < newScore) top[now] = newScore;
    else return;
    while (top[now] > top[now - 1] && now > 0)
    {
        swap(top[now],top[--now]);
    }
}

void HighScoreMenu::render()
{
    SDL_RenderClear(renderer);
    for (int i = 0; i < TOP_SCORE; i++)
    {
        if (topScore[i]->texture != NULL) SDL_DestroyTexture(topScore[i]->texture);
        stringstream point;
        point << '#' << i+1 << ' ' << top[i];
        topScore[i]->loadFromRenderedText(point.str());
        topScore[i]->drawWord(100,80 * i);
    }

    SDL_RenderPresent(renderer);
}
