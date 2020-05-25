#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

//BOJ 배열돌리기4 [17406](https://www.acmicpc.net/problem/17406)

int map[51][51];
typedef struct R
{
    int r, c, s;
};
R dirs[7];
int n, m, k;
int ans = 987654321;
bool chk[7];
void print()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cout << map[i][j] << ' ';
        }
        cout << '\n';
    }
}
int calc()
{
    int minn = 987654321;
    for (int i = 1; i <= n; i++)
    {
        int sum = 0;
        for (int j = 1; j <= m; j++)
        {
            sum += map[i][j];
        }
        if (sum < minn)
        {
            minn = sum;
        }
    }
    return minn;
}
void dfs(int idx)
{
    if (idx == k)
    {
        //각 행을 더 한 값이 가장 작은 것을 반환
        int res = calc();
        ans = ans > res ? res : ans;
        // cout << res << '\n';
        // print(map);
        return;
    }

    for (int i = 0; i < k; i++)
    {
        if (!chk[i])
        {
            chk[i] = true;
            R now = dirs[i];
            int r = now.r;
            int c = now.c;
            int s = now.s;

            int cnt = 0;
            int c_map[51][51];
            memcpy(c_map, map, sizeof(map));

            while (cnt < s)
            {
                int tmp = map[r - s + cnt][c - s + cnt];
                //->
                for (int y = c - s + cnt; y < c + s - cnt; y++)
                {
                    int tmp2 = map[r - s + cnt][y + 1];
                    map[r - s + cnt][y + 1] = tmp;
                    tmp = tmp2;
                }
                //V
                for (int x = r - s + cnt; x < r + s - cnt; x++)
                {
                    int tmp2 = map[x + 1][c + s - cnt];
                    map[x + 1][c + s - cnt] = tmp;
                    tmp = tmp2;
                }

                //<-
                for (int y = c + s - cnt; y > c - s + cnt; y--)
                {
                    int tmp2 = map[r + s - cnt][y - 1];
                    map[r + s - cnt][y - 1] = tmp;
                    tmp = tmp2;
                }

                //^
                for (int x = r + s - cnt; x > r - s + cnt; x--)
                {
                    int tmp2 = map[x - 1][c - s + cnt];
                    map[x - 1][c - s + cnt] = tmp;
                    tmp = tmp2;
                }
                cnt++;
            }
            // cout << i << '\n';
            // print();
            dfs(idx + 1);
            memcpy(map, c_map, sizeof(map));
            chk[i] = false;
        }
    }
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> k;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> map[i][j];
        }
    }

    int a, b, c;
    for (int j = 0; j < k; j++)
    {
        cin >> a >> b >> c;
        dirs[j] = {a, b, c};
    }

    dfs(0);
    cout << ans << '\n';
    return 0;
}