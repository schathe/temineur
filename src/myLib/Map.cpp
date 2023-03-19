/**
 * Creation date:   2022-12-12
 * Creator:         Schathe (Théo Schaffner)
 * Description:     This file is made to contain all the functions and the modification of the map layer.
 * Version:         V-1.0
*/

#include "../myLibHeaders/Map.hpp"
#include <cstdlib>

Map::Map(float spriteScaleValue, int paddingX, int paddingY)
{
    for (int i = 0; i < mapSizeY; i++)
    {
        std::vector<Tile> ListX;
    
        for (int j = 0; j < mapSizeX; j++)
        {
            ListX.push_back(Tile(((float)paddingX/2 + j * 32 * spriteScaleValue), ((float)paddingY/2 + i * 32 * spriteScaleValue)));
        }

        tileList.push_back(ListX);
    }
}

Map::~Map()
{
    
}

void Map::drawBombsPositions()
{
    for (int i = 0; i < bombNumber; i++)
    {
        short posX = rand() % mapSizeX;
        short posY = rand() % mapSizeY;

        if (!this->tileList[posY][posX].isBomb())
        {
            this->tileList[posY][posX].setValue(Bomb);
        }
        else
        {
            i--;
        }
    }
}

void Map::show()
{
    for (unsigned long i = 0; i < tileList.size(); i++)
    {
        for (unsigned long j = 0; j < tileList[i].size(); j++)
        {
            std::cout << tileList[i][j].getSpriteValue() <<  ( tileList[i][j].getSpriteValue() > 9 ?  " " : "  ") ;
        }
        std::cout << std::endl;
    }
}

void Map::reset()
{
    int count = tileList.size();
    for (int i = 0; i < count; i++)
    {
        tileList.pop_back();
    }
}

void Map::test()
{
    std::cout << "bombNumber: " << bombNumber << std::endl;
    std::cout << "mapSizeX: " << mapSizeX << std::endl;
    std::cout << "mapSizeY: " << mapSizeY << std::endl;
    std::cout << "tileList: " << std::endl;
    show();
}