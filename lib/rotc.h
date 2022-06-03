#ifndef ROTC_H_INCLUDED
#define ROTC_H_INCLUDED

#include "header.h"
#include"graph.h"
#include "kcore.h"
#include "geometry.h"

class rotc{
public:
    rotc(){}
    rotc(Graph<Point> & gra):g(gra){}
    vector<circle>& query(int k, double r, int id){
        //store the circles which satisfy the query condition
        vector<circle>& res = *(new vector<circle>());

        //find point p
        int pnum = g.get_num(id);
        Point &p = g[pnum];
        vector<pair<double,int> > ps;

        //find points dis within 2 times radius
        //and generate entering circle and leaving circle
        for(int i=0;i<g.size();i++){
            if(i==pnum)continue;
            if(p.within_dis(g[i],2*r)&&g[i].id!=-1){
                add2point(p, g[i], r, g[i].id, ps);
            }
        }

        //sort points(enterning circle and leaving circle) by polar angle
        sort(ps.begin(),ps.end());

        //bin-search the first set satisfy k-core

        int l=0;r=ps.size()-1;
        while(l<=r){
            int mid = (l+r)/2;
            if(true){
                r = mid - 1;
            }else {
                l = mid + 1;
            }

        }

        //judge k-core in increasing order
        kcore kc;
        int sz = ps.size();
        for(int i = 0; i < sz; i++){
            int nid = ps[i].second;
            if(nid < INF){//entering circle
                kc.add_point(nid,g.gen_edge_id(g.get_num(nid)));
            }else if(nid >= INF){//leaving circle
                nid%=INF;
                int maxk = kc.get_maxk();
                if(maxk >= k){
                    double theta = ps[i].first;
                    circle cir(p.x + r*cos(theta), p.y+r*sin(theta) ,r);
                    res.push_back(cir);
                }
                if(kc.include(nid))kc.del_point(nid);
            }

        }



        return res;
    }
private:
    Graph<Point> g;
};

#endif // ROTC_H_INCLUDED
