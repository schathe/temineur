/**
 * Creation date:   2022-12-12
 * Creator:         Schathe (Théo Schaffner)
 * Description:     This file is made to contain all the functions and the modification of the map layer.
 * Version:         V-1.0
*/

#include "../myLibHeaders/Map.hpp"
#include <cstdlib>
#include <iostream>

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

void Map::changeCasesValues()
{
    int count = 0;

    for (int posX = 0; posX < mapSizeX; posX++)
    {
        for (int posY = 0; posY < mapSizeY; posY++)
        {
            if (this->tileList[posY][posX].getSpriteValue() != Bomb)
            {
                for (int x = posX - 1; x <= posX + 1; x++)
                {
                    for (int y = posY -1; y <= posY + 1; y++)
                    {
                        if (y >= 0 && y < mapSizeY && x >= 0 && x < mapSizeX)
                        {
                            if (this->tileList[y][x].getSpriteValue() == Bomb)
                            {
                                count ++;
                            }
                        }
                    }
                }

                if (count != 0)
                {
                    this->tileList[posY][posX].setValue((caseSpriteValue)(count + 2));
                    count = 0;
                }    
            }
        }
    }
}

void Map::changeMapSize()
{
    if (mapSizeX == 15)
    {
        mapSizeX = 30;
        mapSizeY = 16;
        bombNumber = 99;
    }
    else if (mapSizeX == 30)
    {
        mapSizeX = 10;
        mapSizeY = 10;
        bombNumber = 10;
    }
    else if (mapSizeX == 10)
    {
        mapSizeX = 15;
        mapSizeY = 13;
        bombNumber = 40;
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