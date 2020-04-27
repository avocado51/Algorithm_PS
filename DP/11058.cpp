#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

typedef pair<int, int> pp;
int max(const int &a, const int &b)
{
    if (a > b)
        return a;
    return b;
}
// void bfs()
// {
//     queue<pp> q;
//     q.push(pp(0, 0));
//     int buffer = 0; //버퍼에 들어있는 A의 개수
//     while (!q.empty())
//     {
//         int cnt = q.front().first;
//         int Ass = q.front().second;
//         q.pop();

//         if (cnt >= n)
//         {
//             res = max(res, Ass);
//             continue;
//         }

//         for (int i = 0; i < 4; i++)
//         {
//             switch (i)
//             {
//             case 0:
//                 //A 출력
//                 q.push(pp(cnt + 1, Ass + 1));
//                 break;
//             case 1:
//                 //전체 선택
//                 q.push(pp(cnt + 1, Ass));
//                 break;
//             case 2:
//             {
//                 buffer = Ass;
//                 q.push(pp(cnt + 1, Ass));
//                 break;
//             }
//             case 3:
//                 q.push(pp(cnt + 1, Ass + buffer));
//                 break;
//             default:
//                 break;
//             }
//         }
//         cout << cnt << " " << Ass << '\n';
//     }
// }
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