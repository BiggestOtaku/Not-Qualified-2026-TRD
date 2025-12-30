/**
 * Author: kingmessi
 * Date: 2024-12-23
 * License: CC0
 * Source: self
 * Description: implicit treap
 * Time: O(\log N) per operation
 * Status: tested
 */
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
using pt = struct tnode*;
pt root = NULL;
struct tnode {
    int pri, val; pt c[2]; // essential
    int sz; ll sum; // for range queries
    bool flip = 0; // lazy update
    tnode(int _val) {
        pri = rng(); sum = val = _val;
        sz = 1; c[0] = c[1] = nullptr;
    }
    ~tnode() { rep(i,0,2) delete c[i]; } /// assume no sharing of data
};
int getsz(pt x) { return x?x->sz:0; }
ll getsum(pt x) { return x?x->sum:0; }
void prop(pt x) { // lazy propagation
    if (!x || !x->flip) return;   
    swap(x->c[0],x->c[1]);
    x->flip = 0; rep(i,0,2) if (x->c[i]) x->c[i]->flip ^= 1;
}
pt calc(pt x) {
    pt a = x->c[0], b = x->c[1];
    // assert(!x->flip); 
    prop(a), prop(b);
    x->sz = 1+getsz(a)+getsz(b);
    x->sum = x->val+getsum(a)+getsum(b);
    return x;
}
void tour(pt x, vi& v) { // print values of nodes, 
    if (!x) return; // inorder traversal
    prop(x); tour(x->c[0],v); v.pb(x->val); tour(x->c[1],v);
}
pair<pt,pt> splitsz(pt t, int sz) { // sz nodes go to left used for implicit
    if (!t) return {t,t};
    prop(t);
    if (getsz(t->c[0]) >= sz) {
        auto p = splitsz(t->c[0],sz); t->c[0] = p.ss;
        return {p.ff,calc(t)};
    } else {
        auto p=splitsz(t->c[1],sz-getsz(t->c[0])-1); t->c[1]=p.ff;
        return {calc(t),p.ss};
    }
}
pt merge(pt l, pt r) { //  keys in l < keys in r
    if (!l || !r) return l?:r;
    prop(l), prop(r); pt t;
    if (l->pri > r->pri) l->c[1] = merge(l->c[1],r), t = l;
    else r->c[0] = merge(l,r->c[0]), t = r;
    return calc(t);
}
pt ins(pt x, int v,int idx) { // insert v at idx(0 based indexing)
    auto a = splitsz(x,idx);
    return merge(a.ff,merge(new tnode(v),a.ss)); }
pt del(pt x, int idx) { // delete v at idx(0 based indexing)
    auto a = splitsz(x,idx), b = splitsz(a.ss,1);
    return merge(a.ff,b.ss); }
int find_kidx(pt t,int idx){//idx is 1 based
    assert(getsz(t) >= idx);
    prop(t);
    if(getsz(t->c[0]) == idx-1)return t->val;
    else if(getsz(t->c[0]) < idx)return find_kidx(t->c[1],idx-getsz(t->c[0])-1);
    else return find_kidx(t->c[0],idx);
}
//root = ins(root,a[i],i)
//auto a = splitsz(root,l);auto b = splitsz(a.ss,r-l);ll ans = b.ff->sum;
//root = merge(a.ff,merge(b.ff,b.ss)); sum l to r