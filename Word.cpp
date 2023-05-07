#include "Word.h"

////////////////WRITE WORDS//////////////////

Word::Word(const int& _x, const int& _y, SDL_Renderer* renderer, TTF_Font* gFont, Entity* gPad)
{
    this->renderer = renderer;
    font = gFont;
    pad = gPad;
    color = {255, 255, 255};

    x = _x;
    y = _y;
}

void Word::loadFromRenderedText(const string& textureText)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid( font, textureText.c_str(), color );
    if( textSurface == NULL )
    {
        cerr << "Unable to render text surface! SDL_TTF Error: " << TTF_GetError() << endl;
    }
    else
    {

        //Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if( texture == NULL )
        {
            cerr << "Unable to create texture from rendered text! SDL Error: %" << SDL_GetError() << endl;
        }
        else
        {
            //Get image dimensions
            SDL_QueryTexture(texture,NULL,NULL,&w,&h);
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
}

void Word::drawWord()
{
    SDL_Rect temp = {170 - w , y + 5 , w , h};
    if (pad != NULL) pad->draw(NULL,x,y,180,60);
    SDL_RenderCopy(renderer,texture,NULL,&temp);
}

void Word::drawWord(const int& _x, const int& _y)
{
    SDL_Rect temp = {_x,_y,w,h};
    if (pad != NULL)  pad->draw(NULL,_x,_y,w,h,0);
    SDL_RenderCopy(renderer,texture,NULL,&temp);
}

void Word::drawWord(const int& _x, const int& _y, const int& _w, const int& _h)
{
    SDL_Rect temp = {_x,_y,_w,_h};
    if (pad != NULL) pad->draw(NULL,_x,_y,_w,_h,0);
    SDL_RenderCopy(renderer,texture,NULL,&temp);
}


Name::Name(const string& _name, const unsigned int& _point)
{
    name = _name;
    point = _point;
}
