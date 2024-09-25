using cd = complex<double>;
const double PI = acos(-1);


void fft(vector<cd> & a, int inv) {
    int n = a.size();
   for(int i = 1, j = 0; i < n - 1; ++i){
		for(int k = n >> 1; (j ^= k) < k; k >>= 1);
		if(i < j) swap(a[i], a[j]);
	}
    
	vector<cd> w(n >> 1);

    for (int k = 2; k <= n; k <<= 1) {
        //   cd w1 = polar(1.0,  2 * PI / k * inv) ;
        w[0] = 1;
        for (int j = 1; j < k >> 1; j++) // best precision but slower
            w[j] = polar(1.0, 2 * j * PI / k * inv);
        	// w[j] = w[j-1]*w1;
        for (int i = 0; i < n; i += k) {
            for (int j = 0; j < k >> 1; j++) {
                cd u = a[i + j], v = a[i + j + (k >> 1)] * w[j];
                a[i + j] = u + v;
                a[i + j + (k >> 1)] = u - v;
            }
        }
    }
    if (inv == -1) for (cd & x : a) x /= n;
}

vector<ll> multiply(vector<ll> const& a, vector<ll> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size() - 1)  n <<= 1;
	fa.resize(n); fb.resize(n);
    
	fft(fa, 1); fft(fb, 1);
	fore(i,0,n) fa[i] *= fb[i];
    fft(fa, -1);

    vector<ll> result(n);
    for (int i = 0; i < n; i++) result[i] = round(fa[i].real());
    return result;
}

/* if it's numbers and not polynomials, we have to normalise */
void normalise(vll &ans) {
	for (ll i = 0, carry = 0; i < ans.size(); ++i) {
		ans[i] += carry;
		carry = ans[i] / 10;
		ans[i] %= 10;
	}
}