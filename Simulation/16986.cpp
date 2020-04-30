#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// boj 16986 인싸들의 가위바위보 https://www.acmicpc.net/problem/16986
//unsolved

int n, k;
int matrix[10][10];
vector<int> B, C;
int s1 = 0, s2 = 0, s3 = 0;
typedef pair<int, int> pp;
int limit = 0;
int c2 = 0, c3 = 0;
bool visited[10];
void dfs(int idx1, int idx2, int cnt)
{
    if (cnt == limit)
    {
        if (s1 < k)
            cout << 0 << '\n';
        else
            cout << 1 << '\n';
        return;
    }

    if (idx2 == 1)
    {
        for (int i = 0; i < n; i++)
        {
            if (matrix[B[c2]][i] == 0)
            {
                if (!visited[i])
                {
                    visited[i] = true;
                    dfs(idx1, 2, cnt + 1);
                    visited[i] = false;
                }
            }
        }
        c2++;
    }
}
int main()
{

    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k;
    limit = 3 * (k - 1) + 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> matrix[i][j];
        }
    }

    for (int i = 0; i < 20; i++)
    {
        int tmp;
        cin >> tmp;
        B.push_back(tmp);
    }
    for (int i = 0; i < 20; i++)
    {
        int tmp;
        cin >> tmp;
        C.push_back(tmp);
    }

    if (n < k)
    {
        cout << 0 << '\n';
    }
    else
    {
        dfs(0, 1, 0);
    }
    return 0;
}
