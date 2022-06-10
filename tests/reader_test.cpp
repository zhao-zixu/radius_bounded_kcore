#include <bits/stdc++.h>
using namespace std;
//#include "../lib/header.h"
#include "../lib/graph.h"
#include "../lib/kcore.h"
#include "../lib/geometry.h"
#include "../lib/reader.h"




int ioTest() {
	int nbRows = 5, nbCols = 3;
	auto grid = read<vector<vector<int>>>(nbRows, nbCols);

	write(grid);
	return 0;
}
int main(){
	#ifdef LOCAL
		freopen("input.txt","r",stdin);
		//freopen("output.txt","w",stdout);
	#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
    ioTest();
	return 0;
}
