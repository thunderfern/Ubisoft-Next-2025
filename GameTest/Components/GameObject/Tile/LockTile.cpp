#include "stdafx.h"

#include "LockTile.h"
#include "../../../App/app.h"
#include "../../Physics/Collision.h"

LockTile::LockTile(TileColour c) {
    colour = c;
    // creating the sprite based off of what colour it needs to be
    sprite = App::CreateSprite("Assets/keyblocks.png", 4, 4);
    if (colour == TileColour::PURPLE) sprite->SetFrame(0);
    else if (colour == TileColour::ROUGE) sprite->SetFrame(2);
    else if (colour == TileColour::GREEN) sprite->SetFrame(4);
    else sprite->SetFrame(6);
    sprite->SetScale(0.25f);
    width = sprite->GetWidth() * sprite->GetScale();
    height = sprite->GetHeight() * sprite->GetScale();

    // adding the lines for the collision of the box
    Collision *col = new Collision(this, CollisionShape::LINE, width, 0.0f, width / -2, height / 2);
    Collision *col1 = new Collision(this, CollisionShape::LINE, 0.0f, height * -1, width / 2, height / 2);
    Collision *col2 = new Collision(this, CollisionShape::LINE, width, 0.0f, width / -2, height / -2);
    Collision *col3 = new Collision(this, CollisionShape::LINE, 0.0f, height * -1, width / -2, height / 2);

    // adding the collisions to the end of the collision list to store it
    collision.push_back(col);
    collision.push_back(col1);
    collision.push_back(col2);
    collision.push_back(col3);
}

// when this tile is notifed by the unlock tile, it should no longer be on the screen
void LockTile::notify() {
    setState(false);
}