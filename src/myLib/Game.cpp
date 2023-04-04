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

Game::Game()
{
    // Creation of the window with all the predefined parameters
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Démineur_V1", sf::Style::Close);
    // sf::Style::Close;    -> to block the resize of the window
    // sf::Style::Titlebar; -> to block the resize AND disable the x to close the window WITH impossibilty to alt + f4

    window.setPosition(sf::Vector2i(450, 200));

    // Set the pointer of the window to use it in functions wihout passing it throug parameters
    pWindow = &window;

    // Call the setup functions 
    setScaleValue();
    loadTextures();

    // Fill the map with the map constructor wich fill it with fresh tiles
    map = Map(spriteScaleValue, padding_WindowX, PADDING_WINDOW_Y);
    
    // Start of a clock to prevent the programm to do to much things and probably save some of the memory leack
    sf::Clock clock;

    // Main loop of the program
    while (window.isOpen())
    {
        // Update game logic every 25th of a second
        if(clock.getElapsedTime().asMilliseconds() >= 60)
        {
            clock.restart();

            // Clear the window before doing anything with the sprites
            window.clear();

            // Call the game drawing function
            displayTile();
            
            // Get every events appening on the window (click/keyboard/windows rezise/closed/...)
            inputEvent(window);

            // Display the window wich have every sprites on it, need to be the last line of code of the main loop !!
            window.display();
        }
    }
    delete pWindow;
}

Game::~Game()
{
    
}

void Game::displayTile()
{
    // Pass through all the tileList to check every Tile
    for (unsigned long i = 0; i < map.tileList.size(); i++)
    {
        for (unsigned long j = 0; j < map.tileList[i].size(); j++)
        {
            Tile tile = map.tileList[i][j];
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
            // If Tile is Displayed, dispatch depending on the Tile value and display a background on the tiles
            else if (tile.getState() == Displayed)
            {
                if ((spriteValue >= CaseOneColored  && spriteValue <= CaseNineColored) || (spriteValue == Bomb || spriteValue == BombExploded || spriteValue == FlagMissed || spriteValue == Empty))
                {
                    backgroundTile.setValue(CaseBackground);
                    setTileTexture(&backgroundTile);
                }
                // If tile value is Flag, keep the Hide tile background
                else if (spriteValue == Flag)
                {
                    backgroundTile.setValue(CaseHover);
                    setTileTexture(&backgroundTile);
                }

                setTileTexture(&tile);
            }

                // After all the sprites are set, display them at their right places (if there is no background, he is empty)
                backgroundTile.sprite.setPosition(backgroundTile.getPosX(), backgroundTile.getPosY());
                backgroundTile.sprite.scale(sf::Vector2f(spriteScaleValue, spriteScaleValue));

                tile.sprite.setPosition(tile.getPosX(),tile.getPosY());
                tile.sprite.scale(sf::Vector2f(spriteScaleValue, spriteScaleValue));
                
                // Draw the tiles and background on the game
                pWindow->draw(backgroundTile.sprite);
                pWindow->draw(tile.sprite);
        }
    }
}

