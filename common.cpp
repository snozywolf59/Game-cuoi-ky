#include "common.h"

void logSDLError(std::ostream& os,const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

//******************IMG

//******************TTF
string convertIntToString(const int& x)
{
    stringstream result;

    result << x;

    return result.str();
}
//******************MIXER
