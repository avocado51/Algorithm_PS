#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#define INF 987654321
using namespace std;
//boj 이모티콘 https://www.acmicpc.net/problem/14226
//unsolved

typedef pair<int, int> pp;
typedef pair<int, pp> ppp;

int visited[1001][1001];
int s;

int dfs(int now, int clip)
{
    if (now < 1 || now > 1000 || clip > 1000)
        return INF;

    if (now == s)
    {
        return 0;
    }

    int &ret = visited[now][clip];
    if (ret != INF)
        return ret;

    ret = min(ret, min(dfs(now, clip + now) + 1, min(dfs(now + clip, clip) + 1, dfs(now - 1, clip) + 1)));

    return ret;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> s;

    for (int i = 0; i <= 1000; i++)
    {
        for (int j = 0; j <= 1000; j++)
            visited[i][j] = INF;
    }

    cout << dfs(1, 0) << '\n';

    return 0;
}
