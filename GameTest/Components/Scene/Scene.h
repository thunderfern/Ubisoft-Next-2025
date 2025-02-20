#include "../GameObject/GameObject.h"
#include "../Camera/Camera.h"
#include "../Mouse/Mouse.h"

#include <vector>

#ifndef Scene_h
#define Scene_h
class Scene {

    protected:
        std::vector<GameObject *> gameObjects;
        Camera *camera;
        virtual void updateSubScene() = 0;
    
    public:
        Scene();
        void addObject(GameObject *obj);
        void renderObjects();
        void updateScene(float deltaTime);
        ~Scene() = default;

};
#endif