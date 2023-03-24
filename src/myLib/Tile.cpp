/**
 * @file Tile.cpp
 * @author Schathe (Théo Schaffner)
 * @brief This file is made to contain the attitudes of the tiles of the game.
 * @date 2022-12-12
 * 
 * @copyright Copyright (c) 2023
 */

#include "../myLibHeaders/Tile.hpp"

// (state(Hide) set the state value to Hide... like state = Hide...)
Tile::Tile(int x, int y): state(Hide), spriteValue(Empty), posX(x), posY(y)
{
    // Set the value to empty to prevent bug or something else like wrong value
    setValue(Empty);
}

Tile::~Tile()
{

}

caseState Tile::getState()
{
    return state;
}

caseSpriteValue Tile::getSpriteValue()
{
    return spriteValue;
}

int Tile::getPosX()
{
    return posX;
}

int Tile::getPosY()
{
    return posY;
}

void Tile::setValue(caseSpriteValue newValue)
{
    spriteValue = newValue;
}

void Tile::setState(caseState newState)
{
    state = newState;
}

bool Tile::isBomb()
{
    bool isBomb = false;

    if (spriteValue == Bomb)
    {
        isBomb = true;
    }
    
    return isBomb;
}

void Tile::test()
{
    std::cout << "state: " << state << std:: endl;
    std::cout << "caseSpriteValue: " << spriteValue << std:: endl;
    std::cout << "posX: " << posX << std:: endl;
    std::cout << "posY: " << posY << std:: endl;
}

