#include "../GameObject.h"

#include <vector>

#ifndef Tile_h
#define Tile_h

class Tile : public GameObject {

    private:
        void addCollision(int idx);

    public:
        Tile(int idx, float x, float y);

};
#endif
