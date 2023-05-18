#include "friend.h"
#include<bits/stdc++.h>
 
using namespace std;
int findSample(int n, int confidence[], int host[], int protocol[]){
	vector<int>edges[n];
	vector<int>tip(n, 0);
	for (int i = 1; i < n; i++){
		if (protocol[i] == 0){
			//iam your friend
			edges[i].push_back(host[i]);
			edges[host[i]].push_back(i);
			tip[i] = tip[host[i]] ^ 1;	
		}else{
			for (int& x : edges[host[i]]){
				edges[i].push_back(x);
				edges[x].push_back(i);
			}
			tip[i] = tip[host[i]];
		}
	}
	//bipirtite max match is congruent to Min Vertex cover
	//because of konig's theorem
	//max independent set is opposite of min vertex cover
	vector<bool>used(n, false);
	vector<int>to(n, -1);
	int res = n;
	
	function<int(int)>dfs = [&](int u){
		for (int& x : edges[u]){
			if (used[x])continue;
			used[x] = 1;
			if (to[x] == -1 || dfs(to[x])){
				to[x] = u;
				return 1;
			}
		} 
		return 0;
	};
	
	for (int i = 0; i < n; i++){
			if (tip[i])continue;
			used.assign(n, false);
			res -= dfs(i);
		
	}
	return res;
}
