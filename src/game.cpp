#include "game.hpp"
#include "graphics.cpp"

Game::Game(sf::RenderWindow *window) : score_(0), difficulty_(0), window_(window) 
{
    dungeon_ = Map(difficulty_);
    p1_ = new Player(dungeon_.GetStartingRoom());
    //inventory_ = new Inventory(p1_);
    clock_.restart();
    isRunning_ = true;
}
Game::~Game(){}


void Game::init() //might be redundant
{
    //game should also open all required sprites to memory, throw errors if files are not found.
}


void Game::input()
{
    sf::Event event;
    while(window_->pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
            //handle window close
                isRunning_ = false;
                break;

            case sf::Event::KeyPressed: 
            //pass keyboard input to the player object, needs to be updated if second player is implemented
            //note, the event only handles key down / key up, meaning that pressing a key must start the player moving
            //until the key is released, ie. the key up event is passed to the player!! 
                switch (event.key.code)
                {
                case sf::Keyboard::W:
                    p1_->accUp(true);
                    break;
                case sf::Keyboard::A:
                    p1_->accLeft(true);
                    break;
                case sf::Keyboard::S:
                    p1_->accDown(true);
                    break;
                case sf::Keyboard::D:
                    p1_->accRight(true);
                    break;
                default:
                //could add other keys here...
                    break;
                }
                break;

            case sf::Event::KeyReleased:
                switch (event.key.code)
                {
                case sf::Keyboard::W:
                    p1_->accUp(false);
                    break;
                case sf::Keyboard::A:
                    p1_->accLeft(false);
                    break;
                case sf::Keyboard::S:
                    p1_->accDown(false);
                    break;
                case sf::Keyboard::D:
                    p1_->accRight(false);
                    break;
                default:
                //could add other keys here...
                    break;
                }
                break;
/*  ignoring mouse for now
            case sf::Event::MouseButtonPressed:
                mousestate_[event.mouseButton] = true;
                break;

            case sf::Event::MouseButtonReleased:
                mousestate_[event.mouseButton] = false;
                break;
*/
            default:
                break;
        }
    }
}

void    Game::update()
{
    sf::Time time = clock_.getElapsedTime();
    sf::Time elapsed = time - lastUpdate_;
    p1_->update(elapsed);
    /*for(auto i : p1_->GetRoom()->GetEnemies())
    {
        i->update(elapsed);
    }*/
    /*for(auto i : p1_->GetRoom()->GetProjectiles())
    {
        i->update(elapsed);
    }
*/
    lastUpdate_ = time;

    //go through all the active entities in the current room and move them up to their speed.
    //enemy AI should happen here
    //check fore entity & projectile collision
    //
} 
void Game::render()
{
    window_->clear(sf::Color::Black);
    double scale = std::min(window_->getSize().y/1080,window_->getSize().x/1900);
    //placeholder
    sf::Vector2f roomSize = p1_->GetRoom()->GetSize();
    if(DEBUGGING){std::cout << roomSize.x << " " << roomSize.y << std::endl;}
    sf::RectangleShape room(sf::Vector2f(100,100));
    room.setFillColor(sf::Color::White);
    sf::CircleShape player(10);
    player.setFillColor(sf::Color(100, 250, 50));
    player.setPosition(p1_->GetPosition());
    window_->draw(room);
    window_->draw(player);
    /* draw the background, room, player and all other entities */ 
    window_->display();
}

void Game::clean()
{
    window_->close();
    //memory cleanup on game close, will be created later...
}
