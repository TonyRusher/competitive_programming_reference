struct DSU {
	vector<int> parent;
	vector<int> rank;
	DSU(int n) : parent(n), rank(n) {
		fore(i,0,n) parent[i] = i;
	}
	int find(int u) {
		return parent[u] = (u == parent[u]? u : find(parent[u]));
	}
	void setUnion(int u, int v) {
		int pv = find(v);
		int pu = find(u);
		if(pv != pu) {
			if(rank[pu] < rank[pv]) swap(pu, pv);
			if(rank[pu] == rank[pv]) rank[pu]++;
			parent[pv] = pu;
		}
	}
	bool isSame(int u, int v) {
		return find(u) == find(v);
	}
};