// Handle: Osama Fathy
// Problem: 820 - Internet Bandwidth
// Submission ID: 16797980
// Verdict: AC
// Runtime: 0.019

// Hint: Max Flow - Ford-Fulkerson method
#include <bits/stdc++.h>
using namespace std;
const int kMax = 101;
int bandwidth[kMax][kMax];
int path[kMax];
bool vis[kMax];
int n;

int *findPath(int cur, int curLen, int target, int maxBW) {
	path[curLen] = cur;
	vis[cur] = true;
	if(cur == target)  return maxBW;

	for(int i = 0; i < n; i++) {
		if(!vis[i] && bandwidth[cur][i] > 0) {
			int bw = findPath(i, curLen+1, target, min(maxBW, bandwidth[cur][i]));
			if(bw > 0) return bw;
		}
	}
	return 0;
}
int maxFlow(int src, int sink) {
	int totalBW = 0;

	while(1) {
		memset(vis, 0, sizeof(vis));
		int bw = findPath(src, 0, sink, 2e9);
		if(!bw) break;
		totalBW += bw;

		int ind = 0;
		while(path[ind] != sink) {
			bandwidth[path[ind]][path[ind+1]] -= bw;
			bandwidth[path[ind+1]][path[ind]] += bw;
			ind++;
		}
	}
	return totalBW;
}
int main() {
    int src, dest, edges;
	for (int f = 1;; f++) {
		cin>>n;
		if (!n) break;

		memset(bandwidth, 0, sizeof(bandwidth));
		cin>>src>>dest>>edges;
		for(int i = 0; i < edges; i++) {
			int node1, node2, bw;
			cin >> node1 >> node2 >> bw;
			bandwidth[node1-1][node2-1] += bw;
            bandwidth[node2-1][node1-1] += bw;
        }
		cout<<"Network "<<f<<"\nThe bandwidth is "<<maxFlow(src-1, dest-1)<<".\n\n";
	}
	return 0;
}
