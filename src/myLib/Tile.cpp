#include "../myLibHeaders/Tile.hpp"
#include <cstddef>
#include<cstdlib>
#include <iostream>
#include <string>

Tile::Tile(int x, int y): state(Hide), posX(x), posY(y), spriteValue(Empty)
{
    setValue(rand() % 28);
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

void Tile::setValue(int newValue)
{
    spriteValue = (caseSpriteValue)newValue;
}

void Tile::setState(int newState)
{

}

void Tile::setPosX()
{

}

void Tile::setPosY()
{

}

void Tile::test()
{

}

