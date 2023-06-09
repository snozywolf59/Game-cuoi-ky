#include "HighScore.h"

HighScoreMenu::HighScoreMenu()
{}


HighScoreMenu::HighScoreMenu(Resource* _res)
{
    res = _res;

    for (int i = 0; i < TOP_SCORE; i++)
    {
        topScore[i] = new Word(0,0,res->renderer,res->font,NULL);
    }
    newS = new Word(0,0,res->renderer, res->font,NULL);
    read();
    createTexture();
    maxL = false;
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
            topScore[i]->texture = NULL;
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
    if (cnt < TOP_SCORE)
    {
        cout << "High score file is invalid\n";
        exit(1);
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

string HighScoreMenu::enter_name()
{
    string returnName;
    while (1)
    {
        if (Mix_PlayingMusic() == 0){
            Mix_PlayMusic(res->Menu_bgMusic,0);
        }
        int x,y;
        SDL_GetMouseState(&x,&y);
        res->Menu_Mouse->x = x, res->Menu_Mouse->y = y;
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    return (returnName == "" ? "NoName" : returnName);
                    break;
                case SDL_TEXTINPUT:
                    if (returnName.size() < NameMaxLength)
                        {
                            returnName += *event.text.text;
                            maxL = false;
                        }
                        else maxL = true;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_BACKSPACE && returnName.size() > 0)
                    {
                        maxL = false;
                        returnName.pop_back();
                    }
                    if (event.key.keysym.sym == SDLK_RETURN)
                    return returnName;
                    break;
            }
        }
        render_enter_name(returnName);
    }
}

void HighScoreMenu::render_enter_name(const string& returnName)
{
    SDL_Color textColor = {255,255,255,0};
    SDL_SetRenderDrawColor(res->renderer, 0, 0, 0, 255);
    SDL_RenderClear(res->renderer);

    SDL_Surface* inputSurface = TTF_RenderText_Solid(res->font, returnName.c_str(), textColor);
    SDL_Texture* inputTexture = SDL_CreateTextureFromSurface(res->renderer, inputSurface);
    int w,h;
    SDL_QueryTexture(inputTexture,NULL,NULL,&w,&h);
    SDL_Rect des = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
    res->BG2->draw(&des,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    res->congratulate->drawWord(SCREEN_WIDTH/2 - res->congratulate->w/2,100);
    newS->drawWord(SCREEN_WIDTH/2 - newS->w/2, 165);
    res->enter_name->drawWord(SCREEN_WIDTH/2 - res->enter_name->w/2,230);
    des = {SCREEN_WIDTH/2 - w/2,320,w,h};
    SDL_RenderCopy(res->renderer, inputTexture, NULL, &des);
    if (maxL) res->too_long->drawWord(260,450);
    res->Menu_Mouse->draw(NULL);

    SDL_RenderPresent(res->renderer);
    SDL_FreeSurface(inputSurface);
    SDL_DestroyTexture(inputTexture);

    SDL_Delay(frameDelay);
}

bool HighScoreMenu::check(const unsigned int& newScore)
{
    if (newScore > top[TOP_SCORE - 1].point) {
        newS->loadFromRenderedText(convertIntToString(int(newScore)));
        return true;
    }
    return false;
}


void HighScoreMenu::update(const Name& newScore)
{
    updateScore(newScore);
    write();
}

void HighScoreMenu::createTexture()
{
    for (int i1 = 0; i1 < TOP_SCORE; i1++)
    {
        stringstream point;
        point << " #" << i1+1 << "      " << top[i1].name;
        for (int j1 = NameMaxLength + 3 - top[i1].name.size(); j1 > 0; j1--) point << ' ';
        point << top[i1].point ;
        topScore[i1]->loadFromRenderedText(point.str());
    }
}
void HighScoreMenu::deleteTexure()
{
    for (int i = 0; i < TOP_SCORE; i++)
    {
        if (topScore[i]->texture != NULL)
        {
            SDL_DestroyTexture(topScore[i]->texture);
            topScore[i]->texture = NULL;
        }
    }
}


void HighScoreMenu::updateScore(const Name& newScore)
{
    unsigned int now = TOP_SCORE - 1;
    if (top[now].point < newScore.point) {
            top[now].point = newScore.point;
            top[now].name = newScore.name;
    }
    else return;
    while (now > 0 && top[now].point > top[now - 1].point)
    {
        swap(top[now],top[now-1]);
        now--;
    }

    return;
}

void HighScoreMenu::render()
{
    SDL_RenderClear(res->renderer);
    res->MenuBG->draw(NULL,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    res->board->draw(NULL,SCREEN_WIDTH/2,SCREEN_HEIGHT/2,SCREEN_WIDTH - 100,SCREEN_HEIGHT - 50,1);
    res->score->draw(NULL,SCREEN_WIDTH/2,65,234,45,1);
    for (int i = 0; i < TOP_SCORE; i++)
    {
        topScore[i]->drawWord(135,100 * i + 130);
    }
    res->But_Back->drawButton(0,SCREEN_HEIGHT - ING_BUT_H,ING_BUT_W,ING_BUT_H);
    res->Menu_Mouse->draw(NULL);
    SDL_RenderPresent(res->renderer);
}
