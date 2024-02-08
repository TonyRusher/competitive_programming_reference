const int  mod = 998244353, g = 3;

lli powMod(lli a, lli b, lli mod){
	lli ans = 1;
	b %= mod-1;
	if(b < 0) b+= mod-1;
	while(b){
		if(b&1) ans = ans * a % mod;
		a = a*a %mod;
		b>>=1;
	}
	return ans;
}
lli inverse(lli a, lli mod){return powMod(a,mod-2, mod);}

template<int mod, int g>
void ntt(vector<int> & X, int inv){
	int n = X.size();
	for(int i = 1, j = 0; i < n - 1; ++i){
		for(int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(X[i], X[j]);
	}
	vector<lli> wp(n>>1, 1);
	for(int k = 1; k < n; k <<= 1){
		lli wk = powMod(g, inv * (mod - 1) / (k<<1), mod);
		for(int j = 1; j < k; ++j)
			wp[j] = wp[j - 1] * wk % mod;
		for(int i = 0; i < n; i += k << 1){
			for(int j = 0; j < k; ++j){
				int u = X[i + j], v = X[i + j + k] * wp[j] % mod;
				X[i + j] = u + v < mod ? u + v : u + v - mod;
				X[i + j + k] = u - v < 0 ? u - v + mod : u - v;
			}
		}
	}
	if(inv == -1){
		lli nrev = inverse(n, mod);
		for(int i = 0; i < n; ++i)
			X[i] = X[i] * nrev % mod;
	}
}

template<int mod, int g>
vector<int> multiply(vector<int> const& a, vector<int> const& b) {
    vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size() - 1)  n <<= 1;
	fa.resize(n); fb.resize(n);
    
	ntt<mod, g>(fa, 1); ntt<mod, g>(fb, 1);
	fore(i,0,n) fa[i] = (1LL * fa[i] * fb[i]) % mod;
    ntt<mod, g>(fa, -1);

    return fa;
}
