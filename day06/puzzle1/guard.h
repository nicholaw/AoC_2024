#pragma once

#include <utility>

enum Orientation {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

class Guard {
    private:
        std::pair<int, int> position;
        Orientation orientation;

    public:
        Guard(int xpos, int ypos, Orientation startingOrientation);
        std::pair<int, int> getPosition();
        Orientation getOrientation();
        void rotate();
        void step();
};