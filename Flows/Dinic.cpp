typedef tuple<int, ll, ll> edge;
class max_flow{
	private:
		int V; 
		vector<edge> EL;
		vvi AL;
		vi d, last;
		vpii p;
		bool BFS(int s, int t){
			d.assign(V, -1);d[s] = 0;
			queue<int> q({s});
			p.assign(V, {-1, -1});
			while( !q.empty()){
				int u = q.front(); q.pop();
				if( u== t) break;
				for(auto &idx: AL[u]){
					auto &[v, cap, flow] = EL[idx];
					if( (cap - flow > 0) && d[v] == -1){
						d[v] = d[u] + 1, q.push(v), p[v] = {u, idx};
					}
				}
			}
			return d[t] != -1;
		}
		ll send_one_flow(int s, int t, ll f = inf){
			if  ( s == t) return f;
			auto &[u,idx] = p[t];
			auto &cap = get<1>(EL[idx]), &flow = get<2>(EL[idx]);
			ll pushed = send_one_flow(s, u, min(f, cap-flow));
			flow += pushed;
			return pushed;
		}
		ll DFS(int u, int t, ll f = inf){
			if( (u == t) || (f == 0)) return f;
			for(int &i = last[u]; i < (int) AL[u].size(); ++i){
				auto &[v, cap, flow] = EL[AL[u][i]];
				if(d[v] != d[u] + 1) continue;
				if(ll pushed = DFS(v, t, min(f, cap - flow))){
					flow += pushed;
					auto &rflow = get<2> (EL[AL[u][i] ^ 1]);
					rflow -= pushed;
					return pushed;
				}
			}
			return 0;
		}
	public:
		max_flow(int initialV) : V(initialV){
			EL.clear();
			AL.assign(V, vi());
		}
		void add_edge(int u, int v, ll w, bool directed = true){
			if( u == v) return;
			EL.emplace_back(v, w, 0);
			AL[u].pb(EL.size() - 1);
			EL.emplace_back(u, directed ? 0 : w, 0);
			AL[v].pb(EL.size() - 1);
		}
		ll edmonds_karp(int s, int t){
			ll mf = 0;
			while( BFS(s,t)){
				ll f = send_one_flow(s, t);
				if ( f == 0)break;
				mf += f;
			}
			return mf;
		}
		ll dinic(int s, int t ){
			ll mf = 0;
			while( BFS(s,t)){
				last.assign(V, 0);
				while( ll f = DFS(s,t)){
					mf += f;
				}
			}
			return mf;
		}
};