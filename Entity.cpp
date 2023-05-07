#include "Entity.h"

static int* a;

float getAngleGlobal(const float& x1, const float& y1,const float& x2, const float& y2)
{
    return atan2(y1 - y2, x1 - x2) + PI;
}

float getDistance(const float& x1, const float& y1, const float& x2, const float& y2)
{
    return sqrtf(pow(x1-x2,2) + pow(y1-y2,2));
}

float getSqDis(const float& x1, const float& y1, const float& x2, const float& y2)
{
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
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
void Entity::draw(SDL_Rect* clip,const Vec2f& camera, int atCenter)
{
    if (clip != NULL)
    {
        w = clip->w * scale;
        h = clip->h * scale;
    }

    SDL_Rect renderQuad = { int(x - w/2 * scale * atCenter - camera.x),
                            int(y - h/2 * scale * atCenter - camera.y),
                            int(scale * w),
                            int(scale * h)
                            };

    //Render to screen
    SDL_RenderCopyEx(renderer, texture, clip, &renderQuad,
                                    angle * 180 / PI,NULL, SDL_FLIP_NONE);
}

void Entity::draw(SDL_Rect* clip, const int& _x, const int& _y, const Vec2f& camera, int atCenter)
{
    SDL_FRect des = {    _x  -  w/2 * scale *  atCenter - camera.x,
                        _y  -  h/2 * scale * atCenter - camera.y,
                        w * scale,
                        h * scale
                    };
    SDL_RenderCopyExF(renderer, texture, clip, &des,
                                    angle * 180 / PI,NULL, SDL_FLIP_NONE);
}

void Entity::draw(SDL_Rect* clip, const int& _x,const int& _y, const int& _w, const int& _h,
                   int atCenter, const Vec2f& camera)
{
    SDL_FRect des = {    _x  -  _w/2 * scale *  atCenter - camera.x,
                        _y  -  _h/2 * scale * atCenter - camera.y,
                        _w * scale,
                        _h * scale
                    };
    SDL_RenderCopyExF(renderer, texture, clip, &des,
                                    angle * 180 / PI,NULL, SDL_FLIP_NONE);
}

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

////////////////////////MOUSE AND WORDS////////////////


