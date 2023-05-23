#include "gameEntities.h"

// Bonfire
bonfireSprite::bonfireSprite() {
    
    // Set up the bonfire animation frames
    bonfire.addFrame(sf::IntRect(0, 0, 55, 79));
    bonfire.addFrame(sf::IntRect(55, 0, 55, 79));
    bonfire.addFrame(sf::IntRect(110, 0, 55, 79));
    bonfire.addFrame(sf::IntRect(165, 0, 55, 79));
    bonfire.addFrame(sf::IntRect(220, 0, 55, 79));

    bonfire.addFrame(sf::IntRect(0, 79, 55, 79));
    bonfire.addFrame(sf::IntRect(55, 79, 55, 79));
    bonfire.addFrame(sf::IntRect(110, 79, 55, 79));
    bonfire.addFrame(sf::IntRect(165, 79, 55, 79));
    bonfire.addFrame(sf::IntRect(220, 79, 55, 79));

    bonfire.addFrame(sf::IntRect(0, 158, 55, 79));
    bonfire.addFrame(sf::IntRect(55, 158, 55, 79));
    bonfire.addFrame(sf::IntRect(110, 158, 55, 79));
    bonfire.addFrame(sf::IntRect(165, 158, 55, 79));
    bonfire.addFrame(sf::IntRect(220, 158, 55, 79));

    bonfire.addFrame(sf::IntRect(0, 237, 55, 79));
    bonfire.addFrame(sf::IntRect(55, 237, 55, 79));
    bonfire.addFrame(sf::IntRect(110, 237, 55, 79));
    bonfire.addFrame(sf::IntRect(165, 237, 55, 79));
    bonfire.addFrame(sf::IntRect(220, 237, 55, 79));

    bonfire.setFrameSpeed(1.f / 12.f);

    currentBonfireAnimation = &bonfire;
}

// Creatures
slimeCreature::slimeCreature() {
    // Set up the slime animation frames
	slimeMove.addFrame(sf::IntRect(132, 12, 26, 12));
	slimeMove.addFrame(sf::IntRect(164, 12, 26, 12));
	slimeMove.addFrame(sf::IntRect(196, 12, 26, 12));
	slimeMove.addFrame(sf::IntRect(228, 13, 26, 12));

	slimeMove.setFrameSpeed(1.f / 8.f);

    currentAnimation = &slimeMove;
}

// Animate the bonfire
void bonfireSprite::update(float dt) {
    bonfire.animate(dt);
    setTextureRect(bonfire.getCurrentFrame());

    void update(float dt);
}

// Animate and move the slime
void slimeCreature::update(float dt) {
    slimeMove.animate(dt);
    setTextureRect(slimeMove.getCurrentFrame());

    void update(float dt);

    // Set move speed
    moveSpeed = 100.0f;
    float horizontalMovement = moveSpeed * dt;

    activeDisplacement = 200;

    // Check the current direction, then move slime in accordance and flip the animation
    if (moveRight) {
        // Right movement
        move(horizontalMovement, 0);
        currentAnimation->setFlipped(true);
    }
    else {
        // Left movement
        move(-horizontalMovement, 0);
        currentAnimation->setFlipped(false);
        
    }

    // Update the displacement
    finalDisplacement += std::abs(horizontalMovement);

    // Check if the slime needs to change direction
    if (finalDisplacement >= activeDisplacement) {
        // Reverse the direction
        moveRight = !moveRight;
        finalDisplacement = 0.0f;
    }
}

slimeCreature::~slimeCreature() {

}

bonfireSprite::~bonfireSprite() {

}