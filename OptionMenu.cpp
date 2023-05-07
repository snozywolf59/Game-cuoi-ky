#include "OptionMenu.h"

int tempX = 300;
int tempY = 260;
int slideW = 500;
int slideH = 25;

OptionMenu::OptionMenu(Resource* _res)
{
    res = _res;
}

int OptionMenu::handleAndUpdate(unsigned int& volume, unsigned int& snd)
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        int x,y;
        SDL_GetMouseState(&x,&y);
        res->Menu_Mouse->x = x;
        res->Menu_Mouse->y = y;
        if (e.type == SDL_QUIT) return QUIT;

        if (res->But_Back->beChosen(x,y,ING_BUT_W,ING_BUT_H)) {
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
    int x = res->Menu_Mouse->x;
    int y = res->Menu_Mouse->y;
    if (vol > 0) {
            if (res->But_MusicOff->beChosen(x,y,ING_BUT_W,ING_BUT_H))
                if (e->type == SDL_MOUSEBUTTONDOWN)
                    vol = 0;
        }
        else if (res->But_MusicOn->beChosen(x,y,ING_BUT_W,ING_BUT_H))
                if (e->type == SDL_MOUSEBUTTONDOWN)
                    vol = 128;
        if (e->type == SDL_MOUSEBUTTONDOWN) {

            if (tempX <= x && x <= tempX + slideW)
                if (tempY <= y && y <= tempY + slideH)
                {
                    vol = (x * 1.0f - tempX)/slideW * 128;
                }
            res->Menu_Mouse->scale = 1.2;
        }
        if (e->type == SDL_MOUSEBUTTONUP){
            res->Menu_Mouse->scale = 1;
        }
}

void OptionMenu::doSnd(unsigned int& snd, SDL_Event* e)
{
    int x = res->Menu_Mouse->x;
    int y = res->Menu_Mouse->y;
    if (snd > 0) {
            if (res->But_SoundOff->beChosen(x,y,ING_BUT_W,ING_BUT_H))
                if (e->type == SDL_MOUSEBUTTONDOWN)
                    snd = 0;
        }
        else if (res->But_SoundOn->beChosen(x,y,ING_BUT_W,ING_BUT_H))
                if (e->type == SDL_MOUSEBUTTONDOWN)
                    snd = 128;
        if (e->type == SDL_MOUSEBUTTONDOWN) {

            if (tempX <= x && x <= tempX + slideW)
                if (tempY + 200 <= y && y <= tempY + 200 + slideH)
                {
                    snd = (x * 1.0f - tempX)/slideW * 128;
                }
            res->Menu_Mouse->scale = 1.2;
            }
        if (e->type == SDL_MOUSEBUTTONUP){
                    res->Menu_Mouse->scale = 1;
        }
}

void OptionMenu::render(const unsigned int& vol, const unsigned int& snd)
{
    SDL_RenderClear(res->renderer);
    res->MenuBG->draw(NULL,0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    res->board->draw(NULL,SCREEN_WIDTH/2,SCREEN_HEIGHT/2,SCREEN_WIDTH - 100,SCREEN_HEIGHT - 50,1);
    res->But_Back->drawButton(0, SCREEN_HEIGHT - ING_BUT_H,ING_BUT_W,ING_BUT_H);

    if (vol > 0) res->But_MusicOff->drawButton(tempX - 100,tempY - 35,ING_BUT_W,ING_BUT_H);
    else res->But_MusicOn->drawButton(tempX - 100,tempY - 35,ING_BUT_W,ING_BUT_H);

    if (snd > 0) res->But_SoundOff->drawButton(tempX - 100,tempY + 165 ,ING_BUT_W,ING_BUT_H);
    else res->But_SoundOn->drawButton(tempX - 100,tempY + 165,ING_BUT_W,ING_BUT_H);

    res->slider->draw(NULL,tempX,tempY, slideW,slideH);
    SDL_Rect src = {0,0,int(vol / 128.0f * res->yellow_bar->w), res->yellow_bar->h};
    res->yellow_bar->draw(&src,tempX + 2,tempY + 1, (slideW - 3)/ 128.0f * vol,slideH - 2);
    res->But_slide->draw(NULL,tempX - 10 + (slideW - 3)/ 128.0f * vol, tempY - 4,25,32);

    src = {0,0,int(snd / 128.0f * res->yellow_bar->w), res->yellow_bar->h};
    res->slider->draw(NULL,tempX,tempY + 200, slideW,slideH);
    res->yellow_bar->draw(&src,tempX + 2,tempY + 201, (slideW - 3)/ 128.0f * snd,slideH - 2);
    res->But_slide->draw(NULL,tempX - 10 +(slideW - 3)/ 128.0f * snd, tempY + 196,25,32);
    res->Menu_Mouse->draw(NULL);

    SDL_RenderPresent(res->renderer);
}

