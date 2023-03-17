#include "../myLibHeaders/Map.hpp"
#include <iostream>
#include <ostream>
#include <vector>

Map::Map()
{

}

Map::Map(float spriteScaleValue, int paddingX, int paddingY)
{
    for (int i = 0; i < mapSizeY; i++)
    {
        std::vector<Tile> ListX;
    
        for (int j = 0; j < mapSizeX; j++)
        {
            ListX.push_back(Tile(((float)paddingX/2 + j * 32 * spriteScaleValue), ((float)paddingY/2 + i * 32 * spriteScaleValue)));
            // std::cout << "state: " << ListX[j].getState() << " value: " << ListX[j].getValue() << std::endl;
        }
        tileList.push_back(ListX);
    }
}

Map::~Map()
{

}

void Map::show()
{
    for (int i = 0; i < tileList.size(); i++)
    {
        for (int j = 0; j < tileList[i].size(); j++)
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