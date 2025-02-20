#ifndef Collision_h
#define Collision_h

class GameObject;

#ifndef CollisionShape_e
#define CollisionShape_e
enum CollisionShape {
    SQUARE = 0,
    CIRCLE = 1,
    LINE = 2
};
#endif

class Collision {

    private:
        GameObject *object;
        CollisionShape collisionShape;
        float width;
        float height;
        float x;
        float y;
    
    public:
        Collision(GameObject *object, CollisionShape collisionShape, float width, float height, float x, float y);
        bool colliding(Collision *collision);
        float getWidth();
        float getHeight();
        float getX();
        float getY();
        CollisionShape getShape();
        
};
#endif