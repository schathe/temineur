/**
 * Creation date:   2022-12-12
 * Creator:         Schathe (Théo Schaffner)
 * Description:     This file is use to put the declarations of the functions of the program.
 * Version:         V-1.0
*/

#include "../myLibHeaders//Map.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <string>


class Game
{
    private:
        Map map;

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
        sf::Texture caseHiden;
        sf::Texture caseHover;
        sf::Texture caseBackground;

        // Troll
        sf::Texture gyarados;

        void errorLoadingSprite();
        void loadTextures();
        sf::Texture getTexture(caseSpriteValue tileValue);

    public:
        Game();
        ~Game();

        sf::RenderWindow* pWindow;

        void drawTile();
        void inputEvent();

};