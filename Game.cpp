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
    sub_score = 0;

    //player
    player->initStat();
    player->initPos();
    player->x += camera.x;
    player->y += camera.y;
    //enemy
    enemy_list.clear();
    E_bullets.clear();

    for (int i = 0 ; i < ING_TOTAL; i++){
        SDL_SetTextureAlphaMod(res->But_InG[i]->texture, 255);
    }
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
        case SDLK_q: player->skl2 = 1; break;
        case SDLK_SPACE: player->skl1 = 1; break;
    }
    if (e.type == SDL_KEYUP)
    switch (e.key.keysym.sym)
    {
        case SDLK_w: player->up = 0; break;
        case SDLK_s: player->down = 0; break;
        case SDLK_a: player->left = 0; break;
        case SDLK_d: player->right = 0;break;
        case SDLK_q: player->skl2 = 0; break;
        case SDLK_SPACE: player->skl1 = 0; break;
    }
}

void Game::updateEBullets()
{
    for (auto b = E_bullets.begin(); b != E_bullets.end();)
    {
        b->update();
        b->now++;
        bool alive = true;
        if (gMap->getRadius(b->y/BLOCK_SIZE, b->x/BLOCK_SIZE) > 0) alive = false;
        else if (getDistance(b->x,b->y,player->x,player->y) < R_bullet + R_player)
        {
            player->getDmg(b->dmg);
            alive = false;
        }
        else if (b->s > E_RANGE[ENEMY_RANGED]) {
            alive = false;
        }
        if (alive) ++b;
        else b = E_bullets.erase(b);
    }
}

//UPDATE
void Game::updateEnemy()
{
    //spawn
    if (currentTime % E_SPAWN_T[ENEMY_MELEE] == 0)
        if (enemy_list.size() <= 7 + currentTime/800)
            spawnEnemyMelee(currentTime, enemy_list,player,gMap);

    if (currentTime % E_SPAWN_T[ENEMY_RANGED] == 0)
        if (enemy_list.size() <= 7 + currentTime/1000)
            spawnEnemyRanged(currentTime, enemy_list,player,gMap);
    //check all enemies
    for (auto prop = enemy_list.begin(); prop != enemy_list.end();)
    {
       prop->update(enemy_list,player,E_bullets,gMap);
       if (prop->alive ==  false)
       {
           spawnItem(items,prop->x,prop->y,currentTime);
           sub_score += 3 + prop->type;
           prop = enemy_list.erase(prop);
           Mix_PlayChannel(SND_ENEMY_DIE, res->enemy_die, 0);
       }else{
            ++prop;
       }
    }
}

void Game::updateItems()
{
    for (auto it = items.begin(); it != items.end();){
        it->update();
        player->getItem(*it,sub_score);
        if (it->last == 0) it = items.erase(it);
        else it++;
    }
}


void Game::update()
{
    if (!pause)
    {
        updateItems();

        updateEBullets();

        updateEnemy();

        //UPDATE PLAYER
        player->update(camera,res->InGame_Mouse,gMap,currentTime);

        if (player->alive == false) gameOver = true;

        //update score;
        score = sub_score + currentTime/500;
        if (score_word->texture != NULL) SDL_DestroyTexture(score_word->texture);
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
        for (int i = ING_RESUME; i < ING_TOTAL; i++)
            {
                res->But_InG[i]->drawButton(SCREEN_WIDTH/2 - BUTTON_WIDTH/2,
                                     20 + BUTTON_HEIGHT * 1.2 * i,
                                     BUTTON_WIDTH, BUTTON_HEIGHT);
            }
    }
}

void Game::drawEnemy()
{
    SDL_Rect cur;
    for (EnemyProp& x: enemy_list)
    {
        if (x.health > 0)
        {
            cur = {(x.now /DELAY) * 51, x.st * 51,51,51};
            if (x.type == ENEMY_MELEE){
                res->enemy_melee->angle = x.angle;
                res->enemy_melee->draw(&cur,x.x,x.y,50,50,1,camera);
            }
            if (x.type == ENEMY_RANGED){
                res->enemy_ranged->angle = x.angle;
                res->enemy_ranged->draw(&cur,x.x,x.y,50,50,1,camera);
            }
        }else{
            cur = {x.now/DELAY * 48,0,48,48};
            res->explosion->draw(&cur,x.x,x.y,60,60,1,camera);
        }
    }
}

void Game::drawEBullets()
{
    SDL_Rect cur;
    for (BulletProp& bul:E_bullets)
    {
        cur = {((bul.now/5)%4) * 32, 0, 32, 32};
        res->e_bullet->angle = bul.angle;
        res->e_bullet->draw(&cur, bul.x,bul.y,50,50,1,camera);
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
void Game::drawItems()
{
    SDL_Rect t;
    for (Item& it: items){
        t = {((it.now/5) % 6) * 16, 0, 16, 16};
        res->Items[it.type]->draw(&t,it.x,it.y,25,25,1,camera);
    }
}

void Game::drawPoint()
{
    player->drawHealthBar();
    score_word->drawWord();
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
        drawEBullets();
        drawItems();
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
    enemy_list.clear();
    E_bullets.clear();
    player->p_bullets.clear();
}
