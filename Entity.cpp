#include "Entity.h"

float getAngleGlobal(const float& x1, const float& y1,const float& x2, const float& y2)
{
    return atan2(y1 - y2, x1 - x2) + PI;
}

float getDistance(const float& x1, const float& y1, const float& x2, const float& y2)
{
    return sqrt(pow(x1-x2,2) + pow(y1-y2,2));
}


SDL_Texture* loadTexture(const string& path, SDL_Renderer* renderer )
{
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
    if ( loadedSurface == nullptr )
        cerr << "Unable to load image " << path << " SDL_image Error: "
             << IMG_GetError() << endl;
    else {
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == nullptr )
            cerr << "Unable to create texture from " << path << " SDL Error: "
                 << SDL_GetError() << endl;
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}

///////////////////////ENTITY///////////////////////


Entity::Entity()
{}


Entity::Entity(SDL_Renderer* _renderer, const string& path, const int& _x, const int& _y)
{
    renderer = _renderer;
    x = _x, y = _y;
    loadEntity(path);
}

            /////load image for entity
void Entity::loadEntity(const string& path)
{
    texture = loadTexture(path,renderer);
    SDL_QueryTexture(texture,NULL,NULL,&w,&h);
}

float Entity::getAngle(Entity* temp)
{
    return getAngleGlobal(x, y, temp->x, temp->y);
}

                ///////draw entity
void Entity::draw(SDL_Rect* clip,SDL_Renderer* renderer,const SDL_Point& camera, int atCenter)
{
    if (clip != NULL)
    {
        w = clip->w;
        h = clip->h;
    }

    SDL_Rect renderQuad = { int(x - w/2 * scale * atCenter) - camera.x,
                            int(y - h/2 * scale * atCenter) - camera.y,
                            int(scale * w),
                            int(scale * h)
                            };

    //Render to screen
    SDL_RenderCopyEx(renderer, texture, clip, &renderQuad,
                                    angle * 180 / PI,NULL, SDL_FLIP_NONE);
}

void Entity::draw(SDL_Rect* clip, const int& _x,const int& _y, const int& _w, const int& _h,
                  SDL_Renderer* renderer, int atCenter, const SDL_Point& camera)
{
    SDL_Rect des = {    _x  -  _w/2 * scale *  atCenter - camera.x,
                        _y  -  _h/2 * scale * atCenter - camera.y,
                        _w * scale,
                        _h * scale
                    };
    SDL_RenderCopyEx(renderer, texture, clip, &des,
                                    angle * 180 / PI,NULL, SDL_FLIP_NONE);
}


/****************************************************/

    //Clean
void clean(Entity* entity, bool del)
{
    entity->w = 0;
    entity->h = 0;
    entity->x = 0;
    entity->y = 0;

    if (del) {
            SDL_DestroyTexture(entity->texture);
            delete entity;
    }

    entity = NULL;
}

////////////////////////////////////BUTTON////////////////////////
Button::Button(SDL_Renderer* _renderer, const string& path)
{
    renderer = _renderer;
    loadEntity(path);
}



bool Button::beChosen(const int& _x,const int& _y, const int& _w, const int& _h)
{
    if ( _x >= x && _x <= x + _w)
        if (_y >= y && _y <= y + _h)
        {
            now = 1;
            scale = 1.1;
            return true;
        }

    now = 0;
    scale = 1;
    return false;
}


void Button::drawButton(const int& _x,const int& _y, const int& _w, const int& _h, SDL_Renderer* renderer)
{
    this->x = _x;
    this->y = _y;

    SDL_Rect selected = {now * w/2, 0, w/2, h};

    draw(&selected,_x,_y,_w,_h,renderer,0);
}


////////////////////////MOUSE AND WORDS////////////////
Mouse::Mouse(SDL_Renderer* _renderer, const string& path)
{
    renderer = _renderer;
    loadEntity(path);
}


    //MOUSE
void Mouse::updateMouse(SDL_Point& camera)
{
    x = camera.x + real_mouse_x;
    y = camera.y + real_mouse_y;
    now = (now + 1)%16;
}

////////////////WRITE WORDS//////////////////

Word::Word(SDL_Renderer* renderer)
{
    this->renderer = renderer;
}

void Word::loadFromRenderedText(string textureText, SDL_Color textColor, SDL_Renderer* renderer)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid( font, textureText.c_str(), textColor );
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




