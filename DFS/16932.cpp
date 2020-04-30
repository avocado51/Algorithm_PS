#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <set>

using namespace std;

//boj 모양 만들기 https://www.acmicpc.net/problem/16932

int n, m;
int map[1001][1001];
bool visited[1001][1001];
int labelMap[1001][1001];
int dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};
int labelCnt[1000001];
bool chk[1001][1001];

typedef pair<int, int> pp;

int max(const int &a, const int &b)
{
    if (a > b)
        return a;
    return b;
}
bool checkRange(int nx, int ny)
{
    if (nx < 0 || nx >= n || ny < 0 || ny >= m)
        return false;
    return true;
}
void dfs(int x, int y, int label)
{
    visited[x][y] = true;
    labelMap[x][y] = label;
    labelCnt[label]++;
    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (checkRange(nx, ny) && map[nx][ny] && !visited[nx][ny])
        {
            dfs(nx, ny, label);
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

    //수를 하나 변경해서 1이 연결되는 최대 값을 구한다.
    //두 개로 나눠져있다면 그 두개를 연결하는 좌표를바꾸면 된다.
    int label = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (map[i][j] && !visited[i][j])
            {
                ++label;
                dfs(i, j, label);
            }
        }
    }

    
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (map[i][j])
            {
                for (int d = 0; d < 4; d++)
                {
                    int nx = i + dx[d];
                    int ny = j + dy[d];

                    if (checkRange(nx, ny) && !map[nx][ny] && !chk[nx][ny])
                    {
                        chk[nx][ny] = true;
                        int res = labelCnt[labelMap[i][j]];
                        set<int> combine;
                        set<int>::iterator it;
                        for (int k = 0; k < 4; k++)
                        {
                            int nnx = nx + dx[k];
                            int nny = ny + dy[k];

                            if (checkRange(nnx, nny) && labelMap[nnx][nny] && labelMap[nnx][nny] != labelMap[i][j])
                            {
                                combine.insert(labelMap[nnx][nny]);
                            }
                        }

                        for (it = combine.begin(); it != combine.end(); it++)
                        {
                            res += labelCnt[*it];
                        }
                        ans = max(ans, res + 1);
                    }
                }
            }
        }
    }
    cout << ans << '\n';
    return 0;
}