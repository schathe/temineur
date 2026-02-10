/**
 * @file Game.cpp
 * @author Schathe (Théo Schaffner)
 * @brief This file is made to contain the main part of the programm, all the game activities.
 * @date 2022-12-12
 *
 * @copyright Copyright (c) 2023
 */

#include "../myLibHeaders/Game.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cstdlib>
#include <iostream>
#include <ostream>

Game::Game() : 
gameStateValue(Stop), 
PADDING_WINDOW_Y(100),
WIDTH(sf::VideoMode::getDesktopMode().width), 
HEIGHT(sf::VideoMode::getDesktopMode().height - 200)
{
    
}

Game::~Game()
{
    
}

void Game::init()
{
    // Creation of the window with all the predefined parameters
    this->window.create(sf::VideoMode(WIDTH, HEIGHT), "Demineur_V1", sf::Style::Default);

    // Force the window to be on the top left corner.
    this->window.setPosition(sf::Vector2i(0, 0));

    // Fill the map with the map constructor wich fill it with fresh tiles
    // this->map = Map();

    // Call the setup functions 
    setScaleValue();
    loadTextures();
}

void Game::run()
{
    // Start of a clock to prevent the programm to do to much things and probably save some of the memory leack
    sf::Clock clock;

    while (window.isOpen())
    {
        // Update game logic every 25th of a second
        if(clock.getElapsedTime().asMilliseconds() >= 60)
        {
            clock.restart();

            // Clear the window before doing anything with the sprites
            this->window.clear();

            // Call the game drawing function
            displayTile();
            
            // Get every events appening on the window (click/keyboard/windows rezise/closed/...)
            inputEvent();

            // Display the window wich have every sprites on it, need to be the last line of code of the main loop !!
            window.display();
        }
    }
}

void Game::displayTile()
{
    // Pass through all the tileList to check every Tile
    for (unsigned long j = 0; j < map.getYSize(); j++)
    {
        for (unsigned long i = 0; i < map.getXSize(); i++)
        {
            Tile tile = map.getTile(i, j);
            Tile backgroundTile = Tile(tile.getPosX(), tile.getPosY());

            caseSpriteValue spriteValue = tile.getSpriteValue();

            // If Tile is hide, don't display the Tile depending of the value but the Hide tile sprite.
            if (tile.getState() == Hide)
            {
                tile.setValue(CaseHide);
                setTileTexture(&tile);
            }
            // If Tile is hover, don't display the Tile depending of the value but the Hover tile sprite.
            else if (tile.getState() == Hover)
            {
                tile.setValue(CaseHover);
                setTileTexture(&tile);
            }
            // If Tile is Flagged, display a background as the hover and a flag in front.
            else if (tile.getState() == Flagged)
            {
                backgroundTile.setValue(CaseHover);
                setTileTexture(&backgroundTile);

                tile.setValue(Flag);
                setTileTexture(&tile);
            }
            // If Tile is Displayed, dispatch depending on the Tile value and display a background on the tiles
            else if (tile.getState() == Displayed)
            {
                if ((spriteValue >= CaseOneColored  && spriteValue <= CaseNineColored) || (spriteValue == Bomb || spriteValue == BombExploded || spriteValue == FlagMissed || spriteValue == Empty))
                {
                    backgroundTile.setValue(CaseBackground);
                    setTileTexture(&backgroundTile);
                }

                setTileTexture(&tile);
            }

                // ((float)paddingX/2 + j * 32 * spriteScaleValue), ((float)paddingY/2 + i * 32 * spriteScaleValue)

                // After all the sprites are set, display them at their right places (if there is no background, he is empty)
                backgroundTile.getSprite()->setPosition(positionCompute(backgroundTile.getPosX(), padding_window_x),positionCompute(backgroundTile.getPosY(), PADDING_WINDOW_Y));
                backgroundTile.getSprite()->scale(sf::Vector2f(spriteScaleValue, spriteScaleValue));

                tile.getSprite()->setPosition((float)padding_window_x/2 + tile.getPosX() * TEXTURE_SIZE * spriteScaleValue,((float)PADDING_WINDOW_Y/2 + tile.getPosY() * 32 * spriteScaleValue));
                tile.getSprite()->scale(sf::Vector2f(spriteScaleValue, spriteScaleValue));
                
                // Draw the tiles and background on the game
                window.draw(*backgroundTile.getSprite());
                window.draw(*tile.getSprite());
        }
    }
}

