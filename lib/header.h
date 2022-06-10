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

#define printv(v) {for(auto&x:v){cout<<x<<",";}cout<<endl;}
#define printvv(vv) for(auto&y:vv){printv(y);cout<<endl;}cout<<endl;
inline void out(auto a){cout<<a<<endl;}
inline void out(auto a,auto b){cout<<a<<","<<b<<endl;}
inline void out(auto a,auto b,auto c){cout<<a<<","<<b<<","<<c<<endl;}

template<class T> inline T min(T a, T b, T c){return min(min(a, b), c);}

clock_t startTime;
double getCurrentTime() {
	return (double)(clock() - startTime) / CLOCKS_PER_SEC;
}
void time(){
    cout<<"Time:"<<getCurrentTime()<<endl;
}
void time(string s){
    cout<<s<<" Time:"<<getCurrentTime()<<endl;
}
#endif // HEADER_H_INCLUDED
