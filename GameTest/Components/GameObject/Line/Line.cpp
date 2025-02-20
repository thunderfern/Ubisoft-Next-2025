#include "stdafx.h"

#include <math.h>

#include "Line.h"

Line::Line(): x2{0.0f}, y2{0.0f}, dist{0.0f}, colour{Colour::WHITE} { }

void Line::setPos2(float xpos, float ypos) {
    x2 = xpos;
    y2 = ypos;
    updateDist();
}

float Line::getX2() { return x2; }

float Line::getY2() { return y2; }

//standard distance formula
void Line::updateDist() { dist = (float)sqrt((x2 - x) * (x2 - x) + (y2 - y) * (y2 - y)); }

void Line::setColour(Colour newColour) { colour = newColour; }

Colour Line::getColour() { return colour; }

float Line::getDist() { return dist; }