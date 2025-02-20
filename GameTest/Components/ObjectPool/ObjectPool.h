#include "GameObject.h"

#include <vector>

template <typename T> 

class ObjectPool {

    private:
        std::vector<T*> objects;

    public:
        void allocateObjects(int num);
        void deleteObjects();
        T* getObject();
        void releaseObject(T* obj);

};