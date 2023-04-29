#include "OptionMenu.h"

OptionMenu::OptionMenu(TTF_Font* _font, Entity* mouse, SDL_Renderer* tRenderer)
{
    opMouse = mouse;
    renderer = tRenderer;
    font = _font;

    musicOn = new Button(renderer,file_music_buttonOn);
    musicOff = new Button(renderer,file_music_buttonOff);
    backButton = new Button(renderer,file_back_button);
}

int OptionMenu::handleAndUpdate(unsigned int& volume)
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        int x,y;
        SDL_GetMouseState(&x,&y);
        if (e.type == SDL_QUIT) return QUIT;

        if (backButton->beChosen(x,y,ING_BUT_W,ING_BUT_H)) {
            if (e.type == SDL_MOUSEBUTTONDOWN)
                return DEFAULT;
        }

        if (volume > 0) {
            if (musicOff->beChosen(x,y,ING_BUT_W,ING_BUT_H))
                if (e.type == SDL_MOUSEBUTTONDOWN)
                    volume = 0;
        }
        else if (musicOn->beChosen(x,y,ING_BUT_W,ING_BUT_H))
                if (e.type == SDL_MOUSEBUTTONDOWN)
                    volume = 1;
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
        opMouse->x = x;
        opMouse->y = y;
    }
    return NORMAL;
}

void OptionMenu::render(const unsigned int& vol)
{
    SDL_RenderClear(renderer);
    backButton->drawButton(0, SCREEN_HEIGHT - ING_BUT_H,ING_BUT_W,ING_BUT_H);
    if (vol > 0) musicOff->drawButton(800,300,ING_BUT_W,ING_BUT_H);
    else musicOn->drawButton(800,300,ING_BUT_W,ING_BUT_H);
    opMouse->draw(NULL);

    SDL_RenderPresent(renderer);
}

