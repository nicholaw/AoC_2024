#pragma once

class MemoryBrick {
    private:
        int id;
    
    public:
        MemoryBrick(int _id) {id = _id;};
        int getId() {return id;};
};