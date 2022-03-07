/*
    Language: C++20
    Submitted By: 
        Umesh Yadav 
        (github.com/umesh72614)
        (hackerrank.com/2018ucs0078)
    Score: 20/20
*/ 

#include <vector>
#include <queue>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;

int m, n, sr, sc, er, ec;

vector<pair<int, int>> dir = {{1,0}, {0,-1}, {-1,0}, {0,1}};
vector<int> revDir = {2, 3, 0, 1};

int bfs(vector<vector<char>> &mat, int iDir) {
    vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    dist[sr][sc] = 0;
    pq.push({0, iDir, sr, sc});
    while (!pq.empty()) {
        auto v = pq.top(); pq.pop();
        auto dis = v[0], D = v[1], r = v[2], c = v[3];
        for (int d = 0; d < 4; d++) {
            if (d == revDir[D]) continue;
            auto &[dr, dc] = dir[d];
            auto nr = r + dr, nc = c + dc;
            if (nr >= 0 && nr < m && nc >= 0 && nc < n && mat[nr][nc] != '#') {
                auto nDis = (d != D) + dis;
                if (nDis < dist[nr][nc]) {
                    dist[nr][nc] = nDis;
                    pq.push({nDis, d, nr, nc});
                }
            }
        }
    }
    return dist[er][ec];
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    cin >> m >> n;
    vector<vector<char>> mat(m, vector<char>(n));
    for (int r = 0; r < m; r++)
        for (int c = 0; c < n; c++) {
            cin >> mat[r][c];
            if (mat[r][c] == 'S')
                sr = r, sc = c;
            else if (mat[r][c] == 'E')
                er = r, ec = c; 
        }
    int ans = INT_MAX;
    for (int d = 0; d < 4; d++)
        ans = min(ans, bfs(mat, d));
    if (ans == INT_MAX) cout << "IMPOSSIBLE";
    else cout << ans;
    return 0;
}
