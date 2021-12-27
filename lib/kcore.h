#ifndef KCORE_H_INCLUDED
#define KCORE_H_INCLUDED
#include "graph.h"
// point for k core
class KcPoint{
public:
    KcPoint(int id_=-1,int core_=0, bool del_=false):id(id_),del(del_), core(core_){}
//    KcPoint(int id_=-1,int deg_=0, int core_=0, bool del_=false):id(id_),del(del_), core(core_), deg(deg_) {}
    int id;
    bool del;// is delete
    int core;//core number
//    int deg;// degree
    void print(){
        printf("ID: %d core number:%d is_delete:%s\n",id, core, del?"true":"false");
    //    printf("ID: %d core number:%d degree:%d is_delete:%s\n",id, core, deg, del?"true":"false");
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

    int get_maxk(){
        //can be optimized using seg_tree later
        int maxk=0;
        auto&ps=g.get_point_set();
        for(auto&p:ps){
            maxk=max(maxk,p.core);
        }
        return maxk;
    }
    void print(){
        g.print_all_point();
    }
    void print_edge(){
        g.print_edge();
    }
    void print_core(){
        vector<KcPoint>&ps=g.get_point_set();
        map<int,int> core;
        for(auto&p:ps){
            core[p.core]++;
        }
        auto it = core.rbegin();
        //map<int,int>::iterator it = core.begin();
        while(it!=core.rend()){
            cout<<it->first<<": "<<it->second<<endl;
            it++;
        }
    }
    // add a new point to graph
    void add_point(int id, const vector<int>&e){
        assert(!g.include_id(id));
        KcPoint p(id);
        add_point(p,e);
    }
    void add_point(KcPoint p,const vector<int>&e){
        g.add_point(p);
        int num=g.get_num(p.id);
        for(auto&v: e){
            if(g.include_id(v)){
                insert_edge(num,g.get_num(v));
            }
        }
    }
    void del_point(int id){
        if(g.get_point(id).del)return;
        int nid = g.get_num(id);
        auto& edges = g.get_edge_set();
        int n=edges[nid].size();
        for(int i=n-1;i>=0;i--){
            del_edge(nid,edges[nid][i]);
        }
        g[nid].id=-1;
        g.erase(id);
//        for(auto& x:edges[nid]){
//            out(nid,x);
//            del_edge(nid,x);
//            out(nid,x);
//            print_edge();
//            cout<<"--------"<<endl;
//        }
//        g.del_point(id);
    }
    typedef unordered_map<int,int> VC;
    void insert_edge(int from,int to){
        assert(0<=from&&from<(int)g.size());
        assert(0<=to&&to<(int)g.size());
        g.add_edge(from,to);
        int c,p;
        if(g[from].core<g[to].core){
            c=g[from].core;
            p=from;
        }else {
            c=g[to].core;
            p=to;
        }
        VC s;
        vector<bool> vis(g.size(),0);
        color(p,c,s,vis);
        recolor_insert(c,s);
        update_insert(c,s);
    }
    void del_edge(int from, int to){
        g.del_edge(from,to);
        int c,p;
        if(g[from].core<g[to].core){
            c=g[from].core;
            p=from;
        }else {
            c=g[to].core;
            p=to;
        }
        VC s;
        vector<bool> vis(g.size(),0);
        color(p,c,s,vis);
        if(g[from].core==g[to].core){
            fill(vis.begin(),vis.end(),false);
            color(from,c,s,vis);
        }
        recolor_del(c,s);
        update_del(c,s);
    }
    bool include(int id){
        return g.include_id(id);
    }
private:
    void color(int u, int c, VC&s, vector<bool>& vis){
        vis[u]=1;
        s.insert(make_pair(u,1));
        auto&edge = g.get_edge_set();
        for(auto v:edge[u]){
            if(!vis[v]&&g[v].core==c){
                color(v,c,s,vis);
            }
            vis[v]=true;
        }
    }
    void recolor_insert(int c, VC&s){
        bool flag=false;
        auto& edge=g.get_edge_set();
        for(auto&x: s){
            if(x.second==1){
                int xu=0;
                for(auto&v:edge[x.first]){
                    if(g[v].core>c||(s.count(v)==1&&s[v]==1)){
                        xu++;
                    }
                }
                if(xu<=c){
                    x.second=0;
                    flag=true;
                }
            }
        }
        if(flag==true)recolor_insert(c, s);
    }
    void update_insert(int c, VC&s){
        for(auto& x: s){
            if(x.second==1){
                g[x.first].core++;
            }
        }
    }
    void recolor_del(int c, VC& s){
        bool flag=false;
        auto& edge = g.get_edge_set();
        for(auto&x:s){
            if(x.second==1){
                int xu=0;
                for(auto&v:edge[x.first]){
                    if(g[v].core>c||(s.count(v)==1&&s[v]==1)){
                        xu++;
                    }
                }
                if(xu<c){
                    x.second=0;
                    flag=true;
                }
            }
        }
        if(flag){
            recolor_del(c,s);
        }
    }
    void update_del(int c, VC& s){
        for(auto x: s){
            if(x.second==0){
                g[x.first].core--;
            }
        }
    }
public:
    //compute the core number of each point
    void compute_core(){
        int max_deg=g.get_max_degree();


        //initialize the k class
        vector<unordered_set<int> > kclass(max_deg+1);
        vector<KcPoint>&ps=g.get_point_set();
        auto&e = g.get_edge_set();
        vector<int> deg(e.size());
        for(int i=0;i<(int)deg.size();i++){
            deg[i]=e[i].size();
        }

        for(int i=0;i<(int)ps.size();i++){
            assert(0<=e[i].size());
            assert(e[i].size()<kclass.size());
            kclass[e[i].size()].insert(i);
        }

        // do the k-core decomposition
        for(int i=1;i<=max_deg;i++){
            while(!kclass[i].empty()){
                unordered_set<int>::iterator it = kclass[i].begin();
                assert(it!=kclass[i].end());
//                assert(it!=NULL);
                int num=*it;
                assert(0<=num);
                assert(num<(int)ps.size());
                ps[num].core=i;

                //remove point from k-class
                for(auto v:e[num]){
                    if(!ps[v].del&&deg[v]>ps[num].core){
                        kclass[deg[v]].erase(v);
                        deg[v]--;
                        assert(0<=deg[v]);
                        assert(deg[v]<(int)kclass.size());
                        if(deg[v]>=i)kclass[deg[v]].insert(v);
                    }
                }

                kclass[i].erase(it++);
            }
        }

    }
private:
    graph<KcPoint> g;
    int maxk;
};


#endif // KCORE_H_INCLUDED
