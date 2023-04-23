#include "Game.h"


//GAME INIT

Game::Game(SDL_Renderer* gRenderer){
    renderer = gRenderer;

    if (renderer == NULL)
    {
        cout << "LOI RENDERER CUA STAGE";
        exit(1);
    }
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
    logSuccess("enemy");
}


void Game::initMap(string path)
{
    gMap = new Map();
    gMap->dirt = loadTexture("image/map/dirt.png",renderer);
    gMap->wall = loadTexture("image/map/wall.png",renderer);
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
    score_word = new Word(renderer);
    score_word->font = TTF_OpenFont(gameFont.c_str(),50);
    if( score_word->font == nullptr )
    {
        cout << "Failed to load game font! SDL_ttf Error: " << TTF_GetError() << endl;
    }
    score_word->color = {255, 255, 255};

    score_word->x = 0;
    score_word->y = 25;
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
    camera.x = (MAP_SIZE/4-1)*BLOCK_SIZE - BLOCK_SIZE/2;
    camera.y = (MAP_SIZE/2-1)*BLOCK_SIZE - BLOCK_SIZE;

    gameOver = false;
    pause = false;

    //set time
    currentTime = 0;

    //score

    score = 0;

    //player
    player->initStat();
    player->initPos();

    //enemy
    enemy_list.clear();
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
        case SDLK_f: player->atk = 1; break;
                        //case SDLK_SPACE: pause = true; break;
    }
    if (e.type == SDL_KEYUP)
    switch (e.key.keysym.sym)
    {
        case SDLK_w: player->up = 0; break;
        case SDLK_s: player->down = 0; break;
        case SDLK_a: player->left = 0; break;
        case SDLK_d: player->right = 0; break;
        case SDLK_f: player->atk = 0; break;
                    //case SDLK_SPACE: pause = false; break;
    }
}


/****************************************************/

//UPDATE
void Game::updateEnemy()
{
    //spawn
    if (currentTime % spawnTime[ENEMY_MELEE] == 0) {
            spawnEnemyMelee(enemy_list,player,gMap);
    }
    //check all enemies
    for (auto prop = enemy_list.begin(); prop != enemy_list.end();)
    {
       prop->update(enemy_list,player);
       if (prop->alive ==  false)
       {
           prop = enemy_list.erase(prop);
       }else{
            ++prop;
       }
    }
}

/*******************************************************/

void Game::update()
{
    //MOUSE
    mouse->updateMouse(camera);


    if (!pause)
    {
        updateEnemy();

        //UPDATE PLAYER
        player->update(camera,mouse,gMap);

        if (player->alive == false) gameOver = true;

        //update score;s
        score_word->loadFromRenderedText(convertIntToString(currentTime) ,score_word->color,renderer);
    }
}

/******************************************************/
void Game::drawButtons()
{
    if (!pause)
    {
        Ing_Button[ING_PAUSE]->drawButton(SCREEN_WIDTH - ING_BUT_W, 0 ,
                                          ING_BUT_W, ING_BUT_H,renderer);
    }
    else{
        SDL_RenderClear(renderer);
        for (int i = ING_RESUME; i < ING_TOTAL; i++)
            {
                Ing_Button[i]->drawButton(SCREEN_WIDTH/2 - BUTTON_WIDTH/2,
                                     -120 + BUTTON_HEIGHT * 1.2 * i,
                                     BUTTON_WIDTH, BUTTON_HEIGHT, renderer);
            }
    }
}


void Game::drawEnemy()
{
    for (EnemyMeleeProp& x: enemy_list)
    {
        SDL_Rect cur = {(x.now /DELAY) * ENEMY_MELEE_BLOCK_SIZE, 0,ENEMY_MELEE_BLOCK_SIZE,ENEMY_MELEE_BLOCK_SIZE};
        enemy_melee->angle = x.angle;
        enemy_melee->draw(&cur,x.x,x.y,50,50,renderer,1,camera);
    }
}

void Game::drawPlayer()
{
    player->drawPlayer(renderer,camera);
}
void Game::drawMap()
{
    gMap->drawMap(renderer,camera);
}

void Game::drawPoint()
{
    score_word->draw(NULL,0,0,score_word->w,score_word->h,renderer);
    SDL_DestroyTexture(score_word->texture);
}

void Game::drawMouse()
{
    SDL_Rect c = {mouse->now/8 * 30,0,30,30};
    mouse->draw(&c,renderer,camera,1);
}




void Game::render()
{
    SDL_RenderClear(renderer);

    drawMap();
    drawPlayer();
    drawEnemy();
    drawButtons();
    drawPoint();
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
    //clear player
    player->p_bullets.clear();

    //clear window, renderer
//    window = nullptr;
//    renderer = nullptr;
    cout << "\end a stage\n";
}
