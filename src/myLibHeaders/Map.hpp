/**
 * @file Map.hpp
 * @author Schathe (Théo Schaffner)
 * @brief This file is used to put the declarations of the function and the variables of the map.cpp.
 * @date 2022-12-12
 *
 * @details The map is the main part of the game, it's used to manage all the tile of the game. The map contain the list
 * of the tiles, the size of the game and the number of bomb on the game.
 * 
 * @copyright Copyright (c) 2023
 */

#pragma once

#include "Tile.hpp"

/**
 * @class Map
 * @brief There are all the componnents of the map class
 */
class Map
{
    private:

    public:
        /* VARIABLES OF THE MAP */

        /**
         * @brief 2D list with the objectif to stock all the Tile placed on their location on the window depending on their map position
         */
        std::vector<std::vector<Tile>> tileList;

        // Defaults sizes: 10/10-10 15/13-40 30/16-99 (X/Y-Bombs)
        int bombNumber = 20;
        int mapSizeX = 15;
        int mapSizeY = 13;


        /**
         * @brief Construct a new Map
         * 
         * @param spriteScaleValue - use a scale value to display the 32pixels sprites with the right size
         * @param paddingX - take the padding between the game map end the window on X
         * @param paddingY - take the padding between the game map end the window on Y
         */
        Map();

        /**
         * @brief Destroy the Map
         */
        ~Map();

        /**
         * @brief Randomly draw the bombs position and modify the value of the Tile
         */
        void drawBombsPositions();

        /**
         * @brief Take every Tile, check the 8 Tiles around and change the number value depengin on the number of bombs around.
         */
        void changeTilesValues();

        /**
         * @brief Switch between map sizes
         */
        void changeMapSize();

        /**
         * @brief Display the map on the console like a 2D platforme
         */
        void show();

        /**
         * @brief Empty the list to reset or stop the game
         */
        void reset();


        /**
         * @brief Display every informations of the map
         */
        void test();
};