#include<bits/stdc++.h>
#include<wall.h>
using namespace std;
#define fr first
#define sc second
#define pb push_back
#define mp make_pair
#define ll long long 

const int EX = (int)-1e9;
const int MAXN = 2000000*3;
pair<ll,ll> t[MAXN];
pair<ll,ll> lazy[MAXN]; //{max,min}
int n;
void propagate(int k, int l, int r){
	{
			t[k].fr = max(t[k].fr, lazy[k].fr);
			t[k].sc = max(t[k].sc, t[k].fr);
			if (l != r){
				lazy[k*2].fr = max(lazy[k*2].fr, lazy[k].fr);
				lazy[k*2].sc = max(lazy[k*2].sc, lazy[k*2].fr);
				lazy[k*2+1].fr = max(lazy[k*2+1].fr, lazy[k].fr);
				lazy[k*2+1].sc = max(lazy[k*2+1].sc, lazy[k*2+1].fr);
			}
			lazy[k].fr = EX;
	}
	{
		t[k].sc = min(t[k].sc, lazy[k].sc);
		t[k].fr = min(t[k].fr, t[k].sc);
		if (l!=r){
			lazy[k*2].sc = min(lazy[k*2].sc, lazy[k].sc);
			lazy[k*2].fr = min(lazy[k*2].fr, lazy[k*2].sc);
			lazy[k*2+1].sc = min(lazy[k*2+1].sc, lazy[k].sc);
			lazy[k*2+1].fr = min(lazy[k*2+1].fr, lazy[k*2+1].sc);
		}
		lazy[k].sc = -EX;
	}
}
void update(int a, int b, int inc, int v, int l = 0, int r = n - 1, int k = 1){
	propagate(k,l,r);
	if (l > b || r < a)return;
	if (l >= a && r <= b){
		if (inc)lazy[k].fr = v;
		else lazy[k].sc=v;
		propagate(k,l,r);
		return;
	}
	update(a,b,inc,v,l,(l+r)/2,k*2);
	update(a,b,inc,v,(l+r)/2+1,r,k*2+1);
}
int query(int a, int l = 0, int r = n - 1, int k=  1){
	propagate(k,l,r);
	if (l == r){
		return t[k].fr;
	}
	int m = (l + r)/2;
	if (a <= m)return query(a,l,m,k*2);
	else return query(a,m+1,r,k*2+1);
}
void buildWall(int nn, int k, int op[], int left[], int right[], int height[], int finalHeight[]){
	n = nn;
	for (int i = 0; i < MAXN;i++){
		t[i] = {EX, -EX};
		lazy[i]= {EX,-EX};
	}
	for (int i = 0; i < k; ++i){
		update(left[i], right[i], (op[i] == 1), height[i]);
	}
	for (int i =0 ; i < n; ++i){
		finalHeight[i] = max(0, query(i));
	}
}
