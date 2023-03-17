/**
 * Creation date:   2022-12-12
 * Creator:         Schathe (Théo Schaffner)
 * Description:     This file is used to put the declarations of the program functions.
 * Version:         V-1.0
*/

#include "../myLibHeaders/Game.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>


Game::Game()
{
    // Creation of the window, the textures and the sprites
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Démineur_V1", sf::Style::Close);
    // sf::Style::Close;    -> to block the resize of the window
    // sf::Style::Titlebar; -> to block the resize AND disable the x to close the window WITH impossibilty to alt + f4
    sf::Texture texture;
    sf::Texture textureBomba;
    sf::Sprite sprite;
    sf::Sprite bomba;
    sf::IntRect bombaPosSize(128, 96, 32, 32);

    pWindow = &window;

    setScaleValue();
    loadTextures();

    map = Map(spriteScaleValue, padding_WindowX, PADDING_WINDOW_Y);

    
    // map.show();

    // Loading of the textures for the sprites of the game
    //  to load a texture from a sprite sheet:
    //   !texture.loadFromFile("src/img/spriteSheet.png", sf::IntRect(128, 96, 32, 32))
    // IntRect(posXonFile, posYonFile, sizeX, sizeY)
    if (!texture.loadFromFile("src/img/spriteSheet.png"))
    {
        std::cout << "error loading sprite " << std::endl;
    }
    if (!textureBomba.loadFromFile("src/img/spriteSheet.png", bombaPosSize))
    {
        std::cout << "error loading sprite " << std::endl;
    }

    // Filling the windows with ONE sprite scaled the x and y of the window
    sprite.setTexture(texture);
    // sprite.setTexture(getTexture(CaseBackground));
    bomba.setTexture(textureBomba);

    sprite.scale(sf::Vector2f((float)window.getSize().x/texture.getSize().x, (float)window.getSize().y/texture.getSize().y));
    bomba.scale(sf::Vector2f(5,5));
    
    sprite.setPosition(sf::Vector2f(0.f, 0.f)); // absolute position
    bomba.setPosition(sf::Vector2f(10.f, 10.f)); // absolute position


/*  DEBUG CODE, USED TO GET THE SIZE OF THE SPRITE LOADED (X;Y)

    std::cout << "x: " << texture.getSize().x << std::endl;
    std::cout << "y: " << texture.getSize().y << std::endl;
*/

    sf::Clock clock;


    // Main loop of the program
    while (window.isOpen())
    {

        if(clock.getElapsedTime().asMilliseconds() >= 1000/60)
        {
            sf::Time elapsed = clock.restart();


            // Clear the window before doing anything with the sprites
            window.clear();

            // Draw the sprites on the window, the position of the sprites still need to be fix...
            //  (Here it's correctly set because it's on a corner and the size is based on the window's one)
            // window.draw(sprite);

            drawTile();
            
            // window.draw(bomba);
            
            // Get every events appening on the window (click/keyboard/windows rezise/closed/...)
            inputEvent();

            // Display the window wich have every sprites on it, need to be the last line of code of the main loop !!
            window.display();
        }
    }
}

Game::~Game()
{
    
}

void Game::drawTile()
{
    for (int i = 0; i < map.tileList.size(); i++)
    {
        for (int j = 0; j < map.tileList[i].size(); j++)
        {
            Tile tile = map.tileList[i][j];

            setTileTexture(&tile);
            tile.sprite.setPosition(tile.getPosX(),tile.getPosY());
            tile.sprite.scale(sf::Vector2f(spriteScaleValue, spriteScaleValue));
            
            pWindow->draw(tile.sprite);
            
        }
    }
}

void Game::inputEvent()
{
    sf::Event event;
    while (pWindow->pollEvent(event))
    {
        // Get the close window event (every event are tracked like this)
        if (event.type == sf::Event::Closed)
        {
            pWindow->close();
        }

        if(event.type == sf::Event::KeyPressed){
            if (event.key.code == sf::Keyboard::Space)
            {
                map.reset();
                map = Map(spriteScaleValue, padding_WindowX, PADDING_WINDOW_Y);
            }
        }
    }
}

void Game::setScaleValue()
{
    float screenHeight = pWindow->getSize().y, screenWidth = pWindow->getSize().x;

    // (float)window.getSize().x/texture.getSize().x

    spriteScaleValue = (screenHeight - PADDING_WINDOW_Y) / TEXTURE_SIZE_Y / map.mapSizeY;

    padding_WindowX = screenWidth - (TEXTURE_SIZE_X * map.mapSizeX * spriteScaleValue);

    std::cout << spriteScaleValue << std::endl;

    // effectué les calcules pour savoir quelle taille de scale faire...
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
    default:
        tile->sprite.setTexture(gyarados);
    }
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
}

void Game::errorLoadingSprite()
{
    std::cout << "error loading sprite " << std::endl;
}
