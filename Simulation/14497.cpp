#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

#define INF 987654321
using namespace std;
//BOJ 주난의 난 [14497](https://www.acmicpc.net/problem/14497)

int n, m;
char map[301][301];
int sx, sy, ex, ey;
int ans = INF;
int visited[301][301];
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};

typedef struct Q
{
    int x, y;
};

// bool operator<(const Q &a, const Q &b)
// {
//     return a.cnt > b.cnt;
// }
void print()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cout << visited[i][j] << ' ';
        }
        cout << '\n';
    }
}
void bfs()
{
    queue<Q> q, nq;
    q.push({sx, sy});
    visited[sx][sy] = 0;
    int depth = 0;
    while (1)
    {
        //sx, sy 4방향과 주변의 0을 모두 넣어준다.
        while (!q.empty())
        {
            Q qq = q.front();
            q.pop();

            int x = qq.x;
            int y = qq.y;

            // cout << x << " " << y << " " << depth << '\n';
            for (int i = 0; i < 4; i++)
            {
                int nx = x + dx[i];
                int ny = y + dy[i];

                if (nx <= 0 || nx > n || ny <= 0 || ny > m || visited[nx][ny] != -1)
                    continue;

                if (map[nx][ny] == '#')
                {
                    ans = depth + 1;
                    return;
                }
                else if (map[nx][ny] == '1')
                {
                    nq.push({nx, ny});
                    map[nx][ny] = '0';
                    visited[nx][ny] = depth + 1;
                }
                else if (map[nx][ny] == '0')
                {
                    q.push({nx, ny});
                    visited[nx][ny] = depth;
                }
            }
        }
        depth++;
        while (!q.empty())
            q.pop();

        while (!nq.empty())
        {
            q.push(nq.front());
            nq.pop();
        }
    }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    cin >> sx >> sy >> ex >> ey;

    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> map[i][j];
            visited[i][j] = -1;
            if (map[i][j] == '1')
                cnt++;
        }
    }
    if (!cnt)
    {
        cout << 1 << '\n';
    }
    else
    {

        bfs();
        cout << ans << '\n';
    }

    return 0;
}