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

class LockTile;

#ifndef UnlockTile_h
#define UnlockTile_h
class UnlockTile : public GameObject {

    protected:
        // linked tiles that observe the current tile
        std::vector<LockTile*> linkedTiles;
        TileColour colour;

    public:
        UnlockTile(TileColour c);
        // Observer pattern inspired functions
        void notifyTiles();
        void addObserver(LockTile* lockTile);
        TileColour getColour() { return colour; }
};
#endif