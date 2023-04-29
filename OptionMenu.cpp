#include "OptionMenu.h"

OptionMenu::OptionMenu(TTF_Font* _font, Entity* mouse, SDL_Renderer* tRenderer)
{
    opMouse = mouse;
    renderer = tRenderer;
    font = _font;

    music = new Button(renderer,file_music_button);
    backButton = new Button(renderer,file_back_button);
}



int OptionMenu::handleAndUpdate(int& volume)
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        int x,y;
        SDL_GetMouseState(&x,&y);
        if (e.type == SDL_QUIT) return QUIT;

        if (e.type == SDL_MOUSEBUTTONDOWN) {
            opMouse->scale = 1.2;
            if (backButton->beChosen(x,y,BUTTON_WIDTH,BUTTON_HEIGHT)) return DEFAULT;
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

void OptionMenu::render()
{
    SDL_RenderClear(renderer);
    backButton->drawButton(0, SCREEN_HEIGHT - ING_BUT_H,ING_BUT_W,ING_BUT_H);
    opMouse->draw(NULL);

    SDL_RenderPresent(renderer);
}

