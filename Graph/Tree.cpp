struct Tree { // 1 indexed
	int n, root;
	vvi ancestros; // Binary lifting
	vi level, sz; // Binary lifting
	vi tin, tout, aplanado;// Euler tour
	vi distancias; //Diameter or distance from a node 
	
	Tree(int n, int root, vvi& adj): root(root), n(n), 
	ancestros(21, vi(n+1, 0)), sz(n+1, 1), level(n+1), 
	tin(n+1, 0), tout(n+1, 0), aplanado(n+1,0) {
		int idx = 1; 
		precalc(root, root, adj, idx);// precalculos
		fore(k, 1, 21) fore(x, 1, n + 1) //binary lifting
			ancestros[k][x] = ancestros[k - 1][ancestros[k - 1][x]];
		tout[0] = n + 1;// just in case
	}
	
	void precalc(int curr, int father, vvi &adj, int &idx) {//DFS O(n)
		tin[curr] = idx;
		aplanado[idx] = curr;
		
		for (auto& next : adj[curr]) {
			if (next == father) continue;
			ancestros[0][next] = curr;
			level[next] = level[curr] + 1;
			
			idx++; precalc(next, curr, adj, idx);
			sz[curr] += sz[next];
		}
		tout[curr] = idx;
	}

	int kAncestorOfx(int k, int x) {//O(log(n))
		fore(j,0,21) if (k & (1 << j)) x = ancestros[j][x];
		return x;
	}

	int LCA(int u, int v) {//O(log(n))
		if(level[u] < level[v]) swap(u,v);
		int k = level[u] - level[v];
		u = kAncestorOfx(k, u);
		if(u == v) return u;
		for(int i = 20; i >= 0; i--){
			if(ancestros[i][u] != ancestros[i][v]){
				u = ancestros[i][u];
				v = ancestros[i][v];
			}
		}
		return ancestros[0][u];
	}
	
	int isAncestor(int u, int v) { // O(1)
		return tin[u] <= tin[v] && tout[v] <= tout[u];
	}
	int LCA2(int u, int v) {//O(log(n))
		if (isAncestor(u, v)) return u;
		if (isAncestor(v, u)) return v;
		for(int k = 20; k >= 0; k--){
			if(!isAncestor(ancestros[k][u], v)) 
				u = ancestros[k][u];
		}
		return ancestros[0][u];
	}
	
	void dfs_distances(int curr, int father, vvi &adj, vi &distancias, int dist){//O(n)
		distancias[curr] = dist;
		for(auto &next : adj[curr]){
			if(next == father) continue;
			dfs_distances(next, curr, adj, distancias, dist + 1);
		}
	}
	int getDiameter(vvi &adj){// O(2n)
		distancias.assign(n+1,0);
		dfs_distances(root, root, adj, distancias, 0);
		int farthest = root;
		int max_dist = 0;
		fore(i,1,n+1){
			if(distancias[i] > max_dist){
				farthest = i;
				max_dist = distancias[i];
			}
		}
		
		distancias.assign(n+1,0);
		max_dist = 0;
		dfs_distances(farthest, farthest, adj, distancias, 0);
		fore(i,1,n+1){
			max_dist = max(max_dist, distancias[i]);
		}
		return max_dist;
	}

	int getCentroid(vvi& adj){ // 
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
	
	void printData(){
		// fore(i,0,n+1) cout << tin[i] << ' ' ; cout << endl;
		// fore(i,0,n+1) cout << tout[i] << ' '; cout << endl;
		// fore(i,0,4) {fore(j,0,n+1) cout << ancestros[i][j] <<' '; cout << endl;}
	}
};