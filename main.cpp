#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
#define all(X) X.begin(),X.end()
#define allr(X) X.rbegin(),X.rend()
#define vi vector<ll>
#define YES {cout << "YES\n"; return;}
#define NO {cout << "NO\n"; return;}
#define EPS 1e-15
#define nl '\n'
#define pow2(k) (1ll << (k))
const ll inf = 1e18, N = 4e4 + 5, MOD = 1e9+7,RED = 1,BLUE = 2,NONE = 0;
const int dx[4] = { 1, 0, 0, -1 } ,
dy[4] = { 0, -1, 1, 0 };
char dir[4] = {'D','L','R','U'};
#define Ali_Was_Here ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);;
#define INF 1e9
void Ali() {
    ll n,k;cin>>n>>k;
    vi v(n),twos(202),fives(202);
    for (int i = 0 ; i < n;i++)
        cin>>v[i];
    for (int i = 0 ; i < n;i++) {
        while (v[i] % 2 == 0) {
            twos[i]++;
            v[i] /= 2;
        }
        while (v[i] % 5 == 0) {
            fives[i]++;
            v[i] /= 5;
        }
    }
    ll tot = accumulate(all(fives),0);
    vector<vi> dp_prev(k+1, vi(tot+1, -1e9));
    vector<vi> dp_cur(k+1, vi(tot+1, -1e9));

    dp_prev[0][0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= k; j++) fill(dp_cur[j].begin(), dp_cur[j].end(), -1e9);
        for (int j = 0; j <= k; j++) {
            for (int f = 0; f <= tot; f++) {
                if (dp_prev[j][f] < 0) continue;
                dp_cur[j][f] = max(dp_cur[j][f], dp_prev[j][f]);
                if (j + 1 <= k && f + fives[i] <= tot) {
                    dp_cur[j+1][f + fives[i]] = max(dp_cur[j+1][f + fives[i]], dp_prev[j][f] + twos[i]);
                }
            }
        }
        swap(dp_prev, dp_cur);
    }

    ll res = 0;
    for (ll f = 0; f <= tot; f++) {
        if (dp_prev[k][f] >= 0)
            res = max(res, min(f, dp_prev[k][f]));
    }
    cout<<res<<nl;
}


int main() {
    Ali_Was_Here;
    //freopen("cardgame.in", "r", stdin);
    //freopen("cardgame.out", "w", stdout);
    // cout<<fixed<<setprecision(7);
    int tc = 1;
    //cin >> tc;
    for (int i = 1; i <= tc; i++)Ali();
}
