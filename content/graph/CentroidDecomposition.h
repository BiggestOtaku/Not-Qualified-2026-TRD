/**
 * Author: kingmessi
 * Date: 2024-12-21
 * License: CC0
 * Source: self
 * Description: CentoridDecomposition
 * Time: O(N \log N)
 * Status: tested
 */

const int MX = 2e5+1;
template<int SZ> struct Centroid {
    int N; vi adj[SZ]; void ae(int a, int b) { adj[a].pb(b), adj[b].pb(a); }
    bool done[SZ]; int sub[SZ], par[SZ];
    void dfs(int x) {
        sub[x] = 1;
        for(auto y : adj[x]) if (!done[y] && y != par[x]) {
            par[y] = x; dfs(y); sub[x] += sub[y]; }
    }
    int centroid(int x) {
        par[x] = -1; dfs(x); 
        for (int sz = sub[x];;) {
            pii mx = {0,0};
            for(auto y : adj[x]) if (!done[y] && y != par[x]) 
                mx=max(mx,{sub[y],y});
            if (mx.ff*2 <= sz) return x; 
            x = mx.ss;
        }
    }
    int cen[SZ], lev[SZ]; //cen[x] : par,lev[x] : depth
    vector<vi> dist; // dists[i][x] gives distance to ith ancestor in centroid tree
    void genDist(int x, int p, int lev) {
        dist[lev][x] = dist[lev][p]+1;
        for(auto y : adj[x]) if (!done[y] && y != p) genDist(y,x,lev); 
    } // CEN = {centroid above x, label of centroid subtree}
    void gen(int CEN, int x) {
        done[x = centroid(x)] = 1; cen[x] = CEN;  
        lev[x] = (CEN == -1 ? 0 : lev[CEN]+1);
        if (lev[x] >= dist.size()) dist.emplace_back(N+1,-1); 
        dist[lev[x]][x] = 0;
        for(auto y : adj[x]) if (!done[y]) genDist(y,x,lev[x]);
        for(auto y : adj[x]) if (!done[y]) gen(x,y);
    }
    void init(int _N) { N = _N; gen(-1,1); } // start with vertex 1
};Centroid<MX> ct;