#pragma once

#include "Entity.h"
#include "Resource.h"
#include "Game.h"

const int TOP_SCORE = 5;

const string file_score = "text/HighScore.txt";

struct Name{
    string name;
    unsigned int point;

    Name(const string& _name = "NoName", const int& _point = 0);
};

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

    void render();

private:
    Name top[TOP_SCORE];
    Word* topScore[TOP_SCORE];
    Resource* res;
};
