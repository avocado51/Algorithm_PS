#include <iostream>
#include <vector>

using namespace std;
//BOJ 크리보드 https://www.acmicpc.net/problem/11058

int dp[101];
int n;
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

    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        dp[i] = i;
    }

    for (int i = 1; i <= n; i++)
    {
        //그냥 A를 n번 출력하는 것과, 보드에 있는 것을 복사해서 붙여넣는 것
        int buffer = dp[i];
        int cnt = 1;
        for (int j = i; j <= n; j++)
        {
            int tmp = dp[i] + buffer * cnt;
            // cout << j << " " << tmp << '\n';
            dp[j + 3] = max(dp[j + 3], tmp);
            cnt++;
        }
    }
    cout << dp[n] << '\n';

    return 0;
}