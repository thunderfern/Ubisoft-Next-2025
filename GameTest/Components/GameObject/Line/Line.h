#include "../GameObject.h"

#ifndef Colour_e
#define Colour_e
enum Colour {
    RED,
    WHITE
};
#endif

#ifndef Line_h
#define Line_h
class Line : public GameObject {

    protected:
        float x2;
        float y2;
        float dist;
        Colour colour;
    
    public:
        Line();
        void setPos2(float xpos, float ypos);
        float getX2();
        float getY2();
        void updateDist();
        float getDist();
        void setColour(Colour newColour);
        Colour getColour();

};
#endif