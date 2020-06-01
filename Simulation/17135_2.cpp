#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;
//BOJ 캐슬 디펜스 [17135](https://www.acmicpc.net/problem/17135)

int map[16][15];
int n, m, d;
bool chk[15];
int ans = 0;
int maxx = 0;
typedef struct Q
{
    int x, y, d;
};

int dx[3] = {0, -1, 0}, dy[3] = {-1, 0, 1};

int attack(int x, int y)
{
    if (map[x - 1][y] == 1)
    {
        //적이 있음
        map[x - 1][y] = 2;
        return 1;
    }
    if (map[x - 1][y] == 2)
        return 0;

    //d거리 이하의 적을 찾는다.
    queue<Q> q;
    q.push({x - 1, y, 1});

    while (!q.empty())
    {
        Q qq = q.front();
        q.pop();
        int xx = qq.x;
        int yy = qq.y;
        int dist = qq.d;

        if (dist >= d)
            continue;

        for (int j = 0; j < 3; j++)
        {
            int nx = xx + dx[j];
            int ny = yy + dy[j];

            if (nx < 0 || ny < 0 || ny >= m)
                continue;
            if (map[nx][ny] == 2)
                return 0;

            if (map[nx][ny] == 1 && dist + 1 <= d)
            {
                map[nx][ny] = 2;
                return 1;
            }

            q.push({nx, ny, dist + 1});
        }
    }
    return 0;
}
//1- 적, 2- 이미 죽은 적, 3-궁수
int playAttack()
{
    int res = 0;
    for (int cnt = n; cnt > 0; cnt--)
    {
        //n번쩨 줄에서 시작
        for (int j = 0; j < m; j++)
        {
            if (chk[j])
            {
                map[cnt][j] = 3; //궁수 배치
                res += attack(cnt, j);
            }
        }


        for (int i = cnt; i >= 0; i--)
        {
            for (int j = 0; j < m; j++)
            {
                if (map[i][j] == 2)
                {
                    map[i][j] = 0;
                }
            }
        }
    }
    return res;
}
void dfs(int cnt, int idx)
{
    if (cnt == 3)
    {
        //궁수 공격
        int c_map[16][15];
        memcpy(c_map, map, sizeof(map));

        int res = playAttack();
        ans = max(ans, res);
        memcpy(map, c_map, sizeof(map));
        return;
    }

    for (int i = idx; i < m; i++)
    {
        if (!chk[i])
        {
            chk[i] = true;
            dfs(cnt + 1, i + 1);
            chk[i] = false;
        }
    }
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> d;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> map[i][j];
            if (map[i][j])
                maxx++;
        }
    }
    if (!maxx)
    {
        cout << 0 << '\n';
        return 0;
    }
    dfs(0, 0); //궁수 배치

    cout << ans << '\n';
    return 0;
}