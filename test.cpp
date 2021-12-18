//#define NDEBUG

#include "lib/header.h"
#include "lib/graph.h"
#include "lib/kcore.h"
#include "lib/geometry.h"

const string DATA_PATH[][2] = {
    {"./data/location.txt", "./data/edge.txt"},
    {"./data/location.txt", "./data/edge2.txt"},
    {"./data/foursquare-location2","./data/foursquare-graph"},
};

void testReadData(){
    graph<Point> g;
    string path[2]=DATA_PATH[0];
    g.readPos(path[0].c_str());
    g.readEdge(path[1].c_str());
    cout<<"read data successfully"<<endl;
    while(true){
        int id;
        cin>>id;
        if(g.include_id(id)){
            g.print_edge(id);
        }else{
            cout<<"this id does not exist."<<endl;
        }
        if(id==-1)break;
    }
//    g.printEdge();
}
void testGenSubGraph(){
    graph<Point> g;
    string path[2]=DATA_PATH[2];
    g.readPos(path[0].c_str());
    g.readEdge(path[1].c_str());
    cout<<"read data successfully"<<endl;
    g=*g.gen_sub_graph(1,g.size());
    cout<<"gen subgraph successfully"<<endl;
    int s,e;
    cout<<"max degree: "<<g.get_max_degree()<<endl;
    while(cin>>s>>e){
        if(e>=s&&g.include_id(s)&&g.include_id(e)){
            graph<Point>&sub=*g.gen_sub_graph(s,e);
            sub.printEdge();
        }
    }

}
void testKCore(){
    graph<Point> g;
    string path[2]=DATA_PATH[0];
    g.readPos(path[0].c_str());
    g.readEdge(path[1].c_str());
    kcore kc(*g.gen_sub_graph(1,10));
    cout<<g.get_max_degree();
    kc.print_edge();
}
void testGeometry(){
    ;
}
void testRot(){
    ;
}
int main()
{
    testGenSubGraph();
    testKCore();
    return 0;
}
