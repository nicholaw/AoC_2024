#pragma once

#include <iostream>
#include <utility>

using namespace std;

struct Region {
    private:
        int id;
        char crop;
        int area;
        int perimeter;
    
    public:
        Region(char _crop, int _id) {crop = _crop; id = _id; area = perimeter = 0;};
        int addPlot(int localPerimeter) {perimeter += localPerimeter; area++; return area;};
        bool cropsMatch(char target) {return (crop == target);};
        pair<int, int> getMeasurements() {return pair<int, int>(area, perimeter);};
        void printInfo() {cout << "(" << id << ") " << crop << ", Area = " << area << " Perimeter = " << perimeter << "\n";};
        bool operator<(const Region& other) const {return id < other.id;};
};