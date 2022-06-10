#ifndef ACTREE_H_INCLUDED
#define ACTREE_H_INCLUDED
#include "header.h"
#include "graph.h"
#include "kcore.h"
#include "rotc.h"
using namespace std;
struct rectangle{
    //center at (x,y)
    // width = 2*w
    // height = 2*h
    double x,y,w,h;

#define nw(r) rectangle(r.x-r.w/2,r.y-h/2,r.w/2,r.h/2)
#define ne(r) rectangle(r.x+w/2,r.y-h/2,w/2,h/2)
#define sw(r) rectangle(r.x-w/2,r.y+h/2,w/2,h/2)
#define se(r) rectangle(r.x+w/2,r.y+h/2,w/2,h/2)
    rectangle(){}
    rectangle(double x,double y,double w,double h):x(x),y(y),w(w),h(h){}
    bool inline intersect(rectangle other){
        rectangle & a = *this;
        rectangle & b = other;
        bool noIntersect = (a.x+a.w < b.x-b.w)
        ||(b.x+b.w<a.x-a.w)
        ||(a.y+a.h<b.y-b.h)
        ||(b.y+b.h<a.y-a.h);
        return !noIntersect;
    }

    bool contain(double x_,double y_){
        return x-w<=x_&&x_<=x+w&&y-h<=y_&&y_<=y+h;
    }
    vector<rectangle> gen_sub_rec(){
        vector<rectangle> r(4);
        r[0]=nw((*this));
        r[1]=ne((*this));
        r[2]=sw((*this));
        r[3]=se((*this));
        return r;
    }
    void print(){
        cout<<"x: "<<x-w<<"to"<<x+w<<"  y:"<<y-h<<"to"<<y+h<<endl;
    }
};

struct attribute{
public:
    attribute(){}
    void add(int key, int val){
        keys[key]+=val;
    }
    void unite(attribute&other){
        for(auto& e:other.keys){
            keys[e.first]+=e.second;
        }
    }
    attribute* intersect(const vector<int>&vkey){
        attribute& res = *(new attribute());
        for(auto&k:vkey){
            res[k]=(*this)[k];
        }
        return &res;
    }
    attribute* intersect(attribute&other){
        attribute& res = *(new attribute());
        attribute& amax = (size()>=other.size())?*this:other;
        attribute& amin = (size()<other.size())?*this:other;
        for(auto&e:amin.keys){
            int key=e.first;
            if(amax.keys.count(key)!=0){
                res[key]=min(amax[key],amin[key]);
            }
        }
        return &res;
    }
    int inline count(int key){
        return keys.count(key);
    }
    inline int& operator[] (int i){
        return keys[i];
    }
    int inline size(){
        return keys.size();
    }
private:
    unordered_map<int,int> keys;
};
class actree{
public:
    actree(graph<Point>g, rectangle r):g(g),range(r){
        REP(i,4)sub[i]=NULL;
    }
    //todo: prunning and priority
    //todo: inverted index
    void build(int k){//dfs build
        kcore kc(g);
        int maxk = kc.get_maxk();
        if(maxk<k){
            is_leaf=true;
            return;
        }else{
            divide();
            REP(i,4){
                sub[i]->build(k);
            }
        }
    }
//    const static dir[2]={-1,1};
    void divide(){
        vector<rectangle> rec = range.gen_sub_rec();
        auto& ps = g.get_point_set();
        graph<Point> subg[4];
        for(auto&p: ps){
            REP(i,4){
                if(rec[i].contain(p.x,p.y)){
                    subg[i].add_point(p);
                    break;
                }
            }
        }
        REP(i,4){
            sub[i]=new actree(subg[i],rec[i]);
        }
    }
    void search_points(rectangle range_, vector<int>& v){
        if(is_leaf){
            auto& ps = g.get_point_set();
            for(auto&p:ps){
                if(range_.contain(p.x,p.y)){
                    v.push_back(p.id);
                }
            }
        }else {
            REP(i,4){
                (*sub[i]).search_points(range_,v);
            }
        }
        return;
    }
    void print(){
        cout<<g.size()<<endl;
        range.print();
        REP(i,4){
            if(sub[i]!=NULL)
                sub[i]->print();
        }
    }
    bool contain(int x, int y){
        return range.contain(x,y);
    }
private:
    bool is_leaf;
    graph<Point> g;
    actree* sub[4];
    rectangle range;
};

#endif // ACTREE_H_INCLUDED
