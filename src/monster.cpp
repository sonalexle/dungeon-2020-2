#include "monster.hpp"
#include <iostream>
#define ORC_HP 100
#define SPEED 20

Monster::Monster(float x, float y, Room* room, sf::Vector2f velocity, int hp) : room_(room), velocity_(velocity), hp_(hp),
    Entity(x, y) {}

const std::string Monster::GetSpriteName() const { return "monster.png"; }

void Monster::load() {
    sf::Texture texture_;
    texture_.loadFromFile(GetSpriteName(), sf::IntRect(currPos_.x, currPos_.y, SPEED, SPEED));
    sprite_.setTexture(texture_);
}

int Monster::GetHP() { return hp_; }

void Monster::SetHP(int hp) { hp_ = hp; }

Orc::Orc(float x, float y, Room* room) : Monster(x, y, room, sf::Vector2f(0, 0), ORC_HP) {}

void Orc::update(sf::Time dt) {
    if(currPos_.x >= room_->GetWidth() && currPos_.y >= room_->GetHeight())
        velocity_ = sf::Vector2f(-SPEED, -SPEED);
    if(currPos_.x < 0 && currPos_.y < 0) {
        velocity_ = sf::Vector2f(SPEED, SPEED);
    }
    currPos_ += dt.asSeconds() * velocity_;
}