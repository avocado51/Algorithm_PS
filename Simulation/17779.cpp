#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>
#define INF 987654321
using namespace std;

int n;
int A[22][22], map[22][22];
typedef pair<int, int> pp;
int ans = INF;
int dx[3] = {1, 0, 0}, dy[3] = {0, -1, 1};
int popu[5];

void print()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cout << map[i][j] << ' ';
        }
        cout << '\n';
    }
}
int calc()
{
    memset(popu, 0, sizeof(popu));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            popu[map[i][j] - 1] += A[i][j];
        }
    }
    int minn = INF, maxx = 0;
    for (int i = 0; i < 5; i++)
    {
        minn = minn > popu[i] ? popu[i] : minn;
        maxx = maxx < popu[i] ? popu[i] : maxx;
    }
    return maxx - minn;
}
void areaOne(int x, int y, int d1, int d2)
{
    for (int i = 1; i < x + d1; i++)
    {
        for (int j = 1; j <= y; j++)
        {
            if (map[i][j])
                continue;

            map[i][j] = 1;
        }
    }
}
void areaTwo(int x, int y, int d1, int d2)
{
    for (int i = 1; i <= x + d2; i++)
    {
        for (int j = y + 1; j <= n; j++)
        {
            if (map[i][j])
                continue;
            map[i][j] = 2;
        }
    }
}
void areaThree(int x, int y, int d1, int d2)
{
    for (int i = x + d1; i <= n; i++)
    {
        for (int j = 1; j < y - d1 + d2; j++)
        {
            if (map[i][j])
                continue;
            map[i][j] = 3;
        }
    }
}

void areaFour(int x, int y, int d1, int d2)
{
    for (int i = x + d2 + 1; i <= n; i++)
    {
        for (int j = y - d1 + d2; j <= n; j++)
        {
            if (map[i][j])
                continue;
            map[i][j] = 4;
        }
    }
}

void fillInner(int x, int y, int d1, int d2)
{
    queue<pp> q;

    for (int i = 0; i < d1; i++)
    {
        q.push(pp(x + i + 1, y - i));
    }
    for (int i = 0; i < d2; i++)
    {
        q.push(pp(x + i + 1, y + i));
    }

    while (!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        map[x][y] = 5;

        for (int i = 0; i < 3; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 1 || ny > n || nx > n || ny < 1 || map[nx][ny] == 5)
                continue;
            q.push(pp(nx, ny));
        }
    }
}
void areaLine(int x, int y, int d1, int d2)
{
    for (int i = 0; i <= d1; i++)
    {
        map[x + i][y - i] = 5;
        map[x + d2 + i][y + d2 - i] = 5;
    }
    for (int i = 0; i <= d2; i++)
    {
        map[x + d1 + i][y - d1 + i] = 5;
        map[x + i][y + i] = 5;
    }
    fillInner(x, y, d1, d2);
}

int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            cin >> A[i][j];
    }

    for (int x = 1; x <= n; x++)
    {
        for (int y = 1; y <= n; y++)
        {
            for (int d1 = 1; d1 <= n; d1++)
            {
                for (int d2 = 1; d2 <= n; d2++)
                {
                    if (0 < y - d1 && y + d2 <= n && x + d1 + d2 <= n)
                    {
                        memset(map, 0, sizeof(map));

                        areaOne(x, y, d1, d2);
                        areaTwo(x, y, d1, d2);
                        areaThree(x, y, d1, d2);
                        areaFour(x, y, d1, d2);
                        areaLine(x, y, d1, d2);
                        // cout << "debbbbbb " << '\n';
                        // print();
                        int res = calc();
                        ans = min(ans, res);
                    }
                }
            }
        }
    }
    cout << ans << '\n';
    return 0;
}