#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>

#define MAXX 100002
#define INF 987654321
using namespace std;

//BOJ 환승 https://www.acmicpc.net/problem/5214

vector<int> station[MAXX];
bool visited[MAXX];
//int dist[MAXX];
int ans = INF;
typedef pair<int, int> pp;

void bfs(int start, int dest)
{
    queue<pp> q;
    q.push(pp(1, start));
    //dist[start] = 1;

    while (!q.empty())
    {
        int size = q.size();
        while (size--)
        {
            int now = q.front().second;
            int cnt = q.front().first;
            q.pop();

            if (now == dest)
            {
                ans = min(ans, cnt);
                continue;
            }

            for (auto i : station[now])
            {
                if (i == now)
                    continue;
                if (!visited[i])
                {
                    visited[i] = true;
                    q.push(pp(cnt + 1, i));
                }
            }
        }
    }
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, k;

    cin >> n >> k >> m;

    vector<int> v;
    for (int i = 0; i < m; i++)
    {
        v.clear();
        for (int j = 0; j < k; j++)
        {
            int tmp;
            cin >> tmp;
            v.push_back(tmp);
        }
        sort(v.begin(), v.end());

        for (int j = 1; j <= n; j++)
        {
            if (find(v.begin(), v.end(), j) != v.end())
            {
                station[j].insert(station[j].end(), v.begin(), v.end());
            }
        }
    }
    //하이퍼에 연결되어있는 역끼리 또 연결한다.

    ////이제 각 역끼리 최단 경로를 구한다.
    bfs(1, n);

    if (ans == INF)
        cout << -1 << '\n';
    else
        cout << ans << '\n';

    return 0;
}