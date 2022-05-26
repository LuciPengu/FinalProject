#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include "Coin.h"

class Player {
public:
    Player(sf::Vector2f size) {
        player.setSize(size);
    }

    void drawTo(sf::RenderWindow& window) {
        window.draw(player);
    }

    void move(sf::Vector2f distance) {
        player.move(distance);
    }

    void setPos(sf::Vector2f newPos) {
        player.setPosition(newPos);
    }

    void setTexture(sf::Texture* texture) {
        player.setTexture(texture);
    }

    void setScale(sf::Vector2f newSize) {
        player.setSize(newSize);
    }

    int getY() {
        return player.getPosition().y;
    }

    int getX() {
        return player.getPosition().x;
    }

    sf::FloatRect getGlobalBounds() {
        return player.getGlobalBounds();
    }

    bool isCollidingWithCoin(Coin* coin) {
        if (player.getGlobalBounds().intersects(coin->getGlobalBounds())) {
            return true;
        }
        return false;
    }

    bool isCollidingWithEnemy(Player enemy) {
        if (player.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
            return true;
        }
        return false;
    }

private:
    sf::RectangleShape player;
};