#ifndef QUADTREE_H_INCLUDED
#define QUADTREE_H_INCLUDED
#include "graph.h"
#include "kcore.h"
#include "rotc.h"

struct Rectangle{
    //center at (x,y)
    // width = 2*w
    // height = 2*h
    Rectangle(double x_, double y_, double w_, double h_):x(x_),y(y_),w(w_),h(h_){
        assert(w>0&&h>0);
    }
    double left(){
        return x-w;
    }
    double right(){
        return x+w;
    }
    double top(){
        return y+h;
    }
    double down(){
        return y-h;
    }
    bool intersect(Rectangle b){
        Rectangle &a = *this;
        return !(
                 (a.right()<b.left())||(b.right()<a.right())||
                 (a.top()<b.down())||(b.top()<a.down())
        );
    }
private:
    double x,y,w,h;
};
bool intersect(Rectangle a, Rectangle b){
    return a.intersect(b);
}
struct AcNode{
    AcNode(Rectangle rec_, vector<int> pointList_):rec(rec_),pointList(pointList_){
        ;
    }
    void split(){
        ;
    }

private:
    Rectangle rec;
//    Atrribute attribute;
    vector<int> pointList;



};

struct AcTree{

    void build(Graph<Point> g){
        double maxX,maxY;
        for(auto&p:g){
            ;
        }
    }
    void addPoint(Point p){
        ;
    }
    void output(){
        ;
    }


private:
    AcNode* root;
};


#endif // QUADTREE_H_INCLUDED
