#include "Player.h"
#include "Framework/VectorHelper.h"
#include "Level.h"
#include "Framework/Collision.h"


Player::Player() : speed(20.f), grounded(false), isColliding(false) {
    
    // Setup idle animation
    idle.addFrame(sf::IntRect(0, 3, 27, 47));
    idle.addFrame(sf::IntRect(128, 3, 27, 47));
    idle.addFrame(sf::IntRect(0, 67, 27, 47));
    idle.addFrame(sf::IntRect(128, 67, 27, 47));
    idle.addFrame(sf::IntRect(0, 131, 27, 47));
    idle.addFrame(sf::IntRect(128, 131, 27, 47));
    idle.addFrame(sf::IntRect(0, 196, 27, 47));
    idle.addFrame(sf::IntRect(128, 196, 27, 47));

    idle.setFrameSpeed(1.f / 4.f);

    // Setup run animation.
    run.addFrame(sf::IntRect(254, 5, 31, 45));
    run.addFrame(sf::IntRect(380, 4, 33, 46));
    run.addFrame(sf::IntRect(252, 68, 34, 46));
    run.addFrame(sf::IntRect(381, 68, 31, 46));
    run.addFrame(sf::IntRect(254, 133, 31, 45));
    run.addFrame(sf::IntRect(382, 132, 30, 46));
    run.addFrame(sf::IntRect(252, 196, 32, 46));
    run.addFrame(sf::IntRect(381, 196, 31, 46));

    run.setFrameSpeed(1.f / 8.f);

    // Setup jump animation.
    // Ascending
    jump.addFrame(sf::IntRect(513, 6, 28, 44));
    jump.addFrame(sf::IntRect(639, 0, 32, 49));
    jump.addFrame(sf::IntRect(517, 64, 27, 47));
    jump.addFrame(sf::IntRect(642, 66, 31, 44));
    // Descending
    jump.addFrame(sf::IntRect(513, 132, 32, 44));
    jump.addFrame(sf::IntRect(642, 134, 28, 44));
    jump.addFrame(sf::IntRect(512, 201, 28, 41));
    jump.addFrame(sf::IntRect(640, 197, 29, 45));

    jump.setFrameSpeed(1.f / 8.f);

    currentAnimation = &idle;
    setTextureRect(currentAnimation->getCurrentFrame());
}

void Player::update(float dt, Input& input) {
    // Set default animation
    currentAnimation->animate(dt);
    setTextureRect(currentAnimation->getCurrentFrame());

    // Setup horizontal acceleration
    const float accelerationX = 100.0f;

    std::cout << "Player position: (" << getPosition().x << ", " << getPosition().y << ")" << std::endl;
    std::cout << "Player velocity: (" << velocity.x << ", " << velocity.y << ")" << std::endl;

    sf::Vector2f acceleration;
    acceleration = sf::Vector2f(0, 150.0f);

    // Horizontal component of player movement
    if (input.isKeyDown(sf::Keyboard::A)) {
        acceleration.x -= accelerationX;

        // Set the run animation and flip it
        currentAnimation = &run;
        currentAnimation->setFlipped(true);

        setTextureRect(currentAnimation->getCurrentFrame());
    } else if (input.isKeyDown(sf::Keyboard::D)) {
        acceleration.x += accelerationX;

        // Set the run animation
        currentAnimation = &run;
        currentAnimation->setFlipped(false);

        setTextureRect(currentAnimation->getCurrentFrame());
    } else /* Animation for idle/no movement */ {
            currentAnimation = &idle;
            velocity.x = 0.0f;
    }

    // Apply acceleration to velocity
    velocity += acceleration * dt;

    // Limit horizontal speed to a maximum
    const float maxSpeed = 100.0f;
    if (velocity.x > maxSpeed) {
        velocity.x = maxSpeed;
    }
    else if (velocity.x < -maxSpeed) {
        velocity.x = -maxSpeed;
    }

    move(velocity * dt);
}

void Player::handleInput(float dt, Input& input) {
    // Player movement up
    if (input.isKeyDown(sf::Keyboard::Space)) {
        velocity.y = -125.0f;
        std::cout << "you have pressed space";
        grounded = false;
    }
}

void Player::collisionDetection(GameObject* collider, map0* tileMap) {
    sf::FloatRect playerBounds = getCollisionBox();
    sf::FloatRect tileBounds = collider->getCollisionBox();

    // Calculate player position post-collision
    float offsetX = playerBounds.left - tileBounds.left;
    float offsetY = playerBounds.top - tileBounds.top;

    std::cout << "Overlap X: " << std::abs(offsetX) << std::endl;
    std::cout << "Overlap Y: " << std::abs(offsetY) << std::endl;
    std::cout << "Player position: (" << getPosition().x << ", " << getPosition().y << ")" << std::endl;
    std::cout << "Player size: (" << getSize().x << ", " << getSize().y << ")" << std::endl;
    std::cout << "Collider position: (" << collider->getPosition().x << ", " << collider->getPosition().y << ")" << std::endl;
    std::cout << "Collider size: (" << collider->getSize().x << ", " << collider->getSize().y << ")" << std::endl;

    if (std::abs(offsetX) > std::abs(offsetY)) {
        // Adjust player position on the X axis
        if (offsetX > 0) {
            move(tileBounds.width - offsetX, 0);
        }
        else {
            move(-tileBounds.width - offsetX, 0);
        }
    }
    else {
        // Adjust player position on the Y axis
        if (offsetY > 0) {

            move(0, -offsetY);

            // Ensure the player is in contact with the top of the tile
            if (getPosition().y < collider->getPosition().y) {
                setPosition(getPosition().x, collider->getPosition().y);
            }
            // set the player's velocity to a negative value to simulate bouncing off the ground
            velocity.y = -std::abs(velocity.y * 0.0f);
            grounded = true;
        }
        else {
            move(0, -tileBounds.height - offsetY);
        }
    }

    // Check for player collision with the tile below player
    bool hitGround = false;
    for (int i = 0; i < tileMap->getLevel()->size(); i++)
    {
        GameObject* tile = &(*tileMap->getLevel())[i];
        if (tile->isCollider() && tile->getPosition().y > getPosition().y &&
            tile->getPosition().y < getPosition().y + getCollisionBox().height &&
            tile->getPosition().x < getPosition().x + getCollisionBox().width &&
            tile->getPosition().x + tile->getCollisionBox().width > getPosition().x)
        {
            hitGround = true;
            break;
        }
    }
    grounded = hitGround;
}

Player::~Player() {

}