#include "stdafx.h"

#include "Mouse.h"
#include "../../App/app.h"
#include "../GameObject/GameObject.h"
#include "../Physics/Collision.h"

Mouse* Mouse::instance() {
    static Mouse *instance = new Mouse();
    return instance;
}

Mouse::Mouse() {
    this->width = 2.0f;
    this->height = 2.0f;
    // adding a circle for the collider of the mouse
    this->mouseCollider = new Collision(this, CollisionShape::CIRCLE, width, height, 0.0f, 0.0f);
    this->clicked = false;
    this->prevClicked = false;
}

// only return true if it is the mouse button lifting up
// that is, if it was held and then now it is not
bool Mouse::isClicked() { return clicked == false && prevClicked == true; }

Collision* Mouse::getCollision() { return mouseCollider; }

// updating the mouse position and the clicked states
void Mouse::update() {
    App::GetMousePos(x, y);
    prevClicked = clicked;
    if (App::IsKeyPressed(MK_LBUTTON)) clicked = true;
    else clicked = false;
}
