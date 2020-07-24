#include "game.hpp"

Game::Game()
{}
Game::~Game()
{}

void Game::init() //add arguments?? 
{
    sf::RenderWindow    window(sf::VideoMode(800, 600),    "TEST GAME");
    dungeon_    =   Map();
    score_  =   0;
    difficulty_ =   0;
    p1_     =   Player();
    window_ = &window;
    clock_.restart();
}

void    Game::input()
{
    sf::Event event;
    while(window_->pollEvent(event))
    {
        switch(event.type)
        {
            case    sf::Event::Closed:
            //handle window close
                window_->close();
                isRunning_  =    false;
                break;
            case    sf::Event::KeyEvent:
            //pass keyboard input to the player object, needs to be updated if second player is implemented
            //note, the event only handles key down / key up, meaning that pressing a key must start the player moving
            //until the key is released, ie. the key up event is passed to the player!! 
                if(event.code   ==  Escape)
                {
                    //code to pause the game
                }
                else
                {
                    p1_.input(event.code);
                }
                break;
            case    sf::Event::MouseButtonEvent:
                p1_.action(event);
                break;
            default:
                
        }
    }
}

void    Game::update()
{
    for(auto i : p1_.room.denizens)
    {
        i.update(clock_.getElapsedTime()-lastUpdate_);
    }
    p1_.update(clock_.getElapsedTime()-lastUpdate_);
    
    lastUpdate_ = clock_.getElapsedTime();

    //go through all the active entities in the current room and move them up to their speed.
    //enemy AI should happen here
    //check fore entity & projectile collision
    //
}

void    Game::render()
{
    /* draw the background, room, player and all other entities */ 
    
}

void    Game::clean()
{
    //memory cleanup on game close
}
