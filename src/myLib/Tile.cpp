/**
 * Creation date:   2022-12-12
 * Creator:         Schathe (Théo Schaffner)
 * Description:     This file is made to contain the attitudes of the tiles of the game.
 * Version:         V-1.0
*/

#include "../myLibHeaders/Tile.hpp"

Tile::Tile(int x, int y): state(Hide), spriteValue(Empty), posX(x), posY(y)
{
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

bool Tile::isBomb()
{
    bool isBomb = false;

    if (spriteValue == Bomb)
    {
        return true;
    }
    
    return isBomb;
}

void Tile::setValue(caseSpriteValue newValue)
{
    spriteValue = (caseSpriteValue)newValue;
}

void Tile::setState(int newState)
{
    state = (caseState)newState;
}

void Tile::test()
{
    std::cout << "state: " << state << std:: endl;
    std::cout << "caseSpriteValue: " << spriteValue << std:: endl;
    std::cout << "posX: " << posX << std:: endl;
    std::cout << "posY: " << posY << std:: endl;
}

