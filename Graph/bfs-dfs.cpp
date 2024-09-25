//salve a la draga la reina eres tu
#include <bits/stdc++.h>

#define endl '\n'
#define ll long long 
#define lli long long int
#define ld long double
#define fore(i,a,b) for (int i = a; i < b; i++)
#define forr(i,a,b) for (int i = a; i > b; i--)
#define forn(i,n) for (int i = 0; i < n; i++)
#define fi first
#define se second
#define pb push_back
#define all(v) v.begin(), v.end()
#define fast_io ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

using namespace std;

typedef pair<ll, ll>  pll;
typedef pair<int, int>  pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<vi> vvi;
typedef vector<pii> vpii;
typedef vector<pll> vpll;
typedef map<int, int> mii;

const int inf = 1<<30;

void bfs(vector<vector<int>> &graph, int start){
	int n = graph.size();
	queue<int> q;
	q.push(start);
	vector<int> visited(n,0);
	while(!q.empty()){
		int current = q.front();
		q.pop();
		for(auto next: graph[current]){
			if(!visited[next]){
				q.push(next);
			}
		}
	}
	
	return;
}

void dfs(int current, vector<vector<int>> &graph, vector<int> visited){
	visited[current] = 1;
	for(auto next: graph[current]){
		if(!visited[next]) 
			dfs(next, graph, visited  );
	}
	return;
}

int main() {
	fast_io;
	
	
	
	return 0;
}