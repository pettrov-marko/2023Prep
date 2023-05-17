#include "friend.h"
#include<bits/stdc++.h>
 
using namespace std;
int findSample(int n, int confidence[], int host[], int protocol[]){
	vector<int>edges[n];
	for (int i = 1; i < n; i++){
		edges[i].push_back(host[i]);
		edges[host[i]].push_back(i);
	}
	vector<vector<int>>dp(n,vector<int>(2,0));
	function<void(int,int)>dfs = [&](int u, int p){
		dp[u][1] = confidence[u];
		for (int& x : edges[u]){
			if (x == p)continue;
			dfs(x,u);
			dp[u][1] += dp[x][0];
			dp[u][0] += max(dp[x][1], dp[x][0]);
		}
	};
	dfs(0,0);
	return max(dp[0][0], dp[0][1]);
}
