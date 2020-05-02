#include <iostream>
#include <vector>
#define MAXX 1001
#define INF 987654321
using namespace std;

//BOj 경찰차 https://www.acmicpc.net/problem/2618
//unsolved

typedef pair<int, int> pp;
vector<pp> inc[MAXX + 2];

int n, w;
int dp[MAXX + 2][MAXX + 2], ans[MAXX + 1];

int dfs(int idx, int i, int j)
{
    if (idx == w)
        return 0;

    if (dp[i][j] != -1)
    {
        return dp[i][j];
    }

    int &ret = dp[i][j];

    int p1Dist = abs(inc[idx].front().first - inc[i].front().first) + abs(inc[idx].front().second - inc[i].front().second);
    int p2Dist = abs(inc[idx].front().first - inc[j].front().first) + abs(inc[idx].front().second - inc[j].front().second);

    // cout << "debug " << idx << " " << i << " " << j << " " << p1Dist << " " << p2Dist << '\n';
    if (p1Dist >= p2Dist)
    {
        ans[idx] = 2;
    }
    else
    {
        ans[idx] = 1;
    }
    return ret = min(dfs(idx + 1, i + 1, j) + p1Dist, dfs(idx + 1, i, j - 1) + p2Dist);
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> w;

    inc[0].push_back(pp(1, 1));
    for (int i = 1; i <= w; i++)
    {
        int x, y;
        cin >> x >> y;
        inc[i].push_back(pp(x, y));
    }
    inc[w + 1].push_back(pp(n, n));

    for (int i = 0; i <= w + 1; i++)
    {
        for (int j = 0; j <= w + 1; j++)
        {
            dp[i][j] = -1;
        }
    }

    //dp[i][j] = min(i번째 문제를 1번 경찰차가 해결했을 때 이동거리, j번재 문제를 2번 자동차가 해결했을 때 이동거리)
    cout << dfs(1, 0, w + 1) << '\n';

    for (int i = 1; i <= w; i++)
    {
        cout << ans[i] << '\n';
    }
    return 0;
}
