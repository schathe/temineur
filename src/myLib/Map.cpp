#include "../myLibHeaders/Map.hpp"
#include <iostream>
#include <ostream>
#include <vector>

Map::Map()
{
    for (int i = 0; i < mapSizeY; i++)
    {
        std::vector<Tile> ListX;
    
        for (int j = 0; j < mapSizeX; j++)
        {
            ListX.push_back(Tile(mapSizeX * 32, mapSizeY * 32));
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