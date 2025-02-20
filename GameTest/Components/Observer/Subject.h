#include "../GameObject/GameObject.h"
#include "Observer.h"

#include <vector>

class Subject : public GameObject {

    std::vector<Observer*> observers;

    public:
        void addObserver(Observer* o);
        void deleteObserver(Observer *o);
        void notifyObservers();
};