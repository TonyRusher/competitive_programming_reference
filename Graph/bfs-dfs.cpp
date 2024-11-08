void bfs(vector<vector<int>> &graph, int start){
	int n = graph.size();
	queue<int> q; q.push(start);
	vector<int> visited(n,0);
	while(!q.empty()){
		int current = q.front(); q.pop();
		for(auto next: graph[current])
			if(!visited[next])
				q.push(next);
	}
	return;
}
void dfs(int current, vector<vector<int>> &graph, vector<int> visited){
	visited[current] = 1;
	for(auto next: graph[current])
		if(!visited[next])  dfs(next, graph, visited );
	return;
}