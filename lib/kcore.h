#ifndef KCORE_H_INCLUDED
#define KCORE_H_INCLUDED
#include "graph.h"
// point for k core
class KcPoint{
public:
    KcPoint(int id_=-1,int deg_=0, int core_=0, bool del_=false):id(id_),del(del_), core(core_), deg(deg_) {}
    int id;
    bool del;// is delete
    int core;//core number
    int deg;// degree
    void print(){
        printf("ID: %d core number:%d degree:%d is_delete:%s\n",id, core, deg, del?"true":"false");
    }
};

class kcore{
public:
    kcore(){}
    kcore(graph<Point> gra){
        vector<int> ids = gra.get_ids();
        for(auto&i:ids){
            Point p = gra.get_point(i);
            KcPoint kp(p.id);
            vector<int> e = gra.get_edge(i);
            g.add_point(kp,e);
        }
    }
//    kcore(graph<Point> gra, vector<int> ids){
//        this->kcore(gra);
////        kcore(*g.gen_sub_graph(ids));
//    }
    //compute the core number of each point
    void compute_core(){
        int max_deg=g.get_max_degree();
    }
    int get_maxk(){
        //seg_tree
        return maxk;
    }
    print(){
        g.print_all_point();
    }
    print_edge(){
        g.print_edge();
    }
    void add_point(){
        ;
    }
    void del_point(){
        ;
    }
    void insert_edge(int from,int to){

    }
    void del_edge(int from, int to){
    }

    process(){
        ;
    }
private:
    void color(){

    }
    void recolor_insert(){

    }
    void update_insert(){

    }
    void recolor_del(){
    }
    void update_del(){

    }

    graph<KcPoint> g;
    int maxk;
};


#endif // KCORE_H_INCLUDED
