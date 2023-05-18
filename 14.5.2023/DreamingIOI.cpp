#include<bits/stdc++.h>
#include "dreaming.h"
using namespace std;
const int maxN = (int)1e5 + 5;
#define ll long long
vector<vector<pair<ll,ll>>>adj(maxN);
ll vis[maxN], dist[maxN], parent[maxN];
ll mx = 0, source = -1;
ll ans = 0;
void dfs(int u, int p = -1, ll d = 0){
    vis[u] = 1;
    parent[u] = p;
    dist[u] = d;
    ans = max(ans, d);
    if (mx < d){
        mx = d;
        source = u;
    }
    for (auto x : adj[u]){
        if (x.first == p){
            continue;
        }
        dfs(x.first, u, x.second + d);
    }
}
 
int travelTime(int N, int M, int L, int A[], int B[], int T[]){
    for (int i = 0; i < M; i++){
        //cout<<A[i]<<" "<<B[i]<<endl;
        adj[A[i]].push_back({B[i], T[i]});
        adj[B[i]].push_back({A[i], T[i]});
    }
    vector<pair<ll,ll>>centroids;
    for (int i = 0; i < N; i++){
        if (vis[i])continue;
        mx = -1, source = -1;
        dfs(i);
        int S = source;
        mx = -1;
        dfs(S);
        int E = source;
        vector<pair<ll,ll>>path;
       // cout<<S<<" "<<E<<endl;
        while(E != S){
            path.push_back({E, dist[E]});
            E = parent[E];
        }
        path.push_back({E, dist[E]});
        reverse(path.begin(), path.end());
        ll diameter = path.back().second;
        ll best_node = path[0].first, best_dist = 1e18;
        for(int j = 0; j < path.size(); j++){
            if(max(path[j].second, diameter - path[j].second) < best_dist){
                best_node = path[j].first;
                best_dist = max(path[j].second, diameter - path[j].second);
            }
        }
        centroids.push_back({best_dist, best_node});
    }
   // for (auto j  : centroids)cout<<j.first<<" "<<j.second<<endl;
    sort(centroids.rbegin(), centroids.rend());
    for(int i = 1; i < centroids.size(); i++){
        adj[centroids[0].second].push_back({centroids[i].second, L});
        adj[centroids[i].second].push_back({centroids[0].second, L});
    }
    mx = -1;
    dfs(0);
    mx = -1;
    dfs(source);
    return mx;
}
