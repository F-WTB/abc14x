#include <bits/stdc++.h>
#include <atcoder/all>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using namespace atcoder;
using ll = long long;
using bint = boost::multiprecision::cpp_int;
using mint = modint998244353;
using pr = pair<int, int>;
ostream &operator<<(ostream &os, const mint &x) {
    os << x.val();
    return os;
}
template <class T>
inline bool chmin(T &a, T b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}
template <class T>
inline bool chmax(T &a, T b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}
struct fast {
    fast() {
        cin.tie(0);
        ios::sync_with_stdio(0);
    }
} fast;

const int M = 100000;
int N;
ll A[M];
bool red[M];

int main() {
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> A[i];
    vector<bitset<M + 1>> v;
    for (int x = 60 - 1; x >= 0; --x) {
        bitset<M + 1> b;
        for (int i = 0; i < N; ++i)
            if (A[i] & 1ll << x) b.set(i, 1);
        if (b.count() & 1) continue;
        b.set(M, 1);
        v.push_back(b);
    }
    int K = v.size();
    bitset<M + 1> par;
    for (int i = 0; i < N; ++i) par.set(i, 1);

    for (int x = 0; x < K; ++x) {
        bool flag = 0;
        int idx;
        for (int i = 0; i < N; ++i)
            if (v[x].test(i)) {
                flag = 1;
                idx = i;
                break;
            }
        if (!flag) continue;
        for (int y = 0; y < K; ++y) {
            if (y == x) continue;
            if (v[y].test(idx)) v[y] ^= v[x];
        }
        par.set(idx, 0);
    }
    for (int x = 0; x < K; ++x) {
        bitset<M + 1> b = v[x] & ~par;
        for (int i = 0; i < N; ++i)
            if (b.test(i)) red[i] = v[x].test(M);
    }

    ll a = 0, b = 0;
    for (int i = 0; i < N; ++i) (red[i] ? a : b) ^= A[i];
    cout << a + b << '\n';
}
