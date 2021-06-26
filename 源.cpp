#include<iostream>
#include<algorithm>
#include<cstring>
#include<complex>
#include<queue>
#include<bits/stdc++.h>
#include<unordered_map>
#include<memory>
#define lowbit(x) x&(-x)
#define l(o) (o<<1)
#define r(o) (o<<1)|1
using namespace std;
#define rep(i,a,b) for(int i=a;i<=b;i++)
#define mem(a,b) memset(a,b,sizeof(a))
typedef long long ll;
template<class A>void read(A& a) {
	a = 0; int c = getchar(), f = 0;
	for (; !isdigit(c); c = getchar()) f |= c == '-';
	for (; isdigit(c); c = getchar()) a = a * 10 + (c ^ 48);
	if (f) a = -a;
}
template<class A, class ...B>
void read(A& a, B&...b) { read(a); read(b...); }
//---------------------------------------------------------------------
unordered_map<int, int> mp;
const int maxn = 1e5 + 11;
ll dp[maxn][33];
ll md = 123456789;
int a[maxn];
int temp[maxn];
ll v[33][maxn];
ll sum(int k,int p) {
	ll ans = 0;
	while (p) {
		ans += v[k][p];
		p -= lowbit(p);
	}
	return ans;
}
void add(int k,int p, ll val) {
	while (p < maxn) {
		v[k][p] += val;
		p += lowbit(p);
	}
}
//dp  前i个长度恰好为j
void solve() {
	int n, m;
	read(n, m);
	rep(i, 1, n) {
		read(a[i]); temp[i] = a[i];
	}
	sort(temp + 1, temp + 1 + n);
	int k = unique(temp + 1, temp + 1 + n) - temp;
	for (int i = 1; i < k; ++i) mp[temp[i]] = i;
	for (int i = 1; i <= n; ++i) a[i] = mp[a[i]];
	//cout << "*****" << endl;
	mem(v, 0);
	mem(dp, 0);
	dp[0][0] = 1;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j <= i; ++j) {
			if (j == 1)  dp[i][j] = 1;
			else if(j>1){
				dp[i][j] += sum(j - 1, a[i] - 1);
			}
			dp[i][j] %= md;
			add(j, a[i], dp[i][j]);
			//cout << i << " | " << j << " " << dp[i][j] << endl;
		}
	}
	ll ans = 0;
	rep(i, 1, n) ans += dp[i][m];
	cout << ans << endl;
}

int main() {
	solve();
}