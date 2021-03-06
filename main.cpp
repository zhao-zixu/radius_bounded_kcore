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
    Graph<Point> g;

    const string* path = DATA_PATH[1];

//    string path[2] = {DATA_PATH[1][0],DATA_PATH[1][1]};

    g.readPos(path[0].c_str());
    g.readEdge(path[1].c_str());
    g.printEdge();
    g.print_all_point();
    kcore kc(g);
    kc.print();

}

int main(){

    test();
    return 0;
}
