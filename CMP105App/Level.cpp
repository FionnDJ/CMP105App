#include "Framework/Collision.h"
#include "Framework/GameState.h"
#include "Level.h"
#include "Map0.h"

Level::Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud) {
	
	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;

	tileMap = new map0;
	gameState->setCurrentState(State::MENU);

	// Set up menu textures
	menuTexture.loadFromFile("gfx/Menu.png");
	menu.setSize(sf::Vector2f(1800, 900));
	menu.setTexture(&menuTexture);
	menu.setPosition(0, 0);

	// Set up pause textures
	pauseTexture.loadFromFile("gfx/Pause.png");
	pause.setSize(sf::Vector2f(1800, 900));
	pause.setTexture(&pauseTexture);
	pause.setPosition(0, 0);

	// Set up credits/win textures
	creditsTexture.loadFromFile("gfx/Credits.png");
	credits.setSize(sf::Vector2f(1800, 900));
	credits.setTexture(&creditsTexture);
	credits.setPosition(0, 0);

	// Set up background music (BGM)
	audio->addMusic("sfx/02 - DavidKBD - Belmont Chronicles Pack - The Mystic Forest.ogg", "BGM");

	// Set view
	view = sf::View(sf::FloatRect(0, 0, hwnd->getSize().x, hwnd->getSize().y));
	view.setCenter(view.getSize().x / 2.f, view.getSize().y / 2.f);

	// Set up the player
	playerTexture.loadFromFile("gfx/Knight - Full.png");
	player.setSize(sf::Vector2f(27, 47));
	player.setTexture(&playerTexture);
	player.setCollisionBox(sf::FloatRect(0, 0, 27, 47));
	player.setPosition(0, 700);

	// Find the player starting position
	playerStartingPosition = player.getPosition();

	// Set up the slime creature
	slimeCreatureTexture.loadFromFile("gfx/slimeSheet.png");
	slimeCreature.setSize(sf::Vector2f(52, 24));
	slimeCreature.setTexture(&slimeCreatureTexture);
	slimeCreature.setCollisionBox(sf::FloatRect(0, 0, 52, 24));
	slimeCreature.setCollider(true);
	slimeCreature.setPosition(980, 744);

	// Set up bonfire world object
	bonfireTexture.loadFromFile("gfx/bonfire.png");
	bonfireSprite.setSize(sf::Vector2f(55, 79));
	bonfireSprite.setTexture(&bonfireTexture);
	bonfireSprite.setCollisionBox(sf::FloatRect(0, 0, 55, 79));
	bonfireSprite.setCollider(true);
	bonfireSprite.setPosition(3500, 689);
}

// Player reset function
void Level::playerReset() {
	player.setPosition(playerStartingPosition);
}

// handle user input
void Level::handleInput(float dt, Input& input) {
	player.handleInput(dt, input);

	// Menu input
	if (((gameState->getCurrentState()) == State::MENU) && (input.isPressed(sf::Keyboard::Enter))) {
		gameState->setCurrentState(State::LEVEL);
	}

	// Pause
	if (((gameState->getCurrentState()) == State::LEVEL) && (input.isPressed(sf::Keyboard::Escape))) {
		gameState->setCurrentState(State::PAUSE);
	}

	// Unpause
	if (((gameState->getCurrentState()) == State::PAUSE) && (input.isPressed(sf::Keyboard::Space))) {
		gameState->setCurrentState(State::LEVEL);
	}
}

// Update game objects
void Level::update(float dt, Input& input) {

	switch (gameState->getCurrentState()) {
	
	case State::MENU:
		break;
	case State::LEVEL:
		// Play background music (BGM)
		if (audio->getMusic()->getStatus() == sf::SoundSource::Stopped) {
			audio->playMusicbyName("BGM");
		}

		// Have the camera follow player
		if ((player.getPosition().x < view.getCenter().x && view.getCenter().x > 900) || (player.getPosition().x > view.getCenter().x && view.getCenter().x < 3420)) {
			view.setCenter(player.getPosition().x, view.getSize().y / 2.f);
		}

		// Reset the player and camera if the player falls off the map or gets killed by an enemy creature
		if (player.getPosition().y > 1000 || Collision::checkBoundingBox(&player, &slimeCreature) && slimeCreature.isCollider()) {
			playerReset();
			view.setCenter(view.getSize().x / 2.f, view.getSize().y / 2.f);
		}

		if (Collision::checkBoundingBox(&player, &bonfireSprite) && bonfireSprite.isCollider()) {
			// Player collided with the flag
			// Show the win screen
			gameState->setCurrentState(State::CREDITS);
		}

		for (int i = 0; i < tileMap->getLevel()->size(); i++) {
			GameObject* tile = &(*tileMap->getLevel())[i];

			if (Collision::checkBoundingBox(&player, tile) && tile->isCollider()) {
				player.collisionDetection(tile, tileMap);
			}
		}

		player.update(dt, input);
		slimeCreature.update(dt);
		bonfireSprite.update(dt);
		break;
	case State::PAUSE:
		break;
	case State::CREDITS:
		break;
	}

	window->setView(view);
}

// Render level
void Level::render() {

	switch (gameState->getCurrentState()) {
	case State::MENU:
		beginDraw();
		window->setView(view);
		window->draw(menu);
		endDraw();
		break;
	case State::LEVEL:

		beginDraw();
		window->setView(view);

		for (int i = 0; i < tileMap->getLevel()->size(); i++) {
			GameObject* tile = &(*tileMap->getLevel())[i];
			window->draw(*tile);
		}

		window->draw(bonfireSprite);
		window->draw(player);
		window->draw(slimeCreature);
		endDraw();
		break;

	case State::PAUSE:
		view.setCenter(view.getSize().x / 2.f, view.getSize().y / 2.f);
		beginDraw();
		window->setView(view);
		window->draw(pause);
		endDraw();
		break;
	case State::CREDITS:
		view.setCenter(view.getSize().x / 2.f, view.getSize().y / 2.f);
		beginDraw();
		window->setView(view);
		window->draw(credits);
		endDraw();
		break;
	}
}

Level::~Level() {
	delete tileMap;
}