#include "stdafx.h"

#include "../GameObject/GameObject.h"
#include "Camera.h"
#include "../../App/SimpleSprite.h"

Camera::Camera() { following = new GameObject(); }

GameObject* Camera::getFollowing() { return following; }

void Camera::setFollowing(GameObject* newFollow) { following = newFollow; }

// returns the objects in the frame of the Camera
std::vector<GameObject*> Camera::getInFrame(std::vector<GameObject*> objList) {
    std::vector<GameObject*> returnObj;
    for (int i = 0; i < objList.size(); i++) {
        // if there is a sprite object, update the position of the sprite to reflect the GameObject's x and y position
        if (objList[i]->sprite != NULL) objList[i]->sprite->SetPosition(objList[i]->x, objList[i]->y);
        // since the Camera is not following any object right now, everything should be in frame
        returnObj.push_back(objList[i]);
    }
    return returnObj;
}