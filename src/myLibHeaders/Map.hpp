#pragma once

#include "Tile.hpp"
class Map
{
    private:
        // Defaults sizes: 10/10-10 15/13-40 30/16-99 (X/Y-Bombs)
        int mapSizeX = 15;
        int mapSizeY = 13;
        int bombNumber = 40;

    public:
        std::vector<std::vector<Tile>> tileList;

        Map();
        ~Map();

        void show();
};