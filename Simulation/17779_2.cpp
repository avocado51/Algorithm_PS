#include <iostream>
#include <vector>
#include <cstring>
#define INF 987654321
using namespace std;

//BOJ 게리맨더링2 [17779](https://www.acmicpc.net/problem/17779)
//속도 16ms (다른 풀이보다 더 빠름)

int A[21][21];
int map[21][21];
int n;
int ans = INF;
int total = 0;
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
void lineBorder(int x, int y, int d1, int d2)
{
    //x, y 지점에서 시작
    for (int i = 0; i <= d1; i++)
    {
        map[x + i][y - i] = 5;
        map[x + i + d2][y - i + d2] = 5;
    }
    for (int i = 0; i <= d2; i++)
    {
        map[x + i][y + i] = 5;
        map[x + d1 + i][y - d1 + i] = 5;
    }
}
void areaOne(int x, int y, int d1, int d2)
{
    //5를 만나면 다음 줄로 넘김
    for (int i = 1; i < x + d1; i++)
    {
        for (int j = 1; j <= y; j++)
        {
            if (map[i][j])
            {
                //0이 아닌 것을 만났으면
                break; //다음 줄로 넘어간다.
            }
            else
            {
                map[i][j] = 1;
            }
        }
    }
}
void areaTwo(int x, int y, int d1, int d2)
{

    for (int i = 1; i <= x; i++)
    {
        for (int j = y + 1; j <= n; j++)
        {
            map[i][j] = 2;
        }
    }

    int idx = 1;
    for (int i = x + 1; i <= x + d2; i++)
    {
        int k = y + ++idx;

        while (k <= n)
        {
            map[i][k++] = 2;
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
                break;
            map[i][j] = 3;
        }
    }
}
void areaFour(int x, int y, int d1, int d2)
{
    int idx = 1;
    for (int i = x + d2 + 1; i <= x + d1 + d2; i++)
    {
        int k = y + d2 - idx++;

        while (k + 1 <= n)
        {
            map[i][k + 1] = 4;
            k++;
        }
    }
    if (x + d1 + d2 < n)
    {
        for (int i = x + d1 + d2 + 1; i <= n; i++)
        {
            for (int j = y - d1 + d2; j <= n; j++)
            {
                map[i][j] = 4;
            }
        }
    }
}
int calc()
{
    int maxx = 0, minn = INF;
    int res[5] = {0, 0, 0, 0, 0};
    for (int x = 1; x <= n; x++)
    {
        for (int y = 1; y <= n; y++)
        {
            if (!map[x][y] || map[x][y] == 5)
                res[0] += A[x][y];
            else
                res[map[x][y]] += A[x][y];
        }
    }

    for (int i = 0; i < 5; i++)
    {
        maxx = maxx > res[i] ? maxx : res[i];
        minn = minn < res[i] ? minn : res[i];
    }

    return maxx - minn;
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> A[i][j];
        }
    }

    for (int x = 1; x <= n; x++)
    {
        for (int y = 1; y <= n; y++)
        {
            for (int d1 = 1; d1 <= n; d1++)
            {
                for (int d2 = 1; d2 <= n; d2++)
                {
                    if (1 > y - d1 || y + d2 > n || x + d1 + d2 > n)
                        continue;

                    memset(map, 0, sizeof(map));
                    lineBorder(x, y, d1, d2);

                    areaOne(x, y, d1, d2);

                    areaTwo(x, y, d1, d2);

                    areaThree(x, y, d1, d2);

                    areaFour(x, y, d1, d2);

                    ans = min(ans, calc());
                }
            }
        }
    }
    cout << ans << '\n';
    return 0;
}