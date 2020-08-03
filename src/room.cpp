#pragma once
#include "room.hpp"


Room::Room() : size_.first(100.0), size_second(100.0) {}

std::list<Entity*> Room::GetPlayer() {
    return player_;
}

std::list<Entity*> Room::GetEnemies() {
    return enemies_;
}

std::list<Entity*> Room::GetConnections() {
    return connections_;
}

std::list<Entity*> Room::GetProjectiles() {
    return projectiles_;
}

std::list<Entity*> Room::GetObstacles() {
    return obstacles_;
}

double Room::GetWidth() {
    return size_.first;
}

double Room::GetHeight() {
    return size_.second;
}
