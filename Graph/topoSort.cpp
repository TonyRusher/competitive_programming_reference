vi toposortBFS(vvi &graph){
    int n = graph.size();
    vi incoming_edges(n);
	fore(i,0,n) for(auto v: graph[i]) incoming_edges[v]++;
    queue<int> q;
    fore(i,0,n) if(incoming_edges[i] == 0) q.push(i);        
    int cnt = 0;
    vi ans;
    while(!q.empty()){
        int u = q.front(); q.pop();
        ans.push_back(u);
        cnt++;
        for(auto v: graph[u]){
            incoming_edges[v]--;
            if(incoming_edges[v] == 0) q.push(v);
        }
    }
    if(cnt != n) return {-1};
    return ans;
}
void dfs(int curr, vector<bool> &visited, vector<vector<int>> &graph, vector<int> &ans){
    if(visited[curr]) return;
    visited[curr] = true;
    for(auto nextNode: graph[curr])  dfs(nextNode, visited, graph, ans);
    ans.push_back(curr);
    return;
}
vector<int> toposort_dfs(vector<vector<int>> &graph){
    int n = graph.size();
    vector<bool> visited(n);
    vector<int> ans;
    fore(i,0,n) if(!visited[i]) dfs(i, visited, graph, ans);
    reverse(ans.begin(), ans.end());//dfs => reverse
    return ans;
}