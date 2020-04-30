#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int n, m, c;
int map[11][11];
int cost[11][11];
bool chk[6];
int value = 0;
typedef pair<int, int> pp;

int max(const int &a, const int &b)
{
    if (a > b)
        return a;
    return b;
}
void calc(vector<int> &arr)
{
    int res = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        if (chk[i])
        {
            res += arr[i] * arr[i];
        }
    }
    value = max(res, value);
}
void makeComb(int idx, int amount, vector<int> &arr)
{
    if (idx == arr.size())
    {
        //m개를 뽑았음
        return;
    }
    for (int i = idx; i < arr.size(); i++)
    {
        if (!chk[i])
        {
            if (amount + arr[i] > c)
                continue;
            chk[i] = true;
            calc(arr);
            makeComb(i + 1, amount + arr[i], arr);
            chk[i] = false;
        }
    }
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    for (int tc = 1; tc <= t; tc++)
    {
        memset(cost, 0, sizeof(cost));

        cin >> n >> m >> c;
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

                value = 0;
                if (m == 1)
                {
                    value = map[i][j] * map[i][j];
                }
                else
                {
                    //m개를 뽑는데, c를 넘지 않는 요소들을 뽑는다.
                    vector<int> arr;
                    memset(chk, 0, sizeof(chk));
                    for (int k = 0; k < m && j + k < n; k++)
                    {
                        arr.push_back(map[i][j + k]);
                    }
                    makeComb(0, 0, arr);
                }

                cost[i][j] = value;
            }
        }
        // for (int i = 0; i < n; i++)
        // {
        //     for (int j = 0; j < n; j++)
        //     {
        //         cout << cost[i][j] << ' ';
        //     }
        //     cout << '\n';
        // }
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int tmp = cost[i][j];
                int tmp2 = 0;
                if (j + m + m < n)
                {
                    int idx = j + m;
                    for (int k = idx; k < n; k++)
                    {
                        tmp2 = max(tmp2, cost[i][k]);
                    }
                }
                if (i != n - 1)
                {
                    for (int k = i + 1; k < n; k++)
                    {
                        for (int l = 0; l < n; l++)
                        {

                            tmp2 = max(tmp2, cost[k][l]);
                        }
                    }
                }
                if (ans < tmp + tmp2)
                {
                    // cout << tmp << " " << tmp2 << '\n';
                    ans = tmp + tmp2;
                }
            }
        }
        // cout << map[idx1.first][idx1.second] << " " << map[idx2.first][idx2.second] << '\n';

        // for (int i = 0; i < m; i++)
        // {
        //     ans += map[idx1.first][idx1.second + i] * map[idx1.first][idx1.second + i];
        //     ans += map[idx2.first][idx2.second + i] * map[idx2.first][idx2.second + i];
        // }
        // int ans = map[idx1.first][idx1.second] * map[idx1.first][idx1.second] + map[idx2.first][idx2.second] * map[idx2.first][idx2.second];

        cout << "#" << tc << " " << ans << '\n';
    }
    return 0;
}