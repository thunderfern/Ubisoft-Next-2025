
//#include "../Physics/Collision.h"
//#include "../Physics/Physics.h"
//#include "../../App/SimpleSprite.h"

#include <vector>
#include <string>

class Collision;
class Physics;
class CSimpleSprite;

#ifndef GameObject_h
#define GameObject_h
class GameObject {

    protected:
        float x;
        float y;
        float x2;
        float y2;
        float width;
        float height;
        bool state; // true if the object is active, false if it is not active
        CSimpleSprite *sprite;
        std::vector<Collision*> collision;
        Physics *physics;

    public:
        GameObject();
        GameObject(std::string spritePath, int spriteRow, int spriteCol, float scale);
        void setState(bool s);
        bool getState() { return state; }
        float getX();
        float getY();
        float getX2() { return x2; }
        float getY2() {return y2; }
        void setPos(float xpos, float ypos);
        void setPos2(float xpos, float ypos) { x2 = xpos, y2 = ypos; }
        float getWidth();
        float getHeight();
        Physics *getPhysics();
        void setPhysics(Physics *newPhysics);
        CSimpleSprite *getSprite();
        void addCollision(Collision *col);
        virtual void update(float deltaTime);
        std::vector<Collision*> getCollisionList();
        ~GameObject();
    
    friend class Scene;
    friend class Physics;
    friend class Camera;
    
};
#endif