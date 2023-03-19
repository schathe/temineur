/**
 * Creation date:   2022-12-12
 * Creator:         Schathe (Théo Schaffner)
 * Description:     This file is used to put the declarations of the function and the variables of the map.cpp.
 * Version:         V-1.0
*/

#pragma once

#include "Tile.hpp"

class Map
{
    private:

    public:
        std::vector<std::vector<Tile>> tileList;
        // Defaults sizes: 10/10-10 15/13-40 30/16-99 (X/Y-Bombs)
        int bombNumber = 40;
        int mapSizeX = 15;
        int mapSizeY = 13;

        Map(float spriteScaleValue = 3.3, int paddingX = 50, int paddingY = 200);
        ~Map();

        void drawBombsPositions();

        void show();
        void reset();

        void test();
};