void Game::discoverNeightboorTiles(Tile *tile)
{
    // There is a way to save space on the stack because on recusive fonctions vars are stored. 
    // -> if not remembered, talk with valchap
    
    short posX = tile->getPosX(); 
    short posY = tile->getPosY();

    // Debug for the tiles checked
    // std::cout << "posX: " << posX << " posY: " << posY << std::endl;

    for (short x = posX - 1; x <= posX + 1; x++)
    {
        for (short y = posY - 1; y <= posY + 1; y++)
        {
            if ((x >= 0 && x < map.getXSize()) && (y >= 0 && y < map.getYSize()) && !(x == posX && y == posY))
            {
                Tile *neightboorTile = &map.getTileRef(x, y);

                if (neightboorTile->getState() != Displayed)
                {
                    neightboorTile->setState(Displayed);
            
                    if (neightboorTile->getSpriteValue() == Empty)
                    {
                        discoverNeightboorTiles(neightboorTile);
                    }
                }
            }
        }
    }
}

void Game::inputEvent()
{
    sf::Event event;

    // Get the events on the game
    while (window.pollEvent(event))
    {
        // Get the close window event (every event are tracked like this)
        if (event.type == sf::Event::Closed)
        {
            window.close();
            return;
        }

        // Get keyboard event
        if (event.type == sf::Event::KeyPressed)
        {
            // Switch between keyboard input
            switch (event.key.code)
            {
                case sf::Keyboard::Space:
                    if (gameStateValue == Stop)
                    {
                        setGameState(Run);
                    }
                    map.reset();
                    map = Map();
                    map.drawBombsPositions();
                    map.changeTilesValues();
                    break;
                case sf::Keyboard::R:
                    setGameState(Stop);
                    map.reset();
                    map = Map();
                    break;
                // Actually don't work
                case sf::Keyboard::Q:
                    map.changeMapSize();
                default:
                    break;
            }
        }
        
        // Get mouse button event
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if ((mousePosX >= 0 && mousePosY >= 0) && (mousePosX < map.getXSize() && mousePosY < map.getYSize()))
            {
                Tile *thisTile = &map.getTileRef(mousePosX, mousePosY); 
                if (thisTile->getState() == Hover)
                {
                    thisTile->setState(Displayed);

                    if (thisTile->getSpriteValue() == Empty)
                    {
                        discoverNeightboorTiles(thisTile);
                    }
                }
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Right) || event.key.code == sf::Keyboard::F)
        {
            if ((mousePosX >= 0 && mousePosY >= 0) && (mousePosX < map.getXSize() && mousePosY < map.getYSize()))
            {
                Tile *tile = &map.getTileRef(mousePosX, mousePosY);
                if (tile->getState() == Hover)
                {
                    // Change tile value
                    // TODO !!!! Change the management of the flag, like this it will just drop the real value of the tile, 
                    //  make it to be a state of the tile
                    tile->setState(Flagged);
                }
                else if (tile->getState() == Flagged)
                {
                    tile->setState(Hover);
                }
            }
        }
        
        // Get mouse movements event
        if (event.type == sf::Event::MouseMoved)
        {
            mousePosX = (sf::Mouse::getPosition(window).x - (float)padding_window_x / 2) / TEXTURE_SIZE / spriteScaleValue;
            mousePosY = (sf::Mouse::getPosition(window).y - (float)PADDING_WINDOW_Y / 2) / TEXTURE_SIZE / spriteScaleValue;
            
            

            if (gameStateValue == Run)
            {
                Tile *thisTile = NULL;
                Tile *previousTile = NULL;

                // Check the mouse is on the tiles
                if ((mousePosX >= 0 && mousePosY >= 0) && (mousePosX < map.getXSize() && mousePosY < map.getYSize()))
                {
                    thisTile = &map.getTileRef(mousePosX, mousePosY);

                    // Check if the last mouse position was on the tiles
                    if ((prevMousePosX >= 0 && prevMousePosY >= 0) && (prevMousePosX < map.getXSize() && prevMousePosY < map.getYSize()))
                    {
                        previousTile = &map.getTileRef(prevMousePosX, prevMousePosY);
                    }

                    if (thisTile->getState() == Hide)
                    {
                        thisTile->setState(Hover);
                    }
    
                    if (prevMousePosY != mousePosY || prevMousePosX != mousePosX)
                    {
                        if (previousTile->getState() == Hover)
                        {
                            previousTile->setState(Hide);
                        }

                        prevMousePosX = mousePosX;
                        prevMousePosY = mousePosY;
                    }
                }
            }
        }
    }
}

