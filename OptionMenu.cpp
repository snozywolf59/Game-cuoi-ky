#include "OptionMenu.h"

int tempX = 300;
int tempY = 100;
int slideW = 500;
int slideH = 25;

OptionMenu::OptionMenu(TTF_Font* _font, Entity* mouse, SDL_Renderer* tRenderer)
{
    opMouse = mouse;
    renderer = tRenderer;
    font = _font;

    musicOn = new Button(renderer,file_music_buttonOn);
    musicOff = new Button(renderer,file_music_buttonOff);
    soundOn = new Button(renderer,file_sound_buttOn);
    soundOff = new Button(renderer,file_sound_buttOff);

    backButton = new Button(renderer,file_back_button);

    yellow_bar = new Entity(renderer,file_yellow_bar);
    music_slider = new Entity(renderer,file_music_slider);
}

int OptionMenu::handleAndUpdate(unsigned int& volume, unsigned int& snd)
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        int x,y;
        SDL_GetMouseState(&x,&y);
        opMouse->x = x;
        opMouse->y = y;
        if (e.type == SDL_QUIT) return QUIT;

        if (backButton->beChosen(x,y,ING_BUT_W,ING_BUT_H)) {
            if (e.type == SDL_MOUSEBUTTONDOWN)
                return DEFAULT;
        }

        doVol(volume,&e);
        doSnd(snd,&e);
    }
    Mix_VolumeMusic(volume);
    Mix_Volume(-1,snd);

    return NORMAL;
}

void OptionMenu::doVol(unsigned int& vol,SDL_Event* e)
{
    int x = opMouse->x;
    int y = opMouse->y;
    if (vol > 0) {
            if (musicOff->beChosen(x,y,ING_BUT_W,ING_BUT_H))
                if (e->type == SDL_MOUSEBUTTONDOWN)
                    vol = 0;
        }
        else if (musicOn->beChosen(x,y,ING_BUT_W,ING_BUT_H))
                if (e->type == SDL_MOUSEBUTTONDOWN)
                    vol = 128;
        if (e->type == SDL_MOUSEBUTTONDOWN) {

            if (tempX <= x && x <= tempX + slideW)
                if (tempY <= y && y <= tempY + slideH)
                {
                    vol = (x * 1.0f - tempX)/slideW * 128;
                }
            opMouse->scale = 1.2;
            }
        if (e->type == SDL_MOUSEBUTTONUP){
                    opMouse->scale = 1;
        }
}

void OptionMenu::doSnd(unsigned int& snd, SDL_Event* e)
{
    int x = opMouse->x;
    int y = opMouse->y;
    if (snd > 0) {
            if (soundOff->beChosen(x,y,ING_BUT_W,ING_BUT_H))
                if (e->type == SDL_MOUSEBUTTONDOWN)
                    snd = 0;
        }
        else if (soundOn->beChosen(x,y,ING_BUT_W,ING_BUT_H))
                if (e->type == SDL_MOUSEBUTTONDOWN)
                    snd = 128;
        if (e->type == SDL_MOUSEBUTTONDOWN) {

            if (tempX <= x && x <= tempX + slideW)
                if (tempY + 200 <= y && y <= tempY + 200 + slideH)
                {
                    snd = (x * 1.0f - tempX)/slideW * 128;
                }
            opMouse->scale = 1.2;
            }
        if (e->type == SDL_MOUSEBUTTONUP){
                    opMouse->scale = 1;
        }
}

void OptionMenu::render(const unsigned int& vol, const unsigned int& snd)
{
    SDL_RenderClear(renderer);
    backButton->drawButton(0, SCREEN_HEIGHT - ING_BUT_H,ING_BUT_W,ING_BUT_H);

    if (vol > 0) musicOff->drawButton(tempX - 100,tempY - 35,ING_BUT_W,ING_BUT_H);
    else musicOn->drawButton(tempX - 100,tempY - 35,ING_BUT_W,ING_BUT_H);

    if (snd > 0) soundOff->drawButton(tempX - 100,tempY + 165 ,ING_BUT_W,ING_BUT_H);
    else soundOn->drawButton(tempX - 100,tempY + 165,ING_BUT_W,ING_BUT_H);

    music_slider->draw(NULL,tempX,tempY, slideW,slideH);
    SDL_Rect src = {0,0,vol / 128.0f * yellow_bar->w, yellow_bar->h};
    yellow_bar->draw(&src,tempX + 2,tempY + 1, (slideW - 3)/ 128.0f * vol,slideH - 2);

    src = {0,0,snd / 128.0f * yellow_bar->w, yellow_bar->h};
    music_slider->draw(NULL,tempX,tempY + 200, slideW,slideH);
    yellow_bar->draw(&src,tempX + 2,tempY + 201, (slideW - 3)/ 128.0f * snd,slideH - 2);
    opMouse->draw(NULL);

    SDL_RenderPresent(renderer);
}

