#include "stdafx.h"

#include "Collision.h"
#include "../GameObject/GameObject.h"

//distance between two points squared
float pointLen(float x1, float x2, float y1, float y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

Collision::Collision(GameObject *object, CollisionShape collisionShape, float width, float height, float x, float y): object{object}, collisionShape{collisionShape}, width{width}, height{height}, x{x}, y{y} {}

bool Collision::colliding(Collision *collision) {
    if (this == NULL || collision == NULL) return false;
    GameObject *o1 = object, *o2 = collision->object;
    float o1x = o1->getX() + x, o2x = o2->getX() + collision->x, o1y = o1->getY() + y, o2y = o2->getY() + collision->y;
    float o1w = width, o2w = collision->width, o1h = height, o2h = collision->height;
    CollisionShape o1s = collisionShape, o2s = collision->collisionShape;

    // follow SQUARE, CIRCLE, LINE, swap so that o1 < o2
    if (o1s > o2s) {
        std::swap(o1x, o2x);
        std::swap(o1y, o2y);
        std::swap(o1w, o2w);
        std::swap(o1h, o2h);
        std::swap(o1s, o2s);
    }

    if (o1s == SQUARE) {
        // square and square
        if (o2s == SQUARE) {

        }
        // square and circle
        else if (o2s == CIRCLE) {
            //checking the edges
            if (o2x >= std::min(o1x, o1x + o1w) - o2w && o2x <= std::max(o1x, o1x + o1w) + o2w) {
                if (o2y >= std::min(o1y, o1y + o1h) && o2y <= std::max(o1y, o1y + o1h)) return true;
            }
            if (o2y >= std::min(o1y, o1y + o1h) - o2w && o2y <= std::max(o1y, o1y + o1h) + o2w) {
                if (o2x >= std::min(o1x, o1x + o1w) && o2x <= std::max(o1x, o1x + o1w)) return true;
            }
            // checking the corners
            if (pointLen(o1x, o2x, o1y, o2y) <= o2w * o2w || pointLen(o1x + o1w, o2x, o1y, o2y) <= o2w * o2w || pointLen(o1x, o2x, o1y + o1h, o2y) <= o2w * o2w || pointLen(o1x + o1w, o2x, o1y + o1h, o2y) <= o2w * o2w) return true;
            return false;
        }
        else {

        }

    }
    else if (o1s == CIRCLE) {
        if (o2s == CIRCLE) {
            // if the objects colliding is circle and circle
            if (pointLen(o1x, o2x, o1y, o2y) <= (o1w + o2w) * (o1w + o2w)) return true;
            return false;
        }
        else {
            o1w += 5.0f;
            // checking endpoints
            if (pointLen(o1x, o2x, o1y, o2y) <= o1w * o1w || pointLen(o1x, o2x + o2w, o1y, o2y + o2h) <= o1w * o1w) return true;
            // checking if it is a vertical line
            else if (o2w == 0.0f) {
                // if its a vertical line, the shortest path is just to go across
                if (pointLen(o1x, o2x, o1y, o1y) <= o1w * o1w && o1y >= std::min(o2y, o2y + o2h) && o1y <= std::max(o2y, o2y + o2h)) return true;
                return false;
            }
            else if (o2h == 0.0f) {
                // if its a horizontal line, the shortest path is just to go down
                if (pointLen(o1x, o1x, o1y, o2y) <= o1w * o1w && o1x >= std::min(o2x, o2x + o2w) && o1x <= std::max(o2x, o2x + o2w)) return true;
                return false;
            }
            else {
                float m1 = o2h, m2 = o2w;
                // calculating the b value for both the line and the perpendicular line that passes thoguh the circle to get the shortest path to the line
                float b1 = o2y - m1 / m2 * o2x, b2 = o1y + m2 / m1 * o1x;
                // checking the optimal x on the line using the shortest path
                float cx = (b2 - b1) / (m1 / m2 + m2 / m1);
                // if the optimal x is not on the given line (since the line could not reach there, it is not colliding)
                if (cx > o2x + o2w || cx < o2x) return false;
                else {
                    float cy = m1 / m2 * cx + b1;
                    // otherwise, check the distance to that point
                    if (pointLen(o1x, cx, o1y, cy) <= o1w * o1w) return true;
                    return false;
                }
            }
        }
    }
    else {

    }
    return false;
}

float Collision::getWidth() { return width; }

float Collision::getHeight() { return height; }

float Collision::getX() { return x; }

float Collision::getY() { return y; }

CollisionShape Collision::getShape() { return collisionShape; }

