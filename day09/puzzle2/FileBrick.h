#include <utility>
#pragma once

class FileBrick {
    private:
        int id;
        std::pair<int, int> range;
        bool moved;
    
    public:
        FileBrick(int _id, int start, int end) {id = _id; range = std::pair(start, end); moved = false;};
        int getId() {return id;};
        int getSize() {return (range.second - range.first);};
        void move(std::pair<int, int> newRange) {range = newRange; moved = true;};
        bool wasMoved() {return moved;};
};