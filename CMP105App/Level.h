#pragma once
#include <SFML/Graphics.hpp>
#include "Framework/BaseLevel.h"
#include "Framework/Input.h"
#include "Framework/GameObject.h"
#include "Player.h"
#include "gameEntities.h"
#include "Map0.h"

class Level : BaseLevel {
public:
    Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud);
    ~Level();

    void handleInput(float dt, Input& input) override;
    void update(float dt, Input& input) override;
    void render() override;
    void playerReset();

    sf::View view;

    GameObject menu;
    sf::Texture menuTexture;

    GameObject pause;
    sf::Texture pauseTexture;

    GameObject credits;
    sf::Texture creditsTexture;

    Player player;
    sf::Vector2f playerStartingPosition;
    sf::Texture playerTexture;

    bonfireSprite bonfireSprite;
    sf::Texture bonfireTexture;

    slimeCreature slimeCreature;
    sf::Texture slimeCreatureTexture;

    sf::RectangleShape collisionBox;
    map0* tileMap;
};