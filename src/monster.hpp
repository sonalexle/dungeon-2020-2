#include "entity.hpp"
#include "player.hpp"
#include <SFML/Graphics.hpp>

class Monster : public Entity
{
    public:

    Monster();

    Monster(float x, float y, sf::Vector2f velocity, int hp, Player* p);

    const std::string GetSpriteName() const;

    void load();

    int GetHP();

    void SetHP(int);

    void SetPlayer(Player*);

    Player* GetPlayer();

    protected:

    sf::Sprite sprite_;

    int hp_;

    Player* p_;

};

class Orc : public Monster
{
    public:
    Orc() = delete;
    Orc(float x, float y, Player* p);
    void update(sf::Time dt);
};

class Orge : public Monster
{
    public:
    Orge() = delete;
    Orge(float x, float y, Player* p);
    void update(sf::Time dt);
};