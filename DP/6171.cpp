#include <iostream>
#include <vector>
#include <climits>
#define MAXX 50001
using namespace std;

//BOJ https://www.acmicpc.net/problem/6171
//unsolved

int n;
int w[MAXX], h[MAXX];
int dp[MAXX];
typedef long long ll;
ll ans = LLONG_MAX;
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> w[i] >> h[i];
    }

    dp[0] = w[0] * h[0];
    int maxh = h[0];
    int maxw = w[0];
    for (int i = 1; i < n; i++)
    {
    }

    return 0;
}