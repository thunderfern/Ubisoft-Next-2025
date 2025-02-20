#include "../GameObject/GameObject.h"

class Collision;

#ifndef Mouse_h
#define Mouse_h
class Mouse : public GameObject {

    private:
    Collision* mouseCollider;
    bool clicked;
    bool prevClicked;
    Mouse();

    public:
        bool isClicked();
        Collision* getCollision();
        void update();

        static Mouse* instance();
        ~Mouse();

};
#endif