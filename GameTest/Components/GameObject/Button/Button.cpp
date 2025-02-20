#include "stdafx.h"

#include <string>

#include "Button.h"
#include "../../Mouse/Mouse.h"
#include "../../Scene/SceneManager.h"
#include "../../Physics/Collision.h"
#include "../../../App/SimpleSprite.h"

// button constructor, adds a collision of a square to the button
Button::Button(std::string spritePath, int spriteRow, int spriteCol, float scale, int dframe, int sframe, int nextScene): GameObject(spritePath, spriteRow, spriteCol, scale), defaultFrame{dframe}, swapFrame{sframe}, nextScene{nextScene} { 
    Collision *col = new Collision(this, CollisionShape::SQUARE, width, -1 * height, -1 * width / 2, height / 2);
    collision.push_back(col);
    sprite->SetFrame(dframe);
}

void Button::update(float deltaTime) {
    // swaps the frame if the mouse is colliding with the button
    if (collision[0]->colliding(Mouse::instance()->getCollision())) {
        // if the button is clicked, swap the scene
        if (Mouse::instance()->isClicked() && nextScene != -1) SceneManager::instance()->nextScene = nextScene;
        sprite->SetFrame(swapFrame);
    }
    else sprite->SetFrame(defaultFrame);
    
}

bool Button::isClicked() {
    if (collision[0]->colliding(Mouse::instance()->getCollision())) {
        if (Mouse::instance()->isClicked()) return true;
    }
    return false;
}