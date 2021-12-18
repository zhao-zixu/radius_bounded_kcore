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
        compute_core();
    }
//    kcore(graph<Point> gra, vector<int> ids){
//        this->kcore(gra);
////        kcore(*g.gen_sub_graph(ids));
//    }
    //compute the core number of each point
    void compute_core(){
        int max_deg=g.get_max_degree();


        //initialize the k class
        vector<set<int> > kclass(max_deg+1);
        vector<KcPoint> ps=g.get_point_set();
        auto e = g.get_edge_set();
        vector<int> deg(e.size());
        for(int i=0;i<deg.size();i++){
            deg[i]=e[i].size();
        }

        for(int i=0;i<ps.size();i++){
            assert(0<=e[i].size());
            assert(e[i].size()<kclass.size());
            kclass[e[i].size()].insert(i);
        }

        // do the k-core decomposition
        for(int i=1;i<=maxk;i++){
            while(!kclass[i].empty()){
                set<int>::iterator it = kclass[i].begin();
                assert(it!=kclass[i].end());
                int num=*it;
                assert(0<=num);
                assert(num<ps.size());
                ps[num].core=i;

                //remove point from k-class
                for(auto v:e[num]){
                    cout<<num<<","<<v<<endl;
                    if(!ps[v].del&&deg[v]>ps[v].core){
                        kclass[deg[v]].erase(v);
                        deg[v]--;
                        assert(0<=deg[v]);
                        assert(deg[v]<kclass.size());
                        if(deg[v]>=i)kclass[deg[v]].insert(v);
                    }
                }

                kclass[i].erase(it++);
            }
        }

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
