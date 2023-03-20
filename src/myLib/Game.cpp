/**
 * Creation date:   2022-12-12
 * Creator:         Schathe (Théo Schaffner)
 * Description:     This file is made to contain the main part of the programm, all the game activities.
 * Version:         V-1.0
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
        if(clock.getElapsedTime().asMilliseconds() >= 1000/25)
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
}

Game::~Game()
{
    
}

void Game::displayTile()
{
    for (unsigned long i = 0; i < map.tileList.size(); i++)
    {
        for (unsigned long j = 0; j < map.tileList[i].size(); j++)
        {
            Tile tile = map.tileList[i][j];

            caseSpriteValue spriteValue = tile.getSpriteValue();

            if (spriteValue >= CaseOneColored  && spriteValue <= CaseNineColored )
            {
                Tile backgroundTile = Tile(tile.getPosX(), tile.getPosY());
                backgroundTile.setValue(CaseBackground);
                setTileTexture(&backgroundTile);
                backgroundTile.sprite.setPosition(backgroundTile.getPosX(), backgroundTile.getPosY());
                backgroundTile.sprite.scale(sf::Vector2f(spriteScaleValue, spriteScaleValue));

                pWindow->draw(backgroundTile.sprite);
            }
            else if (spriteValue == Bomb || spriteValue == BombExploded || spriteValue == FlagMissed || spriteValue == Empty)
            {
                Tile backgroundTile = Tile(tile.getPosX(), tile.getPosY());
                backgroundTile.setValue(CaseBackground);
                setTileTexture(&backgroundTile);
                backgroundTile.sprite.setPosition(backgroundTile.getPosX(), backgroundTile.getPosY());
                backgroundTile.sprite.scale(sf::Vector2f(spriteScaleValue, spriteScaleValue));

                pWindow->draw(backgroundTile.sprite);
            }
            else if (spriteValue == Flag)
            {
                Tile backgroundTile = Tile(tile.getPosX(), tile.getPosY());
                backgroundTile.setValue(CaseHover);
                setTileTexture(&backgroundTile);
                backgroundTile.sprite.setPosition(backgroundTile.getPosX(), backgroundTile.getPosY());
                backgroundTile.sprite.scale(sf::Vector2f(spriteScaleValue, spriteScaleValue));

                pWindow->draw(backgroundTile.sprite);
            }

            setTileTexture(&tile);
            tile.sprite.setPosition(tile.getPosX(),tile.getPosY());
            tile.sprite.scale(sf::Vector2f(spriteScaleValue, spriteScaleValue));
            
            pWindow->draw(tile.sprite);
        }
    }
}

void Game::inputEvent(sf::RenderWindow &renderWindow)
{
    sf::Event event;
    while (pWindow->pollEvent(event))
    {
        // Get the close window event (every event are tracked like this)
        if (event.type == sf::Event::Closed)
        {
            pWindow->close();
        }

        if (event.type == sf::Event::KeyPressed)
        {
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
                    map.changeCasesValues();
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
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            // mousePosX = (sf::Mouse::getPosition(renderWindow).x - (float)padding_WindowX / 2) / 32 / spriteScaleValue;
            // mousePosY = (sf::Mouse::getPosition(renderWindow).y - (float)PADDING_WINDOW_Y / 2) / 32 / spriteScaleValue;
            // std::cout << "Mouse Pos x: " << mousePosX << std::endl << "Mouse Pos y: " << mousePosY << std::endl;
        }
        
        if (event.type == sf::Event::MouseMoved)
        {
/* 
            mousePosX = (sf::Mouse::getPosition(renderWindow).x - (float)padding_WindowX / 2) / 32 / spriteScaleValue;
            mousePosY = (sf::Mouse::getPosition(renderWindow).y - (float)PADDING_WINDOW_Y / 2) / 32 / spriteScaleValue;
            
            if (gameStateValue == Run)
            {
                if (prevMousePosX != mousePosX)
                {
                    if (prevMousePosX >= 0 && prevMousePosY >= 0)
                    {
                        if (prevMousePosX < map.mapSizeX && prevMousePosY < map.mapSizeY)
                        {
                            map.tileList[prevMousePosY][prevMousePosX].setValue(Empty);
                        }
                    }
                    prevMousePosX = mousePosX;
                }
                if (prevMousePosY != mousePosY)
                {
                    if (prevMousePosX >= 0 && prevMousePosY >= 0)
                    {
                        if (prevMousePosX < map.mapSizeX && prevMousePosY < map.mapSizeY)
                        {
                            map.tileList[prevMousePosY][prevMousePosX].setValue(Empty);
                        }
                    }
                    prevMousePosY = mousePosY;
                }

                if (mousePosX >= 0 && mousePosY >= 0)
                {
                    if (mousePosX < map.mapSizeX && mousePosY < map.mapSizeY)
                    {
                        map.tileList[mousePosY][mousePosX].setValue(CaseHide);
                    }
                }
                
                if (prevMousePosX >= 0 && prevMousePosY >= 0)
                {
                    if (prevMousePosX < map.mapSizeX && prevMousePosY < map.mapSizeY)
                    {
                        // map.tileList[prevMousePosY][prevMousePosX].setValue(Empty);
                    }
                }
            }
 */
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
    switch (tile->getSpriteValue()) {
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
    if (!caseHide.loadFromFile("src/img/spriteSheet.png", sf::IntRect(0*TEXTURE_SIZE_X,0*TEXTURE_SIZE_Y,TEXTURE_SIZE_X,TEXTURE_SIZE_Y)))
    {
        errorLoadingSprite();
    }
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
    // Display an error on the console when a texture can't be loaded
    std::cout << "error loading texture " << std::endl;
}
