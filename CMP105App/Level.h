#pragma once
#include <SFML/Graphics.hpp>
#include "Framework/BaseLevel.h"
#include "Framework/Input.h"
#include "Framework/GameObject.h"
#include "Player.h"
#include "Map0.h"

class Level : BaseLevel {
public:
    Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud);
    ~Level();

    void handleInput(float dt, Input& input) override;
    void update(float dt, Input& input) override;
    void render() override;

    // Default functions for rendering to the screen.

    sf::View view;
    Player player;
    sf::Texture playerTexture;
    sf::RectangleShape collisionBox;
    map0* tileMap;
    // Default variables for level class.

};