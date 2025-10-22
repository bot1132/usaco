#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, q;
    cin >> n >> q;
    int a[n+1];
    map <int, set <int>> vote; // vote[i] is the set of all cows who have exactly i votes
    int pre[n+1], suf[n+1]; // pre[i] is the first cow from the left that has >= i votes
    int maxvotes = 0;
    int cows[n+1]; // cows[i] is the number of votes cow i gets
    memset(cows, 0, sizeof(cows));
    memset(pre, 0, sizeof(pre));
    memset(suf, 0, sizeof(suf));
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        cows[a[i]]++;
    }
    for (int i = 1; i <= n; i++) {
        vote[cows[i]].insert(i);
        maxvotes = max(maxvotes, cows[i]);
    }
    pre[0] = 1;
    int cur = 0;
    for (int i = 1; i <= n; i++) {
        if (cows[i] > cur) {
            for (int j = cur + 1; j <= cows[i]; j++) {
                pre[j] = i;
            }
            cur = cows[i];
        }
    }
    suf[0] = n;
    cur = 0;
    for (int i = n; i >= 1; i--) {
        if (cows[i] > cur) {
            for (int j = cur + 1; j <= cows[i]; j++) {
                suf[j] = i;
            }
            cur = cows[i];
        }
    }
    while (q--) {
        int i, x;
        cin >> i >> x;
        // a[i] is the cow originally being voted for
        // x is the new cow being voted for
        cows[a[i]]--;
        cows[x]++;
        if (pre[cows[x]] == 0) pre[cows[x]] = x;
        else pre[cows[x]] = min(pre[cows[x]], x);
        if (suf[cows[x]] == 0) suf[cows[x]] = x;
        else suf[cows[x]] = max(suf[cows[x]], x);
        if (pre[cows[a[i]]+1] == a[i]) {
            pre[cows[a[i]]+1] = pre[cows[a[i]]+2];
            if (next(vote[cows[a[i]]+1].lower_bound(a[i])) != vote[cows[a[i]]+1].end()) {
                pre[cows[a[i]]+1] = min(pre[cows[a[i]]+1], *next(vote[cows[a[i]]+1].lower_bound(a[i])));
            }
        }
        if (suf[cows[a[i]]+1] == a[i]) {
            suf[cows[a[i]]+1] = suf[cows[a[i]]+2];
            if (vote[cows[a[i]]+1].lower_bound(a[i]) != vote[cows[a[i]]+1].begin()) {
                suf[cows[a[i]]+1] = max(suf[cows[a[i]]+1], *prev(vote[cows[a[i]]+1].lower_bound(a[i])));
            }
        }
        vote[cows[a[i]]+1].erase(a[i]);
        if (vote[cows[a[i]]+1].empty()) {
            vote.erase(cows[a[i]]+1);
        }
        vote[cows[a[i]]].insert(a[i]);
        vote[cows[x]-1].erase(x);
        if (vote[cows[x]-1].empty()) {
            vote.erase(cows[x]-1);
        }
        vote[cows[x]].insert(x);
        a[i] = x;
        int ans = 0, t = 0;
        maxvotes = vote.rbegin()->first;
        for (auto it = vote.begin(); it != vote.end(); it++) {
            int need = maxvotes - it->first;
            if (need == 0 || it->first == 0) continue;
            int lpos = pre[need], rpos = suf[need];
            set <int> &pos = it->second;
            if (pos.size() == 0) continue;
            int lmax = max(abs(lpos - *pos.begin()), abs(lpos - *pos.rbegin()));
            int rmax = max(abs(rpos - *pos.begin()), abs(rpos - *pos.rbegin()));
            if (lpos != 0) ans = max(ans, lmax);
            if (rpos != 0) ans = max(ans, rmax);
        }
        cout << ans << endl;
    }
}
