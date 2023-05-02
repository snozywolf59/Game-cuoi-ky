#include "GameMenu.h"

GameMenu::GameMenu(Resource* _res)
{
    res = _res;
    //menu item
        //create a stage to play
    stage = new Game(res);

        //option
    op = new OptionMenu(res);
    volume = MIX_MAX_VOLUME;
    snd = MIX_MAX_VOLUME;
    over = new OverMenu(res);
    scores = new HighScoreMenu(res);

    quit = false;

}

GameMenu::~GameMenu()
{}

void GameMenu::handleMouse()
{
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT) quit = true;

        if (e.type == SDL_MOUSEBUTTONDOWN) {
                res->Menu_Mouse->scale = 1.2;
                current = choose;
        }
        if (e.type == SDL_MOUSEBUTTONUP){
                res->Menu_Mouse->scale = 1;
        }
    }
}

void GameMenu::update()
{
    int x,y;
    SDL_GetMouseState(&x,&y);
    res->Menu_Mouse->x = x;
    res->Menu_Mouse->y = y;

    bool check = false;

    int old_choose = choose;

    for (int i = 0; i < TOTAL_BUTTON; i++)
    {
        if(res->But_Menu[i]->beChosen(x,y, BUTTON_WIDTH,BUTTON_HEIGHT))
        {
            check = true;
            choose = i;
        }
    }

    if (check == false) {
            choose = -1;
    }

    if (old_choose != choose && choose != -1) Mix_PlayChannel(0,res->But_beChosen,0);
}

void GameMenu::menuDefault()
{
    if (Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(res->Menu_bgMusic,0);
    }

    SDL_RenderClear(res->renderer);

    //background

    res->MenuBG->draw(NULL,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);

    //draw button

    for (int i = 0; i < TOTAL_BUTTON; i++)
    {
        res->But_Menu[i]->drawButton(100, int(BUTTON_HEIGHT * 1.5 * i) + 50,
                             BUTTON_WIDTH,BUTTON_HEIGHT);
    }
}


// NEED TO DO START, OPTION, QUIT, OVER
void GameMenu::menuStart()
{
    Mix_HaltMusic();
    //init stage
    stage->resetStage();

    //run game
    current = stage->GameLoop();
    choose = current;

    stage->clearGame();

    Mix_HaltMusic();
}

void GameMenu::menuOpTion()
{
    //this func will display highscore and button to turn off music
    while(1)
    {
        if (Mix_PlayingMusic() == 0)
        {
        Mix_PlayMusic(res->Menu_bgMusic,0);
        }
        current = op->handleAndUpdate(volume,snd);
        op->render(volume,snd);
        if (current != NORMAL) break;
    }
}


void GameMenu::menuQuit()
{
    quit = true;
}

//in game button
void GameMenu::menuOver()
{
    unsigned int newScore = stage->getScore();
    if (scores->check(newScore))
    {
        string newName = scores->enter_name();
        scores->update(Name(newName,newScore));
    }
    while(1){
            if (Mix_PlayingMusic() == 0)
            {
            Mix_PlayMusic(res->Menu_bgMusic,0);
            }
            current = over->handle();
            over->render();
            if (current != NORMAL) break;
    }
}

void GameMenu::menuScores()
{
    scores->read();
    scores->createTexture();
    while(1){
            if (Mix_PlayingMusic() == 0)
            {
                Mix_PlayMusic(res->Menu_bgMusic,0);
            }
            current = scores->handle();
            scores->render();
            if (current != NORMAL) break;
    }
}


void GameMenu::render()
{
    switch(current)
    {
    case DEFAULT:
        menuDefault();
        break;
    case START:
        menuStart();
        break;
    case OPTION:
        menuOpTion();
        break;
    case HIGHSCORE:
        menuScores();
        break;
    case QUIT:
        menuQuit();
        break;
    case NORMAL:
        menuOver();
        break;
    };

    //draw mouse

    res->Menu_Mouse->draw(NULL);

    SDL_RenderPresent(res->renderer);
}

bool GameMenu::out()
{
    return quit;
}

void GameMenu::clearMenu()
{
        //quit sdl
    Mix_Quit();
    IMG_Quit();
    TTF_Quit();

    SDL_Quit();
}


