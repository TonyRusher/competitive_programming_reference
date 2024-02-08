int hasCycleDirected(int current, vector<vector<int>> &graph, vector<int> &color){
	if(color[current] == 1) return 1;
	if(color[current] == 2) return 0;
	color[current] = 1;
	int ans = 0;
	for(int child: graph[current]){
		ans = ans | hasCycleDirected(child, graph, color);
	}
	color[current] = 2;
	return ans;
}
int hasCycleUndirected(int current, int father, vector<vector<int>> &graph, vector<int> &color){
	if(color[current] == 1) return 1;
	color[current] = 1;
	int ans = 0;
	for(int child: graph[current]) if(child != father)
		ans = ans | hasCycleUndirected(child, current, graph, color);
	return ans;
}
int isBipartiteDFS(int current, vector<vector<int>> &graph, vector<int> &color){
	bool is = 1;
	for(int child : graph[current]){
		if(color[child] == 0){//no esta coloreado
			color[child] = color[current] == 1 ? 2 : 1;// coloreo con el color opuesto a mi nodo current
			is = is & isBipartiteDFS(child, graph, color);
		}
		else if(color[child] == color[current]) return 0;//si son iguales no es bipartito 
	}
	return is;
}
bool isBipartiteBFS(int start, vector<vector<int>> &graph, vector<int> &color){
	int n = graph.size();
	queue<pair<int, int>> q; //node, color
	q.push({start, 1});
	color[start] = 1;
	while(!q.empty()){
		auto current = q.front(); q.pop();
		for (int child :graph[current.first]){
			if(color[child] == current.second) return false;
			if(color[child] == 0){
				color[child] = current.second == 1 ? 2 : 1;
				q.push({child, color[child]});
			}
		}
	}
	return true;
}