#include <bits/stdc++.h>

#define endl '\n'
#define ll long long 
#define lli long long int
#define ld long double
#define fore(i,a,b) for (int i = a; i < b; i++)
#define forr(i,a,b) for (int i = a; i > b; i--)
#define forn(i,n) for (int i = 0; i < n; i++)
#define fi first
#define se second
#define pb push_back
#define all(v) v.begin(), v.end()
#define fast_io ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);

using namespace std;

typedef pair<ll, ll>  pll;
typedef pair<int, int>  pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<vi> vvi;
typedef vector<pii> vpii;
typedef vector<pll> vpll;
typedef map<int, int> mii;

const int inf = 1<<30;


struct Node{
	int l, r, mark;
	ll sum, lazy;
	Node() {}
	Node(int l, int r):l(l), r(r){}
	Node operator+(const Node &ot){
		Node res(l, ot.r);
		res.sum = sum + ot.sum;
		return res;
	}
	void updateNodeLazy(ll value){
		sum += (r - l + 1) * value;//
		mark = 1; lazy += value;//
	}
	void resetLazy(){
		mark = 0; lazy = 0;
	}
};//0 +, 1 *, 0 gcd, 1 mcm
const int Neutro = 0;
template<typename TT> struct SegmentTree{
	int n, h;
	vector<Node> st;
	
	SegmentTree	(int m,  vector<TT> &values) : n(m){
		h = ((int)( ceil(log2(n)) + 1));
		st.resize( 1 << h );
		build(1, 1, n, values);
	}
	int left(int n){ return (n << 1);}
	int right(int n){return (n << 1) | 1;}
	
	void initLeaf(int curr, TT value){
		st[curr].mark = 0; st[curr].lazy = Neutro;
		st[curr].sum = value;//
	}
	void updateFromChildren(int curr){//
		st[curr].sum = st[left(curr)].sum + st[right(curr)].sum;
	}

	void propagate(int curr){//propagate lazy
		if(st[curr].mark != 0){
			st[left(curr)].updateNodeLazy(st[curr].lazy);
			st[right(curr)].updateNodeLazy(st[curr].lazy);
			st[curr].resetLazy();
		}
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
			propagate(curr);
			int m = ((r - l) >> 1) +  l;
			rangeUpdate(left(curr), l, m, ql, qr, value);
			rangeUpdate(right(curr), m + 1, r, ql, qr, value);
			updateFromChildren(curr);
		}
	}// not lazy 
	// void pointUpdate(int curr, int l, int r, int pos, TT value){
	// 	if(l == r){
	// 		st[curr].sum += value;
	// 	}else{
	// 		int m = ((r - l) >> 1) +  l;
	// 		if(pos <= m) pointUpdate(left(curr), l, m, pos, value);
	// 		else pointUpdate(right(curr), m + 1, r, pos, value);
	// 		updateFromChildren(curr);
	// 	}
	// }
	Node rangeQuery(int curr, int l, int r, int ql, int qr){
		if( r < ql || qr < l ) return Neutro;
		else if( ql <= l && r <= qr){
			return st[curr];
		}else{
			propagate(curr);
			int m = ((r - l) >> 1) + l;
			return rangeQuery(left(curr), l, m, ql, qr) + rangeQuery(right(curr), m+1, r, ql, qr);
		}
	}
	void update( int ql, int qr, int value){
		rangeUpdate(1, 1, n, ql, qr, value);
	}
	ll query(int ql, int qr){
		return rangeQuery(1, 1, n, ql, qr).sum;
	}
	// void printST(){
	// 	cout << endl << "st = ";
	// 	fore(i,0, 1 << h) cout << st[i].sum << ' '; cout << endl;
	// }
};
// vector<ll> nums(n + 1);
// SegmentTree<ll>* st = new SegmentTree<ll>(n, nums);
// st->update(l,r,x); st->query(l, r);



int main() {
	fast_io;
	
	
	
	return 0;
}