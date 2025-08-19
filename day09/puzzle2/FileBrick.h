#pragma once

class FileBrick {
    private:
        int id;
        int size;
    
    public:
        FileBrick(int _id, int _size) {id = _id; size = _size;};
        int getId() {return id;};
        int getSize() {return size;};
};