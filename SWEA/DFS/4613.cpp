#include <iostream>
#include <vector>
#include <cstring>
#define INF 987654321
using namespace std;
//SWEA 4613. 러시아 국기 같은 깃발
//https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AWQl9TIK8qoDFAXj&categoryId=AWQl9TIK8qoDFAXj&categoryType=CODE

int color[51][51];
int n, m;
int ans = INF;
int chk[51];

int calc()
{
    int ret = INF;

    for (int i = 1; i < n - 1; i++)
    {
        if (chk[i] == 2)
        {
            ret = 0;
            break;
        }
        //이 색으로 바꿔야 하낟.
    }
    if (!ret)
    {
        for (int i = 1; i < n - 1; i++)
        {
            int flag = chk[i];
            for (int j = 0; j < m; j++)
            {
                if (color[i][j] != flag)
                {
                    ret++;
                }
            }
        }
    }

    return ret;
}
void dfs(int x, int c)
{
    if (x == n - 1)
    {
        int res = calc();
        ans = min(ans, res);
        return;
    }

    if (!chk[x])
    {
        int prev = chk[x - 1];
        for (int j = prev; j <= 3; j++)
        {
            chk[x] = j;
            dfs(x + 1, j);
            chk[x] = 0;
        }
    }
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int tc = 1; tc <= t; ++tc)
    {
        cin >> n >> m;

        memset(color, 0, sizeof(color));
        memset(chk, 0, sizeof(chk));
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                char c;
                cin >> c;
                if (c == 'W')
                    color[i][j] = 1;
                else if (c == 'B')
                    color[i][j] = 2;
                else if (c == 'R')
                    color[i][j] = 3;
            }
        }
        //조합으로 구하기
        ans = INF;
        int res = 0;

        for (int j = 0; j < m; ++j)
        {
            if (color[0][j] != 1)
            {

                res++;
                color[0][j] = 1;
            }
            if (color[n - 1][j] != 3)
            {

                res++;
                color[n - 1][j] = 3;
            }
        }

        //1행부터 n-2행까지는 흰 -> 파 -> 빨 순서대로 와야 한다.
        //각각 몇 개의 행을 차지하는 지는 조합으로 구한다.
        dfs(1, 1);
        cout << "#" << tc << " " << res + ans << '\n';
    }

    return 0;
}