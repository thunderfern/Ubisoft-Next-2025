#ifndef Physics_h
#define Physics_h

class GameObject;
class Collision;

enum PhysicsType {
    STATIC,
    DYNAMIC
};

class Physics {
    private:
        GameObject *object;
        PhysicsType physicsType;
        float weight;
        float acceleration;
    
    public:
        Physics(GameObject *obj, PhysicsType physicsType, float weight, float speed, float acceleration, float direction);
        void updatePhysics(Physics *physics, Collision *collision);
        void applyPhysics(float deltaTime);
        float direction;
        float speed;
        
    
};
#endif