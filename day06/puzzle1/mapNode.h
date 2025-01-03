#pragma once

class MapNode {
    private:
        bool obstructed;
        int timesVisited;
    
    public:
        MapNode(bool ob);
        bool isObstructed();
        bool wasVisited();
        int getTimesVisited();
        void visit();
};