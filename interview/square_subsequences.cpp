#include <string>
#include <iostream>
#include <stdio.h>

#define bs 1000000007
using namespace std;
static int tests;
static int ans;
static int dp[500][500];

static int solve(string st1, string st2)
{
	for (int i = 0; i <= st1.size(); i++)
	{
		for (int j = 0; j <= st2.size(); j++)
		{
			dp[i][j] = 0;
		}
	}
	for (int i = 0; i < st2.size(); i++)
	{
		if (st2[i] == st1[0])
			dp[1][i+1] = 1;
		if (i)
			dp[1][i+1] += dp[1][i];
	}
	for (int i = 1; i < st1.size(); i++)
	{
		for (int j = 0; j < st2.size(); j++)
		{
			dp[i + 1][j + 1] = dp[i + 1][j] + dp[i][j + 1] - dp[i][j];
			if (st1[i] == st2[j])
			{
				dp[i + 1][j + 1] += dp[i][j];
			}
			dp[i + 1][j + 1] = (dp[i + 1][j + 1] % bs);
			if (dp[i + 1][j + 1] < 0)
				dp[i + 1][j + 1] += bs;
		}
	}
	return dp[st1.size()][st2.size()];
}
int test_square_subsequences() {
	freopen("square_subsequences.txt", "r", stdin);
    
	cin >> tests;
	for (; tests; --tests)
	{
		ans = 0;
		string st;
		cin >> st;
		for (int cp = 1; cp < st.size(); cp++)
		{
			string st1, st2;
			for (int i = 0; i < st.size(); i++)
			{
				if (i < cp)
					st1 += st[i];
				else
					st2 += st[i];
			}
			ans += solve(st2, st1);
			ans %= bs;
		}
		cout << ans << "\n";
	}
	return 0;
}