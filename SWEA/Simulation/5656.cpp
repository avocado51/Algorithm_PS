#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

#define INF 987654321
using namespace std;
//SWEA 벽돌깨기 https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWXRQm6qfL0DFAUo

int n, w, h, ans;

int dx[4] = {0, 0, -1, 1}, dy[4] = {-1, 1, 0, 0};

typedef pair<int, int> pp;

void relocateMap(int (*map)[13])
{
    //0인 부분이 중간에 껴있으면 밑으로 내려준다.
    for (int j = 0; j < w; j++)
    {
        for (int i = h - 2; i >= 0; --i)
        {
            //위에서 벽돌이 시작되는 가장 가까운 좌표
            for (int k = i; k < h - 1; k++)
            {
                if (!map[k + 1][j])
                {
                    swap(map[k + 1][j], map[k][j]);
                }
            }
        }
    }
}
bool checkRange(int x, int y)
{
    if (x < 0 || x >= h || y < 0 || y >= w)
        return false;
    return true;
}
int check(int (*map)[13])
{
    int ret = 0;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (map[i][j])
                ret++;
        }
    }
    return ret;
}
bool noBrick(int (*map)[13])
{
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (map[i][j])
                return false;
        }
    }
    return true;
}
void bomb(int x, int y, int (*map)[13])
{
    queue<pp> q;

    q.push(pp(x, y));

    while (!q.empty())
    {
        int xx = q.front().first;
        int yy = q.front().second;
        q.pop();

        int cnt = map[xx][yy];
        map[xx][yy] = 0;
        for (int d = 0; d < 4; d++)
        {
            for (int k = 1; k < cnt; k++)
            {
                int nx = xx + dx[d] * k;
                int ny = yy + dy[d] * k;

                if (checkRange(nx, ny))
                {
                    if (map[nx][ny] <= 1)
                    {
                        map[nx][ny] = 0;
                    }
                    else
                    {
                        q.push(pp(nx, ny));
                    }
                }
                else
                    break;
            }
        }
    }
}

void dfs(int cnt, int (*map)[13])
{
    if (noBrick(map))
    {
        ans = 0;
        return;
    }
    if (cnt == n)
    {
        int res = check(map); //남은 벽돌의 개수
        ans = min(ans, res);
        return;
    }

    int c_map[16][13];

    for (int i = 0; i < w; i++)
    {
        //떨어뜨린 곳에 또 떨어뜨릴 수 있다.
        memcpy(c_map, map, sizeof(c_map));
        for (int j = 0; j < h; j++)
        {
            if (c_map[j][i])
            {
                if (c_map[j][i] == 1)
                    c_map[j][i] = 0;
                else
                {
                    bomb(j, i, c_map);
                }
                break;
            }
        }
        relocateMap(c_map);
        dfs(cnt + 1, c_map);
    }
}

int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    int map[16][13];

    for (int tc = 1; tc <= t; tc++)
    {
        cin >> n >> w >> h;

        ans = INF;
        for (int i = 0; i < h; i++)
        {
            for (int j = 0; j < w; j++)
            {
                cin >> map[i][j];
            }
        }

        dfs(0, map);
        cout << "#" << tc << " " << ans << '\n';
    }
    return 0;
}