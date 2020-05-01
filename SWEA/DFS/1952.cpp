#include <iostream>
#include <vector>
#include <cstring>
#define INF 987654321
using namespace std;

//수영장

bool chk[13];
int voucher[5];
int dayInMonth[13];
int ans;
int min(const int &a, const int &b)
{
    if (a > b)
        return b;
    return a;
}

void dfs(int idx, int res)
{

    if (idx >= 13)
    {
        //다 돌림
        ans = min(ans, res);
        return;
    }

    chk[idx] = true;
    dfs(idx + 1, res + voucher[1] * dayInMonth[idx]);

    dfs(idx + 1, res + voucher[2]);

    for (int j = idx + 1; j < idx + 3; j++)
    {
        if (j <= 12)
            chk[j] = true;
    }
    dfs(idx + 3, res + voucher[3]);
    for (int j = idx + 1; j < idx + 3; j++)
    {
        if (j <= 12)
            chk[j] = false;
    }

    chk[idx] = false;
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int tc = 1; tc <= t; tc++)
    {
        memset(chk, 0, sizeof(chk));

        for (int i = 1; i <= 4; i++)
            cin >> voucher[i];

        for (int i = 1; i <= 12; i++)
            cin >> dayInMonth[i];
        ans = voucher[4]; //1년 이용권

        dfs(1, 0);
        cout << "#" << tc << " " << ans << '\n';
    }
    return 0;
}