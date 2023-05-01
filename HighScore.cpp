#include "HighScore.h"

Name::Name(const string& _name, const int& _point)
{
    name = _name;
    point = _point;
}


HighScoreMenu::HighScoreMenu()
{}


HighScoreMenu::HighScoreMenu(Resource* _res)
{
    res = _res;

    for (int i = 0; i < TOP_SCORE; i++)
    {
        topScore[i] = new Word(0,0,res->renderer,res->font,res->pad);
    }

}

HighScoreMenu::~HighScoreMenu()
{
    for (int i = 0; i < TOP_SCORE; i++)
    {
        top[i].name = "";
        top[i].point = 0;
        if (topScore[i]->texture != NULL)
        {
            SDL_DestroyTexture(topScore[i]->texture);
            delete topScore[i];
            topScore[i] = NULL;
        }
    }
}

void HighScoreMenu::read()
{
    ifstream readfile(file_score);
    string line;

    int cnt = 0;
    while (!readfile.eof())
    {
        getline(readfile,top[cnt].name);

        getline(readfile,line);

        stringstream s(line);

        s >> top[cnt].point;

        cnt++;

        if (cnt >= TOP_SCORE) break;
    }

    readfile.close();
}

void HighScoreMenu::write()
{
    ofstream writefile(file_score);
    for (int i = 0; i < TOP_SCORE; i++)
        writefile << top[i].name << '\n' << top[i].point << '\n';
    writefile.close();
}

int HighScoreMenu::handle()
{
    Uint32 start = SDL_GetTicks();
    SDL_Event event;
    int x,y;
    SDL_GetMouseState(&x,&y);
    res->Menu_Mouse->x = x, res->Menu_Mouse->y = y;

    while (SDL_PollEvent(&event)){
        if (event.type == SDL_QUIT) return QUIT;


        if (res->But_Back->beChosen(x,y,ING_BUT_W,ING_BUT_H))
            if (event.type == SDL_MOUSEBUTTONDOWN) return DEFAULT;

        if (event.type == SDL_MOUSEBUTTONDOWN) res->Menu_Mouse->scale = 1.1;
        if (event.type == SDL_MOUSEBUTTONUP) res->Menu_Mouse->scale = 1;
    }

    Uint32 real_delay = SDL_GetTicks() - start;
    if (real_delay < frameDelay)
    {
        SDL_Delay(frameDelay - real_delay);
    }
    return NORMAL;
}

bool HighScoreMenu::check(const unsigned int& newS)
{
    if (newS > top[TOP_SCORE - 1].point) return true;
    return false;
}


void HighScoreMenu::update(const Name& newScore)
{
    updateScore(newScore);
}

void HighScoreMenu::createTexture()
{
    for (int i = 0; i < TOP_SCORE; i++)
    {
        if (topScore[i]->texture != NULL) SDL_DestroyTexture(topScore[i]->texture);
        stringstream point;
        point << '#' << i+1 << ' ' << top[i].name << ' ' << top[i].point << '\n';
        topScore[i]->loadFromRenderedText(point.str());
    }
}


void HighScoreMenu::updateScore(const Name& newScore)
{
    unsigned int now = TOP_SCORE;
    if (top[--now] .point< newScore.point) {
            top[now].point = newScore.point;
            top[now].name = newScore.name;
    }
    else return;
    while (top[now].point > top[now - 1].point && now > 0)
    {
        swap(top[now].name, top[now - 1].name);
        swap(top[now].point, top[--now].point);
    }
}

void HighScoreMenu::render()
{
    SDL_RenderClear(res->renderer);
    res->board->draw(NULL,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    res->score->draw(NULL,SCREEN_WIDTH/2,51,361,101,1);
    for (int i = 0; i < TOP_SCORE; i++)
    {
        topScore[i]->drawWord(300,100 * i + 120);
    }
    res->But_Back->drawButton(0,SCREEN_HEIGHT - ING_BUT_H,ING_BUT_W,ING_BUT_H);
    res->Menu_Mouse->draw(NULL);
    SDL_RenderPresent(res->renderer);
}
