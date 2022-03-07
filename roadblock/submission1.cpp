/*
    Language: C++20
    Submitted By: 
        Umesh Yadav 
        (github.com/umesh72614)
        (hackerrank.com/2018ucs0078)
    Score: 11.25/30
*/ 

#include <vector>
#include <unordered_set>
#include <iostream>
#include <algorithm>
using namespace std;

#define LL long long
#define vl vector<LL>
#define vvl vector<vl>
#define us unordered_set
#define vus vector<us<LL>>
#define pll pair<LL, LL>
#define vll vector<pll>

LL n, m;
vus adj, revAdj;
vll edges;
vl E;

LL dfs(vl &M, vus &G, LL &t, LL j) {
    if (j == t) return M[j] = 1;
    if (M[j] >= 0) return M[j];
    LL a = 0;
    for (auto &k: G[j]) a += dfs(M, G, t, k);
    return M[j] = a;
}

bool roadBlock() {
    vl M(n, -1), rM(n, -1);
    LL s = 0, t = n - 1, j = -1;
    dfs(M, adj, t, s);
    if (M[s] <= 1) return false;
    dfs(rM, revAdj, s, t);
    if (rM[t] <= 1) return false;
    for (int i = 0; i < m; i++) {
        auto &[x, y] = edges[i];
        if (E[i] < 0) {
            adj[x].erase(y), revAdj[y].erase(x);
            continue;
        }
        if (rM[x] <= 0 or M[y] <= 0)
            E[i] = -1, adj[x].erase(y), revAdj[y].erase(x);
        else {
            E[i] = rM[x] * M[y];
            if (j < 0 or E[i] > E[j]) j = i;
        }
    }
    if (j >= 0) {
        if (E[j] == M[s]) return false;
        auto &[x, y] = edges[j];
        E[j] = -1, adj[x].erase(y), revAdj[y].erase(x);
    }
    return j >= 0;
}

int solve() {
    int ans = 0;
    while (roadBlock()) ans++;
    return ans;
}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    cin >> n >> m;
    adj.resize(n), revAdj.resize(n);
    E.resize(m);
    for (int i = 0; i < m; i++) {
        LL x, y;
        cin >> x >> y;
        adj[x].insert(y), revAdj[y].insert(x);
        edges.push_back({x, y});
    }
    cout << solve();
    return 0;
}
