/**
 * Author: kingmessi
 * Date: 2024-12-21
 * License: CC0
 * Source: self
 * Description: complementary graph connected comp
 * Time: O(N \log N)
 * Status: tested
 */

set<int> adj[N];set<int> unused;
void dfs(int current){
    unused.erase(current);if(unused.size()==0)return;
    auto it = unused.begin();    
    while(it != unused.end()){
        int W = *(it);
        if(!adj[current].count(W)){
            union_sets(current,W);dfs(W);
        }if(unused.size()==0)return;
        it = unused.upper_bound(W);
    }
}
//Usage:
repin make_set(i),unused.insert(i);
repin if(unused.count(i))dfs(i);