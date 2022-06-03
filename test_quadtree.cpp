//#define NDEBUG

#include "lib/header.h"
#include "lib/graph.h"
#include "lib/kcore.h"
#include "lib/geometry.h"
#include "lib/quadtree.h"
//#include "lib/actree.h"
#include "assert.h"

//testing part
string DATA_PATH[][2] = {
    {"./data/location.txt", "./data/edge.txt"},
    {"./data/location.txt", "./data/edge2.txt"},
    {"./data/foursquare-location2","./data/foursquare-graph"},
};
namespace parameter{
    int  data_path;
}
void init(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    FILE * f = fopen("parameter.txt","r");
    fscanf(f,"%d",&parameter::data_path);
    cout<<parameter::data_path<<endl;
}

void test(){
    Graph<Point> g;
    string*path = DATA_PATH[parameter::data_path];
    g.readPos(path[0].c_str());
    g.readEdge(path[1].c_str());
    cout<<"read data successfully\n";
//    quadtree qt;
    /*
    qt(g);
    qt.build();?

    int k = 1;
    keyword kw = {0,1,2};
    double r = 5.0;
    query q(k,r,kw);
    result rs = qt.query(q);
    rs.output();

    */
    g.printEdge();
}
void testactree(){
    ;
}
int main(){
    init();
    test();
    return 0;
}
