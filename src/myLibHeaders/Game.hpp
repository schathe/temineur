/**
 * Creation date:   2022-12-12
 * Creator:         Schathe (Théo Schaffner)
 * Description:     This file is use to put the declarations of the function and the variables of game.cpp.
 * Version:         V-1.0
*/

#pragma once

#include "../myLibHeaders/Map.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Window.hpp>

class Game
{
    private:
        Map map;
        float spriteScaleValue;
        const int WIDTH = 2100, HEIGHT = 1500;
        const short PADDING_WINDOW_Y = 100;
        const short TEXTURE_SIZE_X = 32, TEXTURE_SIZE_Y = 32;
        short padding_WindowX = 300;

        /* TEXTURES OF THE GAME */

        // Numbers white
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

        // Numbers colored
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
        Game();
        ~Game();

        sf::RenderWindow* pWindow;

        void displayTile();

        void inputEvent(sf::RenderWindow &renderWindow);

        void setScaleValue();
        void setTileTexture(Tile* tile);

        void test();

        // Functions called only once
        void loadTextures();
        void errorLoadingSprite();
};