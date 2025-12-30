/**
 * Author: kingmessi
 * Date: 2024-12-21
 * License: CC0
 * Source: self
 * Description: slopeTrick
 * Time: O(N \log N)
 * Status: tested
 */
const int MAXN = 100005;
int Z = 1;int ls, rs, lv, zp;map<int, int> MP;
void fix_left(ll s) {
    if (ls >= s) return;
    auto it = MP.begin();
    while (ls + it->second <= s) {
        ls += it->second;
        lv += ls * (next(it)->first - it->first);
        MP.erase(it++);
    }
    it->second -= s - ls;ls = s;
}
void fix_right(ll s) {
    if (rs <= s) return;
    auto it = --MP.end();
    while (rs - it->second >= s) {
        rs -= it->second;
        MP.erase(it--);
    }
    it->second += s - rs;rs = s;
}
void advance() {
    ll lo = MP.begin()->first;
    if (zp < lo) lv += ls * (zp - lo);
    else lv += Z * (zp - lo);
    ls -= Z, rs += Z;
    MP[zp] += 2 * Z;
}