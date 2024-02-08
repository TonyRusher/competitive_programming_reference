//SQRT decomposition
//if RTE, change limits to min(br, n)
template <typename TT>
struct SQRT{
	int n, s;
	TT neutro = 0;
	vector<TT> A, B;
	vector<TT> lazy, marks;
	
	SQRT(int m, vector<TT> &arr): n(m){
		s = sqrt(n) + 1;//puede variar
		A.assign(n, neutro);
		B.assign(n / s + 1, neutro);
		lazy.assign(s, neutro); marks.assign(s, neutro);
		fore(i,0,n){ A[i] = arr[i]; B[i/s] += arr[i]; }
	}
	void pushLazy(int block){
		if(marks[block]){
			fore(i,block,(block+1) * s && i < n) A[i] += lazy[block];
			lazy[block] = neutro; marks[block] = 0;
		}
	}
	void rangeUpdate(int l, int r, TT value){
		int bl = l/s, br = r/s;
		if(bl == br){
			pushLazy(bl);
			fore(i,l,r+1) A[i] += value;
			TT res = neutro;
			fore(i, bl*s, (bl+1) * s && i < n) res += A[i];
			B[bl] = res;
		}else{
			pushLazy(bl);pushLazy(br);
			fore(i,l,(bl+1) * s){ A[i] += value; B[bl] += value;}
			fore(i,bl+1, br)    { B[i] += s * value; lazy[i] += value; marks[i] = 1;}
			fore(i,br * s, r+1) { A[i] += value; B[br] += value;}
		}
	}
	void pointUpdate(int idx, TT value){//not lazy
		int block = idx / s;
		A[idx] = value;
		TT res = neutro;
		fore(i, block * s, (block + 1) * s && i < n) res += A[i];
		B[block] = res;
	}
	TT rangeQuery(int l, int r){
		int bl = l/s, br = r/s;
		TT res = 0;
		if(bl == br){
			pushLazy(bl);
			fore(i,l,r+1) res += value;
		}else{
			pushLazy(bl); pushLazy(br);
			fore(i,l,(bl+1) * s) res += A[i]; 
			fore(i,bl+1, br)     res += B[i];
			fore(i,br * s, r+1)  res += A[i];
		}
	}
};
//MO's algorithm
ll answer, neutro = 0; vll arr;
struct MOquery{
	int l, r, index, S;
	MOquery(int l, int r, int idx, int S): l(l), r(r), index(idx), S(S){}
	bool operator<(const MOquery & q) const{
		int bl = l / S, bq = q.l / S;
		if(bl == bq) return r < q.r;
		return bl < bq;
	}
};
void add(int idx){
	answer += arr[idx];
}
void remove(int idx){
	answer -= arr[idx];
}
vector<ll> MO(vector<MOquery> & queries){
	vector<ll> ans(queries.size());
	sort(queries.begin(), queries.end());
	ll current = 0;
	int prevL = 0, prevR = -1;
	int i, j;
	answer = neutro;
	for(const MOquery & q : queries){
		while (prevL > q.l) { prevL--; add(prevL); }
		while (prevR < q.r) { prevR++; add(prevR); }
		while (prevL < q.l) { remove(prevL); prevL++; }
		while (prevR > q.r) { remove(prevR); prevR--;}
		ans[q.index] = answer;
	}
	return ans;
}