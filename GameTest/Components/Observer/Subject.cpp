#include "Subject.h"

void Subject::addObserver(Observer *o) {
    observers.push_back(o);
}

void Subject::deleteObserver(Observer *o) {
    for (int i = 0; i < observers.size(); i++) {
        if (o == observers[i]) observers.erase(observers.begin() + i);
    }
}

void Subject::notifyObservers() {
    for (auto o : observers) o->notify(this);
}