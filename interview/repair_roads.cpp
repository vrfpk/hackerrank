#include<iostream>
#include<vector>
#include<stdio.h>
#include<set>
#include<string.h>
#include<stdlib.h>

using namespace std ;
#define INF (int)1e9
#define MAXN 10002

static vector<int> G[MAXN];
static int n;
static int parent[MAXN];

void dfs(int k, int p)
{
    parent[k] = p;
    for(int i = 0; i < G[k].size(); i++) if(G[k][i] != p)
        dfs(G[k][i],k) ;
}

static int u[MAXN], v[MAXN], f[MAXN], nleaf[MAXN];

int solve()
{
    memset(u, 0, sizeof(u));
    memset(v, 0, sizeof(v));
    memset(nleaf, 0, sizeof(nleaf));
    memset(parent, 255, sizeof(parent));

    dfs(0, -1);
    
    for (int i = 1; i < n; i++) nleaf[parent[i]]++;

    int nodes = n, ret = 0;
    for (int i = 1; i < n; i++) if (nleaf[i] == 0 && u[i] == 0) {
        nleaf[parent[i]]--;
        u[parent[i]] = 1;
        parent[i] = -1;
        nodes--;
    }
    if (nodes == 1) return 1;
    
    while (nodes > 1) {
        ret++;
        memset(f, 255, sizeof(f));
        char mark[MAXN] = {};
        for (int i = 1; i < n; i++) if (parent[i] != -1) if (nleaf[i] > 1)
            mark[i] = 1;
        int a = -1, b = -1, c = -1;
        for (int i = 1; i < n; i++) if (parent[i] != -1) if (nleaf[i] == 0) {
            int j = i;
            while(j > 0 && !mark[j]) j = parent[j];
            if(f[j] == -1) f[j] = i;
            else {
                a = f[j];
                b = i;
                c = j;
                break;
            }
        }
        if (a == -1 || b == -1) break;
        while (a != c) { int t = parent[a]; parent[a] = -1; nleaf[t]--; nodes--; a = t; }
        while (b != c) { int t = parent[b]; parent[b] = -1; nleaf[t]--; nodes--; b = t; }
        u[c] = 0;
        for (int i = 1; i < n; i++) if (parent[i] == c) v[i] = 1;
        v[c] = 1;
        if (nodes == 1) break;
        if (c > 0 && nleaf[c] == 0) { int t = parent[c]; parent[c] = -1; nleaf[t]--; nodes--; c = t; }
        while (c > 0 && nleaf[c] == 0 && !u[c]) {
            if (v[c]) { int t = parent[c]; parent[c] = -1; nleaf[t]--; nodes--; c = t; }
            else { int t = parent[c]; parent[c] = -1; u[t] = 1; nleaf[t]--; nodes--; c = t; }
        }
        if (nodes == 1 && c == 0 && u[c]) ret++;
    }
    return ret;
}

int test_repair_roads()
{
    freopen("repair_roads.txt", "r", stdin);
    int runs;
    scanf("%d", &runs);
    while (runs--) {
        scanf("%d", &n);
        for (int i = 0; i < MAXN; i++) G[i].clear();
        for (int i = 1;i < n;i++) {
            int a, b;
            scanf("%d%d", &a, &b);
            G[a].push_back(b);
            G[b].push_back(a);
        }
        int ret = solve();
        printf("%d\n", ret);
    }
    return 0;
}