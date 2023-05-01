#include "GameMenu.h"



SDL_Window* gWindow;
SDL_Renderer* gRenderer;
Resource* res;

void init(bool fullScreen);

int main(int argc, char* argv[])
{

    srand(time(NULL));

    init(0);

    res = new Resource(gRenderer);
//
//    GameMenu* menu =  new GameMenu(res);
//
//    while (!menu->out())
//    {
//        menu->handleMouse();
//
//        menu->update();
//
//        menu->render();
//    }
//
//    menu->clearMenu();

    OverMenu test(res);
    cout << test.enter_name();

    return 0;
}

void init(bool fullScreen)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        logSDLError(cout, "SDL_Init", true);
    }
    else
    {
        int flag = 0;
        if (fullScreen) flag = SDL_WINDOW_FULLSCREEN;

        gWindow = SDL_CreateWindow(TITLE,SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH,SCREEN_HEIGHT,flag);
        if (gWindow == nullptr) logSDLError(cout, "CreateWindow", true);

        gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED |SDL_RENDERER_PRESENTVSYNC);

        if (gRenderer == nullptr) logSDLError(cout, "CreateRenderer", true);

        /////////////IMAGE TRUE TYPE FONT AND  MIXER
        int imgFlags = IMG_INIT_PNG;

        if( !( IMG_Init( imgFlags ) & imgFlags ) )
        {
            cerr <<  "SDL_image could not initialize! SDL_image Error: " << IMG_GetError();
            exit(2);
        }
        if( TTF_Init() == -1 )
        {
            cerr << "SDL_ttf could not initialize! SDL_ttf Error: "<< TTF_GetError() ;
            exit(3);
        }

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
        {
            cerr << "SDL_mixer could not initialize! SDL_mixer Error: "<< Mix_GetError();
            exit(4);
        }

        Mix_AllocateChannels(SND_MAX);

        //set color
        SDL_SetRenderDrawColor(gRenderer,0,0,0,0);

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
        SDL_ShowCursor(0);
    }
}
