#include "stdafx.h"

#include "../../../App/app.h"
#include "../../Physics/Physics.h"
#include "../../Physics/Collision.h"

#include "Tile.h"

Tile::Tile(int idx, float x, float y) {
    // adding the sprites + setting the basic information
    this->sprite = App::CreateSprite("Assets/golfcourse.png", 4, 4);
    this->sprite->SetFrame(idx);
    this->sprite->SetScale(0.25f);
    this->x = x;
    this->y = y;
    this->width = this->sprite->GetWidth() * this->sprite->GetScale();
    this->height = this->sprite->GetHeight() * this->sprite->GetScale();
    // adding physics object
    this->physics = new Physics(this, PhysicsType::STATIC, 10.0f, 0.0f, 0.0f, 0.0f);
    // adding the collisions for the tile based off what tile it is
    addCollision(idx);
};

// template line collision, is a helper function
Collision* tileCollisionTemplate(GameObject* obj, float width, float height, float xoffset, float yoffset) {
    Collision *col = new Collision(obj, CollisionShape::LINE, width, height, xoffset, yoffset);
    return col;
}

// adds the collision based off the lines that it needs for each tile
void Tile::addCollision(int idx) {

    Collision* col;

    switch (idx) {
        // top left
        case 0:
            col = tileCollisionTemplate(this, width, 0.0f, width / -2, height / 2); // horizontal
            collision.push_back(col);
            col = tileCollisionTemplate(this, 0.0f, height * -1, width / -2, height / 2); // vertical
            collision.push_back(col);
            break;
        // top
        case 1:
            col = tileCollisionTemplate(this, width, 0.0f, width / -2, height / 2); // horizontal
            collision.push_back(col);
            break;
        // top right
        case 2:
            col = tileCollisionTemplate(this, 0.0f, height * -1, width / 2, height / 2); // vertical
            collision.push_back(col);
            col = tileCollisionTemplate(this, width, 0.0f, width / -2, height / 2); // horizontal
            collision.push_back(col);
            break;
        // left
        case 4:
            col = tileCollisionTemplate(this, 0.0f, height * -1, width / -2, height / 2); // vertical
            collision.push_back(col);
            break;
        // right
        case 6:
            col = tileCollisionTemplate(this, 0.0f, height * -1, width / 2, height / 2); // vertical
            collision.push_back(col);
            break;
        // bottom left
        case 8:
            col = tileCollisionTemplate(this, 0.0f, height * -1, width / -2, height / 2); // vertical
            collision.push_back(col);
            col = tileCollisionTemplate(this, width, 0.0f, width / -2, height / -2); // horizontal
            collision.push_back(col);
            break;
        // bottom
        case 9:
            col = tileCollisionTemplate(this, width, 0.0f, width / -2, height / -2); // horizontal
            collision.push_back(col);
            break;
        // bottom right
        case 10:
            col = tileCollisionTemplate(this, 0.0f, height * -1, width / 2, height / 2); // vertical
            collision.push_back(col);
            col = tileCollisionTemplate(this, width, 0.0f, width / -2, height / -2); // horizontal
            collision.push_back(col);
            break;
        // diagonal backslash
        case 3:
        case 12:
        case 14:
            col = tileCollisionTemplate(this, width, width * -1, width / -2, width / 2);
            collision.push_back(col);
            break;
        // diagonal slash
        case 7:
        case 13:
        case 15:
            col = tileCollisionTemplate(this, width, width, width / -2, width / -2);
            collision.push_back(col);
            break;
        default:
            break;
    }
}