int Game::positionCompute(int position, int padding)
{
    return (float)padding/2 + position * TEXTURE_SIZE * spriteScaleValue;
}

void Game::setScaleValue()
{
    spriteScaleValue = (window.getSize().y - PADDING_WINDOW_Y) / TEXTURE_SIZE / map.getYSize();

    padding_window_x = window.getSize().x - (TEXTURE_SIZE * map.getXSize() * spriteScaleValue);
}

void Game::setGameState(gameState state)
{
    gameStateValue = state;
}

void Game::setTileTexture(Tile* tile)
{
    switch (tile->getSpriteValue())
    {
    case CaseHide:
        tile->getSprite()->setTexture(caseHide);
        break;
    case CaseBackground:
        tile->getSprite()->setTexture(caseBackground);
        break;
    case CaseHover:
        tile->getSprite()->setTexture(caseHover);
        break;
    case CaseOneColored:
        tile->getSprite()->setTexture(caseOneColored);
        break;
    case CaseTwoColored:
        tile->getSprite()->setTexture(caseTwoColored);
        break;
    case CaseThreeColored:
        tile->getSprite()->setTexture(caseThreeColored);
        break;
    case CaseFourColored:
        tile->getSprite()->setTexture(caseFourColored);
        break;
    case CaseFiveColored:
        tile->getSprite()->setTexture(caseFiveColored);
        break;
    case CaseSixColored:
        tile->getSprite()->setTexture(caseSixColored);
        break;
    case CaseSevenColored:
        tile->getSprite()->setTexture(caseSevenColored);
        break;
    case CaseEightColored:
        tile->getSprite()->setTexture(caseEightColored);
        break;
    case CaseNineColored:
        tile->getSprite()->setTexture(caseNineColored);
        break;
    case Zero:
        tile->getSprite()->setTexture(zero);
        break;
    case One:
        tile->getSprite()->setTexture(one);
        break;
    case Two:
        tile->getSprite()->setTexture(two);
        break;
    case Three:
        tile->getSprite()->setTexture(three);
        break;
    case Four:
        tile->getSprite()->setTexture(four);
        break;
    case Five:
        tile->getSprite()->setTexture(five);
        break;
    case Six:
        tile->getSprite()->setTexture(six);
        break;
    case Seven:
        tile->getSprite()->setTexture(seven);
        break;
    case Eight:
        tile->getSprite()->setTexture(eight);
        break;
    case Nine:
        tile->getSprite()->setTexture(nine);
        break;
    case Bomb:
        tile->getSprite()->setTexture(bomb);
        break;
    case BombExploded:
        tile->getSprite()->setTexture(bombExploded);
        break;
    case Flag:
        tile->getSprite()->setTexture(flag);
        break;
    case FlagMissed:
        tile->getSprite()->setTexture(flagMissed);
        break;
    case Empty:
        tile->getSprite()->setTexture(empty);
        break;
    default:
        tile->getSprite()->setTexture(gyarados);
    }
}

void Game::test()
{
    // Use all the test fucntions of the objects (only use it on one entity)
    map.test();
    map.getTile(0, 0).test();
}

