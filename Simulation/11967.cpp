#include <iostream>
#include <vector>
#include <queue>

using namespace std;
//BOJ 불끄기 [11967](https://www.acmicpc.net/problem/11967)

int n, m;
int map[101][101];

typedef pair<int, int> pp;

vector<pp> sswitch[101][101];
int ans = 0;
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
int visited[101][101];

void bfs()
{
    queue<pp> q;
    q.push({1, 1});

    map[1][1] = 1;
    ans = 1;
    visited[1][1] = 1;
    while (!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (pp next : sswitch[x][y])
        {
            if (visited[next.first][next.second] == 1 || map[next.first][next.second] == 1)
                continue;
            ans++;
            if (visited[next.first][next.second] == -1)
            {
                q.push({next.first, next.second});
            }

            map[next.first][next.second] = 1;
        }

        for (int j = 0; j < 4; j++)
        {
            int nx = x + dx[j];
            int ny = y + dy[j];

            if (nx <= 0 || nx > n || ny <= 0 || ny > n || visited[nx][ny] == 1)
                continue;

            if (map[nx][ny])
            {
                //켜져있는 곳
                visited[nx][ny] = 1;
                q.push({nx, ny});
            }
            else
                visited[nx][ny] = -1;
        }
    }
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    int sx, sy, ex, ey;
    while (m--)
    {
        cin >> sx >> sy >> ex >> ey;
        sswitch[sx][sy].push_back({ex, ey});
    }

    bfs();

    cout << ans << '\n';
    return 0;
}