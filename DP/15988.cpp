#include <iostream>
#include <vector>
#define MAXX 1000001
#define MOD 1000000009
using namespace std;
//BOJ 1,2,3 더하기 3 https://www.acmicpc.net/problem/15988
typedef long long ll;
ll dp[MAXX];

int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 4;
    for (int i = 4; i < MAXX; i++)
    {
        //해당 숫자를 만들 수 있는 경우의 수를 미리 구해놓는다. -> 한 번만 계산
        dp[i] += dp[i - 1] % MOD;
        dp[i] += dp[i - 2] % MOD;
        dp[i] += dp[i - 3] % MOD;
    }

    while (t--)
    {
        int n;
        cin >> n;
        cout << dp[n]%MOD << '\n';
    }
    return 0;
}