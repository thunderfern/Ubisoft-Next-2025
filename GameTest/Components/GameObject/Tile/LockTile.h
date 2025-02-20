#include "../GameObject.h"

#ifndef TileColour_e
#define TileColour_e
enum TileColour {
    PURPLE,
    ROUGE,
    GREEN,
    BLUE
};
#endif

#ifndef LockTile_h
#define LockTile_h
class LockTile : public GameObject {

    protected:
        TileColour colour;

    public:
        LockTile(TileColour c);
        TileColour getColour() { return colour; }
        void notify();

};
#endif