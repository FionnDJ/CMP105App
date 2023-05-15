#include "Level.h"
#include "Map0.h"
#include "Framework/Collision.h"


Level::Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud) {
	

	tileMap = new map0;

	view = sf::View(sf::FloatRect(0, 0, hwnd->getSize().x, hwnd->getSize().y));
	view.setCenter(view.getSize().x / 2.f, view.getSize().y / 2.f);

	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;
	playerTexture.loadFromFile("gfx/Knight - Full.png");
	player.setSize(sf::Vector2f(27, 47));
	player.setPosition(0, 0);
	player.setTexture(&playerTexture);
	player.setCollisionBox(sf::FloatRect(0, 0, 27, 47));
}

Level::~Level() {
	delete tileMap;
}

// handle user input
void Level::handleInput(float dt, Input& input) {
	player.handleInput(dt, input);
}

// Update game objects
void Level::update(float dt, Input& input) {
	window->setView(view);

	player.update(dt, input);
	for (int i = 0; i < tileMap->getLevel()->size(); i++) {
		GameObject* tile = &(*tileMap->getLevel())[i];
		if (Collision::checkBoundingBox(&player, tile) && tile->isCollider())
		{
			player.collisionDetection(tile, tileMap);
		}
	}
}

// Render level
void Level::render()
{
	beginDraw();
	window->setView(view);

	for (int i = 0; i < tileMap->getLevel()->size(); i++) {
		GameObject* tile = &(*tileMap->getLevel())[i];
		window->draw(*tile);
	}

	window->draw(player);
	//window->draw();
	//window->draw();
	endDraw();
}