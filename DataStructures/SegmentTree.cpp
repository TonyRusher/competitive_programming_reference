struct Node{
    int l=0, r=0;
    ll sum=0;
    int mark=0;
    ll lazy=Neutro;
};
//Neutros: (+, 0) (*, 1) (gcd, 0) (lcm, 1) (min, inf) (max, -inf)
const int Neutro = 0;
template<typename TT> struct SegmentTree{
	int n, h;
	vector<Node> st;
	
	SegmentTree	(int m,  vector<TT> &values) : n(m){
		// h = 1 << ((int)( ceil(log2(n)) + 1));
		// st.resize( h );
		st.resize(4*n + 5);
		for (auto &node : st) { node.mark = 0; node.lazy = 1; node.sum = 0; }
		build(1, 1, n, values);
	}
	TT merge(TT l, TT r){ return l + r; }//for query//!CHANGE 
	TT getValue(int curr){ return st[curr].sum; }//same^^
	
	int left(int n){ return (n << 1);}
	int right(int n){return (n << 1) | 1; }

	void initLeaf(int curr, TT value){//!CHANGE 
		st[curr].mark = 0; st[curr].lazy = Neutro;
		st[curr].sum = value;//
	}
	void updateFromChildren(int curr){//!CHANGE 
		st[curr].sum = st[left(curr)].sum + st[right(curr)].sum;
	}
	void updateNodeLazy(int curr, TT value){//updates lazy
		int l = st[curr].l, r = st[curr].r;
		st[curr].sum += (r - l + 1) * value;//!CHANGE 
		st[curr].mark = 1; st[curr].lazy += value;//
	}
	void propagateToChildren(int curr){//propagate lazy
		if(st[curr].mark == 0) return;
		updateNodeLazy(left(curr), st[curr].lazy );
		updateNodeLazy(right(curr), st[curr].lazy);
		st[curr].mark = 0; st[curr].lazy = Neutro; 
	}
	void build(int curr, int l, int r, vector<TT> &values){
		st[curr].l = l; st[curr].r = r;
		if(l == r) {
			initLeaf(curr, values[l]);//
		}else{
			int m = ((r - l) >> 1) + l;
			build(left(curr), l, m, values);
			build(right(curr), m + 1, r, values);
			updateFromChildren(curr);
		}
	}
	void rangeUpdate(int curr, int l, int r, int ql, int qr, TT value){
		if( r < ql || qr < l ) return;
		else if( ql <= l && r <= qr){
			updateNodeLazy(curr, value);
		}else{
			propagateToChildren(curr);
			int m = ((r - l) >> 1) +  l;
			rangeUpdate(left(curr), l, m, ql, qr, value);
			rangeUpdate(right(curr), m + 1, r, ql, qr, value);
			updateFromChildren(curr);
		}
	}
	// not lazy: //!Coment up or down
	void pointUpdate(int curr, int l, int r, int pos, TT value){
		if(l == r){
			st[curr].sum += value;
		}else{
			int m = ((r - l) >> 1) +  l;
			if(pos <= m) pointUpdate(left(curr), l, m, pos, value);
			else pointUpdate(right(curr), m + 1, r, pos, value);
			updateFromChildren(curr);
		}
	}
	TT rangeQuery(int curr, int l, int r, int ql, int qr){
		if( r < ql || qr < l ) return Neutro;
		else if( ql <= l && r <= qr){
			return getValue(curr);
		}else{
			propagateToChildren(curr);//!CHANGE 
			int m = ((r - l) >> 1) + l;
			return merge( rangeQuery(left(curr), l, m, ql, qr), rangeQuery(right(curr), m+1, r, ql, qr)) ;
		}
	}
	void update( int ql, int qr, int value){
		rangeUpdate(1, 1, n, ql, qr, value);
		// pointUpdate(1, 1, n, pos, value);//!CHANGE 
	}
	TT query(int ql, int qr){
		return rangeQuery(1, 1, n, ql, qr);
	}
	// void printST(){
	// 	cout << endl << "st = ";
	// 	fore(i,0,h) cout << st[i].sum << ' '; cout << endl;
	// }
};
// vector<TYPE> nums(n + 1); //1 indexed
// SegmentTree<TYPE> st(n,nums);// both must be same TYPE 
// st.update(l,r,x); st.query(l, r);

// SegmentTree<ll>* st = new SegmentTree<ll>(n, nums);
// st->update(l,r,x); st->query(l, r);