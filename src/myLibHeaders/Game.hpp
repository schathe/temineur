/**
 * @file Game.hpp
 * @author Schathe (Théo Schaffner)
 * @brief This file is use to put the declarations of the function and the variables of game.cpp.
 * @date 2022-12-12
 *
 * @details The game is the main part of the programm, it's used to track the events like mouse or keyboard, to display
 * the textures, have all the logic of the programm... The game contain a Map which contain a lot of Tiles, it's used to
 * know the position of the mouse on the map and detect wich tile while get modified.
 * 
 * @copyright Copyright (c) 2023
 */

#pragma once

#include "../myLibHeaders/Map.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Window.hpp>

/**
 * @brief Enum of the possible states of the game, it's more about the playable state of the game
 */
enum gameState
{
    Stop,
    Pause,
    Run
};

/**
 * @class Game
 * @brief There are all the components of the game class, the game class is called at the beginning of the programm and
 * contain the main logic of the game. 
 */
class Game
{
    private:
        /* VARIABLES OF THE GAME */

        Map map;
        // Set the gameStateValue to stop, because the game can't be running without actions of the user
        gameState gameStateValue = Stop;

        // Constants and variable for the Window
        const int WIDTH = 2100, HEIGHT = 1500, PADDING_WINDOW_Y = 100;
        int padding_WindowX = 300;
        // Constants for the Srpites sizes
        const short TEXTURE_SIZE_X = 32, TEXTURE_SIZE_Y = 32;
        float spriteScaleValue;

        /**
         * @brief Variables to track the position of the mouse on the mouse movements
         */
        int mousePosX = 0, mousePosY = 0, prevMousePosX = 0, prevMousePosY = 0;


        /* TEXTURES OF THE GAME */

        // Numbers white (number for a timer)
        sf::Texture zero;
        sf::Texture one;
        sf::Texture two;
        sf::Texture three;
        sf::Texture four;
        sf::Texture five;
        sf::Texture six;
        sf::Texture seven;
        sf::Texture eight;
        sf::Texture nine;

        // Numbers colored (number for the game)
        sf::Texture caseOneColored;
        sf::Texture caseTwoColored;
        sf::Texture caseThreeColored;
        sf::Texture caseFourColored;
        sf::Texture caseFiveColored;
        sf::Texture caseSixColored;
        sf::Texture caseSevenColored;
        sf::Texture caseEightColored;
        sf::Texture caseNineColored;

        // Items
        sf::Texture flag;
        sf::Texture flagMissed;
        sf::Texture bomb;
        sf::Texture bombExploded;

        // Cases
        sf::Texture caseHide;
        sf::Texture caseHover;
        sf::Texture caseBackground;
        sf::Texture empty;

        // Troll
        sf::Texture gyarados;

    public:
        /**
         * @brief Construct a new Game
         */
        Game();

        /**
         * @brief Destroy the Game
         */
        ~Game();


        sf::RenderWindow* pWindow;

        /**
        * @brief Function that go through the tileList and display every Tile depending of their value
        */
        void displayTile();

        /**
        * @brief Take every input of the game and dispatch them depending on their source and utility
        * 
        * @param renderWindow - pass the renderWindow in parameter because the pointer is not working with the mouse getPosition
        */
        void inputEvent(sf::RenderWindow &renderWindow);

        /**
         * @brief Set the spriteScaleValue of the Game's sprites
         */
        void setScaleValue();

        /**
         * @brief Set the gameStateValue of the Game
         * 
         * @param gameState - enum of the game states
         */
        void setGameState(gameState state);

        /**
         * @brief Set the Tile texture depending of their value
         * 
         * @param Tile 
         */
        void setTileTexture(Tile* tile);

        /**
         * @brief Display every informations of the Game
         */
        void test();


        /* FUNCTIONS CALLED ONLY ONCE */

        /**
         * @brief Load the texture to the project
         */
        void loadTextures();

        /**
         * @brief Display an error in the console if the sprite can't be loaded
         */
        void errorLoadingSprite();
};