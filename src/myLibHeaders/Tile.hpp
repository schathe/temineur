/**
 * @file Tile.hpp
 * @author Schathe (Théo Schaffner)
 * @brief This file is used to define the functions, enumerations and the variables of the tile.cpp. 
 * @date 2022-12-12
 *
 * @details A tile is an element of the map, it's a specific area with a specific size, his own variables and independents
 * states from the map or the game.
 * 
 * @copyright Copyright (c) 2023
 */

#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

/**
 * @brief Enum of the possible states of the tiles
 */
enum caseState
{
    Hide = 0,
    Hover,
    Displayed,
    Flagged
};

/**
 * @brief Enum of the value of the sprites of the tiles, the value corresponds to the value of the sprite on the spritesheat.
 */
enum caseSpriteValue
{
    CaseHide,
    CaseBackground,
    CaseHover,
    CaseOneColored,
    CaseTwoColored,
    CaseThreeColored,
    CaseFourColored,
    CaseFiveColored,
    CaseSixColored,
    CaseSevenColored,
    CaseEightColored,
    CaseNineColored,
    Zero,
    One,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Bomb,
    BombExploded,
    Flag,
    FlagMissed,
    Gyarados,
    Empty
};

/**
 * @class Tile
 * @brief There are all the componnents of the tile class
 */
class Tile
{
    private:
        /* VARIABLES OF THE TILE */

        caseState state;
        caseSpriteValue spriteValue;

        // Positions of the Tile in the TileList of the map
        int posX;
        int posY;

        // Sprite of the Tile, in public to be able to change it easily in the game file
        sf::Sprite sprite;

    public:
        /**
         * @brief Construct a new Tile
         * 
         * @param x - value of the position in X on the tileList of map
         * @param y - value of the position in Y on the tileList of map
         */
        Tile(int x = 0, int y = 0);

        /**
         * @brief Destroy the Tile
         */
        ~Tile();

        /**
         * @brief Get the State of the Tile
         * 
         * @return state
         */
        caseState getState();

        /**
         * @brief Get the Sprite Value of the Tile
         * 
         * @return spriteValue
         */
        caseSpriteValue getSpriteValue();

        /**
        * @brief Set a new value to the Tile
        * 
        * @param newValue - (default Empty)
        */
        void setValue(caseSpriteValue newValue = Empty);

        /**
         * @brief Set a new state to the Tile
         * 
         * @param newState - (default Hide)
         */
        void setState(caseState newState = Hide);

        /**
         * @brief Get the X position of the Tile on the tileList
         * 
         * @return posX
         */
        int getPosX();

        /**
         * @brief Get the Y position of the Tile on the tileList
         * 
         * @return posY
         */
        int getPosY();

        /**
         * @brief Get the Sprite of the Tile
         * 
         * @return sprite
         */
        sf::Sprite* getSprite();

        /**
         * @brief Check if the actual Tile is a bomb
         * 
         * @return Boolean
         */
        bool isBomb();

        /**
         * @brief Allow to show the informations of the sprite (Pos X/Y - State - Value)
         */
        void test();
};