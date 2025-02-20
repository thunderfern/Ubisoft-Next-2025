#include "stdafx.h"

#include "GameObject.h"
#include "../../App/app.h"
#include "../Physics/Physics.h"
#include "../Physics/Collision.h"

#include <string>

GameObject::GameObject() { state = true; }

GameObject::GameObject(std::string spritePath, int spriteRow, int spriteCol, float scale) {
    sprite = App::CreateSprite(spritePath.c_str(), spriteRow, spriteCol);
    x = 200.0f, y = 100.0f;
    sprite->SetFrame(0);
    sprite->SetScale(scale);
    width = sprite->GetWidth() * scale;
    height = sprite->GetHeight() * scale;
    state = true;
}

void GameObject::setState(bool s) { state = s; }

float GameObject::getX() { return x; }

float GameObject::getY() { return y; }

void GameObject::setPos(float xpos, float ypos) {
    x = xpos;
    y = ypos;
}

float GameObject::getWidth() { return width; }

float GameObject::getHeight() { return height; }

//template update function for GameObjects is just to apply the physics
void GameObject::update(float deltaTime) { 
    if (physics != NULL) physics->applyPhysics(deltaTime);
}

Physics* GameObject::getPhysics() { return physics; }

void GameObject::setPhysics(Physics *newPhysics) { physics = newPhysics; }

CSimpleSprite* GameObject::getSprite() { return sprite; }

void GameObject::addCollision(Collision *col) { collision.push_back(col); }

std::vector<Collision*> GameObject::getCollisionList() { return collision; }

GameObject::~GameObject() {
    // deleting all the collisions, physics and sprite, everything they own
    for (int i = 0; i < collision.size(); i++) {
        delete collision[i];
        collision[i] = NULL;
    }
    delete physics;
    delete sprite;
    physics = NULL;
    sprite = NULL;
}