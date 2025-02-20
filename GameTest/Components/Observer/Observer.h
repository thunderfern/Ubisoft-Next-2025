#include "../GameObject/GameObject.h"

class Observer : public GameObject {
    private:
        GameObject* observeFor;
    public:
        //void notify() { observeFor->notify(); }
};

