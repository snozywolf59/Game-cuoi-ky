#pragma once

#include "Entity.h"
#include "Resource.h"
#include "Game.h"

const int TOP_SCORE = 5;

const string file_score = "text/HighScore.txt";

class HighScoreMenu
{
public:
    HighScoreMenu();
    HighScoreMenu(Resource* _res);
    ~HighScoreMenu();

    void read();
    void write();
    int handle();

    bool check(const unsigned int& newS);

    void update(const Name& newScore);
    void updateScore(const Name& newScore);
    void createTexture();
    void deleteTexure();

    string enter_name();

    void render_enter_name(const string& temp);

    void render();

private:
    Name top[TOP_SCORE];
    Word* topScore[TOP_SCORE];
    Resource* res;
    bool maxL;
};
