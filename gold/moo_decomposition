#include <bits/stdc++.h>
using namespace std;
#define int long long

int MOD = 1e9 + 7;
int fact[1000001], invfact[1000001];

int k, n, l;
string t;

int modexp(int base, int exp, int mod) {
    int res = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            res = (res * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    res %= mod;
    return res;
}

void computefactorials() {
    fact[0] = 1;
    for (int i = 1; i <= 1000000; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
    }
}

void computeinverses() {
    for (int i = 0; i <= 1000000; i++) {
        invfact[i] = modexp(fact[i], MOD - 2, MOD);
    }
}

signed main() {
    cin >> k >> n >> l;
    cin >> t;
    int ocnt = 0;
    int ans = 1;
    computefactorials();
    computeinverses();
    for (int i = n - 1; i >= 0; i--) {
        if (t[i] == 'M') {
            // we want ocnt choose k
            ans *= (fact[ocnt] * invfact[k] % MOD * invfact[ocnt - k] % MOD) % MOD;
            ocnt -= k;
        }
        else {
            ocnt++;
        }
        ans %= MOD;
    }
    cout << modexp(ans, l, MOD) << endl;
}
