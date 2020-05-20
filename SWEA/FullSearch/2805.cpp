#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

//SWEA 농작물 수확하기 [2805](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV7GLXqKAWYDFAXB&)
int map[50][50];

int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;

    cin >> t;

    for (int tc = 1; tc <= t; tc++)
    {

        int ans = 0;

        int n;
        cin >> n;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                char c;

                cin >> c;
                map[i][j] = c - '0';
            }
        }

        int mid = n / 2;
        int cnt = 0;
        for (int i = 0; i <= mid; i++)
        {
            //upside
            ans += map[i][mid];
            int idx = mid;
            int m = cnt;
            while (m--)
            {
                ans += map[i][--idx];
            }
            m = cnt;
            idx = mid;
            while (m--)
            {
                ans += map[i][++idx];
            }
            cnt++;
        }

        cnt--;
        for (int i = mid + 1; i < n; i++)
        {
            //upside
            cnt--;

            ans += map[i][mid];
            int idx = mid;
            int m = cnt;
            while (m--)
            {
                ans += map[i][--idx];
            }
            m = cnt;
            idx = mid;
            while (m--)
            {
                ans += map[i][++idx];
            }
        }
        cout << "#" << tc << " " << ans << '\n';
    }
    return 0;
}