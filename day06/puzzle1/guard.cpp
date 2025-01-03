#include "guard.h"

/**
 * Constructs a guard.
 */
Guard::Guard(int xpos, int ypos, Orientation startingOrientation) {
    orientation = startingOrientation;
    position = {xpos, ypos};
}//constructor

/**
 * Returns the guard's current position.
 */
std::pair<int, int> Guard::getPosition() {
    return position;
}//getPosition

/**
 * Returns the guard's current orientation.
 */
Orientation Guard::getOrientation() {
    return orientation;
}//getOrientation

/**
 * Rotates the guard's orientation 90 degrees from the guard's current orientation.
 */
void Guard::rotate() {
    switch(orientation) {
        case UP:
            orientation = RIGHT;
            break;
        case RIGHT:
            orientation = DOWN;
            break;
        case DOWN:
            orientation = LEFT;
            break;
        case LEFT:
            orientation = UP;
            break;
        default:
            orientation = UP;
    }
}//rotate

/**
 * Moves the guard one position in the direction she is oriented.
 */
void Guard::step() {
    switch(orientation) {
        case UP:
            position.first--;
            break;
        case RIGHT:
            position.second++;
            break;
        case DOWN:
            position.first++;
            break;
        case LEFT:
            position.second--;
    }
}//step