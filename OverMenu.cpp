#include "OverMenu.h"

OverMenu::OverMenu(Resource* _res)
{
    res = _res;
    cnt = 0;
    maxL = false;
}

int OverMenu::handle()
{
    int x,y;
    SDL_GetMouseState(&x,&y);
    res->Menu_Mouse->x = x, res->Menu_Mouse->y = y;
    SDL_Event event;
    Uint32 start = SDL_GetTicks();
    while (SDL_PollEvent(&event)){
        if (event.type == SDL_QUIT) return QUIT;
        if (cnt > 255)
        {
            if (res->But_InG[ING_MENU]->beChosen(x,y,BUTTON_WIDTH/2,BUTTON_HEIGHT/2))
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    res->But_InG[ING_MENU]->now = 0;
                    cnt = 0;
                    return DEFAULT;
                }
            if (res->But_NewGame->beChosen(x,y,BUTTON_WIDTH,BUTTON_HEIGHT))
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    res->But_NewGame->now = 0;
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
    SDL_RenderClear(res->renderer);
    int now = cnt % 120;
    SDL_Rect temp = {(now - (now/5) * 5)/6 * 250,(now / 5)/6 * 28 , 250, 28};
    res->game_over->draw(&temp,300,80,375,42);

    SDL_SetTextureAlphaMod(res->But_NewGame->texture, cnt > 255 ? 255:cnt);
    SDL_SetTextureAlphaMod(res->But_InG[ING_MENU]->texture, cnt > 255 ? 255:cnt);
    if (cnt <= 255)
    {
        res->But_NewGame->scale = cnt/255.0;
        res->But_InG[ING_MENU]->scale = cnt/255.0;
    }
    res->But_NewGame->drawButton(375,250,BUTTON_WIDTH/2,BUTTON_HEIGHT/2);
    res->But_InG[ING_MENU]->drawButton(375,420,BUTTON_WIDTH/2,BUTTON_HEIGHT/2);
    res->Menu_Mouse->draw(NULL);
    SDL_RenderPresent(res->renderer);
}
