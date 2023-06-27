#include "sound_effect.hpp"
#include<unistd.h>


int main() 
{
    using namespace arkanoid;
    SoundEffects sounds{};
    while(true)
    {
        sounds.playBreakBrick();
        sleep(4);
    }
}