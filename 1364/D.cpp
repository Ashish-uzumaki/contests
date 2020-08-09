#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef long long ll;
typedef long double lld;
typedef long long int lli;
using namespace std;
const int N = 1000001;
const int MOD = 1e9+7;
const bool DEBUG = 1;
#define sd(x) scanf("%d ", &x)
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
#define __			\
    freopen("input.txt", "r", stdin);			\
    freopen("output.txt", "w", stdout);
#define all(c) c.begin(), c.end()
#define inf 1000000000000000001
#define epsilon 1e-6
#define int ll
#define RUN_T			\
    int _t;			\
    cin >> _t;			\
    while (_t--)
#define tr(...)			\
if (DEBUG) {			\
    cout << __FUNCTION__ << ' ' << __LINE__ << " = ";			\
    trace(#__VA_ARGS__, __VA_ARGS__);			\
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
int gcd(int a, int b) {
     if (b == 0)
           return a;
     return gcd(b, a % b);
}
vector<vector<int>>g;
vector<int>v,col,par,mark;
int num , flag ,cyclenum;
void dfs(int root, int p){
    if(col[root] == 2) return; 
    if (col[root] == 1) { 
        cyclenum++; 
        int cur = p; 
        mark[cur] = cyclenum;  
        while (cur != root) { 
            cur = par[cur]; 
            mark[cur] = cyclenum; 
        } 
        return; 
    }
    par[root] = p;
    col[root] = 1;
    for(auto t: g[root]){
        if(t == par[root]) continue;
        dfs(t, root);
    }
    col[root] = 2;
}
vector<int>col2;
vector<int>cycles[N];
void dfs2(int root, int pr){
    col2[root] = col2[pr] ^ 1;
    for(auto p: g[root]){
        if( p == pr) continue;
        dfs2(p, root);
    }
}
vector<int> printCycles(int m, int k) { 
    for (int i = 1; i <= m; i++) { 
        if (mark[i] != 0) 
            cycles[mark[i]].push_back(i); 
    }
    for(int i = 1; i <= cyclenum; i++) { 
        if(cycles[i].size() <= k and cycles[i].size() >= 3){
            return cycles[i]; 
        }
    } 
    for(int i = 1; i <= cyclenum; i++) {
        if(cycles[i].size() >= 3){
            return cycles[i]; 
        } 
    } 
    return cycles[1];
} 
int32_t main(){
    int n, m ,k ,x, y;
    cin >> n >> m >> k;
    g.clear();
    par.clear();
    mark.clear();
    g.resize(n + 1);
    par.resize(n + 1, 0);
    mark.resize(n + 1, 0);
    col.resize(n + 1, 0);
    for(int i = 1 ; i <= m; i++){
        cin >> x >> y;
        g[x].pb(y);
        g[y].pb(x);
    }
    for(int i = 1; i <= n; i++){
        if(col[i] == 0){
            dfs(i, 0);
        }
    }
    // tr(cyclenum);
    if(cyclenum > 0){
        vector<int> ans = printCycles(m, k);
        if(ans.size() <= k){
            cout << 2 << endl;
            cout << ans.size() << endl;
            for(int i = 0; i < ans.size(); i++){
                cout<< ans[i] <<" ";
            }
        }else{
            cout << 1 << endl;
            int p = (k + 1)/ 2;
            for(int i = 0; i < ans.size(); i++){
                if(i != ans.size() -1 and i % 2 == 0 and p){
                    cout << ans[i] <<" ";
                    p--;
                }
            }
        }
    }else{
        col2.resize(n + 1, 0);
        dfs2(1, 0);
        vector<int>v1,v2;
        for(int i = 1 ;i <= n; i++){
            if(col2[i] == 0){
                v2.pb(i);
            }else{
                v1.pb(i);
            }
        }
        cout << 1 << endl;
        int t = (k + 1)/ 2;
        if(v1.size() >= k / 2){
            for(int p: v1){
                if(t > 0){
                    cout <<p <<" ";
                    t--;
                }
            }
        }else if(v2.size() >= k / 2){
            for(int p: v1){
                if(t > 0){
                    cout <<p <<" ";
                    t--;
                }
            }
        }
    }
}