#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
//#include "atcoder/segtree"

#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i=0;i<n;i++)
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define DWN(i,b,a) for(int i=b;i>=a;i--)
#define mp(a,b) make_pair(a,b)
#define pb push_back
#define ALL(x) (x).begin(),(x).end()

typedef long long ll;
typedef vector<int> VI;
typedef vector<ll> VL;
typedef vector<VI> VVI;
typedef vector<VL> VVL;
typedef pair<int,int> PII;
typedef pair<ll,ll> PLL;

typedef complex<double> P;
#define X()  real()
#define Y()  imag()

void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}
void __print(P x) {cerr<<"("<<x.X()<<","<<x.Y()<<")";}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef NDEBUG
#define dbg(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define dbg(x...)
#endif

template<class T> inline T min(T a, T b, T c){return min(min(a, b), c);}

clock_t startTime,lastTime;
double getLastTime() {
    double ret = (double)(clock() - lastTime) / CLOCKS_PER_SEC;
    lastTime = clock();
	return ret;
}
double getCurrentTime() {
	return (double)(clock() - startTime) / CLOCKS_PER_SEC;
}
void time(){
    cerr<<"Time:"<<getCurrentTime()<<endl;
}
void time(string s){
    cerr<<s<<" Time:"<<getCurrentTime()<<endl;
}
#endif // HEADER_H_INCLUDED
