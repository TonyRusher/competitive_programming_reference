const int sink = 37;
int C[50][50], F[50][50], visited[50];
int sendFlow(int node, int bottleneck){
	if(node == sink){
		return bottleneck;
	}
	visited[node] = true;
	fore(i,0,sink+1){
		int f = C[node][i] - F[node][i];
		if(f>0 && !visited[i]){
			f = sendFlow(i, min(f, bottleneck));
			if(!f) continue;
			F[node][i] += f;
			F[i][node] -= f;
			return f;
		}
	}
	return 0;
}