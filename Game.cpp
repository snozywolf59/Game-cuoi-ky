#include "Game.h"


//GAME INIT

Game::Game(SDL_Renderer* gRenderer, TTF_Font* tempFont, Entity* tempPad){
    renderer = gRenderer;

    if (renderer == NULL)
    {
        cout << "LOI RENDERER CUA STAGE";
        exit(1);
    }

    font = tempFont;
    pad = tempPad;

    initStage();
}

Game::~Game(){}
            //INIT

void Game::initStage()
{
    logSuccess("loading stage");
    initMap(txt_map);
    initPlayer();
    initEnemy();
    initMouse();
    initSoundGame();
    initFont();
    initIng();
    logSuccess("stage");
}


void Game::initPlayer()
{
    player = new Player(renderer);

    //load sound
    player->attack = Mix_LoadWAV(snd_player_shoot);
    player->isHitted = Mix_LoadWAV(snd_player_hitted);

    if (player->attack == NULL||player->isHitted == NULL)
    {
        cerr << "Failed to load player shoot or player is hitted sound effect! SDL_mixer Error: "
        << Mix_GetError();
        exit(1);
    }
    logSuccess("Player");
}

void Game::initEnemy()
{
    enemy_melee = new Entity(renderer,file_enemy_melee);
    logSuccess("enemy melee");

    enemy_ranged = new Entity(renderer,file_enemy_ranged);
    e_bullet = new Entity(renderer,"image/enemy/bullet.png");
    logSuccess("enemy ranged");


    explosion = new Entity(renderer,"image/enemy/explosion.png");
    logSuccess("explosion");
}


void Game::initMap(const string& path)
{
    gMap = new Map(renderer);
    gMap->loadMap(path);
    logSuccess("map");
}



void Game::initMouse()
{
    mouse = new Mouse(renderer,file_ing_mouse);
    logSuccess("mouse");
}

/****************************************************/

void Game::initSoundGame()
{
    //sound when an enemy dies
    enemy_die = Mix_LoadWAV(snd_enemy_die);
    if (enemy_die == NULL)
    {
        cerr << "Failed to load enemy die sound effect! SDL_mixer Error: " << Mix_GetError();
        exit(1);
    }

    //background music
    bgMusic =  Mix_LoadMUS(snd_game_bgMusic);
    if (bgMusic == NULL)
    {
        cerr << "Failed to load background music! SDL_mixer Error: " << Mix_GetError();
        exit(1);
    }
    logSuccess("sound");
}

/****************************************************/

void Game::initFont()
{
    score_word = new Word(0,0,renderer,font,pad);
    logSuccess("font");
}

/****************************************************/

void Game::initIng()
{
    //load button

    for (int i = 0; i < ING_TOTAL; i++)
    {
        Ing_Button[i] = new Button(renderer,FILE_ING_BUT[i]);
    }
    logSuccess("buttons");
}

void Game::resetStage()
{
    camera.x = MAP_SIZE/2 - SCREEN_WIDTH/2;
    camera.y = MAP_SIZE/2 - SCREEN_HEIGHT/2;

    gameOver = false;
    pause = false;

    //set time
    currentTime = 0;

    //score

    score = 0;

    //player
    player->initStat();
    player->initPos();
    player->x += camera.x;
    player->y += camera.y;
    //enemy
    enemy_melee_list.clear();
    enemy_ranged_list.clear();
}

//GAME LOOP
int Game::handleEvent()
{
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT) return QUIT;

        doMouse();

        doKeyBoard();

        int a = doButton();

        if (a != NORMAL) return a;
    }
    return NORMAL;
}


int Game::doButton()
{
    for (int i = 0; i < ING_TOTAL; i++)
        {
            int tw = (i == 0 ? ING_BUT_W:BUTTON_WIDTH);
            int th = (i == 0 ? ING_BUT_H:BUTTON_HEIGHT);
            if (Ing_Button[i]->beChosen(mouse->x - camera.x,
                                       mouse->y - camera.y, tw, th)
                && e.type == SDL_MOUSEBUTTONDOWN)
            {
                if (!pause && i == ING_PAUSE) pause = true;
                if (pause) {
                    switch (i)
                    {
                    case ING_RESUME:
                        pause = false;
                        return NORMAL;
                    case ING_MENU:
                        return DEFAULT;
                    case ING_QUIT:
                        return QUIT;
                        break;
                    }
                }
            }
        }
    return NORMAL;
}

void Game::doMouse()
{
     SDL_GetMouseState(&mouse->real_mouse_x,&mouse->real_mouse_y);
     if (e.type == SDL_MOUSEBUTTONUP) {
            player->atk = 0;
            mouse->scale = 1;
     }
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            player->atk = 1;
            mouse->scale = 1.2;
        }
}


void Game::doKeyBoard()
{
                //MOVE
    if (e.type == SDL_KEYDOWN)
    switch (e.key.keysym.sym)
    {
        case SDLK_w: player->up = 1; break;
        case SDLK_s: player->down = 1; break;
        case SDLK_a: player->left = 1; break;
        case SDLK_d: player->right = 1;break;
                        //case SDLK_SPACE: pause = true; break;
    }
    if (e.type == SDL_KEYUP)
    switch (e.key.keysym.sym)
    {
        case SDLK_w: player->up = 0; break;
        case SDLK_s: player->down = 0; break;
        case SDLK_a: player->left = 0; break;
        case SDLK_d: player->right = 0; break;
                    //case SDLK_SPACE: pause = false; break;
    }
}


