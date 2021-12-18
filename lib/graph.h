#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include"header.h"
// point
struct Point{
    Point(double x_, double y_, int id_=-1):id(id_),x(x_),y(y_){}
    int id;
    double x,y;

    void print(){
        printf("ID: %d X:%f Y:%f\n",id,x,y);
    }
    double getDis(Point p){
        double dx=x-p.x,dy=y-p.y;
        return sqrt(dx*dx+dy*dy);
    }
    bool withinDis(Point p, double d){
        return getDis(p)<=d;
    }
    double getPolarAngle(Point p){
        double dx=x-p.x,dy=y-p.y;
        return atan2(dy,dx);
    }
};


template <class Point> struct graph{
public:
    graph(): _n(0) {}
    graph(int n) : _n(n), g(n) {}

    void readPos(const char* file_name){
        const int MAX_CHAR_EACH_LINE = 1e5;
        FILE* f = fopen(file_name,"r");
        if(f==NULL){
            printf("Open file failure.\n");
            return;
        }
        char buffer[MAX_CHAR_EACH_LINE];

        while(fgets(buffer,MAX_CHAR_EACH_LINE,f)!=NULL){
            int id;
            double x,y;
            sscanf(buffer,"%d%lf%lf",&id,&x,&y);
            ps.push_back(Point(x,y,id));
            num[id]=ps.size()-1;
        }
        fclose(f);
        _n=ps.size();
        g=vector<vector<int> >(_n);

    }
    void readEdge(const char* file_name){
        FILE* f = fopen(file_name,"r");
        if(f==NULL){
            printf("Open file failure.\n");
            return;
        }
        char c;
        int tmp=0;
        bool read=false;
        int id=-1;
        while(fscanf(f,"%c",&c)!=EOF){
            if('0'<=c&&c<='9'){
                read=true;
                tmp=tmp*10+(c-'0');
            }else if(read&&id!=-1){
                //points_[id-1].AddEdge(tmp);
                g[id-1].push_back(tmp-1);
                tmp=0;
                read=false;
            }else if(read&&id==-1){
                id=tmp;
                tmp=0;
                read=false;
            }else;

            if(c=='\n'){
                id=-1;
                tmp=0;
                read=false;
            }
        }
        if(read&&id!=-1){
            //points_[id-1].AddEdge(tmp);
            g[id-1].push_back(tmp-1);
            tmp=0;
            read=false;
        }
        fclose(f);
    }
    graph* gen_sub_graph(vector<int> id){
        #ifndef NDEBUG
        for(auto&x: id){
            assert(num.count(x)!=0);
        }
        #endif // NEDBUG
        set<int> sid(id.begin(),id.end());
        graph* g=new graph<Point>();
        for(auto&x:sid){
            Point p=ps[num[x]];
            g->ps.push_back(p);
            vector<int> e;
            for(auto&v:this->g[num[x]]){
                if(sid.count(v)!=0){
                    e.push_back(v);
                }
            }
            g->g.push_back(e);
            g->num[p.id]=g->g.size()-1;
        }
        return g;
    }
    graph* gen_sub_graph(int start_,int end_){
        vector<int> v;
        for(int i=start_;i<=end_;i++){
            v.push_back(i);
        }
        return gen_sub_graph(v);
    }
    void printEdge(){
        int n=g.size();
        for(int i=0;i<n;i++){
            printf("ID: %d ",ps[i].id);
            printf("Edge: ");
            for(auto x: g[i]){
                printf("%d ",x);
            }
            printf("\n");
        }
    }
    void writePos(const char* file_name){
        FILE* f = fopen(file_name,"w");
        int n=ps.size();
        for(int i=0;i<n;i++){
            Point &p = ps[i];
            fprintf(f,"%d %f %f\n",p.id,p.x,p.y);
        }
        fclose(f);
    }
    void add_point(Point p, VI e=VI()){
        ps.push_back(p);
        num[p.id]=ps.size()-1;
        g.push_back(e);
    }

    int add_edge(int from, int to){
        assert(num.count(from)!=0);
        assert(num.count(to)!=0);
        from=num[from],to=num[to];
        g[from].push_back(to);
        g[to].push_back(from);
        return 0;
    }

    Point& get_point(int id){
        assert(num.count(id)!=0);
        return ps[num[id]];
    }
    int get_max_degree(){
        int max_deg=0;
        for(auto&e:g){
            max_deg=max(max_deg,(int)e.size());
        }
        return max_deg;
    }
    vector<int>& get_edge(int id){
        assert(num.count(id)!=0);
        return g[num[id]];
    }
    void print_all_point(){
        for(auto&x:ps){
            x.print();
        }
    }
    void print_edge(){
        for(int i=0;i<ps.size();i++){
            ps[i].print();
            for(auto&x: g[i]){
                printf("%d ",ps[x].id);
            }
            printf("\n");
        }
    }
    void print_edge(int id){
        assert(num.count(id)!=0);
        ps[num[id]].print();
        for(auto&x: this->g[num[id]]){
            printf("%d ",ps[x].id);
        }
        printf("\n");
    }
    int size(){
        return ps.size();
    }
    vector<Point>& get_points(){
        return ps;
    }
    bool include_id(int id){
        return num.count(id)!=0;
    }
    vector<int> get_ids(){
        vector<int> ids;
        for(auto p:ps){
            ids.push_back(p.id);
        }
        return ids;
    }
private:
    int _n;

    unordered_map<int,int> num;
    vector<Point> ps;
    vector< vector<int> > g;
};


#endif // GRAPH_H_INCLUDED
