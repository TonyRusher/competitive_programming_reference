//#define feach(f, g) for(auto &f: g)
const int N=1e5+10, MOD=1e9+7, SIG=26;
int id=1, dp[N];
string s;
vector<int> adj[2*N];

struct node{
	int fail,ch[SIG]={};
	vector<int> lens;
}t[2*N];
void insert(string s){
	int u=1;
	for(auto &c: s){
		c-='a';
		if(!t[u].ch[c]) t[u].ch[c]=++id;
		u=t[u].ch[c];
	}
	t[u].lens.pb(s.size());
}
void dfs(int u){
	t[u].lens.insert(t[u].lens.end(), t[t[u].fail].lens.begin(), t[t[u].fail].lens.end());
	for(auto &v: adj) dfs(v);
}
void build(){
	queue<int> q;
	int u=1;
	t[1].fail=1;
	fore(i,0,SIG) {
		if(t[u].ch[i]) t[t[u].ch[i]].fail=u, q.push(t[u].ch[i]);
		else t[u].ch[i]=1;
	}
	while(!q.empty()){
		u=q.front(); q.pop();
		fore(i,0,SIG){
			if(t[u].ch[i]) t[t[u].ch[i]].fail=t[t[u].fail].ch[i], q.push(t[u].ch[i]);
			else t[u].ch[i]=t[t[u].fail].ch[i];
		}
	}
	fore(i,2,id+1) adj[t[i].fail].pb(i);
	dfs(1);
}