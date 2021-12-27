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
    bool within_dis(Point p, double d){
        return getDis(p)<=d;
    }
    double getPolarAngle(Point p){
        double dx=x-p.x,dy=y-p.y;
        return atan2(dy,dx);
    }
};
struct Reader{
    #define NEXT_LINE -2
    static const int MAX_CHAR = 1e6;
    char buffer[MAX_CHAR];
    FILE*f;
    int n,i;
    bool new_line;
    Reader(const char* file_name){
        f = fopen(file_name,"r");
        if(f==NULL){
            printf("Open file failure.\n");
            return;
        }
        i=0;
        n = fread(buffer,1,MAX_CHAR,f);
        new_line=false;
    }
    inline char get_char(){
        if(f==NULL){
            return EOF;
        }
        if(i<n){
            return buffer[i++];
        }else{
            n = fread(buffer,1,MAX_CHAR,f);
            i=0;
            if(n>0){
                return buffer[i++];
            }
            else {
                fclose(f);
                f=NULL;
                return EOF;
            }
        }
    }
    inline int next_char(){
        if(f==NULL)return EOF;
        i++;
        if(i>=n){
            n = fread(buffer,1,MAX_CHAR,f);
            i=0;
            if(n==0){
                fclose(f);
                f=NULL;
                return EOF;
            }
        }
        return 1;
    }
    int next(){
        if(i>=n){
            n = fread(buffer,1,MAX_CHAR,f);
            i=0;
            if(n==0){
                fclose(f);
                f=NULL;
                return EOF;
            }
        }
        if(f==NULL){
            return EOF;
        }
        if(new_line){
            new_line=false;
            return NEXT_LINE;
        }
        while(!isdigit(buffer[i])&&buffer[i]!='\n'){//&&buffer[i]!='-'&&buffer[i]!='.'
            if(next_char()==EOF)return EOF;
        }
        if(buffer[i]=='\n'){if(next_char()==EOF)return EOF;else return NEXT_LINE;}
        else return 1;
    }
//    void out(){
//        cout<<buffer[i]<<","<<i<<","<<n<<endl;
//    }
#define g (c=get_char())
#define d isdigit(g)
#define p x=x*10+c-'0'
#define n x=x*10+'0'-c
#define pp l/=10,p
#define nn l/=10,n
    template<class T> inline int RD(T &x){
        int next_=next();
        while(next_==NEXT_LINE){next_=next();}//return NEXT_LINE;
        if(next_==EOF){return EOF;}
        char c;while(!d);x=c-'0';while(d)p;
        return 1;
    }
    template<class T> inline int RD2(T &x){
        int next_ = next();
        if(next_==NEXT_LINE)return NEXT_LINE;
        else if(next_==EOF)return EOF;
        char c;while(!d);x=c-'0';while(d)p;
        if(c=='\n'){
            new_line=true;
            return 1;
        }
        return 1;
    }
    template<class T> inline int RDD(T &x){
        char c;while(g,c!='-'&&!isdigit(c));
        if (c=='-'){x='0'-g;while(d)n;}
        else{x=c-'0';while(d)p;}
        return 1;
    }
    inline int RF(double &x){
        int next_ = next();
        if(next_==NEXT_LINE)return NEXT_LINE;
        else if(next_==EOF)return EOF;
        //scanf("%lf", &x);
        char c;while(g,c!='-'&&c!='.'&&!isdigit(c));
        if(c=='-')if(g=='.'){x=0;double l=1;while(d)nn;x*=l;}
            else{x='0'-c;while(d)n;if(c=='.'){double l=1;while(d)nn;x*=l;}}
        else if(c=='.'){x=0;double l=1;while(d)pp;x*=l;}
            else{x=c-'0';while(d)p;if(c=='.'){double l=1;while(d)pp;x*=l;}}
        return 1;
    }
#undef nn
#undef pp
#undef n
#undef p
#undef d
#undef g

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


    void read_pos(const char* file_name){
        Reader reader(file_name);
        int id=0;
        while(reader.RD(id)==1){
            double x=0,y=0;
            reader.RF(x),reader.RF(y);
            Point p(x,y,id);
            add_point(p);
        }
        _n=ps.size();
        g=vector<vector<int> >(_n);
    }
    void read_edge(const char* file_name){
        Reader reader(file_name);
        int id=0;
        while(reader.RD(id)==1){
            int e;
            while(reader.RD2(e)==1){
                add_edge(id-1,e-1);
            }
        }
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
    graph* clone(){
        graph* ng = new graph();
        ng.num=num;
        ng.ps=ps;
        ng.g=g;
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
//        assert(num.count(from)!=0);
//        assert(num.count(to)!=0);
//        from=num[from],to=num[to];
        assert(0<=from&&from<(int)ps.size());
        assert(0<=to&&to<(int)ps.size());
        g[from].push_back(to);
        g[to].push_back(from);
        return 0;
    }
    void del_point(int id){
        assert(num.count(id)!=0);
        int nid = num[id];
        for(auto&x:g[nid]){
            del_edge(nid,x);
        }

    }
    void del_edge(int from,int to){
        assert(0<=from&&from<(int)ps.size());
        assert(0<=to&&to<(int)ps.size());

        for(auto&x:g[from]){
            if(x==to){
                swap(x,*g[from].rbegin());
                g[from].pop_back();
                break;
            }
        }
        for(auto&x:g[to]){
            if(x==from){
                swap(x,*g[to].rbegin());
                g[to].pop_back();
                break;
            }
        }
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
    vector<int> gen_edge_id(int num){
        assert(0<=num&&num<(int)ps.size());
        vector<int> e;
        for(auto v:g[num]){
            e.push_back(ps[v].id);
        }
        return e;
    }
    void print_all_point(){
        for(auto&x:ps){
            x.print();
        }
    }
    void print_edge(){
        for(int i=0;i<(int)ps.size();i++){
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
    int get_num(int id){
        assert(num.count(id)!=0);
        return num[id];
    }
    bool include_id(int id){
        return num.count(id)!=0;
    }
    bool include_num(int num){
        return 0<=num&&num<ps.size();
    }
    vector<int> get_ids(){
        vector<int> ids;
        for(auto p:ps){
            ids.push_back(p.id);
        }
        return ids;
    }
    vector<Point>& get_point_set(){
        return ps;
    }
    vector< vector<int> >& get_edge_set(){
        return g;
    }
    Point& operator[](int i){
        assert(0<=i&&i<(int)ps.size());
        return ps[i];
    }
    void erase(int i){
        num.erase(i);
    }
private:
    int _n;

    unordered_map<int,int> num;
    vector<Point> ps;
    vector< vector<int> > g;
};


#endif // GRAPH_H_INCLUDED
