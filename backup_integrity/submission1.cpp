/*
    Language: C++20
    Submitted By: 
        Umesh Yadav 
        (github.com/umesh72614)
        (hackerrank.com/2018ucs0078)
    Score: 20/20
*/ 

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Node {
public:
    string val;
    vector<Node*> children;
    int sz;
    Node (string v) {val = v, sz = 0;}
    Node (string v, vector<Node*> c) {val = v, children = c, sz = 0;}
};

vector<string> genPath(string &s) {
    vector<string> path;
    int i = -1, n = s.size();
    while (++i < n) {
        string dir;
        while (i < n and s[i] != '/')
            dir.push_back(s[i++]);
        path.push_back(dir);
    }
    return path;
}

void insertNode(Node *root, vector<string> &path, int i=0) {
    if (i >= (int) size(path)) return;
    for (auto &child: root->children)
        if (child->val == path[i])
            return insertNode(child, path, i + 1);
    root->children.push_back(new Node(path[i]));
    return insertNode(root->children.back(), path, i + 1);
}

void genTree(Node *root, vector<vector<string>> &paths) {
    for (auto &path: paths)
        insertNode(root, path);
}

int setSz(Node *r) {
    int sz = 1;
    for (auto &nd: r->children)
        sz += setSz(nd);
    return r->sz = sz;
}

void compSz(Node *r, vector<vector<int>> &sz, int l=0) {
    sz[l].push_back(r->sz);
    for (auto &nd: r->children)
        compSz(nd, sz, l + 1);
}

int getHt(Node *R) {
    int ca = 0;
    for (auto &nd: R->children)
        ca = max(ca, getHt(nd));
    return ca + 1;
}

bool comp(Node *r1, Node *r2) {
    int l1 = getHt(r1), l2 = getHt(r2);
    if (l1 != l2) return false;
    vector<vector<int>> sz1(l1 + 1), sz2(l2 + 1);
    setSz(r1), setSz(r2);
    compSz(r1, sz1), compSz(r2, sz2);
    for (int l = 0; l <= l1; l++) {
        sort(begin(sz1[l]), end(sz1[l]));
        sort(begin(sz2[l]), end(sz2[l]));
        if (sz1[l] != sz2[l])
            return false;
    }
    return true;
}

int main() {
    Node *root1 = new Node("/"), *root2 = new Node("/");
    for (int i = 0; i < 2; i++) {
        int n;
        cin >> n;
        vector<vector<string>> paths;
        string s;
        // input has '\n' at first line which cin >> n ignored so we need to eat it first
        getline(cin, s);
        while (n--) {
            getline(cin, s);
            auto path = genPath(s);
            if (path.size()) 
                paths.push_back(path);
        }
        if (i == 0) genTree(root1, paths);
        if (i == 1) genTree(root2, paths);
    }
    if (comp(root1, root2)) cout << "OK\n";
    else cout << "INVALID\n";
}
