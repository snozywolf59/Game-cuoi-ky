#include "GameMenu.h"

optionMenu::optionMenu(Entity* mouse, SDL_Renderer* tRenderer)
{
    opMouse = mouse;
    renderer = tRenderer;
}



int optionMenu::handleAndUpdate(int& volume)
{
    SDL_Event e;

    int x,y;
    while (!out)
    {
        SDL_GetMouseState(&x,&y);
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT) return QUIT;

            if (e.type == SDL_MOUSEBUTTONDOWN) {
                    opMouse->scale = 1.2;

                    if (x >= vol_slider.x && x <= vol_slider.x + vol_slider.w &&
                            y >= vol_slider.y && y <= vol_slider.y + vol_slider.h) {
                        volume = (x - vol_slider.x) / SLIDER_W * MIX_MAX_VOLUME;
                    }
            }
            if (e.type == SDL_MOUSEBUTTONUP){
                    opMouse->scale = 1;
            }
        }

        opMouse->x = x;
        opMouse->y = y;
    }
    return NORMAL;
}

void optionMenu::render()
{
    SDL_RenderClear(renderer);

    opMouse->draw(NULL,renderer);

    SDL_RenderPresent(renderer);
}

GameMenu::GameMenu(SDL_Renderer* gRenderer)
{
    renderer = gRenderer;

    //init(0);
    gRenderer = renderer;

    initMouse();
    initBackGround();
    initButton();
    initSound();

    //menu item
        //create a stage to play
    stage = new Game(renderer);
    stage->initStage();

        //option
    op = new optionMenu(mouse,renderer);

    quit = false;
}

GameMenu::~GameMenu()
{}


void GameMenu::initMouse()
{
    mouse = new Mouse(renderer,file_menu_mouse);
    logSuccess("menu mouse");
}

void GameMenu::initButton()
{
    for (int i = 0; i < TOTAL_BUTTON; i++)
    {
        button[i] = new Button(renderer,FILE_MENU_IMAGE[i]);
    }
    logSuccess("menu buttons");
}


void GameMenu::initBackGround()
{
    bgImage = new Entity(renderer,file_bg);
    bgImage->w = SCREEN_WIDTH;
    bgImage->h = SCREEN_HEIGHT;
    logSuccess("bgImage Menu");
}

void GameMenu::initSound()
{
    beChosen = Mix_LoadWAV(snd_menu_beChosen);
    if (beChosen == NULL)
    {
        cerr << "Failed to load beChosen sound effect! SDL_mixer Error: " << Mix_GetError();
        exit(1);
    }

    bgMusic = Mix_LoadMUS(snd_menu_bgMusic);
    if (bgMusic == NULL)
    {
        cerr << "Failed to load background music! SDL_mixer Error: " << Mix_GetError();
        exit(1);
    }

    volume = MIX_MAX_VOLUME;
    logSuccess("Sound menu");
}


void GameMenu::handleMouse()
{
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT) quit = true;

        if (e.type == SDL_MOUSEBUTTONDOWN) {
                mouse->scale = 1.2;
                current = choose;
        }
        if (e.type == SDL_MOUSEBUTTONUP){
                mouse->scale = 1;
        }
    }
}

void GameMenu::update()
{
    int x,y;
    SDL_GetMouseState(&x,&y);
    mouse->x = x;
    mouse->y = y;

    bool check = false;

    int old_choose = choose;

    for (int i = 0; i < TOTAL_BUTTON; i++)
    {
        if(button[i]->beChosen(x,y, BUTTON_WIDTH,BUTTON_HEIGHT))
        {
            check = true;
            choose = i;
        }
    }

    if (check == false) {
            choose = -1;
    }

    if (old_choose != choose && choose != -1) Mix_PlayChannel(0,beChosen,0);
}


/////////////////////HANDLE CLICKED BUTTON///////////////////////////

void GameMenu::menuDefault()
{
    if (Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(bgMusic,0);
    }

    SDL_RenderClear(renderer);

    //background

    bgImage->draw(NULL,0,0,SCREEN_WIDTH,SCREEN_HEIGHT, renderer);

    //draw button

    for (int i = 0; i < TOTAL_BUTTON; i++)
    {
        button[i]->drawButton(100, int(BUTTON_HEIGHT * 1.5 * i) + 50,
                             BUTTON_WIDTH,BUTTON_HEIGHT,renderer);
    }
}


// NEED TO DO START, OPTION, SCORE, QUIT, OVER
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

void GameMenu::menuOption()
{
    current = op->handleAndUpdate(volume);
    choose = current;

    op->render();
}

void GameMenu::menuScore()
{

}

void GameMenu::menuQuit()
{
    quit = true;
}

//in game button
void GameMenu::menuOver()
{

}



// END OF BUTTON

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
        menuOption();
        break;
    case QUIT:
        menuQuit();
        break;
    case 1000:
        menuOver();
        break;
    };

    //draw mouse

    mouse->draw(NULL,renderer);

    SDL_RenderPresent(renderer);
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


