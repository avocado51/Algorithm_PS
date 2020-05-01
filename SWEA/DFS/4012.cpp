#include <iostream>
#include <vector>

using namespace std;
//요리사 

int n;
int map[17][17];
long long ans = 987654321;
bool visited[17];
typedef long long ll;

int min(const ll &a, const ll &b)
{
    if (a > b)
        return b;
    return a;
}
int calc()
{
    int iA = 0, iB = 0;
    vector<int> teamA(n / 2), teamB(n / 2);

    for (int i = 0; i < n; i++)
    {
        if (visited[i])
        {
            teamA[iA++] = i;
        }
        else
        {
            teamB[iB++] = i;
        }
    }

    //식재료 합의 최소를 구한다.
    long long sumA = 0, sumB = 0;
    for (int i = 0; i < iA - 1; i++)
    {
        for (int j = i + 1; j < iA; j++)
        {
            sumA += map[teamA[i]][teamA[j]] + map[teamA[j]][teamA[i]];
        }
    }
    for (int i = 0; i < iB - 1; i++)
    {
        for (int j = i + 1; j < iB; j++)
        {

            sumB += map[teamB[i]][teamB[j]] + map[teamB[j]][teamB[i]];
        }
    }
    return abs(sumA - sumB);
}
void dfs(int cnt, int idx)
{
    if (cnt == n / 2)
    {
        //정확히 반개로 나눈다.
        ans = min(ans, calc());
        return;
    }

    for (int i = idx; i < n; i++)
    {
        if (!visited[i])
        {
            visited[i] = true;
            dfs(cnt + 1, i + 1);
            visited[i] = false;
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
        ans = 987654321;
        cin >> n;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> map[i][j];
            }
        }

        dfs(0, 0);
        cout << "#" << tc << " " << ans << '\n';
    }
    return 0;
}