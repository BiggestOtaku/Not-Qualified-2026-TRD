/**
 * Author: piyush_pransukhka
 * Date: 2024-04-09
 * License: CC0
 * Source: self
 * Description: Articulation points and bridges
 * Time: O(N + M)
 * Status: tested
 */
int n, timer;
vector<vector<int>> adj;
vector<bool> vis;vector<int> tin, low;
void dfs(int v, int p = -1) { // Bridges
    vis[v] = true, tin[v] = low[v] = timer++;
    int chs = 0;
    for (int to : adj[v]) {
        if (to == p) continue;
        if (vis[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] > tin[v])IS_BRIDGE(v, to);
            if (low[to] >= tin[v] && p!=-1)IS_CUTPOINT(v);
            ++chs;
        }
    }
    if(p == -1 && chs > 1) IS_CUTPOINT(v);
}
void find_bridges_or_cutpoints() {
    timer = 0, vis = vector(n, false);
    tin = low = vector(n, -1);
    for (int i = 0; i < n; ++i)if(!vis[i])dfs(i);
}
