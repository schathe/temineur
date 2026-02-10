/**
 * Creation date:   2022-12-12
 * Creator:         Schathe (Théo Schaffner)
 * Description:     This file is the main of the program, the programm start by here.
 * Version:         V-1.0
*/

#include "src/myLibHeaders/myLib.hpp"

#include <cstdlib>
#include <iostream>

int main()
{
	srand((unsigned) time(NULL));

    Game game;
    game.init();
    game.run();

    return 0;
}

