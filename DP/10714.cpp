#include <iostream>
#include <vector>
#include <cstring>
#define MAXX 2001
using namespace std;
//boj 케이크자르기2 https://www.acmicpc.net/problem/10714
//unsolved

typedef unsigned long long ll;

ll cake[MAXX];
ll dp[MAXX][MAXX];
vector<ll> pick;
ll dfs(int player, int start, int end)
{

    if (start == end)
    {
        if (player)
            return dp[start][end];
        else
            return dp[start][end] = cake[pick[start]];
    }

    if (dp[start][end])
        return dp[start][end];

    ll &ret = dp[start][end];

    if (!player)
    {
        //joi이라면
        ret = max(dfs(1 - player, start + 1, end) + cake[pick[start]], dfs(1 - player, start, end - 1) + cake[pick[end]]);
    }
    else
    {
        ret = min(dfs(1 - player, start + 1, end), dfs(1 - player, start, end - 1));
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        ll tmp;
        cin >> tmp;
        cake[i] = tmp;
    }

    ll max = 0;
    for (int i = 0; i < n; i++)
    {
        pick.clear();

        for (int j = i; j < n; j++)
        {
            pick.push_back(j);
        }
        for (int j = 0; j < i; j++)
        {
            pick.push_back(j);
        }
        memset(dp, 0, sizeof(dp));

        dp[0][0] = cake[pick[0]];

        ll tmp = dfs(0, 1, n - 1);

        max = max < tmp ? tmp : max;
    }

    cout << max << '\n';
    return 0;
}
