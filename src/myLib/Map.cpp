/**
 * @file Map.cpp
 * @author Schathe (Théo Schaffner)
 * @brief This file is made to contain all the functions and the modification of the map layer.
 * @date 2022-12-12
 * 
 * @copyright Copyright (c) 2023
 */

#include "../myLibHeaders/Map.hpp"
#include <cstdlib>
#include <iostream>

Map::Map(float spriteScaleValue, int paddingX, int paddingY)
{
    // Start the list with the Y to have a 2D representation of the list
    for (int i = 0; i < mapSizeY; i++)
    {
        std::vector<Tile> ListX;
    
        for (int j = 0; j < mapSizeX; j++)
        {
            // Push on the ListX a Tile with the correct position on the map
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

        // If there already is a bomb on the position drawed, decreased the counter to redraw it
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

    // Go through all the 2D tileList by passing on every X Tile then every Y Tile
    for (int posX = 0; posX < mapSizeX; posX++)
    {
        for (int posY = 0; posY < mapSizeY; posY++)
        {
            // If the current Tile is not a bomb, go check the 8 Tile arround the current Tile and increment
            // the case value for each bomb on neightboors Tile
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

                // If the count is at zero it's a bomb Tile so no need to modify the case value or reset count
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
    // Take the current size of the map and set it to the next value
    if (mapSizeX == 15)
    {
        this->mapSizeX = 30;
        this->mapSizeY = 16;
        this->bombNumber = 99;
    }
    else if (mapSizeX == 30)
    {
        this->mapSizeX = 10;
        this->mapSizeY = 10;
        this->bombNumber = 10;
    }
    else if (mapSizeX == 10)
    {
        this->mapSizeX = 15;
        this->mapSizeY = 13;
        this->bombNumber = 40;
    }
}

void Map::show()
{
    // Got through all Tile to display them one by one
    for (unsigned long i = 0; i < tileList.size(); i++)
    {
        for (unsigned long j = 0; j < tileList[i].size(); j++)
        {
            std::cout << tileList[i][j].getSpriteValue() <<  (tileList[i][j].getSpriteValue() > 9 ?  " " : "  ") ;
        }
        std::cout << std::endl;
    }
}

void Map::reset()
{
    for (int i = 0; i < (int)(tileList.size()); i++)
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