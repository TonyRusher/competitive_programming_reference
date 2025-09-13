struct DSU {
	vector<int> parent;
	vector<int> rank;
	DSU(int n) : parent(n), rank(n) {
		fore(i,0,n) parent[i] = i;
	}
	int Find(int u) {
		return parent[u] = (u == parent[u]? u : Find(parent[u]));
	}
	void Union(int u, int v) {
		int pv = Find(v);
		int pu = Find(u);
		if(pv != pu) {
			if(rank[pu] < rank[pv]) swap(pu, pv);
			if(rank[pu] == rank[pv]) rank[pu]++;
			parent[pv] = pu;
		}
	}
	bool is_same(int u, int v) {
		return Find(u) == Find(v);
	}
};