#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
//SWEA 활주로 건설 

int n, X;
int map[42][21];
int ans;
int height[7]; //지형의 높이는 6이하
bool chk[21];
int abs(int a, int b)
{
    if (a > b)
        return a - b;
    return b - a;
}
bool check(int x)
{

    memset(height, 0, sizeof(height));
    memset(chk, 0, sizeof(chk));
    int now = map[x][0];
    height[now] = 1;

    for (int i = 1; i < n; i++)
    {
        int next = map[x][i]; //다음 높이

        if (now == next)
        {
            //지나간다.
            height[now]++;
            now = next;
        }
        else if (abs(now, next) == 1)
        {
            //now가 큰 경우
            if (now > next)
            {
                //앞으로 next가 x만큼 이어져야 한다.

                for (int j = i; j < i + X && j < n; j++)
                {
                    if (map[x][j] == next)
                    {
                        height[next]++;
                    }
                }
                if (height[next] >= X)
                {
                    i += X - 1;
                    height[now] = 0;
                    height[next] -= X;
                    now = next;
                }
                else
                    return false;
            }

            //now가 작은 경우
            else
            {
                if (height[now] >= X)
                {
                    height[now] = 0;
                    height[next] = 1;
                    now = next;
                }
                else
                    return false;
            }
        }
        else
        {
            return false;
        }
    }
    return true;
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int tc = 1; tc <= t; tc++)
    {
        cin >> n >> X;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> map[i][j];
            }
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                map[n + i][j] = map[j][i];
            }
        }

        ans = 0;

        for (int i = 0; i < n + n; i++)
        {

            if (check(i))
            {
                //가능한 활주로
                // cout << i << '\n';
                ans++;
            }
        }
        cout << "#" << tc << " " << ans << '\n';
    }
    return 0;
}