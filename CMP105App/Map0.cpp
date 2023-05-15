#include "Map0.h"

map0::map0() {
	// Load the tile sheet for the map tiles
	loadTexture("gfx/Stringstar Fields.png");

	GameObject tile;

	// For loop to create array of the size needed
	for (int i = 0; i < 40; i++) {
		tile.setSize(sf::Vector2f(48, 48));
		tile.setCollisionBox(0, 0, 48, 48);
		tile.setCollider(true);
		tileSet.push_back(tile);
	}

	// Define where on the tile sheet the tiles are
	tileSet[0].setCollider(false);
	tileSet[0].setTextureRect(sf::IntRect(160, 160, 16, 16)); // Air tile

	tileSet[1].setTextureRect(sf::IntRect(0, 144, 16, 16)); // Ground Tile 1

	tileSet[2].setTextureRect(sf::IntRect(16, 144, 16, 16)); // Ground Tile 2 - Left
	tileSet[3].setTextureRect(sf::IntRect(32, 144, 16, 16)); // Ground Tile 2 - Middle
	tileSet[4].setTextureRect(sf::IntRect(48, 144, 16, 16)); // Ground Tile 2 - Right

	tileSet[5].setTextureRect(sf::IntRect(64, 144, 16, 16)); // Ground Tile 3

	tileSet[6].setTextureRect(sf::IntRect(80, 144, 16, 16)); // Ground Tile 4

	tileSet[7].setTextureRect(sf::IntRect(96, 144, 16, 16)); // Ground Tile 5 - Far Left
	tileSet[8].setTextureRect(sf::IntRect(112, 144, 16, 16)); // Ground Tile 5 - Left
	tileSet[9].setTextureRect(sf::IntRect(128, 144, 16, 16)); // Ground Tile 5 - Center Left
	tileSet[10].setTextureRect(sf::IntRect(144, 144, 16, 16)); // Ground Tile 5 - Center Right
	tileSet[11].setTextureRect(sf::IntRect(160, 144, 16, 16)); // Ground Tile 5 - Right
	tileSet[12].setTextureRect(sf::IntRect(176, 144, 16, 16)); // Ground Tile 5 - Far Right

	tileSet[13].setTextureRect(sf::IntRect(192, 144, 16, 16)); // Ground Tile 6 - Left
	tileSet[14].setTextureRect(sf::IntRect(208, 144, 16, 16)); // Ground Tile 6 - Right

	tileSet[15].setTextureRect(sf::IntRect(224, 144, 16, 16)); // Ground Tile 7 - Left
	tileSet[16].setTextureRect(sf::IntRect(240, 144, 16, 16)); // Ground Tile 7 - Middle
	tileSet[17].setTextureRect(sf::IntRect(256, 144, 16, 16)); // Ground Tile 7 - Right

	tileSet[18].setTextureRect(sf::IntRect(272, 144, 16, 16)); // Ground Tile 8

	tileSet[19].setTextureRect(sf::IntRect(0, 160, 16, 16)); // Ground Tile 9

	tileSet[20].setTextureRect(sf::IntRect(16, 160, 16, 16)); // Ground Tile 10

	tileSet[21].setTextureRect(sf::IntRect(32, 160, 16, 16)); // Ground Tile 11 - Left
	tileSet[22].setTextureRect(sf::IntRect(48, 160, 16, 16)); // Ground Tile 11 - Right

	tileSet[23].setTextureRect(sf::IntRect(64, 160, 16, 16)); // Ground Tile 12 - Left
	tileSet[24].setTextureRect(sf::IntRect(80, 160, 16, 16)); // Ground Tile 12 - Right

	tileSet[25].setTextureRect(sf::IntRect(96, 160, 16, 16)); // Ground Tile 13 - Left
	tileSet[26].setTextureRect(sf::IntRect(112, 160, 16, 16)); // Ground Tile 13 - Right

	tileSet[27].setTextureRect(sf::IntRect(128, 160, 16, 16)); // Ground Tile 14 - Left
	tileSet[28].setTextureRect(sf::IntRect(144, 160, 16, 16)); // Ground Tile 14 - Right

	tileSet[29].setTextureRect(sf::IntRect(80, 64, 16, 16)); // Ledge - Far Left
	tileSet[30].setTextureRect(sf::IntRect(96, 64, 16, 16)); // Ledge - Left
	tileSet[31].setTextureRect(sf::IntRect(112, 64, 16, 16)); // Ledge - Middle
	tileSet[32].setTextureRect(sf::IntRect(128, 64, 16, 16)); // Ledge - Right
	tileSet[33].setTextureRect(sf::IntRect(144, 64, 16, 16)); // Ledge - Far Right

	// Set the map dimensions
	mapDimensions = sf::Vector2u(45, 5);

	// Define how the tile map will look, using the tiles defined above
	tileMap = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 14, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 21, 22, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		7, 8, 9, 10, 11, 12, 2, 3, 4, 15, 16, 17, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 14, 15, 13, 7, 8, 9, 10, 11, 12, 1, 2, 3, 4, 5, 6, 1,
	};

	// Set the position of where the map rendering starts and then build the level
	setPosition(sf::Vector2f(0, 0));
	buildLevel();
}

map0::~map0() {
}