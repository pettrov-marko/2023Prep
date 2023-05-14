#include "friend.h"
#include<bits/stdc++.h>
 
using namespace std;
int findSample(int n, int confidence[], int host[], int protocol[]){
	vector <vector <int>> dp(n, vector<int>(2, 0));
	for(int i = 0; i < n; i++)dp[i][1] = confidence[i];
	for (int i = n - 1; i>=1; --i) {
		if (!protocol[i]) {
			dp[host[i]][0] += max(dp[i][0], dp[i][1]);
			dp[host[i]][1] += dp[i][0];
		} else if (protocol[i] == 1) {
			dp[host[i]][1] += max(dp[i][0], dp[i][1]);
			dp[host[i]][1] = max(dp[host[i]][1], dp[host[i]][0] + dp[i][1]);
			dp[host[i]][0] += dp[i][0];
		} else {
			dp[host[i]][1] += dp[i][0];
			dp[host[i]][1] = max(dp[host[i]][1], dp[host[i]][0] + dp[i][1]);
			dp[host[i]][0] += dp[i][0];
 
		}
	}
	return max(dp[0][0], dp[0][1]);
}
