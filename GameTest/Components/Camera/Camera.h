
#include <vector>

class GameObject;

#ifndef Camera_h
#define Camera_h
class Camera {
    private:
        GameObject *following;
        double swidth;
        double sheight;
        double width;
        double height;
        double x;
        double y;
    public:
        Camera();
        GameObject* getFollowing();
        void setFollowing(GameObject* newFollow);
        // returns the objects in the frame of the Camera
        std::vector<GameObject*> getInFrame(std::vector<GameObject*> objList);
};
#endif