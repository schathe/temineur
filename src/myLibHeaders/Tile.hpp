#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>

enum caseState
{
    Hide = 0,
    Hover,
    Pressed,
    Draw
};

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

class Tile
{
    private:
        caseState state;
        caseSpriteValue spriteValue;

        int posX;
        int posY;

    public:
        sf::Sprite sprite;

        Tile(int x = 0, int y = 0);
        ~Tile();

        caseState getState();
        caseSpriteValue getSpriteValue();
        int getPosX();
        int getPosY();

        void setValue(int newValue = 0);
        void setState(int newState = 0);
        void setPosX();
        void setPosY();

        void test();
};