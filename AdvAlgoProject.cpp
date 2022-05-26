#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Coin.h"
#include <sstream>
#include <vector>

int main() {
    sf::RenderWindow window;

    sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);

    window.create(sf::VideoMode(503, 503), "SFML Gravity", sf::Style::Titlebar | sf::Style::Close);
    window.setPosition(centerWindow);

    window.setKeyRepeatEnabled(true);

    sf::Texture walking1;
    walking1.loadFromFile("Walking_Borio1.png");
    sf::Texture walking2;
    walking2.loadFromFile("Walking_Borio2.png");
    sf::Texture walking3;
    walking3.loadFromFile("Walking_Borio3.png");

    sf::Texture backgroundImage;
    backgroundImage.loadFromFile("Background.jpg");
    Player background({ 503, 503 });
    background.setPos({ 0, 0 });
    background.setTexture(&backgroundImage);

    sf::Texture grassImg;
    grassImg.loadFromFile("Grass.jpg");
    Player grass({ 1006, 59 });
    grass.setPos({ 0, 445 });
    grass.setTexture(&grassImg);

    Player player({ 60, 100 });
    player.setPos({ 50, 200 });
    player.setTexture(&walking1);

    sf::Texture enemy1Img;
    enemy1Img.loadFromFile("enemy1.png");


    sf::Texture enemy2Img;
    enemy2Img.loadFromFile("enemy2.png");

    sf::Texture enemy3Img;
    enemy3Img.loadFromFile("enemy3.png");


    std::vector<Coin*> coinVec;
    Coin coin1({ 20, 20 });
    Coin coin2({ 20, 20 });
    coinVec.push_back(&coin1);
    coinVec.push_back(&coin2);

    coin1.setPos({ 50, 600 });
    coin2.setPos({ 100, 600 });

    int score = 0;

    sf::Font arial;
    arial.loadFromFile("mario.ttf");

    std::ostringstream ssScore;
    ssScore << "Score: " << score;

    sf::Text lblScore;
    lblScore.setCharacterSize(30);
    lblScore.setPosition({ 10, 10 });
    lblScore.setFont(arial);
    lblScore.setString(ssScore.str());

    const int groundHeight = 400;
    const float gravitySpeed = 0.3;
    bool isJumping = false;
    const float jumpPower = 300;
    float randomTimer = rand() % 900;
    std::vector<Player> enemies;
    float enemySpeed = -0.15f;
    float currJump = 0;
    int timing = 0;
    int animationTimer = 0;
    const float jumpSpeed = 1;
    bool paused = false;

    while (window.isOpen()) {

        sf::Event Event;

        if (paused)
            continue;
        
        timing++;
        animationTimer++;

        if (player.getY() < groundHeight) {
            player.setTexture(&walking1);
        }
        else if (animationTimer <= 50) {
            player.setTexture(&walking3);
        }
        else if (animationTimer <= 100) {
            player.setTexture(&walking2);
        }
        else {
            player.setTexture(&walking1);
        }
        if (animationTimer >= 150)
            animationTimer = 0;


        if (timing >= 3000-randomTimer) {
            timing=0;
            score += 100;
            ssScore.str("");
            ssScore << "Score " << score;
            lblScore.setString(ssScore.str());
            randomTimer = rand() % 650;
            enemySpeed -= 0.01;
            Player enemy({ 40, 30 });
            int rando = rand() % 3;
            switch (rando)
            {
                case 0:
                    enemy.setScale({ 50,50 });
                    enemy.setPos({ 700, 440 });
                    enemy.setTexture(&enemy1Img);
                    enemies.push_back(enemy);
                    break;
                case 1:
                    enemy.setScale({ 74,54 });
                    enemy.setPos({ 700, 340 });
                    enemy.setTexture(&enemy2Img);
                    enemies.push_back(enemy);
                    break;
                case 2:
                    enemy.setScale({ 66,54 });
                    enemy.setPos({ 700, 440 });
                    enemy.setTexture(&enemy3Img);
                    enemies.push_back(enemy);
                    break;
                default:
                    break;
            }
        }       


      
        if (currJump > 0) {
            player.move({ 0, -jumpSpeed });
            currJump--;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player.getY() >= groundHeight){
            currJump = jumpPower;
            isJumping = true;
        }

        while (window.pollEvent(Event)) {
            switch (Event.type) {

            case sf::Event::Closed:
                window.close();

            case sf::Event::KeyReleased:
                isJumping = false;
            }
        }

        if (player.getY() < groundHeight && currJump <= 0) {
            player.move({ 0, gravitySpeed });
        }

        for (int i = 0; i < coinVec.size(); i++) {
            if (player.isCollidingWithCoin(coinVec[i])) {
                coinVec[i]->setPos({ 422234, 423432 });
                score++;
                ssScore.str("");
                ssScore << "Score " << score;
                lblScore.setString(ssScore.str());
            }
        }
        window.clear();
        background.drawTo(window);
        grass.drawTo(window);
        coin1.drawTo(window);
        window.draw(lblScore);
        coin2.drawTo(window);
        player.drawTo(window);
        for (int i = 0; i < enemies.size(); i++) {

            enemies[i].drawTo(window);
            enemies[i].move({ enemySpeed,0 });
            if (player.isCollidingWithEnemy(enemies[i])) {
                paused = true;
            }
        }

        window.display();

    }
}