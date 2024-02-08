struct Tree {
	int n, root, idx;
	vvi ancestros;
	vi level, tin, tout, aplanado, sz;

	Tree(int n, int root, vvi& adj) :root(root),n(n), ancestros(21, vi(n+1, 0)), 
						level(n+1), tin(n+1), tout(n+1), aplanado(n+1), sz(n+1, 1){
		idx = 1; dfs(root, root, adj);
		fore(k, 1, 21) fore(x, 1, n + 1) ancestros[k][x] = ancestros[k - 1][ancestros[k - 1][x]];
	}
	void dfs(int curr, int father, vvi &adj) {
		tin[curr] = idx;
		aplanado[idx] = curr;
		for (auto& next : adj[curr]) {
			if (next == father) continue;
			
			idx++; dfs(next, curr, adj);
			
			ancestros[0][next] = curr;
			level[next] = level[curr] + 1;
			sz[curr] += sz[next];
		}
		tout[curr] = idx;
	}

	int kAncestorOfx(int k, int x) {
		fore(j,0,21) if (k & (1 << j)) x = ancestros[j][x];
		return x;
	}
	int isAncestor(int u, int v) {
		return tin[u] <= tin[v] && tout[v] <= tout[u];
	}
	int LCA(int u, int v) {
		if(level[u] < level[v]) swap(u,v);
		int k = level[u] - level[v];
		u = kAncestorOfx(k, u);
		if(u == v) return u;
		forr(i, 20, -1){
			if(ancestros[i][u] != ancestros[i][v]){
				u = ancestros[i][u];
				v = ancestros[i][v];
			}
		}
		return ancestros[0][u];
	}
	// int LCA(int u, int v) {
	// 	if (isAncestor(u, v)) return u;
	// 	if (isAncestor(v, u)) return v;
	// 	forr(k, 20, -1) if(!isAncestor(ancestros[k][u], v)) u = ancestros[k][u];
	// 	return ancestros[0][u];
	// }
	int centroid(vvi& adj){
		int vf = 1;
		while(vf){
			vf = 0;
			for(auto next: adj[root]){
				if(sz[next] > n/2){
					int aux = sz[root];
					sz[root] -= sz[next];
					sz[next] = aux;
					root = next;
					vf = 1;
				}
			}
		}
		return root;
	}
	void printAncestros(){
		fore(i,0,4) {fore(j,0,n+1) cout << ancestros[i][j] <<' '; cout << endl;}
	}
};
	
	