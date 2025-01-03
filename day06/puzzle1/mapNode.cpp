#include "mapNode.h"

MapNode::MapNode(bool ob) {
    obstructed = ob;
    timesVisited = 0;
}

bool MapNode::isObstructed() {
    return obstructed;
}

bool MapNode::wasVisited() {
    return (timesVisited > 0);
}

int MapNode::getTimesVisited() {
    return timesVisited;
}

void MapNode::visit() {
    timesVisited++;
}