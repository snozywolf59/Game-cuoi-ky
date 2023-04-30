#include "Resource.h"


Resource::Resource(SDL_Renderer* _renderer)
{
    renderer = _renderer;
    //Button
    for (int i = 0; i < TOTAL_BUTTON; i++)
        But_Menu[i] = new Button(renderer,FILE_MENU_IMAGE[i]);
    for (int i = 0; i < ING_TOTAL; i++)
        But_InG[i] = new Button(renderer,FILE_ING_BUT[i]);

    //entity
    MenuBG = new Entity(renderer,file_bg);
    pad = new Entity(renderer,file_pad);

    enemy_melee = new Entity(renderer,file_enemy_melee);
    enemy_ranged = new Entity(renderer,file_enemy_ranged);
    explosion = new Entity(renderer,file_explosion);
    e_bullet = new Entity(renderer,file_enemy_bullet);


    //mouse
    Menu_Mouse = new Mouse(renderer,file_menu_mouse);
    InGame_Mouse = new Mouse(renderer,file_ing_mouse);

    //music
    Menu_bgMusic = Mix_LoadMUS(snd_menu_bgMusic);
    InG_Music = Mix_LoadMUS(snd_game_bgMusic);
    //chunk
    enemy_die = Mix_LoadWAV(snd_enemy_die);
    But_beChosen = Mix_LoadWAV(snd_menu_beChosen);

    //font
    font = TTF_OpenFont(gameFont.c_str(),30);
}
