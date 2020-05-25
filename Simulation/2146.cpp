#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

#define INF 987654321

using namespace std;
//BOJ 다리만들기 [2146](https://www.acmicpc.net/problem/2146)

int map[101][101], labelMap[101][101];
bool visited[101][101];
int n;
bool chk[101][101];
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
int ans = INF;

typedef struct Q
{
    int cnt, x, y;
};

bool checkRange(int x, int y)
{
    if (x < 0 || x >= n || y < 0 || y >= n)
        return false;
    return true;
}
int bfs(int x, int y)
{
    queue<Q> q;
    q.push({0, x, y});
    memset(visited, 0, sizeof(visited));

    visited[x][y] = true;

    int res = INF;
    while (!q.empty())
    {
        Q qq = q.front();
        q.pop();

        int cnt = qq.cnt;
        int xx = qq.x;
        int yy = qq.y;

        int label = labelMap[x][y];

        for (int i = 0; i < 4; i++)
        {
            int nx = xx + dx[i];
            int ny = yy + dy[i];

            if (checkRange(nx, ny))
            {
                if (!visited[nx][ny])
                {
                    visited[nx][ny] = true;
                    if (!map[nx][ny])
                    {
                        //바다 -> 다리를 잇자
                        q.push({cnt + 1, nx, ny});
                    }
                    else
                    {
                        if (labelMap[nx][ny] == label)
                        {
                            continue; //다른 방향으로간다.
                        }
                        else
                        {
                            res = min(res, cnt);
                            continue;
                        }
                    }
                }
            }
        }
    }
    if (res == INF)
        return -1;
    return res;
}
void dfs(int x, int y, int label)
{
    if (chk[x][y])
        return;
    chk[x][y] = true;
    labelMap[x][y] = label;

    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (checkRange(nx, ny))
        {
            if (map[nx][ny] && !labelMap[nx][ny])
                dfs(nx, ny, label);
        }
    }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> map[i][j];
        }
    }

    int label = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (map[i][j] && !chk[i][j])
            {
                label++;
                dfs(i, j, label);
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (map[i][j])
            {
                //섬일 때
                //가장자리로 가야한다.
                //가장자리 = 자신과 같은 것이 안나오는 좌표 (방향을 잘 봐야 한다.)
                int res = bfs(i, j);
                //다른 섬을 만나서 다리를 완성했으면 그 다리의 길이를 가져온다.
                // cout << i << " " << j << " " << res << '\n';
                if (res != -1)
                {
                    ans = ans > res ? res : ans;
                }
            }
        }
    }

    cout << ans << '\n';
    return 0;
}