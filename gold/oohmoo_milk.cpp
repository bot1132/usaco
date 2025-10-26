#include <bits/stdc++.h>
using namespace std;
#define int long long

const int mod = 1e9 + 7;

signed main() {    
    int n, d, a, b;
    cin >> n >> d >> a >> b;
    int milk[n];
    for (int i = 0; i < n; i++) {
        cin >> milk[i];
    }
    sort(milk, milk + n);
    if (b == 0) {
        for (int i = n-1; i >= n-a; i--) {
            milk[i] += d;
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans += milk[i] * milk[i];
            ans %= mod;
        }
        // cout << ans << endl;
        return 0;
    }
    int left = n - b, right = n - b;
    while (left-1 >= n-a && milk[left-1] == milk[n-b]) left--;
    while (right+1 < n && milk[right+1] == milk[n-b]) right++;
    int overlap = n-b-left;
    int mn = milk[n-b];
    int cnt = 0;
    int bordersum = mn * (right - left + 1);
    // cout << left << " " << right << " " << overlap << endl;
    int time = 0;
    while (true) {
        int sz = right - left + 1;
        int t1 = 1e9, t2 = 1e9;
        // cerr << bordersum << " " << sz << " " << milk[left-1] << " " << overlap << endl;
        if (left-1 >= n-a) t1 = ceil(1.0 * (bordersum - sz * (milk[left-1] + time) - sz + 1) / (sz - overlap));
        if (right+1 < n && overlap != 0) t2 = ceil(1.0 * (sz * milk[right+1] - bordersum) / overlap);
        // cerr << t1 << " " << t2 << endl;
        if (t1 < t2) {
            if (time + t1 > d) {
                t1 = d - time;
                bordersum += t1 * overlap;
                mn = bordersum / sz;
                cnt = bordersum - sz * mn;
                break;
            }
            else time += t1;
            bordersum += t1 * overlap;
            mn = bordersum / sz;
            cnt = bordersum - sz * mn;
            while (left > 0 && milk[left-1] + time == mn) {
                left--;
                overlap++;
                bordersum += mn;
            }   
            // cerr << bordersum << " " << mn << " " << cnt << endl;
        } 
        else {
            if (time + t2 > d) {
                // cout << t2 << endl;
                t2 = d - time;
                bordersum += t2 * overlap;
                mn = bordersum / sz;
                cnt = bordersum - sz * mn;
                break;
            } 
            else time += t2;
            bordersum += t2 * overlap;
            mn = bordersum / sz;
            cnt = bordersum - sz * mn;
            while (right < n-1 && milk[right+1] == mn) {
                right++;
                bordersum += mn;
            }
            // cerr << bordersum << " " << mn << " " << cnt << endl;
        }
    }


    // for (int t = 1; t <= d; t++) {
    //     int sz = right - left + 1;
    //     if (overlap >= sz - cnt) {
    //         mn++;
    //         cnt = overlap - sz + cnt;
    //     }
    //     else {
    //         cnt += overlap;
    //     }
    //     while (left > 0 && milk[left-1] + t == mn) {
    //         left--;
    //         overlap++;
    //         // cout << "left " << t << endl; 
    //     }
    //     while (right < n-1 && milk[right+1] == mn) {
    //         right++;
    //         // cout << "right " << t << endl; 
    //     }
    //     // cerr << cnt << " " << overlap << endl;
    // }
    // for (int i = 0; i < n; i++) {
    //     cerr << milk[i] << " ";
    // }
    // cerr << endl;
    int ans = 0;
    for (int i = n-1; i >= n-a; i--) {
        if (i < left) {
            ans += (milk[i] + d) * (milk[i] + d);
            // cerr << milk[i] + d << endl;
        }
        else if (i > right) {
            ans += milk[i] * milk[i];
        }
        ans %= mod;
    }
    for (int i = 0; i < n-a; i++) {
        ans += (milk[i] * milk[i]);
        // cerr << milk[i] << endl;
        ans %= mod;
    }
    for (int i = 0; i < right - left + 1 - cnt; i++) {
        ans += mn * mn;
        // cerr << mn << endl;
        ans %= mod;
    }
    for (int i = 0; i < cnt; i++) {
        ans += (mn+1) * (mn+1);
        // cerr << mn+1 << endl;
        ans %= mod;
    }
    cout << ans << endl;
}
