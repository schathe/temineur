/**
 * Creation date:   2022-12-12
 * Creator:         Schathe (Théo Schaffner)
 * Description:     This file is use to put the declarations of the functions of the program.
 * Version:         V-1.0
*/

#include "../myLibHeaders/Map.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <string>


class Game
{
    private:
        Map map;

        sf::Texture EMPTY_TEXTURE;

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

        // Troll
        sf::Texture gyarados;

        float spriteScaleValue;

    public:
        const int WIDTH = 2100, HEIGHT = 1500;
        const short PADDING_WINDOW_Y = 100;
        const short TEXTURE_SIZE_X = 32, TEXTURE_SIZE_Y = 32;
        short padding_WindowX = 300;

        Game();
        ~Game();

        sf::RenderWindow* pWindow;

        void drawTile();

        void inputEvent();

        void setScaleValue();
        void setTileTexture(Tile* tile);

        void loadTextures();
        void errorLoadingSprite();
};