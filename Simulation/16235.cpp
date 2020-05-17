#include <iostream>
#include <vector>

#include <algorithm>

using namespace std;

int n, m, k;
int A[11][11], nutri[11][11];
vector<int> tree[11][11];

int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1}, dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

bool check()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (tree[i][j].size())
                return false;
        }
    }
    return true;
}
void doWinter()
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            nutri[i][j] += A[i][j];
        }
    }
}
void doFall()
{
    //나무 번식
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (!tree[i][j].size())
            {
                continue;
            }
            else
            {
                vector<int> v = tree[i][j];
                for (int k = 0; k < v.size(); k++)
                {
                    if (v[k] % 5 == 0)
                    {
                        //5의 배수이면 번식
                        for (int d = 0; d < 8; d++)
                        {
                            int nx = i + dx[d];
                            int ny = j + dy[d];

                            if (nx < 1 || nx > n || ny < 1 || ny > n)
                                continue;

                            tree[nx][ny].push_back(1);
                        }
                    }
                }
            }
        }
    }
}

void doSS()
{
    //봄 여름
    //봄에는 나이가 어린 나무부터 양분을 먹는다.

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            int sum = 0; //죽은 나무들의 양분을 저장
            if (!tree[i][j].size())
            {
                continue;
            }
            else
            {
                //나이가 어린 나무부터 양분을 먹는다.
                vector<int> v = tree[i][j];
                vector<int> live;
                sort(v.begin(), v.end());
                // cout << i << " " << j << '\n';

                for (int k = 0; k < v.size(); k++)
                {
                    // cout << v[k] << ' ';
                    if (nutri[i][j] - v[k] >= 0)
                    {
                        nutri[i][j] -= v[k];
                        live.push_back(v[k] + 1);
                    }
                    else
                    {
                        sum += (v[k] / 2);
                    }
                }
                // cout << '\n';

                nutri[i][j] += sum;

                tree[i][j] = live;
            }
        }
    }
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> k;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            cin >> A[i][j];
            nutri[i][j] = 5; //처음 양분은 5만큼 있다.
        }
    }

    int x, y, a;
    for (int i = 0; i < m; i++)
    {
        cin >> x >> y >> a;
        tree[x][y].push_back(a);
    }

    bool flag = false;
    while (k--)
    {
        if (check())
        {
            flag = true;
            break;
        }

        //더 이상 나무가 없으면 끝

        doSS();
        doFall();
        doWinter();
    }

    int ans = 0;
    if (!flag)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                ans += tree[i][j].size();
            }
        }
    }
    cout << ans << '\n';
    return 0;
}