//UPDATE
void Game::updateEnemy()
{
    //spawn
    if (currentTime % enemy_melee_spawntime == 0) {
            spawnEnemyMelee(enemy_melee_list,player,gMap);
    }

    if (currentTime % enemy_ranged_spawntime == 0)
    {
        spawnEnemyRanged(enemy_ranged_list,player,gMap);
    }
    //check all enemies
    for (auto prop = enemy_melee_list.begin(); prop != enemy_melee_list.end();)
    {
       prop->update(enemy_melee_list,player);
       if (prop->alive ==  false)
       {
           prop = enemy_melee_list.erase(prop);
       }else{
            ++prop;
       }
    }
    for (auto prop = enemy_ranged_list.begin(); prop != enemy_ranged_list.end();)
    {
       prop->update(enemy_ranged_list,player);
       if (prop->alive ==  false)
       {
           prop = enemy_ranged_list.erase(prop);
       }else{
            ++prop;
       }
    }
}

void Game::update()
{
    if (!pause)
    {
        updateEnemy();

        //UPDATE PLAYER
        player->update(camera,mouse,gMap);

        if (player->alive == false) gameOver = true;

        //update score;s
        score_word->loadFromRenderedText(convertIntToString(currentTime) ,score_word->color,renderer);
    }
    gMap->updateMap();
       //MOUSE
    mouse->updateMouse(camera);

}

void Game::drawButtons()
{
    if (!pause)
    {
        Ing_Button[ING_PAUSE]->drawButton(SCREEN_WIDTH - ING_BUT_W, 0 ,
                                          ING_BUT_W, ING_BUT_H);
    }
    else{
        SDL_RenderClear(renderer);
        for (int i = ING_RESUME; i < ING_TOTAL; i++)
            {
                Ing_Button[i]->drawButton(SCREEN_WIDTH/2 - BUTTON_WIDTH/2,
                                     -120 + BUTTON_HEIGHT * 1.2 * i,
                                     BUTTON_WIDTH, BUTTON_HEIGHT);
            }
    }
}


void Game::drawEnemy()
{
    SDL_Rect cur;
    for (EnemyMeleeProp& x: enemy_melee_list)
    {
        if (x.health > 0)
        {
            cur = {(x.now /DELAY) * 51, x.st * 51,51,51};
            enemy_melee->angle = x.angle;
            enemy_melee->draw(&cur,x.x,x.y,50,50,1,camera);
        }else{
            cur = {x.now/DELAY * 48,0,48,48};
            explosion->draw(&cur,x.x,x.y,60,60,1,camera);
        }
    }
    for (EnemyRangedProp& x: enemy_ranged_list)
    {
        if (x.health > 0)
        {
            cur = {(x.now /DELAY) * 51, x.st * 51,51,51};
            enemy_ranged->angle = x.angle;
            enemy_ranged->draw(&cur,x.x,x.y,50,50,1,camera);
            for (FighterProp& bul:x.E_bullets)
            {
                cur = {(bul.now)/5 * 32, 0, 32, 32};
                e_bullet->draw(&cur, bul.x,bul.x,50,50,1,camera);
            }
        }else{
            cur = {x.now/DELAY * 48,0,48,48};
            explosion->draw(&cur,x.x,x.y,60,60,1,camera);
        }
    }
}

void Game::drawPlayer()
{
    player->drawPlayer(camera);
}
void Game::drawMap()
{
    gMap->drawMap(camera);
}

void Game::drawPoint()
{
    player->drawHealthBar();
    score_word->drawWord();
    SDL_DestroyTexture(score_word->texture);
}

void Game::drawMouse()
{
    SDL_Rect c = {mouse->now/8 * 30,0,30,30};
    mouse->draw(&c,camera,1);
}

void Game::render()
{
    SDL_RenderClear(renderer);

    if (!pause){
        drawMap();
        drawPlayer();
        drawEnemy();
        drawPoint();
    }
    drawButtons();
    drawMouse();

    SDL_RenderPresent(renderer);
}

/*******************************************************/

                //////loop/////
int Game::GameLoop()
{
    while (!gameOver)
    {
        Uint32 startFrame = SDL_GetTicks();

        if (Mix_PlayingMusic() == 0)
        {
            Mix_PlayMusic(bgMusic,0);
        }

        int a = handleEvent();

        if (a != NORMAL) return a;

        update();

        render();

        Uint32 endFrame = SDL_GetTicks();

        int realDelay = endFrame - startFrame;


        if (realDelay < frameDelay)
        {
            SDL_Delay(frameDelay - realDelay);
        }

        if (!pause) currentTime++;
    }
    return NORMAL;
}

/*******************************************************/

//clear
void Game::clearGame()
{
    enemy_melee_list.clear();
    enemy_ranged_list.clear();
    player->p_bullets.clear();
}
