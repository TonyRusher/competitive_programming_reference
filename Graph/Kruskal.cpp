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

vector<int> parent, rank;

void make_set(int v) {
    parent[v] = v;
    rank[v] = 0;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (rank[a] < rank[b])
            swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            rank[a]++;
    }
}

struct Edge {
    int u, v, weight;
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};

void Kruskal(){
	int n;
	vector<Edge> edges;

	int cost = 0;
	vector<Edge> result;
	parent.resize(n);
	rank.resize(n);
	for (int i = 0; i < n; i++) make_set(i);

	sort(edges.begin(), edges.end());

	for (Edge e : edges) {
		if (find_set(e.u) != find_set(e.v)) {
			cost += e.weight;
			result.push_back(e);
			union_sets(e.u, e.v);
		}
	}

}

int main() {
	fast_io;
	
	
	
	return 0;
}