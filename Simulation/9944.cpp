#include <iostream>
#include <vector>
#include <cstring>

#define INF 1000001
using namespace std;

//NXM보드 완주하기 
//unsolved

int n, m;
char map[31][31];
int ans;
bool visited[31][31];
int dx[4] = {-1, 1, 0, 0}, dy[4] = {0, 0, -1, 1};
bool checkRange(int x, int y)
{
    if (x < 0 || x >= n || y < 0 || y >= m || map[x][y] == '*')
        return false;
    return true;
}
bool check()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (!checkRange(i, j))
            {
                if (!visited[i][j])
                    return false;
            }
        }
    }
    return true;
}
void dfs(int x, int y, int cnt, int dir)
{
    visited[x][y] = true;
    int nx = x + dx[dir];
    int ny = y + dy[dir];
    cout << x << " " << y << " " << nx << " " << ny << '\n';
    if (!checkRange(nx, ny) || visited[nx][ny])
    {
        for (int j = 0; j < 4; j++)
        {
            if (j == dir)
                continue;
            dfs(x, y, cnt + 1, j);
        }
        return;
    }

    if (check())
    {
        //모두 탐색했는지 확인하기
        ans = min(ans, cnt);
        return;
    }

    dfs(nx, ny, cnt, dir);
    visited[x][y] = false;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie();

    int tc = 1;
    while (1)
    {
        cin >> n >> m;
        if (!n)
            break;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cin >> map[i][j];
            }
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (map[i][j] == '.')
                {
                    for (int d = 0; d < 4; d++)
                    {
                        memset(visited, 0, sizeof(visited));
                        visited[i][j] = true;
                        dfs(i, j, 1, d);
                    }
                }
            }
        }
        cout << "Case " << tc << ": ";
        if (ans == INF)
            cout << -1 << '\n';
        else
            cout << ans << '\n';
        tc++;
    }

    return 0;
}