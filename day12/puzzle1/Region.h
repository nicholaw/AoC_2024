#pragma once

#include <utility>

using namespace std;

class Region {
    private:
        char crop;
        int area;
        int perimeter;
    
    public:
        Region(char _crop) {crop = _crop; area, perimeter = 0;};
        int addPlot(int localPerimeter) {perimeter += localPerimeter; area++; return area;};
        bool cropsMatch(char target) {return (crop == target);};
        pair<int, int> getMeasurements() {return pair<int, int>(area, perimeter);};
        char getCrop() {return crop;};
};