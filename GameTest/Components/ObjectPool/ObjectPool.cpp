#include "ObjectPool.h"

template <typename T>
void ObjectPool<T>::allocateObjects(int num) {
    for (int i = 0; i < num; i++) {
        T* tmp = new T();
        objects.push_back(tmp);
    }
}

template <typename T>
void ObjectPool<T>::deleteObjects() {
    for (int i = 0; i < objects.size(); i++) delete objects[i];
}

template <typename T>
T* ObjectPool<T>::getObject() {
    if (objects.size() != 0) {
        T* tmp = objects[objects.size() - 1];
        objects.erase(objects.size() - 1);
        return tmp;
    }
}

template <typename T>
void ObjectPool<T>::releaseObject(T* obj) {
    objects.push_back(obj);
}