void Game::discoverNeightboorTiles(Tile *tile)
{
    short posX = ((tile->getPosX() - (float)padding_WindowX / 2) / TEXTURE_SIZE_X / spriteScaleValue) + 1; 
    short posY = ((tile->getPosY() - (float)PADDING_WINDOW_Y / 2) / TEXTURE_SIZE_Y / spriteScaleValue) + 1;

    std::cout << "posX: " << posX << " posY: " << posY << std::endl;

    for (short x = posX - 1; x <= posX + 1; x++)
    {
        for (short y = posY - 1; y <= posY + 1; y++)
        {
            if ((x >= 0 && x < map.mapSizeX) && (y >= 0 && y < map.mapSizeY) && !(x == posX && y == posY))
            {
                Tile *neightboorTile = &map.tileList[y][x];

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

void Game::inputEvent(sf::RenderWindow &renderWindow)
{
    sf::Event event;

    // Get the events on the game
    while (pWindow->pollEvent(event))
    {
        // Get the close window event (every event are tracked like this)
        if (event.type == sf::Event::Closed)
        {
            pWindow->close();
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
                    map = Map(spriteScaleValue, padding_WindowX, PADDING_WINDOW_Y);
                    map.drawBombsPositions();
                    map.changeTilesValues();
                    break;
                case sf::Keyboard::R:
                    setGameState(Stop);
                    map.reset();
                    map = Map(spriteScaleValue, padding_WindowX, PADDING_WINDOW_Y);
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
            if ((mousePosX >= 0 && mousePosY >= 0) && (mousePosX < map.mapSizeX && mousePosY < map.mapSizeY))
            {
                Tile *thisTile = &map.tileList[mousePosY][mousePosX]; 
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
        
        // Get mouse movements event
        if (event.type == sf::Event::MouseMoved)
        {
            mousePosX = (sf::Mouse::getPosition(renderWindow).x - (float)padding_WindowX / 2) / TEXTURE_SIZE_X / spriteScaleValue;
            mousePosY = (sf::Mouse::getPosition(renderWindow).y - (float)PADDING_WINDOW_Y / 2) / TEXTURE_SIZE_Y / spriteScaleValue;
            
            

            if (gameStateValue == Run)
            {
                Tile *thisTile = NULL;
                Tile *previousTile = NULL;

                // Check the mouse is on the tiles
                if ((mousePosX >= 0 && mousePosY >= 0) && (mousePosX < map.mapSizeX && mousePosY < map.mapSizeY))
                {
                    thisTile = &map.tileList[mousePosY][mousePosX];

                    // Check if the last mouse position was on the tiles
                    if ((prevMousePosX >= 0 && prevMousePosY >= 0) && (prevMousePosX < map.mapSizeX && prevMousePosY < map.mapSizeY))
                    {
                        previousTile = &map.tileList[prevMousePosY][prevMousePosX];
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

void Game::setScaleValue()
{
    float screenHeight = pWindow->getSize().y, screenWidth = pWindow->getSize().x;

    spriteScaleValue = (screenHeight - PADDING_WINDOW_Y) / TEXTURE_SIZE_Y / map.mapSizeY;

    padding_WindowX = screenWidth - (TEXTURE_SIZE_X * map.mapSizeX * spriteScaleValue);
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
        tile->sprite.setTexture(caseHide);
        break;
    case CaseBackground:
        tile->sprite.setTexture(caseBackground);
        break;
    case CaseHover:
        tile->sprite.setTexture(caseHover);
        break;
    case CaseOneColored:
        tile->sprite.setTexture(caseOneColored);
        break;
    case CaseTwoColored:
        tile->sprite.setTexture(caseTwoColored);
        break;
    case CaseThreeColored:
        tile->sprite.setTexture(caseThreeColored);
        break;
    case CaseFourColored:
        tile->sprite.setTexture(caseFourColored);
        break;
    case CaseFiveColored:
        tile->sprite.setTexture(caseFiveColored);
        break;
    case CaseSixColored:
        tile->sprite.setTexture(caseSixColored);
        break;
    case CaseSevenColored:
        tile->sprite.setTexture(caseSevenColored);
        break;
    case CaseEightColored:
        tile->sprite.setTexture(caseEightColored);
        break;
    case CaseNineColored:
        tile->sprite.setTexture(caseNineColored);
        break;
    case Zero:
        tile->sprite.setTexture(zero);
        break;
    case One:
        tile->sprite.setTexture(one);
        break;
    case Two:
        tile->sprite.setTexture(two);
        break;
    case Three:
        tile->sprite.setTexture(three);
        break;
    case Four:
        tile->sprite.setTexture(four);
        break;
    case Five:
        tile->sprite.setTexture(five);
        break;
    case Six:
        tile->sprite.setTexture(six);
        break;
    case Seven:
        tile->sprite.setTexture(seven);
        break;
    case Eight:
        tile->sprite.setTexture(eight);
        break;
    case Nine:
        tile->sprite.setTexture(nine);
        break;
    case Bomb:
        tile->sprite.setTexture(bomb);
        break;
    case BombExploded:
        tile->sprite.setTexture(bombExploded);
        break;
    case Flag:
        tile->sprite.setTexture(flag);
        break;
    case FlagMissed:
        tile->sprite.setTexture(flagMissed);
        break;
    case Empty:
        tile->sprite.setTexture(empty);
        break;
    default:
        tile->sprite.setTexture(gyarados);
    }
}

void Game::test()
{
    // Use all the test fucntions of the objects (only use it on one entity)
    map.test();
    map.tileList[0][0].test();
}

void Game::loadTextures()
{
    // Try to load the texture of caseHide place on the x - 0 and the y - 0 on the spriteSheat multiplied by the sprites
    //  sizes with the sprite size on x and y
    if (!caseHide.loadFromFile("src/img/spriteSheet.png", sf::IntRect(0*TEXTURE_SIZE_X,0*TEXTURE_SIZE_Y,TEXTURE_SIZE_X,TEXTURE_SIZE_Y)))
    {
        // Throw error on console if the sprite can't load
        errorLoadingSprite();
    }
    // Try to load...
    if (!caseBackground.loadFromFile("src/img/spriteSheet.png", sf::IntRect(1*TEXTURE_SIZE_X,0*TEXTURE_SIZE_Y,TEXTURE_SIZE_X,TEXTURE_SIZE_Y)))
    {
        errorLoadingSprite();
    }
    if (!caseHover.loadFromFile("src/img/spriteSheet.png", sf::IntRect(2*TEXTURE_SIZE_X,0*TEXTURE_SIZE_Y,TEXTURE_SIZE_X,TEXTURE_SIZE_Y)))
    {
        errorLoadingSprite();
    }
    if (!caseOneColored.loadFromFile("src/img/spriteSheet.png", sf::IntRect(3*TEXTURE_SIZE_X,0*TEXTURE_SIZE_Y,TEXTURE_SIZE_X,TEXTURE_SIZE_Y)))
    {
        errorLoadingSprite();
    }
    if (!caseTwoColored.loadFromFile("src/img/spriteSheet.png", sf::IntRect(4*TEXTURE_SIZE_X,0*TEXTURE_SIZE_Y,TEXTURE_SIZE_X,TEXTURE_SIZE_Y)))
    {
        errorLoadingSprite();
    }
    if (!caseThreeColored.loadFromFile("src/img/spriteSheet.png", sf::IntRect(5*TEXTURE_SIZE_X,0*TEXTURE_SIZE_Y,TEXTURE_SIZE_X,TEXTURE_SIZE_Y)))
    {
        errorLoadingSprite();
    }
    if (!caseFourColored.loadFromFile("src/img/spriteSheet.png", sf::IntRect(0*TEXTURE_SIZE_X,1*TEXTURE_SIZE_Y,TEXTURE_SIZE_X,TEXTURE_SIZE_Y)))
    {
        errorLoadingSprite();
    }
    if (!caseFiveColored.loadFromFile("src/img/spriteSheet.png", sf::IntRect(1*TEXTURE_SIZE_X,1*TEXTURE_SIZE_Y,TEXTURE_SIZE_X,TEXTURE_SIZE_Y)))
    {
        errorLoadingSprite();
    }
    if (!caseSixColored.loadFromFile("src/img/spriteSheet.png", sf::IntRect(2*TEXTURE_SIZE_X,1*TEXTURE_SIZE_Y,TEXTURE_SIZE_X,TEXTURE_SIZE_Y)))
    {
        errorLoadingSprite();
    }
    if (!caseSevenColored.loadFromFile("src/img/spriteSheet.png", sf::IntRect(3*TEXTURE_SIZE_X,1*TEXTURE_SIZE_Y,TEXTURE_SIZE_X,TEXTURE_SIZE_Y)))
    {
        errorLoadingSprite();
    }
    if (!caseEightColored.loadFromFile("src/img/spriteSheet.png", sf::IntRect(4*TEXTURE_SIZE_X,1*TEXTURE_SIZE_Y,TEXTURE_SIZE_X,TEXTURE_SIZE_Y)))
    {
        errorLoadingSprite();
    }
    if (!caseNineColored.loadFromFile("src/img/spriteSheet.png", sf::IntRect(5*TEXTURE_SIZE_X,1*TEXTURE_SIZE_Y,TEXTURE_SIZE_X,TEXTURE_SIZE_Y)))
    {
        errorLoadingSprite();
    }
    if (!zero.loadFromFile("src/img/spriteSheet.png", sf::IntRect(0*TEXTURE_SIZE_X,2*TEXTURE_SIZE_Y,TEXTURE_SIZE_X,TEXTURE_SIZE_Y)))
    {
        errorLoadingSprite();
    }
    if (!one.loadFromFile("src/img/spriteSheet.png", sf::IntRect(1*TEXTURE_SIZE_X,2*TEXTURE_SIZE_Y,TEXTURE_SIZE_X,TEXTURE_SIZE_Y)))
    {
        errorLoadingSprite();
    }
    if (!two.loadFromFile("src/img/spriteSheet.png", sf::IntRect(2*TEXTURE_SIZE_X,2*TEXTURE_SIZE_Y,TEXTURE_SIZE_X,TEXTURE_SIZE_Y)))
    {
        errorLoadingSprite();
    }
    if (!three.loadFromFile("src/img/spriteSheet.png", sf::IntRect(3*TEXTURE_SIZE_X,2*TEXTURE_SIZE_Y,TEXTURE_SIZE_X,TEXTURE_SIZE_Y)))
    {
        errorLoadingSprite();
    }
    if (!four.loadFromFile("src/img/spriteSheet.png", sf::IntRect(4*TEXTURE_SIZE_X,2*TEXTURE_SIZE_Y,TEXTURE_SIZE_X,TEXTURE_SIZE_Y)))
    {
        errorLoadingSprite();
    }
    if (!five.loadFromFile("src/img/spriteSheet.png", sf::IntRect(5*TEXTURE_SIZE_X,2*TEXTURE_SIZE_Y,TEXTURE_SIZE_X,TEXTURE_SIZE_Y)))
    {
        errorLoadingSprite();
    }
    if (!six.loadFromFile("src/img/spriteSheet.png", sf::IntRect(0*TEXTURE_SIZE_X,3*TEXTURE_SIZE_Y,TEXTURE_SIZE_X,TEXTURE_SIZE_Y)))
    {
        errorLoadingSprite();
    }
    if (!seven.loadFromFile("src/img/spriteSheet.png", sf::IntRect(1*TEXTURE_SIZE_X,3*TEXTURE_SIZE_Y,TEXTURE_SIZE_X,TEXTURE_SIZE_Y)))
    {
        errorLoadingSprite();
    }
    if (!eight.loadFromFile("src/img/spriteSheet.png", sf::IntRect(2*TEXTURE_SIZE_X,3*TEXTURE_SIZE_Y,TEXTURE_SIZE_X,TEXTURE_SIZE_Y)))
    {
        errorLoadingSprite();
    }
    if (!nine.loadFromFile("src/img/spriteSheet.png", sf::IntRect(3*TEXTURE_SIZE_X,3*TEXTURE_SIZE_Y,TEXTURE_SIZE_X,TEXTURE_SIZE_Y)))
    {
        errorLoadingSprite();
    }
    if (!bomb.loadFromFile("src/img/spriteSheet.png", sf::IntRect(4*TEXTURE_SIZE_X,3*TEXTURE_SIZE_Y,TEXTURE_SIZE_X,TEXTURE_SIZE_Y)))
    {
        errorLoadingSprite();
    }
    if (!bombExploded.loadFromFile("src/img/spriteSheet.png", sf::IntRect(5*TEXTURE_SIZE_X,3*TEXTURE_SIZE_Y,TEXTURE_SIZE_X,TEXTURE_SIZE_Y)))
    {
        errorLoadingSprite();
    }
    if (!flag.loadFromFile("src/img/spriteSheet.png", sf::IntRect(0*TEXTURE_SIZE_X,4*TEXTURE_SIZE_Y,TEXTURE_SIZE_X,TEXTURE_SIZE_Y)))
    {
        errorLoadingSprite();
    }
    if (!flagMissed.loadFromFile("src/img/spriteSheet.png", sf::IntRect(1*TEXTURE_SIZE_X,4*TEXTURE_SIZE_Y,TEXTURE_SIZE_X,TEXTURE_SIZE_Y)))
    {
        errorLoadingSprite();
    }
    if (!gyarados.loadFromFile("src/img/spriteSheet.png", sf::IntRect(2*TEXTURE_SIZE_X,4*TEXTURE_SIZE_Y,TEXTURE_SIZE_X,TEXTURE_SIZE_Y)))
    {
        errorLoadingSprite();
    }
    if (!empty.loadFromFile("src/img/spriteSheet.png", sf::IntRect(3*TEXTURE_SIZE_X,4*TEXTURE_SIZE_Y,TEXTURE_SIZE_X,TEXTURE_SIZE_Y)))
    {
        errorLoadingSprite();
    }
}

void Game::errorLoadingSprite()
{
    std::cout << "error loading texture " << std::endl;
}