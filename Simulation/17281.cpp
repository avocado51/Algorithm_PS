#include <iostream>
#include <vector>

using namespace std;
//BOJ 야구 https://www.acmicpc.net/problem/17281

int inningRes[51][10];
int score = 0;
int inning;
bool chk[10];
int order[10];
int max(const int &a, const int &b)
{
    if (a > b)
        return a;
    return b;
}
int playGame()
{
    for (int i = 1; i <= 9; i++)
    {
        cout << order[i] << ' ';
    }
    cout << '\n';
}

void dfs(int idx, int now, int cnt)
{
    if (cnt == 9)
    {
        //9명 전부 순서를 다 정함
        score = max(score, playGame());
        return;
    }

    if (idx == 4)
    {
        chk[idx] = true;
        order[idx] = 1;
        dfs(idx + 1, now, cnt + 1);
        return;
    }

    for (int i = idx; i <= 9; i++)
    {
        if (chk[i])
            continue;
        chk[i] = 1;
        order[i] = now;
        dfs(i + 1, now + 1, cnt + 1);
        chk[i] = 0;
        order[i] = 0;
    }
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> inning;

    for (int i = 0; i < inning; i++)
    {
        for (int j = 1; j <= 9; j++)
        {
            cin >> inningRes[i][j];
        }
    }

    dfs(1, 2, 0);
    return 0;
}