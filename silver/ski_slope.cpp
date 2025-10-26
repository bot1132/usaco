#include <bits/stdc++.h>
using namespace std;
#define int long long

int n;
vector <int> adj[100001];
int d[100001], e[100001];
int enjoy[100001];
multiset <int> maxvals[100001];

void dfs(int node) {
    for (auto nex : adj[node]) {
        enjoy[nex] = enjoy[node] + e[nex];
        maxvals[nex] = maxvals[node];
        maxvals[nex].insert(d[nex]);
        maxvals[nex].erase(maxvals[nex].begin());
        dfs(nex);
    }
}

signed main() {
    cin >> n;
    for (int i = 2; i <= n; i++) {
        int p, dd, ee;
        cin >> p >> dd >> ee;
        adj[p].push_back(i);
        d[i] = dd;
        e[i] = ee;
    }
    for (int i = 0; i < 11; i++) {
        maxvals[1].insert(0);
    }
    dfs(1);
    int m;
    cin >> m;
    vector <pair <int, int>> queries[11];
    int ord = 0;
    while (m--) {
        ord++;
        int s, c;
        cin >> s >> c;
        queries[c].push_back({s, ord});
    }
    for (int i = 0; i < 11; i++) {
        sort(queries[i].begin(), queries[i].end());
    }
    // for (int i = 1; i <= n; i++) {
    //     cout << "Node " << i << ": ";
    //     for (auto val : maxvals[i]) {
    //         cout << val << " ";
    //     }
    //     cout << endl;
    // // }
    // cout << *prev(prev(maxvals[3].rbegin())) << endl;
    vector <pair <int, int>> ans;
    for (int i = 0; i < 11; i++) {
        vector <pair <int, pair <int, int>>> v;
        for (int j = 1; j <= n; j++) {
            auto it = maxvals[j].rbegin();
            for (int k = 0; k < i; k++) {
                it = next(it);
            }
            v.push_back({*it, {j, 0}});
        }        
        sort(v.begin(), v.end());
        for (int j = 0; j < v.size(); j++) {
            v[j].second.second = (j == 0 ? enjoy[v[j].second.first] : max(enjoy[v[j].second.first], v[j-1].second.second));
        }
        // for (auto x : v) {
        //     cout << x.first << " " << x.second.first << " " << x.second.second << endl;
        // }
    
        for (auto val : queries[i]) {
            auto yes = *prev(upper_bound(v.begin(), v.end(), make_pair(val.first+1, make_pair(0*1LL, 0*1LL))));
            int anss = yes.second.second;
            ans.push_back({val.second, anss});
        }
    }
    sort(ans.begin(), ans.end());
    for (auto x : ans) {
        cout << x.second << endl;
    }
}

// sort the maximum values
// for each node, we have a list of 11 of the largest values from its path to the root
