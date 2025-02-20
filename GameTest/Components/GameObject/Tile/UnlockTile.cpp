#include "stdafx.h"

#include "UnlockTile.h"
#include "LockTile.h"
#include "../../../App/app.h"
#include "../../Physics/Collision.h"

UnlockTile::UnlockTile(TileColour c) {
    // adding the sprite based off the colour and setting the basic information
    colour = c;
    sprite = App::CreateSprite("Assets/keyblocks.png", 4, 4);
    if (colour == TileColour::PURPLE) sprite->SetFrame(1);
    else if (colour == TileColour::ROUGE) sprite->SetFrame(3);
    else if (colour == TileColour::GREEN) sprite->SetFrame(5);
    else sprite->SetFrame(7);
    sprite->SetScale(0.25f);
    width = sprite->GetWidth() * sprite->GetScale();
    height = sprite->GetHeight() * sprite->GetScale();

    // adding the lines to create a box collision
    Collision *col = new Collision(this, CollisionShape::LINE, width, 0.0f, width / -2, height / 2);
    Collision *col1 = new Collision(this, CollisionShape::LINE, 0.0f, height * -1, width / 2, height / 2);
    Collision *col2 = new Collision(this, CollisionShape::LINE, width, 0.0f, width / -2, height / -2);
    Collision *col3 = new Collision(this, CollisionShape::LINE, 0.0f, height * -1, width / -2, height / 2);

    // adding the collisions to the list of collisions for this game object
    collision.push_back(col);
    collision.push_back(col1);
    collision.push_back(col2);
    collision.push_back(col3);
}

// when this is hit, notify the locked tiles linked to this one so they can disappear from the screen
void UnlockTile::notifyTiles() {
    for (auto u : linkedTiles) u->notify();
}
 
// adding the locked tiles that observe this one
void UnlockTile::addObserver(LockTile* lockTile) {
    linkedTiles.push_back(lockTile);
}