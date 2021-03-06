#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef long long ll;
typedef long double lld;
typedef long long int lli;
using namespace std;
const int N = 1005;
const int MOD=1e9+7;
const bool DEBUG = 1;
#define sd(x) scanf("%d", &x)
#define sd2(x, y) scanf("%d%d", &x, &y)
#define sd3(x, y, z) scanf("%d%d%d", &x, &y, &z)
#define endl "\n"
#define fi first
#define se second
#define eb emplace_back
#define fbo find_by_order
#define ook order_of_key
#define pb(x) push_back(x)
#define mp(x, y) make_pair(x, y)
#define LET(x, a) __typeof(a) x(a)
#define foreach(it, v) for (LET(it, v.begin()); it != v.end(); it++)
#define MEMS(a, b) memset(a, b, sizeof(a))
#define _			\
    ios_base::sync_with_stdio(false);			\
    cin.tie(NULL);			\
    cout.tie(NULL);
#define __ 			\
    freopen("input.txt", "r", stdin);			\
    freopen("output.txt", "w", stdout);
#define all(c) c.begin(), c.end()
#define inf 1000000000000000001
#define epsilon 1e-6
#define int ll
#define RUN_T			 \
    int _t; 			 \
    cin >> _t;			 \
    while (_t--)			 
#define tr(...)				\
if (DEBUG) {				\
cout << __FUNCTION__ << ' ' << __LINE__ << " = ";				\
trace(#__VA_ARGS__, __VA_ARGS__);				\
}
template <typename S, typename T>
ostream &operator<<(ostream &out, pair<S, T> const &p) {
    out << '(' << p.fi << ", " << p.se << ')';
    return out;
}
template <typename T>
ostream &operator<<(ostream &out, set<T> const &v) {
    for (auto i = v.begin(); i != v.end(); i++)
        out << (*i) << ' ';
    return out;
}
template <typename T, typename V>
ostream &operator<<(ostream &out, map<T, V> const &v) {
    for (auto i = v.begin(); i != v.end(); i++)
        out << "\n" << (i->first) <<  ":"  << (i->second);
    return out;
}
template <typename T, typename V>
ostream &operator<<(ostream &out, unordered_map<T, V> const &v) {
    for (auto i = v.begin(); i != v.end(); i++)
        out << "\n" << (i->first) <<  ":"  << (i->second);
    return out;
}
template <typename T>
ostream &operator<<(ostream &out, multiset<T> const &v) {
    for (auto i = v.begin(); i != v.end(); i++)
        out << (*i) << ' ';
    return out;
}
template <typename T>
ostream &operator<<(ostream &out, unordered_set<T> const &v) {
    for (auto i = v.begin(); i != v.end(); i++)
        out << (*i) << ' ';
    return out;
}
template <typename T>
ostream &operator<<(ostream &out, unordered_multiset<T> const &v) {
    for (auto i = v.begin(); i != v.end(); i++)
        out << (*i) << ' ';
    return out;
}
template <typename T> ostream &operator<<(ostream &out, vector<T> const &v) {
    ll l = v.size();
    for (ll i = 0; i < l - 1; i++)
        out << v[i] << ' ';
    if (l > 0)
        out << v[l - 1];
    return out;
}
template <typename T> void trace(const char *name, T &&arg1) {
    cout << name <<  ":"  << arg1 << endl;
}
template <typename T, typename... Args>
void trace(const char *names, T &&arg1, Args &&... args) {
    const char *comma = strchr(names + 1, ',');
    cout.write(names, comma - names) <<  ":"  << arg1 <<  "|" ;
    trace(comma + 1, args...);
}
template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
const int LG = 20;
int gcd(int a, int b) {
     if (b == 0)
        return a;
    return gcd(b, a % b);
}
vector<vector<int>>par(N, vector<int>(LG,0));
vector<int>lvl(N, 0);
map<int,vector<int>>g;

void dfs(int u, int p){
    lvl[u] = 1 + lvl[p];
    par[u][0] = p;
    for(int v: g[u]){
        if(v == p) continue;
        dfs(v ,u);
    }
}

int lca(int u,int v){
    
    if(lvl[u] < lvl[v]) swap(u, v);
    
    int lg;
    
    for(lg = 0; (1 << lg) <= lvl[u]; lg++);
    lg--;
    
    for(int i = lg; i >= 0; i--){
        if(lvl[u] - (1<<i) >= lvl[v]){
            u = par[u][i]; 
        }
    }

    if( u == v) return u;
    
    for(int i = lg; i >= 0; i--){
        if(par[u][i]!=-1 and par[u][i] != par[v][i]){
            u = par[u][i];
            v = par[v][i];
        }
    }
    return par[u][0];
}
int32_t main() {
    _
    int r = 1;
    RUN_T{
        int n, x, y, m, u, v;
        cin >> n;
        int root = 1;
        int flag = 0;
        for(int i = 1; i <= n; i++ ){
            lvl[i] = 0;
        }
        g.clear();
        for(int i = 1; i <= n ;i++){
            cin >> m;
            for(int j = 0; j < m ;j++){
                cin >> x;
                if(!flag){
                    root = i;
                    flag = 1;
                }
                g[i].pb(x);
                g[x].pb(i);
            } 
        }
        for(int i = 0 ;i <= n; i++){
            for(int j = 0; j <= LG; j++){
                par[i][j] = -1;
            }
        }
        lvl[0] = -1;
        dfs(root,0);
        // tr("yo");
        for(int i = 1; i <= LG ;i++){
            for(int j = 1; j <= n; j++){
                if(par[j][i - 1] != -1){
                    par[j][i] = par[par[j][i-1]][i-1];
                } 
            }
        }
        // tr("bro");
        int q;
        cin >> q;
        cout<< "Case "<<r<<":"<<endl;
        for(int i = 0; i < q; i++){
            cin >> u >> v;
            int ans = lca( u ,v);
            cout << ans << endl;
        }
        r++;
    }
}