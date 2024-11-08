
struct HeavyLightDecomp {
	int n, root, idx;
	vi level, size, head, pos, newVals;
	vvi ancestros;

	HeavyLightDecomp(int n, int root, vvi & adj, vi& vals):n(n), root(root), ancestros(21, vi(n+1,0)),level(n+1), size(n+1, 1), head(n+1), pos(n+1), newVals(1){
		dfs(root, root, adj);
		idx = 1; hld(root, root, adj, vals);
	}
	void dfs(int curr, int father, vvi & adj) {
		for (auto& next : adj[curr]) {
			if (next == father) continue;
			ancestros[0][next] = curr;
			level[next] = level[curr] + 1;
			dfs(next, curr, adj);
			size[curr] += size[next];
		}
	}
	void hld(int curr, int nodeHead, vvi &adj, vi &vals){
		head[curr] = nodeHead;
		pos[curr] = idx++;
		newVals.pb(vals[curr]);
		int sz_heavy = 0, heavy = -1;
		for(auto next: adj[curr]){
			if(next == ancestros[0][curr])  continue;
			if(size[next] > sz_heavy)
				sz_heavy = size[next], heavy = next;
			
		}
		if(heavy != -1) hld(heavy, nodeHead, adj, vals);
		for(auto next: adj[curr])
			if(next != heavy && next != ancestros[0][curr]) 
				hld(next, next, adj, vals);
	}
	template <class BinaryOperation>
	void traversePath(int u, int v, BinaryOperation op){
		for(; head[u] != head[v]; u = ancestros[0][head[u]]){
			if(level[head[u]] < level[head[v]]) swap(u,v);
			op(pos[head[u]], pos[u]);
		}
		if(pos[u] > pos[v]) swap(u,v);
		op(pos[u], pos[v]);
	}
	template <class DSType> ll query(int u, int v, DSType *st){
		int ans = -1;
		traversePath(u, v, [this, &ans, st](int l, int r){ans = max(ans, st->query(l,r));});
		return ans;
	}
	template <class DSType> void update(int u, ll val, DSType *st){
		traversePath(u, u, [this, &val, st](int l, int r){st->update(l, val);});
	}
};