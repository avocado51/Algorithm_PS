#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
//boj 십자가 2개 놓기 https://www.acmicpc.net/problem/17085

int n, m;
char map[16][16];
int dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};

bool visited[16][16];
int chk[16][16];

typedef long long ll;
ll ans = 0;
bool checkRange(int x, int y)
{
    if (x < 0 || x >= n || y < 0 || y >= m)
        return false;
    return true;
}

void dfs(int cnt, ll res)
{
    if (cnt == 2)
    {
        //최대 너비를 계산
        ans = ans > res ? ans : res;
        return;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (chk[i][j] && !visited[i][j])
            {
                bool c_visited[16][16];
                memcpy(c_visited, visited, sizeof(visited));

                int limit = chk[i][j] - 1;
                visited[i][j] = true;
                int sum = 1;
                if (!limit)
                {
                    dfs(cnt + 1, res * sum);
                    visited[i][j] = false;
                }

                int idx = 1;
                bool flag = true;
                while (limit-- && flag)
                {
                    for (int d = 0; d < 4; d++)
                    {
                        int nx = i + dx[d] * idx;
                        int ny = j + dy[d] * idx;

                        if (checkRange(nx, ny) && !visited[nx][ny])
                        {
                        }
                        else
                        {
                            flag = false;
                            break;
                        }
                    }

                    if (flag)
                    {
                        //4방향으로 모두 알맞게 십자가를 만들었다면
                        for (int d = 0; d < 4; d++)
                        {
                            int nx = i + dx[d] * idx;
                            int ny = j + dy[d] * idx;
                            visited[nx][ny] = true;
                            sum++;
                        }

                        dfs(cnt + 1, res * sum);
                        idx++;
                    }
                }
                memcpy(visited, c_visited, sizeof(visited));
            }
        }
    }
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

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
            if (map[i][j] == '#')
            {
                int idx = 1;

                bool flag = true;
                while (flag)
                {
                    for (int d = 0; d < 4; d++)
                    {
                        int nx = i + dx[d] * idx;
                        int ny = j + dy[d] * idx;

                        if (checkRange(nx, ny) && map[nx][ny] == '#')
                        {
                        }
                        else
                        {
                            flag = false;
                            break;
                        }
                    }
                    if (flag)
                    {
                        idx++;
                    }
                }
                chk[i][j] = idx;
            }
        }
    }

    dfs(0, 1);
    cout << ans << '\n';
    return 0;
}
