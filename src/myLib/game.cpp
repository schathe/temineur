/**
 * Creation date:   2022-12-12
 * Creator:         Schathe (Théo Schaffner)
 * Description:     This file is used to put the declarations of the program functions.
 * Version:         V-1.0
*/

#include "../myLibHeaders/game.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>
#include <iostream>
#include <string>



const int WIDTH = 2100, HEIGHT = 1500;
const short TEXTURE_SIZE_X = 32, TEXTURE_SIZE_Y = 32;

Game::Game()
{
    // Creation of the window, the textures and the sprites
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Démineur_V1");
    sf::Texture texture;
    sf::Texture textureBomba;
    sf::Sprite sprite;
    sf::Sprite bomba;
    sf::IntRect bombaPosSize(128, 96, 32, 32);

    pWindow = &window;

    map = Map();
    map.show();

    loadTextures();

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
    bomba.setTexture(textureBomba);
    sprite.scale(sf::Vector2f((float)window.getSize().x/texture.getSize().x, (float)window.getSize().y/texture.getSize().y));
    
    sprite.setPosition(sf::Vector2f(0.f, 0.f)); // absolute position
    bomba.setPosition(sf::Vector2f(10.f, 10.f)); // absolute position

/*  DEBUG CODE, USED TO GET THE SIZE OF THE SPRITE LOADED (X;Y)

    std::cout << "x: " << texture.getSize().x << std::endl;
    std::cout << "y: " << texture.getSize().y << std::endl;
*/

    // Main loop of the program
    while (window.isOpen())
    {
        // Clear the window before doing anything on the sprites and textures
        window.clear();

        // Draw the sprites on the window, the position of the sprites still need to be fix...
        //  (Here it's correctly set because it's on a corner and the size is based on the window's one)
        window.draw(sprite);
        drawTile();
        //window.draw(bomba);
        
        // Get every events appening on the window (click/keyboard/windows rezise/...)
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Get the close window event (every event are tracked like this)
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }


        // Display the window wich have every sprites on it, need to be the last line of code of the main loop !!
        window.display();
    }
}

Game::~Game()
{

}


void Game::inputEvent()
{

}

void Game::drawTile()
{
    for (int i = 0; i < map.tileList.size(); i++)
    {
        for (int j = 0; j < map.tileList[i].size(); j++)
        {
            Tile tile = map.tileList[i][j];
            tile.sprite.setTexture(getTexture(tile.getSpriteValue()));
            tile.sprite.setPosition(tile.getPosX(), tile.getPosY());
            // tile.sprite.scale(sf::Vector2f((float)pWindow->getSize().x/getTexture(tile.getSpriteValue()).getSize().x, (float)pWindow->getSize().y/getTexture(tile.getSpriteValue()).getSize().y));
            
            pWindow->draw(tile.sprite);
        }
    }
}

void Game::loadTextures()
{
    if (!caseHiden.loadFromFile("src/img/spriteSheet.png", sf::IntRect(0*TEXTURE_SIZE_X,0*TEXTURE_SIZE_Y,TEXTURE_SIZE_X,TEXTURE_SIZE_Y)))
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

sf::Texture Game::getTexture(caseSpriteValue tileValue)
{
    sf::Texture texture;
    switch (tileValue) {
    case CaseHidden:
        texture = caseHiden;
        break;
    case CaseBackground:
        texture = caseBackground;
        break;
    case CaseHover:
        texture = caseHover;
        break;
    case CaseOneColored:
        texture = caseOneColored;
        break;
    case CaseTwoColored:
        texture = caseTwoColored;
        break;
    case CaseThreeColored:
        texture = caseThreeColored;
        break;
    case CaseFourColored:
        texture = caseFourColored;
        break;
    case CaseFiveColored:
        texture = caseFiveColored;
        break;
    case CaseSixColored:
        texture = caseSixColored;
        break;
    case CaseSevenColored:
        texture = caseSevenColored;
        break;
    case CaseEightColored:
        texture = caseEightColored;
        break;
    case CaseNineColored:
        texture = caseNineColored;
        break;
    case Zero:
        texture = zero;
        break;
    case One:
        texture = one;
        break;
    case Two:
        texture = two;
        break;
    case Three:
        texture = three;
        break;
    case Four:
        texture = four;
        break;
    case Five:
        texture = five;
        break;
    case Six:
        texture = six;
        break;
    case Seven:
        texture = seven;
        break;
    case Eight:
        texture = eight;
        break;
    case Nine:
        texture = nine;
        break;
    case Bomb:
        texture = bomb; 
        break;
    case BombExploded:
        texture = bombExploded;
        break;
    case Flag:
        texture = flag;
        break;
    case FlagMissed:
        texture = flagMissed;
        break;
    default:
        texture = gyarados;
    }
    return texture;
}

void Game::errorLoadingSprite()
{
    std::cout << "error loading sprite " << std::endl;
}