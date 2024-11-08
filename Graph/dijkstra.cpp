vi dijkstra(int start, int n, vvpii graph){
	priority_queue<pii, vpii, greater<pii>> pq;
	vi pesos(n, INT_MAX);
	pq.push({0, start});
	pesos[start] = 0;
	while(!pq.empty()){
		int v = pq.top().second;pq.pop();
		for (auto next : graph[v]){
			int u = next.first, w = next.second;
			if(pesos[u] > pesos[v] + w){
				pesos[u] = pesos[v] + w;
				pq.push({pesos[u], u });
			}
		}
	}
	return pesos;
}