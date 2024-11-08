int solve(int n, vi &dp, int &a, int &b, int &c){
	if(n == 0) return 0;
	if(n < 0) return -(1<<30);
	int &ans = dp[n];
	if(ans != -1) return ans;
	ans = max( solve(n-a, dp, a, b, c), max( solve(n-b, dp, a, b, c), solve(n-c, dp, a, b, c) ) ) + 1;
	return ans;
}
