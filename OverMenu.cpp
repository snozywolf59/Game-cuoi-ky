#include "OverMenu.h"

OverMenu::OverMenu(Resource* _res)
{
    res = _res;
    cnt = 0;
}

string OverMenu::enter_name()
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
                    returnName += *event.text.text;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_BACKSPACE && returnName.size() > 0)
                    {
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

void OverMenu::render_enter_name(const string& returnName)
{
    SDL_Color textColor = {255,255,255,0};
    SDL_SetRenderDrawColor(res->renderer, 0, 0, 0, 255);
    SDL_RenderClear(res->renderer);

    SDL_Surface* inputSurface = TTF_RenderText_Solid(res->font, returnName.c_str(), textColor);
    SDL_Texture* inputTexture = SDL_CreateTextureFromSurface(res->renderer, inputSurface);
    int w,h;
    SDL_QueryTexture(inputTexture,NULL,NULL,&w,&h);
    SDL_Rect des = {SCREEN_WIDTH/2 - w/2,300,w,h};
    res->board->draw(NULL,0,-50,SCREEN_WIDTH,SCREEN_HEIGHT + 100);
    res->congratulate->drawWord(200,100);
    res->enter_name->drawWord(350,200);
    SDL_RenderCopy(res->renderer, inputTexture, NULL, &des);
    res->Menu_Mouse->draw(NULL);

    SDL_RenderPresent(res->renderer);
    SDL_FreeSurface(inputSurface);
    SDL_DestroyTexture(inputTexture);

    SDL_Delay(frameDelay);
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
