#include "include/Game.h"

int main(int argc, char** argv)
{
    AbstractGame* game = new Game();
    game->RunMainLoop();
    return 0;
}
