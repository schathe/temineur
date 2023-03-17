/**
 * Creation date:   2022-12-12
 * Creator:         Schathe (Théo Schaffner)
 * Description:     This file is used to define the funcitons, enumerations and the variables of the tile.cpp.
 * Version:         V-1.0
*/

#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

enum caseState
{
    Hide = 0,
    Hover,
    Pressed,
    Displayed
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

        void test();
};