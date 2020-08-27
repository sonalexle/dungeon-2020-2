#include "monster.hpp"
#define ORC_SPEED 15.f
#define ORGE_SPEED 5.f
#define ORC_HP 5
#define ORGE_HP 10
#define BOSS_HP 30
#define BOSS_N_SPEED 100.f //normal speed
#define BOSS_H_SPEED 50.f //enraged speed (H for hard)

Monster::Monster() {}

/** A constructor for a monster
 * @param x x-coord
 * @param y y-coord
 * @param velocity initial velocity
 * @param hp initial hit points
 * @param p the player shared vector
 */
Monster::Monster(float x, float y, sf::Vector2f velocity, int hp, std::shared_ptr<Player> p)
    : Entity(x, y, velocity), hp_(hp), p_(p), active_(true) {}

//renders a monster onscreen
void Monster::Draw(sf::RenderWindow* w) {
    sf::FloatRect m_rec = sprite_.getGlobalBounds();
    sf::RectangleShape m_box(sf::Vector2f(m_rec.width, m_rec.height));
    m_box.setOutlineThickness(2);
    m_box.setOutlineColor(sf::Color::Red);
    m_box.setFillColor(sf::Color::Transparent);
    m_box.setPosition(sf::Vector2f(currPos_.x*3, currPos_.y*3));
    w->draw(m_box);
    sprite_.setPosition(sf::Vector2f(currPos_.x*3, currPos_.y*3));
    w->draw(sprite_);
}

//Getters and setters for managing members
void Monster::SetHP(int hp) { hp_ = hp; }
int Monster::GetHP() { return hp_; }

void Monster::SetPlayer(std::shared_ptr<Player> p) { p_ = p; }
std::shared_ptr<Player> Monster::GetPlayer() { return p_; }

sf::Sprite& Monster::GetSprite() { return sprite_; }

//if a monster is not active (not dead), it won't be drawn
bool Monster::isActive() { return active_; }

//No part of a monster's sprite should be outside of the room on spawn
void Monster::AdjustSpawn() {
    auto bounds = sprite_.getGlobalBounds();
    if (currPos_.x+bounds.width/3 > p_->GetRoom()->GetWidth())
        currPos_ = sf::Vector2f(p_->GetRoom()->GetWidth()-bounds.width/3, currPos_.y);
    if (currPos_.y+bounds.height/3 > p_->GetRoom()->GetHeight())
        currPos_ = sf::Vector2f(currPos_.x, p_->GetRoom()->GetHeight()-bounds.height/3);
}

//subclass orc, patrols from one corner to the opposite one.
Orc::Orc(float x, float y, std::shared_ptr<Player> p)
    : Monster(x, y, sf::Vector2f(ORC_SPEED, ORC_SPEED), ORC_HP, p)
{
    sprite_ = sf::Sprite(p->GetTexture(), sf::IntRect(32,160,16,16));
    sprite_.setScale(sf::Vector2f(2, 2));
    AdjustSpawn();
}

//determines the behavior of an Orc
void Orc::update(sf::Time dt) {
    auto bounds = sprite_.getGlobalBounds();
    //checks collision with player
    if (!p_->CanDie() || !bounds.intersects(p_->GetSprite().getGlobalBounds())) {
        if(currPos_.x+bounds.width/3 > p_->GetRoom()->GetWidth()-1 || currPos_.y+bounds.height/3 > p_->GetRoom()->GetHeight()-1)
            velocity_ = sf::Vector2f(-ORC_SPEED, -ORC_SPEED);
        else if(currPos_.x < 1 || currPos_.y < 1)
            velocity_ = sf::Vector2f(ORC_SPEED, ORC_SPEED);
        currPos_ += dt.asSeconds() * velocity_;
    } else {
        hp_--;
        p_->SetHP(p_->GetHP()-1);
        p_->Immortal();
        std::cout << "oof!" << std::endl;
    }
    //when a monster dies it disappears and gives the player score
    if (hp_ <= 0) {
        active_ = false;
        p_->AddScore(5);
    }
}


//subclass orge, chases the player at constantly increasing speed
Orge::Orge(float x, float y, std::shared_ptr<Player> p)
    : Monster(x, y, sf::Vector2f(0, 0), ORGE_HP, p), aggro_(1)
{
    sprite_ = sf::Sprite(p->GetTexture(), sf::IntRect(101,181,22,28));
    sprite_.setScale(sf::Vector2f(2, 2));
    AdjustSpawn();
}

//determines the behavior of an Orge
void Orge::update(sf::Time dt) {
    if (p_->CanDie() && sprite_.getGlobalBounds().intersects(p_->GetSprite().getGlobalBounds())) {
        p_->SetHP(p_->GetHP()-3);
        p_->Immortal();
        std::cout << "OOF!" << std::endl;
    } else {
        sf::Vector2f target = p_->GetPosition();
        sf::Vector2f diff = target - currPos_;
        diff = diff/(float)sqrt(diff.x*diff.x + diff.y*diff.y);
        velocity_ = diff * ORGE_SPEED * aggro_;
    }
    currPos_ += dt.asSeconds() * velocity_;
    //aggro determines how fast the orge chases the player, increases over time
    aggro_ += dt.asSeconds() * 0.25;
    //when a monster dies it disappears and gives the player score
    if (hp_ <= 0) {
        active_ = false;
        p_->AddScore(20);
    }
}

//subclass Boss, the boss of the game. Defeat it for something interesting.

Boss::Boss(float x, float y, std::shared_ptr<Player> p)
    : Monster(x, y, sf::Vector2f(0, 0), BOSS_HP, p)
{
    sprite_ = sf::Sprite(p->GetTexture(), sf::IntRect(160,177,33,31));
    sprite_.setScale(sf::Vector2f(2, 2));
    AdjustSpawn();
    clock_.restart();
}

//Boss moves in a circle around the center of the room
void Boss::update(sf::Time dt) {
    auto bounds = sprite_.getGlobalBounds();
    sf::Vector2f center = p_->GetRoom()->GetSize()*(float)0.5-sf::Vector2f(bounds.width/6,bounds.height/6);
    sf::Vector2f accdir = currPos_ - center;
    float radius = std::sqrt(accdir.x*accdir.x + accdir.y*accdir.y);
    float elapsed = clock_.getElapsedTime().asSeconds();
    currPos_ = center + sf::Vector2f(std::cos(BOSS_N_SPEED/radius*elapsed), std::sin(BOSS_N_SPEED/radius*elapsed))*radius;
}
