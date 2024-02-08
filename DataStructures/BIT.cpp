struct Fenwick {
    int n;
    vector<long long> tree;

    Fenwick(int _n) : n(_n), tree(n + 1, 0) {}

    void update(int idx, long long val) {
        for (; idx <= n; idx += idx & -idx) {
            tree[idx] += val;
        }
    }

    long long query(int idx) {
        long long ret = 0;
        for (; idx > 0; idx -= idx & -idx) {
            ret += tree[idx];
        }
        return ret;
    }

    long long query(int x, int y) { return query(y) - query(x - 1); }
};