#include "common.h"

void logSDLError(ostream& os,const string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void logSuccess(const string& name)
{
    cout << "Khoi tao " << name << " thanh cong\n";
}


string convertIntToString(const int& x)
{
    stringstream result;

    result << x;

    return result.str();
}
//******************MIXER
