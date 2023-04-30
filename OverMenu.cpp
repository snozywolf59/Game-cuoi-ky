#include "OverMenu.h"

OverMenu::OverMenu(Mouse* _mouse, SDL_Renderer* _renderer)
{
    renderer = _renderer;
    GameOver = new Entity(renderer,file_game_over);
    MainMenu = new Button(renderer,FILE_ING_BUT[ING_MENU]);
    NewGame = new Button(renderer, file_new_game);
    mouse = _mouse;
    cnt = 0;
}

int OverMenu::handle()
{
    SDL_Event event;
    Uint32 start = SDL_GetTicks();
    while (SDL_PollEvent(&event)){
        if (event.type == SDL_QUIT) return QUIT;
        int x,y;
        SDL_GetMouseState(&x,&y);
        mouse->x = x, mouse->y = y;
        if (cnt > 255)
        {
            if (MainMenu->beChosen(x,y,BUTTON_WIDTH/2,BUTTON_HEIGHT/2))
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    MainMenu->now = 0;
                    cnt = 0;
                    return DEFAULT;
                }
            if (NewGame->beChosen(x,y,BUTTON_WIDTH,BUTTON_HEIGHT))
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    NewGame->now = 0;
                    cnt = 0;
                    return START;
                }
        }
    }

        cnt++;
        Uint32 real_delay = SDL_GetTicks() - start;
        if (real_delay < frameDelay)
        {
            SDL_Delay(frameDelay - real_delay);
        }
    return NORMAL;
}

void OverMenu::render()
{
    SDL_RenderClear(renderer);
    int now = cnt % 120;
    SDL_Rect temp = {(now - (now/5) * 5)/6 * 250,(now / 5)/6 * 28 , 250, 28};
    GameOver->draw(&temp,300,80,375,42);

    SDL_SetTextureAlphaMod(NewGame->texture, cnt > 255 ? 255:cnt);
    SDL_SetTextureAlphaMod(MainMenu->texture, cnt > 255 ? 255:cnt);
    if (cnt <= 255)
    {
        NewGame->scale = cnt/255.0;
        MainMenu->scale = cnt/255.0;
    }
    NewGame->drawButton(375,250,BUTTON_WIDTH/2,BUTTON_HEIGHT/2);
    MainMenu->drawButton(375,420,BUTTON_WIDTH/2,BUTTON_HEIGHT/2);
    mouse->draw(NULL);
    SDL_RenderPresent(renderer);
}
