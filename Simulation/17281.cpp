#include <iostream>
#include <vector>

using namespace std;
//BOJ 야구 https://www.acmicpc.net/problem/17281

int inning;
int inningRes[51][10];
int order[10];
bool chk[10];
int score = 0;
int status = 0;

int max(const int &a, const int &b)
{
    if (a > b)
        return a;
    return b;
}
int calc()
{
    int ret = 0;

    for (int i = 4; i < 7; i++)
    {
        if ((status & (1 << i)) > 0)
        {
            ret++;
            status = status & ~(1 << i);
        }
    }

    return ret;
}
int playGame()
{
    int last = -1, idx = 1, cntOut = 0;
    int res = 0;

    for (int j = 1; j <= inning; j++)
    {

        while (1)
        {
            if (last != -1)
            {
                idx = last;
                last = -1;
            }

            int tmp = inningRes[j][order[idx]];

            if (tmp == 0)
            {
                cntOut++;
                if (cntOut == 3)
                {
                    cntOut = 0;
                    status = 0;
                    last = idx + 1;
                    if (last == 10)
                        last = 1;
                    break;
                }
            }
            else if (tmp == 1)
            {
                status++;
                status = status << 1;
                res += calc();
            }
            else if (tmp == 2)
            {
                status++;
                status = status << 2;
                res += calc();
            }
            else if (tmp == 3)
            {
                status++;
                status = status << 3;
                res += calc();
            }
            else if (tmp == 4)
            {
                status++;
                for (int i = 0; i < 4; i++)
                {
                    if ((status & (1 << i)) > 0)
                    {
                        res++;
                    }
                }
                status = 0;
            }

            idx++;
            if (idx == 10)
            {
                last = -1;
                idx = 1;
            }
        }
    }
    return res;
}
void dfs(int cnt)
{
    if (cnt > 9)
    {
        score = max(score, playGame());

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
                chk[i] = 1;
                order[cnt] = i;
                dfs(cnt + 1);
                order[cnt] = 0;
                chk[i] = 0;
            }
        }
    }
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> inning;
    for (int i = 1; i <= inning; i++)
    {
        for (int j = 1; j <= 9; j++)
        {
            cin >> inningRes[i][j];
        }
    }
    chk[1] = true;
    order[4] = 1;
    dfs(1);
    cout << score << '\n';
    return 0;
}