#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include "atcoder/segtree"

#include <bits/stdc++.h>
using namespace std;
#define REP(i,n) for(int i=0;i<n;i++)
#define FOR(i,a,b) for(int i=a;i<=b;i++)
#define DWN(i,b,a) for(int i=b;i>=a;i--)
#define mp(a,b) make_pair(a,b)
#define pb push_back
#define RD(n) scanf("%d",&(n))
#define ALL(x) (x).begin(),(x).end()

typedef long long ll;
typedef vector<int> VI;
typedef vector<ll> VL;
typedef vector<VI> VVI;
typedef vector<VL> VVL;
typedef pair<int,int> PII;
typedef pair<ll,ll> PLL;

#define printv(v) for(auto&x:v)cout<<x<<",";cout<<endl;

template<class T> inline T min(T a, T b, T c){return min(min(a, b), c);}

#endif // HEADER_H_INCLUDED
