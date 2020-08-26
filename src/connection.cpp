#include "connection.hpp"

Connection::Connection() : Entity() {}

Connection::Connection(float x, float y, Player* p) : Entity(x, y, sf::Vector2f()), locked_(true), player_(p) {}

void Connection::unlock() { locked_ = false;}

const std::string Connection::GetSpriteName() const {return "door.png";}

void Connection::update(sf::Time dt) {
    if (sprite_.getGlobalBounds().intersects(player_->GetSprite().getGlobalBounds())) {
        traverse();
    }
}

void Connection::load() {}

void Connection::traverse() {
    double size = player_->GetRoom()->GetHeight();
        if (currPos_.x == size / 2 && currPos_.y == 0.0) { //Connection is north

            Room* nn = player_->GetRoom()->GetNConn();
            player_->SetRoom(nn);
            player_->SetPosition(sf::Vector2f(size / 2, size));
            
        if (currPos_.x == size && currPos_.y == size / 2) { // South

            Room* sn = player_->GetRoom()->GetSConn();
            player_->SetRoom(sn);
            player_->SetPosition(sf::Vector2f(size / 2, 0.0));
        }
        if (currPos_.x == 0 && currPos_.y == size / 2) { // West

            Room* wn = player_->GetRoom()->GetWConn();
            player_->SetRoom(wn);
            player_->SetPosition(sf::Vector2f(size, size / 2));
        }
        if (currPos_.x == size && currPos_.y == size / 2) { // East

            Room* en = player_->GetRoom()->GetEConn();
            player_->SetRoom(en);
            player_->SetPosition(sf::Vector2f(0.0, size / 2));
        }
    }  
}

void Connection::draw(sf::RenderWindow* window) { 
    // if(this->locked_ == false){}

    sf::FloatRect m_rec = sprite_.getGlobalBounds();
    sf::RectangleShape m_box(sf::Vector2f(m_rec.width, m_rec.height));
    m_box.setOutlineThickness(2);
    m_box.setOutlineColor(sf::Color::Red);
    m_box.setFillColor(sf::Color::Transparent);
    m_box.setPosition(sf::Vector2f(currPos_.x*3, currPos_.y*3));
    window->draw(m_box);
    sprite_.setPosition(sf::Vector2f(currPos_.x*3, currPos_.y*3));
    window->draw(sprite_);
    
}