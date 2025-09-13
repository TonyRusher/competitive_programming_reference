vector<bool> visited; // keeps track of which vertices are already visited

void dfs_scc(int v, vvi const& graph, vector<int> &output) {
    visited[v] = true;
    for (auto u : graph[v])
        if (!visited[u])
            dfs_scc(u, graph, output);
    output.push_back(v); // stores the exit time
}

// input: graph -- adjacency list of G
// output: components -- the strongy connected components in G
// output: graph_con -- adjacency list of G^SCC (by root vertices)
void SCC(vvi const& graph, vvi &components, vvi &graph_con) {
    int n = graph.size();
    components.clear(), graph_con.clear();
    vector<int> order; // will be a sorted list of G's vertices by exit time
    visited.assign(n, false);
	// first series of depth first searches
    for (int i = 0; i < n; i++)
        if (!visited[i]) dfs_scc(i, graph, order);
 	
	// create graphacency list of G^T
    vvi graph_rev(n);
    for (int v = 0; v < n; v++)
        for (int u : graph[v])
            graph_rev[u].push_back(v);

    visited.assign(n, false);
    reverse(order.begin(), order.end());

    vector<int> roots(n, 0); // gives the root vertex of a vertex's SCC

    // second series of depth first searches
    for (auto v : order)
        if (!visited[v]) {
            std::vector<int> component;
            dfs_scc(v, graph_rev, component);
            components.push_back(component);
            int root = *min_element(begin(component), end(component));
            for (auto u : component)
                roots[u] = root;
        }

    // add edges to condensation graph
    graph_con.assign(n, {});
    for (int v = 0; v < n; v++)
        for (auto u : graph[v])
            if (roots[v] != roots[u])
                graph_con[roots[v]].push_back(roots[u]);
}