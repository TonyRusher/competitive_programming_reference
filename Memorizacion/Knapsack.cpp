int mochila(int i, int peso, int &N, int &W, vi &v, vi &w, vvi &dp){
	if(peso > W) return -inf;
	if( i == N) return 0;
	int &ans = dp[i][peso];
	if(ans != -inf) return ans;
	//if choose only one:
	//ans = max( mochila(i+1, peso, N, W, v, w, dp), mochila(i+1, peso+w[i], N, W, v, w, dp) + v[i]);
	ans = max( mochila(i+1, peso, N, W, v, w, dp), mochila(i, peso+w[i], N, W, v, w, dp) + v[i]);
	return ans;
}	