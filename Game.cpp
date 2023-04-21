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
    initMap(txt_map);
    initPlayer();
    initEnemy();
    initMouse();
    initSoundGame();
    initFont();
    initIng();
}


void Game::initPlayer()
{
    player = new Player(renderer);

    player->loadEntity(FILE_ENTITY_IMAGE[IMG_PLAYER],renderer);

    if (player == nullptr) cout << "Khong tai dc hinh anh cua player\n";

    //load sound
    player->attack = Mix_LoadWAV(snd_player_shoot);
    player->isHitted = Mix_LoadWAV(snd_player_hitted);

    if (player->attack == NULL||player->isHitted == NULL)
    {
        cerr << "Failed to load player shoot or player is hitted sound effect! SDL_mixer Error: "
        << Mix_GetError();
        exit(1);
    }

    //WEAPON
    tempBullet = new Bullet(renderer);

    tempBullet->loadEntity(FILE_ENTITY_IMAGE[IMG_BULLET],renderer);

    if (tempBullet == NULL) cout << "Khong tai dc hinh anh cua player bullet\n";
}

void Game::initEnemy()
{
    tempEnemyMelee = new EnemyMelee(renderer);
    tempEnemyMelee->loadEntity(FILE_ENTITY_IMAGE[IMG_ENEMY_MELEE],renderer);
    if (tempEnemyMelee == nullptr) cout << "Khong tai dc anh cua Enemy Melee\n";
}


void Game::initMap(string path)
{
    gMap.dirt = loadTexture("image/map/dirt.png",renderer);
    gMap.wall = loadTexture("image/map/wall.png",renderer);
    gMap.loadMap(path);
}



void Game::initMouse()
{
    mouse = new Mouse;
    mouse->loadEntity(FILE_ENTITY_IMAGE[IMG_MOUSE_ING],renderer);
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
}

/****************************************************/

void Game::initFont()
{
    score_word.font = TTF_OpenFont(gameFont,50);
    if( score_word.font == nullptr )
    {
        cout << "Failed to load lazy font! SDL_ttf Error: " << TTF_GetError() << endl;
    }
    score_word.color = {RGB[3*BLACK], RGB[3*BLACK+1], RGB[3*BLACK+2]};

    score_word.x = 0;
    score_word.y = 25;
}

/****************************************************/

void Game::initIng()
{
    //load button
    Ing_Button[ING_PAUSE].loadEntity(file_ing_but[ING_PAUSE],renderer);

    for (int i = ING_RESUME; i < ING_TOTAL; i++)
    {
        Ing_Button[i].loadEntity(file_ing_but[i],renderer);
    }
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
    player->health = PLAYER_MAX_HP;
    player->alive = true;

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
            if (Ing_Button[i].beChosen(mouse->x - camera.x,
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
//    if (currentTime%spawnTime[ENEMY_MELEE] == 0) {
//            spawnEnemyMelee(tempEnemyMelee,enemy_list,player,gMap,renderer);
//    }

    //check all enemies
    for (unsigned i = 0; i < enemy_list.size();i++)
    {
        enemy_list[i]->update(camera,player,gMap);
        if (!enemy_list[i]->alive)
        {
            Mix_PlayChannel(SND_ENEMY_DIE,enemy_die,0);

            clean(enemy_list[i],0);

            delete enemy_list[i];

            enemy_list.erase(enemy_list.begin()+i);

            i--;
        }
    }
}

/*******************************************************/

void Game::update()
{
    //MOUSE
    mouse->updateMouse(camera);

    //UPDATE ENEMY

    if (!pause)
    {
        updateEnemy();

        //UPDATE PLAYER
        player->update(camera,mouse,gMap);

        if (player->alive == false) gameOver = true;

        //update score;s
        score_word.loadFromRenderedText(convertIntToString(currentTime) ,score_word.color,renderer);
    }
}

/******************************************************/

void Game::render()
{
    //clear screen
    SDL_RenderClear(renderer);

    //draw map
    gMap.drawMap(renderer,camera);

    //draw player and his bullet
    player->drawPlayer(renderer,camera);

    for (unsigned i = 0; i < enemy_list.size();i++)
    {
        enemy_list[i]->drawEnemy(renderer,camera);
    }

       //draw score
    score_word.draw(NULL,0,0,score_word.w,score_word.h,renderer);
    SDL_DestroyTexture(score_word.texture);

    //load pause button
    if (!pause)
    {
        Ing_Button[ING_PAUSE].drawButton(SCREEN_WIDTH - ING_BUT_W, 0 ,
                                          ING_BUT_W, ING_BUT_H,renderer);
    }
    else{
        SDL_RenderClear(renderer);
        for (int i = ING_RESUME; i < ING_TOTAL; i++)
            {
                Ing_Button[i].drawButton(SCREEN_WIDTH/2 - BUTTON_WIDTH/2,
                                     -120 + BUTTON_HEIGHT * 1.2 * i,
                                     BUTTON_WIDTH, BUTTON_HEIGHT, renderer);
            }
    }



    //draw mouse
    mouse->draw(NULL,renderer,camera,1);

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

    //clear enemy
    for (unsigned i = 0; i < enemy_list.size(); i++) clean(enemy_list[i],0);

    //clear window, renderer
//    window = nullptr;
//    renderer = nullptr;
    cout << "\end a stage\n";
}
