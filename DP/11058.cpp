#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
//BOJ 크리보드 https://www.acmicpc.net/problem/11058

typedef pair<int, int> pp;
int max(const int &a, const int &b)
{
    if (a > b)
        return a;
    return b;
}

int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    long long dp[101] = {0};

    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 3;
    dp[4] = 4;
    dp[5] = 5;
    dp[6] = 6;

    for (int i = 7; i <= n; i++)
    {
        for (int j = 1; j <= i - 3; j++)
        {
            dp[i] = max(dp[i], dp[i - (j + 2)] * (j + 1));
            cout << i - (j + 2) << " " << dp[i - (j + 2)] << " " << j + 1 << '\n';
        }
        dp[i] = max(dp[i], dp[i - 1] + 1);
    }
    cout << dp[n] << '\n';
    return 0;
}