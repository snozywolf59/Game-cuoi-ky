#include "GameMenu.h"

GameMenu::GameMenu(SDL_Renderer* gRenderer)
{
    renderer = gRenderer;

    //init(0);
    gRenderer = renderer;

    initMouse();
    initBackGround();
    initButton();
    initSound();
    initFontAndPad();

    //menu item
        //create a stage to play
    stage = new Game(renderer,gFont,pad,beChosen);

        //option
    op = new OptionMenu(gFont,mouse,renderer);
    over = new OverMenu(mouse,renderer);

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


void GameMenu::initFontAndPad()
{
    gFont = TTF_OpenFont(gameFont.c_str(),50);
    pad = new Entity(renderer,file_pad);
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

void GameMenu::menuDefault()
{
    Mix_VolumeMusic(volume);
    if (Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(bgMusic,0);
    }

    SDL_RenderClear(renderer);

    //background

    bgImage->draw(NULL,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);

    //draw button

    for (int i = 0; i < TOTAL_BUTTON; i++)
    {
        button[i]->drawButton(100, int(BUTTON_HEIGHT * 1.5 * i) + 50,
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
        current = op->handleAndUpdate(volume);
        op->render(volume);
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
    while(1){
            current = over->handle();
            over->render();
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
    case QUIT:
        menuQuit();
        break;
    case NORMAL:
        menuOver();
        break;
    };

    //draw mouse

    mouse->draw(NULL);

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


