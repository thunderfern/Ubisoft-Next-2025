#include "stdafx.h"

#include "Scene.h"
#include "../../App/app.h"
#include "../Mouse/Mouse.h"
#include "../GameObject/Line/Line.h"
#include "../GameObject/Text/Text.h"
#include "../Physics/Collision.h"
#include "../Physics/Physics.h"

#include <string>

Scene::Scene() {
    camera = new Camera();
}

void Scene::renderObjects() {
    // getting the inframe objects
    std::vector<GameObject*> obj = camera->getInFrame(gameObjects);
    for (int i = 0; i < obj.size(); i++) {
        // if it is not supposed to be there, don't render it
        if (!obj[i]->getState()) continue;
        // render it based on the correct type, if it is sprite, line or text
        if (obj[i]->sprite != NULL) obj[i]->sprite->Draw();
        else {
            Line *curline = dynamic_cast<Line*>(obj[i]);
            if (curline != NULL) {
                if (curline->getColour() == Colour::RED) App::DrawLine(curline->getX(), curline->getY(), curline->getX2(), curline->getY2(), 1.0f, 0.0f, 0.0f);
                else App::DrawLine(curline->getX(), curline->getY(), curline->getX2(), curline->getY2(), 1.0f, 1.0f, 1.0f);
            }
            else {
                Text *curtext = dynamic_cast<Text*>(obj[i]);
                if (curtext != NULL) {
                    App::Print(curtext->getX(), curtext->getY(), curtext->getText().c_str(), 1.0f, 1.0f, 1.0f);
                }
            }
        }
    }
}

void Scene::addObject(GameObject *obj) { gameObjects.push_back(obj); }

void Scene::updateScene(float deltaTime) {

    // updating mouse input
    Mouse::instance()->update();

    updateSubScene();

    // checking for collisions + updating physics
    for (auto obj1 : gameObjects) {
        for (auto obj2 : gameObjects) {
            // if it is the same object, don't check for collision
            if (obj1 == obj2) continue;
            bool foundCollision = false;
            if (!obj1->getState() || !obj2->getState()) continue;
            // going through the collision components
            for (auto col1 : obj1->collision) {
                for (auto col2 : obj2->collision) {
                    // if found a collision, update the physics
                    if (col1->colliding(col2)) {
                        if (obj1->physics != NULL) obj1->physics->updatePhysics(obj2->physics, col2);
                    }
                }
            }
        }
    }

    // updating the gameObjects
    for (int i = 0; i < gameObjects.size(); i++) if (gameObjects[i]->getState()) gameObjects[i]->update(deltaTime);

}