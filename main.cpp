#include "lib/header.h"
#include "lib/graph.h"
#include "lib/kcore.h"
#include "lib/geometry.h"

const string DATA_PATH[][2] = {
    {"./data/location.txt", "./data/edge.txt"},
    {"./data/location.txt", "./data/edge2.txt"},
    {"./data/foursquare-location2","./data/foursquare-graph"},
};

void test(){
    graph<Point> g;
    string path[2]=DATA_PATH[1];
    g.readPos(path[0].c_str());
    g.readEdge(path[1].c_str());
    kcore kc;
}

int main(){

    test();
    return 0;
}
