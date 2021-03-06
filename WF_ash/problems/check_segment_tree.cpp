#include <bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef long long ll;
typedef long double lld;
typedef long long int lli;
using namespace std;
const int N = 1000001;
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
int gcd(int a, int b) {
     if (b == 0)
        return a;
    return gcd(b, a % b);
}
const int MAXN = (1 << 18);

int n, m;
int a[MAXN];
struct node{
	int sum, lazy;

	node() {sum = 0; lazy = 0;}
	node(int val){
		sum = val;
		lazy = 0;
	}
};

node temp, broken;

node merge(node l, node r){
	temp.sum = min(l.sum , r.sum);
	temp.lazy = 0;
	return temp;
}

struct segment_tree{
	node tr[4 * MAXN];

	void push(int l, int r, int idx){
		if(tr[idx].lazy){
			
            tr[idx].sum +=  tr[idx].lazy;
			
            if(l != r){
				tr[2 * idx + 1].lazy += tr[idx].lazy;
				tr[2 * idx + 2].lazy += tr[idx].lazy;
			}

			tr[idx].lazy = 0;
		}
	}
    //start with 0,n-1,1 will work for 0 based indexing
	void init(int l, int r, int idx){
		if(l == r){
			tr[idx] = node(a[l]);
			return;
		}

		int mid = (l + r) >> 1;
		init(l, mid, 2 * idx + 1);
		init(mid + 1, r, 2 * idx + 2);

		tr[idx] = merge(tr[2 * idx + 1], tr[2 * idx + 2]);
	}

	void update(int qL, int qR, int val, int l, int r, int idx){
		push(l, r, idx);

        //fully outside query
		if(qL > r || l > qR)
			return;

        //fully inside
		if(qL <= l && r <= qR){
			tr[idx].lazy += val;
			push(l, r, idx);
			return;
		}

        //partially inside
		int mid = (l + r) >> 1;
		update(qL, qR, val, l, mid, 2 * idx + 1);
		update(qL, qR, val, mid + 1, r, 2 * idx + 2);

		tr[idx] = merge(tr[2 * idx + 1], tr[2 * idx + 2]);
	}

	node query(int qL, int qR, int l, int r, int idx){
		push(l, r, idx);

		if(l > qR || r < qL)
			return broken;

		if(qL <= l && r <= qR)
			return tr[idx];

		int mid = (l + r) >> 1;
		return merge(query(qL, qR, l, mid, 2 * idx + 1), query(qL, qR, mid + 1, r, 2 * idx + 2));
	}
};

segment_tree t;

int32_t main() {
    _
    // RUN_T{
        int n,q,l,r,x;
        cin>>n;
        // memset(a,0,4*n+1);
        for(int i=0;i<n;i++){
            cin>>x;
            a[i]=x;
        }
        t.init(0,n-1,1);
        t.printing(n);
        t.update(4,6,0,0,n-1,1);
        t.printing(n);
        // cout<<endl;
        // for(int i=0;i<q;i++){
        //     int typ,val;
        //     cin>>typ;
        //     if(typ==0){
        //         cin>>l>>r>>val;
        //         --l,--r;
        //         t.update(l,r,val,0,n-1,1);
        //     }else{
        //         cin>>l>>r;
        //         --l,--r;
        //         node p = t.query(l,r,0,n-1,1);
        //         t.printing(n);
        //         cout<<endl;
        //         int ans = p.sum;
        //         cout<< ans <<endl;
        //     }
        // }
    // }
}
