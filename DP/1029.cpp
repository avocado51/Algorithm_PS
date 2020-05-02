#include <iostream>
#include <vector>
using namespace std;
//백준 그림교환 https://www.acmicpc.net/problem/1029
//unsolved

int n;
int dp[16][1 << 16][10]; // //(현재소유자,소유했던사람 상태, maxCost)의 3차원 배열
int value[16][16];

int dfs(int now, int status, int cost)
{
    if (status == ((1 << n) - 1))
        return 0; //모두가 그림을 소유한 적이 있음

    int &ret = dp[now][status][cost];

    if (ret != -1)
        return ret;

    ret = 0;
    for (int i = 0; i < n; i++)
    {
        if (value[now][i] >= cost && ((status & (1 << i)) == 0))
        {
            //팔 수 있는 사람
            ret = max(ret, dfs(i, (status | (1 << i)), value[now][i])) + 1;
        }
    }
    return ret;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    //예술가의 수
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        for (int j = 0; j < n; j++)
        {
            value[i][j] = s[j] - '0'; //그림을 사는 가격을 저장
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < (1 << n); j++)
        {
            for (int k = 0; k <= 9; k++)
                dp[i][j][k] = -1;
        }
    }
    cout << dfs(0, 1, 0) << '\n';
    // for (int i = 1; i < n; i++) {
    //     int cnt = 0;

    //     for (int j = 0; j < n; j++) {
    //         if ((1<<i) & j) cnt++; //현재까지 그림을 산 사람 수를 저장
    //     }
    //     ans = max(ans, cnt);

    //     //그림을 팔때는 현재 그림을 갖고 있는 사람을 찾고, 그 사람이 산 가격에서 가장 최소로 증가된 가격을 제시한 사람에게 팔아야 한다. (최대한 많은 사람에게 팔기 위해선,ㄴ)
    //     for (int j = 0; j < n; j++) {
    //         if ((1<<i) & j) {
    //             //그림을 가지고 있음
    //             int minC = 10, minIdx = 0;
    //             for (int k = 0; k < n; k++) {
    //                 if (!((1<<i)&k) && dp[1<<i][j] <= cost[j][k]) {
    //                     if (minC > cost[j][k]) {
    //                         minC = cost[j][k];
    //                         minIdx = k;
    //                     }
    //                 }
    //             }
    //             dp[i | (1<<minIdx)][j] = minC;

    //         }
    //     }
    //     cout << status << '\n';
    // }

    return 0;
}