void Game::loadTextures()
{
    // Try to load the texture of caseHide place on the x - 0 and the y - 0 on the spriteSheat multiplied by the sprites
    //  sizes with the sprite size on x and y
    if (!caseHide.loadFromFile("src/img/spriteSheet.png", sf::IntRect(0*TEXTURE_SIZE,0*TEXTURE_SIZE,TEXTURE_SIZE,TEXTURE_SIZE)))
    {
        // Throw error on console if the sprite can't load
        errorLoadingSprite();
    }
    // Try to load...
    if (!caseBackground.loadFromFile("src/img/spriteSheet.png", sf::IntRect(1*TEXTURE_SIZE,0*TEXTURE_SIZE,TEXTURE_SIZE,TEXTURE_SIZE)))
    {
        errorLoadingSprite();
    }
    if (!caseHover.loadFromFile("src/img/spriteSheet.png", sf::IntRect(2*TEXTURE_SIZE,0*TEXTURE_SIZE,TEXTURE_SIZE,TEXTURE_SIZE)))
    {
        errorLoadingSprite();
    }
    if (!caseOneColored.loadFromFile("src/img/spriteSheet.png", sf::IntRect(3*TEXTURE_SIZE,0*TEXTURE_SIZE,TEXTURE_SIZE,TEXTURE_SIZE)))
    {
        errorLoadingSprite();
    }
    if (!caseTwoColored.loadFromFile("src/img/spriteSheet.png", sf::IntRect(4*TEXTURE_SIZE,0*TEXTURE_SIZE,TEXTURE_SIZE,TEXTURE_SIZE)))
    {
        errorLoadingSprite();
    }
    if (!caseThreeColored.loadFromFile("src/img/spriteSheet.png", sf::IntRect(5*TEXTURE_SIZE,0*TEXTURE_SIZE,TEXTURE_SIZE,TEXTURE_SIZE)))
    {
        errorLoadingSprite();
    }
    if (!caseFourColored.loadFromFile("src/img/spriteSheet.png", sf::IntRect(0*TEXTURE_SIZE,1*TEXTURE_SIZE,TEXTURE_SIZE,TEXTURE_SIZE)))
    {
        errorLoadingSprite();
    }
    if (!caseFiveColored.loadFromFile("src/img/spriteSheet.png", sf::IntRect(1*TEXTURE_SIZE,1*TEXTURE_SIZE,TEXTURE_SIZE,TEXTURE_SIZE)))
    {
        errorLoadingSprite();
    }
    if (!caseSixColored.loadFromFile("src/img/spriteSheet.png", sf::IntRect(2*TEXTURE_SIZE,1*TEXTURE_SIZE,TEXTURE_SIZE,TEXTURE_SIZE)))
    {
        errorLoadingSprite();
    }
    if (!caseSevenColored.loadFromFile("src/img/spriteSheet.png", sf::IntRect(3*TEXTURE_SIZE,1*TEXTURE_SIZE,TEXTURE_SIZE,TEXTURE_SIZE)))
    {
        errorLoadingSprite();
    }
    if (!caseEightColored.loadFromFile("src/img/spriteSheet.png", sf::IntRect(4*TEXTURE_SIZE,1*TEXTURE_SIZE,TEXTURE_SIZE,TEXTURE_SIZE)))
    {
        errorLoadingSprite();
    }
    if (!caseNineColored.loadFromFile("src/img/spriteSheet.png", sf::IntRect(5*TEXTURE_SIZE,1*TEXTURE_SIZE,TEXTURE_SIZE,TEXTURE_SIZE)))
    {
        errorLoadingSprite();
    }
    if (!zero.loadFromFile("src/img/spriteSheet.png", sf::IntRect(0*TEXTURE_SIZE,2*TEXTURE_SIZE,TEXTURE_SIZE,TEXTURE_SIZE)))
    {
        errorLoadingSprite();
    }
    if (!one.loadFromFile("src/img/spriteSheet.png", sf::IntRect(1*TEXTURE_SIZE,2*TEXTURE_SIZE,TEXTURE_SIZE,TEXTURE_SIZE)))
    {
        errorLoadingSprite();
    }
    if (!two.loadFromFile("src/img/spriteSheet.png", sf::IntRect(2*TEXTURE_SIZE,2*TEXTURE_SIZE,TEXTURE_SIZE,TEXTURE_SIZE)))
    {
        errorLoadingSprite();
    }
    if (!three.loadFromFile("src/img/spriteSheet.png", sf::IntRect(3*TEXTURE_SIZE,2*TEXTURE_SIZE,TEXTURE_SIZE,TEXTURE_SIZE)))
    {
        errorLoadingSprite();
    }
    if (!four.loadFromFile("src/img/spriteSheet.png", sf::IntRect(4*TEXTURE_SIZE,2*TEXTURE_SIZE,TEXTURE_SIZE,TEXTURE_SIZE)))
    {
        errorLoadingSprite();
    }
    if (!five.loadFromFile("src/img/spriteSheet.png", sf::IntRect(5*TEXTURE_SIZE,2*TEXTURE_SIZE,TEXTURE_SIZE,TEXTURE_SIZE)))
    {
        errorLoadingSprite();
    }
    if (!six.loadFromFile("src/img/spriteSheet.png", sf::IntRect(0*TEXTURE_SIZE,3*TEXTURE_SIZE,TEXTURE_SIZE,TEXTURE_SIZE)))
    {
        errorLoadingSprite();
    }
    if (!seven.loadFromFile("src/img/spriteSheet.png", sf::IntRect(1*TEXTURE_SIZE,3*TEXTURE_SIZE,TEXTURE_SIZE,TEXTURE_SIZE)))
    {
        errorLoadingSprite();
    }
    if (!eight.loadFromFile("src/img/spriteSheet.png", sf::IntRect(2*TEXTURE_SIZE,3*TEXTURE_SIZE,TEXTURE_SIZE,TEXTURE_SIZE)))
    {
        errorLoadingSprite();
    }
    if (!nine.loadFromFile("src/img/spriteSheet.png", sf::IntRect(3*TEXTURE_SIZE,3*TEXTURE_SIZE,TEXTURE_SIZE,TEXTURE_SIZE)))
    {
        errorLoadingSprite();
    }
    if (!bomb.loadFromFile("src/img/spriteSheet.png", sf::IntRect(4*TEXTURE_SIZE,3*TEXTURE_SIZE,TEXTURE_SIZE,TEXTURE_SIZE)))
    {
        errorLoadingSprite();
    }
    if (!bombExploded.loadFromFile("src/img/spriteSheet.png", sf::IntRect(5*TEXTURE_SIZE,3*TEXTURE_SIZE,TEXTURE_SIZE,TEXTURE_SIZE)))
    {
        errorLoadingSprite();
    }
    if (!flag.loadFromFile("src/img/spriteSheet.png", sf::IntRect(0*TEXTURE_SIZE,4*TEXTURE_SIZE,TEXTURE_SIZE,TEXTURE_SIZE)))
    {
        errorLoadingSprite();
    }
    if (!flagMissed.loadFromFile("src/img/spriteSheet.png", sf::IntRect(1*TEXTURE_SIZE,4*TEXTURE_SIZE,TEXTURE_SIZE,TEXTURE_SIZE)))
    {
        errorLoadingSprite();
    }
    if (!gyarados.loadFromFile("src/img/spriteSheet.png", sf::IntRect(2*TEXTURE_SIZE,4*TEXTURE_SIZE,TEXTURE_SIZE,TEXTURE_SIZE)))
    {
        errorLoadingSprite();
    }
    if (!empty.loadFromFile("src/img/spriteSheet.png", sf::IntRect(3*TEXTURE_SIZE,4*TEXTURE_SIZE,TEXTURE_SIZE,TEXTURE_SIZE)))
    {
        errorLoadingSprite();
    }
}

void Game::errorLoadingSprite()
{
    std::cout << "error loading texture or font " << std::endl;
}