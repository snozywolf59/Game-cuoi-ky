#include "Game.h"



//GAME INIT

Game::Game(Resource* _res){
    res = _res;

    choose = -1;
    old_choose = -1;

    initStage();
    initPlayer();
    score_word = new Word(0,0,res->renderer,res->font,res->pad);
}

Game::~Game(){}
            //INIT

void Game::initStage()
{
    logSuccess("loading stage");
    initPlayer();
    gMap = new Map(res->renderer);
    gMap->loadMap(txt_map);
    logSuccess("stage");
}


void Game::initPlayer()
{
    player = new Player(res->renderer);
    logSuccess("Player");
}

unsigned int Game::getScore()
{
    return score;
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
    bool inButton = false;
    old_choose = choose;
    for (int i = 0; i < ING_TOTAL; i++)
    {
        int tw = (i == 0 ? ING_BUT_W:BUTTON_WIDTH);
        int th = (i == 0 ? ING_BUT_H:BUTTON_HEIGHT);
        if (res->But_InG[i]->beChosen(res->InGame_Mouse->x - camera.x,res->InGame_Mouse->y - camera.y, tw, th))
        {
            if (!pause && i == ING_PAUSE)
            {
                inButton = true, choose = i;
                if( e.type == SDL_MOUSEBUTTONDOWN) pause = true;
                continue;
            }

            if (pause) {
                inButton = true, choose = i;
                if (e.type == SDL_MOUSEBUTTONDOWN)
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
        continue;
    }
    if (!inButton) choose = -1;
    return NORMAL;
}

void Game::doMouse()
{
     SDL_GetMouseState(&res->InGame_Mouse->real_mouse_x,&res->InGame_Mouse->real_mouse_y);
     if (e.type == SDL_MOUSEBUTTONUP) {
            if (e.button.button ==  SDL_BUTTON_LEFT) player->atk = 0;
            res->InGame_Mouse->scale = 1;
     }
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            if (e.button.button ==  SDL_BUTTON_LEFT) player->atk = 1;
            res->InGame_Mouse->scale = 1.2;
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
           sub_score += 3;
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
           sub_score += 3;
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
        player->update(camera,res->InGame_Mouse,gMap);

        if (player->alive == false) gameOver = true;

        //update score;
        score = sub_score + currentTime/500;
        score_word->loadFromRenderedText(convertIntToString(score));
    }

    if (old_choose != choose && choose != -1) Mix_PlayChannel(0,res->But_beChosen,0);
    gMap->updateMap();

    res->InGame_Mouse->updateMouse(camera);
}

void Game::drawButtons()
{
    if (!pause)
    {
        res->But_InG[ING_PAUSE]->drawButton(SCREEN_WIDTH - ING_BUT_W, 0 ,
                                          ING_BUT_W, ING_BUT_H);
    }
    else{
        SDL_RenderClear(res->renderer);
        for (int i = ING_RESUME; i < ING_TOTAL; i++)
            {
                res->But_InG[i]->drawButton(SCREEN_WIDTH/2 - BUTTON_WIDTH/2,
                                     20 + BUTTON_HEIGHT * 1.2 * i,
                                     BUTTON_WIDTH, BUTTON_HEIGHT);
            }
    }
}

void Game::drawEnemyMelee()
{
    SDL_Rect cur;
    for (EnemyMeleeProp& x: enemy_melee_list)
    {
        if (x.health > 0)
        {
            cur = {(x.now /DELAY) * 51, x.st * 51,51,51};
            res->enemy_melee->angle = x.angle;
            res->enemy_melee->draw(&cur,x.x,x.y,50,50,1,camera);
        }else{
            cur = {x.now/DELAY * 48,0,48,48};
            res->explosion->draw(&cur,x.x,x.y,60,60,1,camera);
        }
    }
}

void Game::drawEnemyRanged()
{
    SDL_Rect cur;
    for (EnemyRangedProp& x: enemy_ranged_list)
    {
        if (x.health > 0)
        {
            cur = {(x.now /DELAY) * 51, x.st * 51,51,51};
            res->enemy_ranged->angle = x.angle;
            res->enemy_ranged->draw(&cur,x.x,x.y,50,50,1,camera);
            for (FighterProp& bul:x.E_bullets)
            {
                cur = {((bul.now/8)%4) * 32, 0, 32, 32};
                res->e_bullet->angle = bul.angle;
                res->e_bullet->draw(&cur, bul.x,bul.y,50,50,1,camera);
            }
        }else{
            cur = {x.now/DELAY * 48,0,48,48};
            res->explosion->draw(&cur,x.x,x.y,60,60,1,camera);
        }
    }
}

void Game::drawEnemy()
{
    drawEnemyMelee();
    drawEnemyRanged();
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
    SDL_Rect c = {res->InGame_Mouse->now/8 * 30,0,30,30};
    res->InGame_Mouse->draw(&c,camera,1);
}

void Game::render()
{
    SDL_RenderClear(res->renderer);

    if (!pause){
        drawMap();
        drawPlayer();
        drawEnemy();
        drawPoint();
    }
    drawButtons();
    drawMouse();

    SDL_RenderPresent(res->renderer);
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
            Mix_PlayMusic(res->InG_Music,0);
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
