#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

//BOJ 로봇청소기 [14503](https://www.acmicpc.net/problem/14503)

int ldir[4] = {3, 0, 1, 2};
int ans = 0;
int n, m;
int map[51][51];
typedef struct Q
{
    int x, y, d;
};
queue<Q> q;
bool visited[51][51];
int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

bool checkRange(int x, int y)
{
    if (x < 0 || x >= n || y < 0 || y >= m || map[x][y])
        return false;
    return true;
}
void bfs()
{
    while (!q.empty())
    {
        Q qq = q.front();
        q.pop();

        int x = qq.x;
        int y = qq.y;
        int dir = qq.d;

        //현재 방향에서의 왼쪽
        bool flag = false;
        for (int j = 0; j < 4; j++)
        {
            int l = ldir[dir];
            int nx = x + dx[l];
            int ny = y + dy[l];

            if (checkRange(nx, ny) && !visited[nx][ny])
            {
                //청소할 공간이 존재한다면 이 방향으로 간다.
                q.push({nx, ny, l});
                visited[nx][ny] = true;
                flag = true;
                break;
            }
            dir = l;
        }
        if (!flag)
        {
            //청소할 곳이 없음
            //바라보는 방향을 유지하고 한 칸뒤로 가낟.
            int b = dir < 2 ? dir + 2 : dir - 2;
            int nx = x + dx[b];
            int ny = y + dy[b];

            if (checkRange(nx, ny))
            {
                q.push({nx, ny, dir});
            }
            else
                break;
        }
    }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie();

    cin >> n >> m;
    int x, y, d;
    cin >> x >> y >> d;
    visited[x][y] = true;
    q.push({x, y, d});

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> map[i][j];
        }
    }

    bfs();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (!map[i][j] && visited[i][j])
            {
                // cout << 1;
                ans++;
            }
        }
        // cout << '\n';
    }

    cout << ans << '\n';
    return 0;
}