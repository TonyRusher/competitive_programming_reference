vi tree[400000];
vi vv;
void build(int a[], int v, int tl, int tr) {
    if (tl == tr) {
        tree[v] = vi(1, a[tl]);
    } else { 
        int tm = (tl + tr) / 2;
        build(a, v*2, tl, tm);
        build(a, v*2+1, tm+1, tr);
        merge(tree[v*2].begin(), tree[v*2].end(), tree[v*2+1].begin(), tree[v*2+1].end(), back_inserter(tree[v]));
    }
}
void query(int v, int tl, int tr, int l, int r, int x){
    if(l > r) return;
    if(tr <= r){
		for(auto i = tree[v].begin(); i < tree[v].end(); i++){
			if(*i <= x) vv.pb(*i);
			else break;
		}
		return;
	}
	if(tl > r) return;
	int tm = (tl + tr) / 2;
	query(v*2, tl, tm, l, r, x), 
	query(v*2+1, tm+1, tr, l, r, x);
	return;
}