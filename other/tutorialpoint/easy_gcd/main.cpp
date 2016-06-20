#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

int gcd(int u, int v)
{
	int t, k = 1;
	u = u < 0 ? -u : u;
	v = v < 0 ? -v : v;
	if (u < v) {
		u = u ^ v;
		v = u ^ v;
		u = u ^ v;
	}
	if (v == 0) return u;
	while ((u & 1) == 0 && (v & 1) == 0) { u >>= 1; v >>= 1; k <<= 1; }
	t = (u & 1) ? -v : u;
	while (t) {
		while ((t & 1) == 0) t >>= 1;
		if (t > 0) u = t;
		else v = -t;
		t = u - v;
	}
	return u * k;
}

int gcd2(int u, int v)
{
	int sh;
	if (u == 0) return v;
	if (v == 0) return u;
	for (sh = 0; ((u | v) & 1) == 0; ++sh) { u >>= 1; v >>= 1; }

	while ((u & 1) == 0) u >>= 1;
	do {
		while ((v & 1) == 0) v >>= 1;
		if (u > v) { u = u ^ v; v = u ^ v; u = u ^ v; }
		v = v - u;
	} while (v != 0);
	return u << sh;
}

int main()
{
	freopen("input.txt", "r", stdin);
	int n;
	int k;
	cin >> n >> k;
	vector<int> A(n);
	for (int i = 0; i < n; i++) cin >> A[i];
	sort(A.begin(), A.end());
	int r = A[0];
	if (A.size() >= 1) for (size_t i = 1; i < A.size(); ++i) r = gcd2(r, A[i]);
	cout << k - (k % r) << "\n";
	return 0;
}