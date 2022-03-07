/*
    Language: C++20
    Submitted By: 
        Umesh Yadav 
        (github.com/umesh72614)
        (hackerrank.com/2018ucs0078)
    Score: 10/10
*/ 

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void dfs(vector<vector<int>> &adj, vector<bool> &vis, int i) {
    cout << i << "\n";
    vis[i] = true;
    for (auto &j: adj[i])
        if (!vis[j]) dfs(adj, vis, j);
}

int main() {
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    vector<int> indeg(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        indeg[y]++;
    }
    vector<bool> vis(n);
    for (int i = 0; i < n; i++)
        if (!indeg[i]) dfs(adj, vis, i);
}
