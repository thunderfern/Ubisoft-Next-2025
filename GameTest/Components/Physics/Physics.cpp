#include "stdafx.h"

#include "Physics.h"
#include "Collision.h"
#include "../GameObject/GameObject.h"

#include <math.h>

Physics::Physics(GameObject *object, PhysicsType physicsType, float weight, float speed, float acceleration, float direction): object{object}, physicsType{physicsType}, weight{weight}, speed{speed}, acceleration{acceleration}, direction{direction} {}

void Physics::updatePhysics(Physics *physics, Collision *collision) {
    // if circle collides with line
    // calculating the xcomponent and ycomponent for the speed
    float xcomp = speed * cosf(direction);
    float ycomp = speed * sinf(direction);
    if (collision->getShape() == CollisionShape::LINE) {
        float colwidth = collision->getWidth(), colheight = collision->getHeight();
        // edge cases
        if (abs(collision->getWidth()) < 0.001f) xcomp *= -1;
        else if (abs(collision->getHeight()) < 0.001f) ycomp *= -1;
        else {
            // adding on values to ensure that things are not 0 (will cause error with division)
            if (colwidth == 0.0f) colwidth += 0.00001f;
            if (colheight == 0.0f) colheight += 0.00001f;

            // calculating the slope of the perpendicular line to the original collision line
            float m = colwidth / colheight;
            float xtmp = xcomp, ytmp = ycomp;
            // using matrix multiplication to calculate the new xcomponent and ycomponent after reflecting across the perpendicular lineS
            xcomp = ((1 - m * m) * xtmp + (2 * m) * ytmp) / (1 + m * m);
            ycomp = ((2 * m) * xtmp + (m * m - 1) * ytmp) / (1 + m * m);
        }
        // ensuring that xcomp is not 0 when recalculating the direction
        if (xcomp == 0.0f) xcomp += 0.0001f;
        direction = atanf(ycomp / xcomp);
        // adjusting for the range of arctan
        if (xcomp < 0.0f) direction += 3.14f;
    }
    // adding on the components so that the collision does not detect again
    object->x += xcomp;
    object->y += ycomp;
}

void Physics::applyPhysics(float deltaTime) {
    if (physicsType == PhysicsType::STATIC) return;
    // adding the acceleration
    speed += acceleration * deltaTime;
    // slowing down the speed (so the object does not move forever, attempts to mimic air resistence)
    speed -= weight * 1.0f * deltaTime / 1000;
    // speed cannot be negative after subtracting the air resistence
    speed = std::max(0.0f, speed);
    // recalculating the xcomponent and ycomponent from the polar coordinates and changing the GameObject's x and y to apply the physics
    float xcomp = speed * cosf(direction);
    float ycomp = speed * sinf(direction);
    object->x += xcomp;
    object->y += ycomp;
}
