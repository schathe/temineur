#pragma once

#include "Tile.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
class Map
{
    private:
        // Defaults sizes: 10/10-10 15/13-40 30/16-99 (X/Y-Bombs)
        int bombNumber = 40;

    public:
        std::vector<std::vector<Tile>> tileList;
        int mapSizeX = 15;
        int mapSizeY = 13;

        Map();
        Map(float spriteScaleValue, int paddingX, int paddingY);
        ~Map();

        void show();
        void reset();
};