#include <iostream>
#include <vector>

using namespace std;
//BOJ 야구 [17281](https://www.acmicpc.net/problem/17281)

int n;
int order[10], player[51][10];
int status = 0;
int ans = 0;
bool chk[10];

int calc()
{
    int res = 0;
    for (int i = 4; i < 7; i++)
    {
        if ((status & (1 << i)) > 0)
        {
            res++;
            status = status & ~(1 << i);
        }
    }
    return res;
}
int playGame()
{
    int idx = 1;
    int res = 0;
    for (int i = 1; i <= n; i++)
    {
        int out = 0;
        int first = idx;

        while (1)
        {
            int point = player[i][order[first]];

            if (point == 1)
            {
                status++;
                status = status << 1;
                res += calc();
            }
            else if (point == 2)
            {
                status++;
                status = status << 2;
                res += calc();
            }
            else if (point == 3)
            {
                status++;
                status = status << 3;
                res += calc();
            }
            else if (point == 4)
            {
                status++;
                for (int j = 0; j < 4; j++)
                {
                    if ((status & (1 << j)) > 0)
                        res++;
                }
                status = 0;
            }
            else if (point == 0)
            {
                out++;

                if (out == 3)
                {
                    idx = first + 1;
                    status = 0;
                    if (idx == 10)
                        idx = 1;
                    break;
                }
            }
            first++;
            if (first == 10)
                first = 1;
        }
    }
    return res;
}
void dfs(int cnt)
{
    if (cnt == 10)
    {
        ans = max(ans, playGame());
        return;
    }

    if (cnt == 4)
    {
        dfs(cnt + 1);
    }
    else
    {
        for (int i = 2; i <= 9; i++)
        {
            if (!chk[i])
            {
                chk[i] = true;
                order[cnt] = i;
                dfs(cnt + 1);
                order[cnt] = 0;
                chk[i] = false;
            }
        }
    }
}

int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= 9; j++)
        {
            cin >> player[i][j];
        }
    }
    chk[1] = true;
    order[4] = 1;
    dfs(1);

    cout << ans << '\n';
    return 0;
}